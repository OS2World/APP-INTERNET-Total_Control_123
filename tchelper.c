// tc123 helper applet by Death Syndrome, with help from dink...
// compile using gcc -Zcrtdll -s -o tc123helper.exe tc123helper.c
#define INCL_DOSFILEMGR       /* DOS File Manager values */
#define INCL_DOSNMPIPES       /* DOS Named Pipes values */
#define INCL_DOSSEMAPHORES    /* DOS Semaphore values */
#define INCL_DOSERRORS        /* DOS Error values */
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char tc_version[] = "1.0.1-RELEASE";                 // Program version

struct rawinf {
    char fname[256], songinfo[256];
    char track[32], artist[32], album[32], comment[32];
    char year[6], playtime[10], timenow[10], genre[25];
};

int main(int argc, char *argv[]) {

    char     outmessage[1024] = "";  // Write buffer
    char     inmessage[1024]  = "";  // Read buffer
    char     tempbuf1[1024]   = "";  // Temp area for building output
    char     tempbuf2[1024]   = "";  // Temp area for building output
    char     pipename[10]     = "";  // name of pipe
    struct   rawinf *inf      = (struct rawinf *) inmessage;
    
    if (argv[1]!=NULL) {
        if (!strcmp(argv[1],"rawinfo")) strcpy(outmessage,"*rawinfo\n\0");
        if (!strcmp(argv[1],"songinfo")) strcpy(outmessage,"*status info\n\0");
        if (!strcmp(argv[1],"file")) strcpy(outmessage,"*status file\n\0");
        if (!strcmp(argv[1],"tag")) strcpy(outmessage,"*status tag\n\0");
        if (!strcmp(argv[1],"-v")) { showver(); return(0); }
        if (!strcmp(argv[1],"-h") || !strcmp(argv[1],"-?")) {
            showhelp();
            return(0);
        }
    }

    if (!strlen(outmessage)) strcpy(outmessage,"*status tag\n\0");

    // printf("%s\n", argv[3]);

    if (argc>=3) {
        if (!strcmp(argv[2], "zmp3")) {
            strcpy(pipename, "\\PIPE\\ZMP3");
            if (!strcmp(argv[1], "tag")) strcpy (outmessage,"*rawinfo\n\0");
        } else strcpy(pipename, "\\PIPE\\PM123");
    } else strcpy(pipename, "\\PIPE\\PM123");

    if (!strcmp(outmessage,"*rawinfo\n")) {
        if (getpipeinfo(pipename,outmessage,inmessage)!=1) {
            if (!strcmp(argv[1],"tag")) {
                if (!strlen(inf->track)) {
                    sprintf(tempbuf1, "Z!: %s%s%s%s", inf->fname," (",inf->playtime,") \n\0");
                    strcpy(inmessage, tempbuf1);
                    printf("%s", inmessage);
                } else {
		    // printf("%s", boolean ? string1 : string2);
                    sprintf(tempbuf1, "Z!: %s%s%s ", strlen(inf->artist) ? inf->artist : "", strlen(inf->artist) ? ": " : "", inf->track);
                    sprintf(tempbuf2, "%s(%s", tempbuf1, strlen(inf->album) ? inf->album : "");
                    sprintf(tempbuf1, "%s%s", tempbuf2, (strlen(inf->album) && strlen(inf->year)) ? ", " : "");
                    sprintf(tempbuf2, "%s%s", tempbuf1, strcmp(inf->year, "????") ? inf->year : "");
                    sprintf(tempbuf1, "%s%s", tempbuf2, strcmp(inf->year, "????") ? ", " : "");
                    sprintf(tempbuf2, "%s%s)\n\0", tempbuf1, inf->playtime);
                    strcpy(inmessage, tempbuf2);
                    printf("%s", inmessage);
                    // printf("Z!: %s: %s (%s, %s, %s)\n", inf->artist, inf->track, inf->album, inf->year, inf->playtime);
                }
            } else {
                printf("filename [%s]\n", inf->fname);
                printf("songinfo [%s]\n", inf->songinfo);
                printf("track    [%s]\n", inf->track);
                printf("artist   [%s]\n", inf->artist);
                printf("album    [%s]\n", inf->album);
                printf("comment  [%s]\n", inf->comment);
                printf("year     [%s]\n", inf->year);
                printf("playtime [%s]\n", inf->playtime);
                printf("timenow  [%s]\n", inf->timenow);
                printf("genre    [%s]\n", inf->genre);
            }
        }
    } else {
        if (getpipeinfo(pipename,outmessage,inmessage)==1) {
            strcpy(inmessage,"0");
            strcpy(outmessage,"*status file\n\0");
            getpipeinfo(pipename,outmessage,inmessage);
        }
        printf("%s\n", inmessage);
    }

    return NO_ERROR;
}

int showver() {
    printf("tc123helper applet for OS/2 version %s\n",tc_version);
    printf("'May the farce be with you, momo!'\n");
}

int showhelp() {
    showver();

    printf("-h or -? :  This help screen.\n");
    printf("songinfo :  Statistics on currently playing song.\n");
    printf("file     :  Current filename being played.\n");
    printf("tag      :  Tag info for current mp3.. gives file if no tag.\n");
    printf("-v       :  Gives version number of this tc123 helper applet.\n");
}

int getpipeinfo(char *pipe, char *outmessage, char *inmessage) {
    APIRET   rc                     = NO_ERROR;   /* Return code */
    HFILE    PipeHandle             = NULLHANDLE; /* Pipe handle */
    ULONG    bytes                  = 0;
    ULONG    Action                 = 0;
    int      i;

    // open the player pipe, try 10 times before giving up!
    for(i=1;i<=10;i++){
        rc = DosOpen(pipe, &PipeHandle, &Action, 0, 0, FILE_OPEN,
                     OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYREADWRITE |
                     OPEN_FLAGS_FAIL_ON_ERROR, NULL);
        if (rc == NO_ERROR) break; else DosSleep(100);
    }

    if (rc != NO_ERROR) {
       printf("DosOpen error: error code = %u\n", rc);
       return 1;
    }

    rc = DosWrite(PipeHandle, outmessage, strlen(outmessage), &bytes);
    if (rc != NO_ERROR) {
       printf("DosWrite error: error code = %u\n", rc);
       return 1;
    }

    rc = DosRead(PipeHandle, inmessage, 1024, &bytes);
    if (rc != NO_ERROR) {
       printf("DosRead error: error code = %u\n", rc);
       return 1;
    }

    rc = DosClose(PipeHandle);
    return bytes;
}
