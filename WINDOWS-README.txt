November 20, 2023

SGV Zippy Clipper Linux Video Media Editor
SGR Player Media Player

Microsoft Windows 11 with WSL2 Notes

Kevin C. O'Kane 
kc.okane@gmail.com
https://www.cs.uni.edu/~okane 
http://threadsafebooks.com/

Notes

The code now works with Windows 11 with WSL 2 / Ubuntu installed subject to availability of
video libraries (depending on your video card and its support under Windows 11).

Please install the latest version of Ubuntu (22.04 as of this writing). Older versions have
different libraries and may not work.

The Windows WSL2 GUI for Linux is, at present, not completely stable. This can result in:

1.	Distortion of the Linux display window.

	Occassionally, for no known reason, the Linux window will exhibit diagonal distortions
	similar to an old NTSC TV with horizontal sweep errors. Often rebooting Linux will
	correct this problem. Close all Linux windows and wait at least 30 seconds to reboot.

2.	Audio connect failures.

	The audio interface between Linux and Windows is limited with regard to the maximum
	bitrate. At present, audio is limited to a 128k bitrate. Attempting to play audio
	with a higher rate will result in failure to play.

	The audio connection between Linux and Windows is fragile. Any number of situations 
	can cause it to crash. 	f the audio does not play, re-boot Linux by closing all
	Linux windows and wait at least 30 seconds before opening a Linux window again.

3.	Lockups and freezing of the GUI and Audio Processor.

	Reboot WSL2 (turn off all WSL2 windows and wait at least 30 seconds before restarting any).
	Hopefully, these issues will resolve with time.

Due to audio timing issues in libvlc 3 and WSL 2, audio does not play correctly with libvlc 3.
Libvlc is the current stable release used in most Linux systems.

This is corrected in libvlc 4. However, libvlc 4, at this writing, does not have a stable release.
You can use the daily unstable releases, however, be aware that a daily update may cause
problems. They probably won't but you have been warned.

To use libvlc 4, do the following to replace version 3 with version 4:

	sudo add-apt-repository ppa:videolan/master-daily
	sudo apt update
	sudo apt upgrade

This will update to the daily libvlc 4 channel. Hopefully, a stable version 4 will be
available soon.

The script file wsl-libvlc-4-install.script contains this code. It must be run as root.

Some ffmpeg filters are unavailable in the WSL2 Ubuntu distro at this time. Consequently,
some options may fail.


