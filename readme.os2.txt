Total Control 123(tc123) for OS/2, version 1.0.1-RELEASE.
Written by Death Syndrome, with assitance from dink.
This software is released under the GNU General Public License,
version 2 or newer.  See COPYING for more details.
This application does REQUIRE the emx runtime 0.9c or newer to function.

***CHANGES:
1.0.1-RELEASE 04-03-99: 1.01-CURRENT with different version string.
1.01-CURRENT  03-18-99: This version is released to provide support for
                            changes in z! v2.4b9.2 and later's rawinfo
                            structure.

Acknowledgements:
Many thanks go to dink for assistance on this code.
OS/2 is copyright IBM Corporation, and is a registered trademark.
z! is Copyright 1997-1999 dink.
PM123 is copyright 1997-1998 Taneli Lepp„ / Samuel Audet.
Many thanks to Eberhard Mattes for making emx!  Who needs a commercial
compiler?  I've got gcc!!

Background:
tc123 is an interface for named-pipe enabled mp3 players to your ircII
compatible client.  This interface has been tested with OpenChat/2,
ircII/OS2, PMBichx-75p1, and a beta port of ircII-EPIC3.004 for OS/2.
Hopefully, bugs have been shaken out of this release, but see the end
of COPYING for warranty details.  This application is designed to
interface primarily with dink's z! MP3 player, version 2.4 and later.
It also happens to function under Taneli's PM123, but is not optimized
for such.  The aim of this application is to be able to totally control
the MP3 player entirely from the console of the irc client.  Feel free
to submit bug reports to deathsyn@yahoo.com.

Use:
The easiest way to get started with tc123, unpacking the distribution
package into the directory in which your ircII-compatible client resides.
Next, if you're running a mp3 player other than z!(such as pm123), modify
tc123.irc(bx) and change the value in the brackets of the player variable
to the name of the named pipe used by your player.  PM123's pipe is pm123.
Then, run your irc client in the normal manner.  Once the client is up,
type the following into the console:

/load tc123.irc

(BitchX users, replace "irc" with "bx".  Currently, the only difference
is the modification of the BX version string.  Future BX specific
enhancements should occur, though.)

After doing the above, you should see something like this:

[tc123] Total Control 123 is loaded.

After that, you can now manipulate the player from your irc client.  With
the player running, try the following:

/np

This should check what the player is playing, and broadcast it to the
current channel, as well as on the console.

Other status type commands work in a similar manner.  These are /songinfo,
/file, and /rawinfo.  Rawinfo doesn't broadcast to the channel, as its
information is verbose enough to annoy many others.  /lnp, /lsonginfo, and
/lfile are the same as their 'l'-less brethern, except they only give
their information to the 'l'ocal console.

Now, for the control commands:

/play  -  tells the player to start playing the current playlist/file.
/stop  -  tells player to stop playing the playlist.
/pause -  pause play of current file at current posititon.  Do it again to
          resume play.  PM123 will die on this command, as implemented.
          If you don't like this, switch to z!, or write replacement code.
/next  -  Move to next file in playlist.
/prev  -  Move to previous file in the playlist.
/shuffle -  Shuffles currently playing list.  Not sure if this works in z!
/tcquit  -  Tells the player to diediedie.
/tcver  -  Just a bit of self-absorbed pride.  Shows your friends how lame
           you/they are.

That's it for now.  I plan on adding new stuff based upon feedback I get
from this release, as well as whatever else I find I need.  This code is
basically the same as the last .8bx edition, for those who wonder.  BTW,
tchelper.exe has many other uses.  Run tchelper -? for information.  A few
applications for this could be for email sigs, wacky shell scripts, etc.

Greets to #os2*(you know who you are), and specifically to dink, SpaceRat,
|tSS|, and sehh, who were instrumental in making this thing as bug-free as
it is.
