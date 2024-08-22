------------------------------------------------------------------------------

August 21, 2024

------------------------------------------------------------------------------

Linux Media Editor

Copyright (C) 2018, 2019, 2021, 2022, 2023, 2024 by Kevin C. O'Kane

Kevin C. O'Kane 
kc.okane@gmail.com
https://www.cs.uni.edu/~okane 
http://threadsafebooks.com/

------------------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
------------------------------------------------------------------------------

Acknowledgments

Run time routines from the VLC run time library are used for audio services.
No VLC source code is used.

ffmpeg commands are used in this project but ffmpeg API is not.

Zippy. Zippy is a puppy. His accomplice is Mabel. They are very good at
cutting things up. If you hit the right button in the right way, you will
see them waiting to shred your video, or socks, whatever.

Check out the latest video currently at:

    https://youtu.be/fZIfAb0x9io

NOTE: If you modify code in the *.in files, you MUST run configure.

Installation

--------------------------------------------------------------------------
Be sure to ee note below on 'configure' for Windows 11 if your are
using the Windows 11 version. The Windows version requires installation
of libvlc 4 or it will not work. The default is version 3.
--------------------------------------------------------------------------

The Linux main module is Zippy.c with additional code contained in the
ZippyEditor/sgv-code/common directory. 

To compile and run in Linux:

	1. Depending on the target Linux system, run the correct Install
	   script.

		./DebInstall.script (for Debian based systems such as Mint and Ubuntu)
		./ArchInstall.script (for Arch based systems such as Manjaro)
		./FedInstall.script (for Fedora/Red Hat based systems)

	   These scripts MUST be run as root. They install standard system software
	   that is needed for compilation.

	2. Depending on your target system, run ./configure:

		./configure all --with-system=debian (the default)

			Note: if you are compiling on a Debian based system,
			      you do not need to specify --with-system=debian
			      WSL2 compile assumes Debian/Ubuntu.

		./configure --with-system=arch
		./configure --with-system=fedora

	3. Compile the system:

		make all -B

	   Optional - if your machine has 4 processors:

		make all -B -j 4

	   Alternatively

		make all -B -j 4

	4. Run the system:

		./Zippy-bin


The graphics code is based on GTK 3 (3.24 at this point in time).

This is an ongoing project and there will be changes, corrections and additions
as time goes by.

------------------------------------------------------------------------------

Notes

----

The Zippy directory should be placed on your Desktop. Videos created by Zippy
will be placed in the Zippy/videos directory. When you click the "Re-Load Clips"
button, the contents of the Zippy/videos directory will appear in the entry
boxes.

----

It is useful to start Zippy-bin from a terminal window but not required. You 
may create a desktop launcher instead. The advantage of starting from a terminal
window is that Zippy generates a lot of messages. Most of these are just informational
but if something goes wrong, these messages should help to correct the problem.
These messages are lost if Zippy is started from a desktop launcher.

----

As mentioned, the "Re-Load Clips" button scans the Zippy/videos directory and displays
the results in date order (newest first).

If you drag a video to an entry box from an explorer window, the video is not copied
to Zippy/videos. Only a reference is stored in the file Zippy/videos/program.lst. If
you clicj the "Re-Load Clips" button, the reference will be lost. However, if you
drag a reference to Zippy, quit Zippy, and re-start Zippy, the reference will still
be present. It will only be deleted when you click the "Re-Load Clips" button. 

----

When creating still images from a video clip, the still images will all be or type 
PNG and placed in the videos/stills sub-directory. Each still image will be of the 
same dimensions as the video and wil be named in the form: "image-xxx.png" where 
"xxx" will be 001, 002, 003, ...

When creating images, you need to specify how many images to create per minute of
video. The default is 60 images or frames per minute or, in other words, one frame
per second. Other popular settings:

	10	1 frame every 6 seconds
	20	1 frame every 3 seconds
	30	1 frame every 2 seconds
	60	1 frame every second
	120	2 frames every second
	180	3 frames every second
	240	4 frames per second
	300	5 frames per second
	...
	1200	20 frames per second
	1440	24 frames per second
	1500	25 frames per second
	3600	30 frames per second

----

Previews appear in an independent ffplay window. The contents of this window
are the output of the ffmpeg command being previewed. The ffmpeg command is run 
as a separate process but it's output is re-directed to an ffplay window rather
than a file. The ffplay window displays images as they are received from ffmpeg.
This means that (1) there will be a lag time until the ffplay window appears due
to initial image buffering, and (2) the images in the ffplay window may be jerky
or contain pauses depending on how fast the ffmpeg command in running and the
speed of your machine. When you kill the ffplay window, there will be a delay
until the ffmpeg tast also quits. The Halt ffmpeg button is the quickest way to
end a preview. 

----

Many of the features work on one or more selected videos or audios. For example,
if you want to convert several videos to a standard size and format, the Video
Adjust / Standardized button will convert all selected videos to the format selected.

Some operations only apply to the currently playing video

----

Only one operation at a time is permittd. So, if you want to convert 5 videos to
a standard format and THEN convert them to monochome, the operations must be
done separately.

----

Some operations only operate on one video or audio, usually the one which is 
playing. The Create Clip button, for example, creates a clip from the current 
video using the current start / end and crop settings. Only one video is created
at a time. 

----

If a video is paused and in sigle frame display, placing the mouse over the video,
while holding down the left button, and dragging the cursor to right and down, 
will highlight an area. When the mouse button is released, the co-ordinates will
be loaded into the crop settings and the still frame will adjust accordingly.

----

The meters display the sound levels being received by the PulseAudio
system. If you have muted or reduced the volume of PulseAudio, the graphs will be
reduced by a corresponding amount. The graphs accurately reflect video sound
levels only when PulseAudio playback is set to 100%.

----

You should only join videos of the same file type (.mp4, .mkv, etc.), geometry,
and timing characteristics. Joining or otherwise mixing video clips with different
file types, geometry or timing will usually fail.

The "Standardize" button can be used to convert one or more clips to a standard
format and file type.

It can occur that even if your original video is of the default file type, extracted clips
from it may not be compatible with the original. This is because the extracted clips
may be of different geometry or use a default set of timing  prarmeters that may differ
from the original.

----

Zippy is compiled for a default file type, normally mp4. Files created by the
editor will be of this type and all files edited by the editor should be of this
type. Use the "Standardize" button to convert one or more files from another
format to the default format.

You may configure the editor for other default types by adding an option to 
the configure command giving the default type:

	configure --with-fmt=mkv && make -B

The above configures the editor to use MKV files as the default.

----

When you join two videos with a transition, the resulting video will be shorter in
time than the sum of the times of the constituent videos. This is because during the
transitions, both videos are playing and thus overlapping.

----

Fedora and Ubuntu may raise a popup to ask if you want to Force Kill Zippy-bin 
when Zippy-bin executes ffmpeg commands. Ignore this. 

----

To run, execute Zippy-bin from the compilation directory. 

----

Place videos or copies of videos you will be working with in the 'videos'
sub-directory of the Zippy directory.

Any videos or still image snapshots created by the editor will be placed in the 
sub-drectory 'videos' and will be named with an appended ascending integer.
Output videos are in MP4 format and still images are in PNG format.

----

If you modify the code, modify the *.in versions and be SURE to run configure
before you compile. The program configure converts the *.in files to *.c
files and it is the C files that are actually compiled. Any changes you make to
a C file directly will be lost.

----

Cell Phone Videos: 

Cell phone videos have a rotation meta data parameter.

Rotation 0 is called 'left' and this a a wide screen format where the top of the
phone is in your left hand when recording.

Rotation 90 is called 'normal' and this is narrow screen format where the top of
the phone is up.

Rotation 180 is called 'right' and this is wide screen where the top of the
phone is in your right hand.

Rotation 270 is called 'upside down' and is narrow format with the top of the
phone down when recording.

Rotation 0 is fully supported. You may play and create clips with rotation 90
only. Cropping and other features are restricted in rotation 90.

The other rotations may be played but are mostly unsupported.

You may convert rotations 90, 180 and 270 to a supported format with the 
'Standardize' tile.

----

Video Operations

When you have clicked a button to initiate a video editing operation, please wait until
the operation has completed. 

DO NOT ATTEMPT ANY OTHER ACTIONS DURING VIDEO PROCESSING.

Video processing takes a lot of time. Randomly clicking other buttons will not increase
the speed and will probably result in the video being trashed.

----

Video processing is done by ffmpeg commands that are constructed based on your 
selections. Copies of the ffmpeg commands are output to the originating console.
There is a button to abort an on-going ffmpeg operation. If you do so, the
video clip being created will be trashed.

----

Hot Keys and Button Equivalent

Home             move to start of video clip (Go To Clip Start)
End              move to end of video clip  (Go To Clip End)
Left Arrow       move back 0.5 seconds (Back)
Right Arrow      move forward 0.5 seconds (Forward)
Down Arrow       decrease playback speed
Up Arrow         increase playback speed
Ctrl-Left Arrow  move back 2 seconds (Back)
Alt-Left Arrow   move back 3 seconds (Back)
Ctrl-Right Arrow move forward 2 seconds (Forward)
Alt-Right Arrow  move forward 3 seconds (Forward)
Space Bar        toggle Pause (Frame By Framwe Mode)
Escape           reset/restart player (Restart)
d                scroll page of media entries down (Page Down)
e                mark clip end (Mark End)
f                halt all ffmpeg actions (Halt ffmpeg)
h                halt player and release video (Halt Player)
p                play clip from start (Play From Clip Start)
s                mark clip start (Mark Start)
u                scroll page of media entries up (Page UP)

----

CODECS

Most video codecs work but some, rarely, don't.

Some video drivers on Linux do not have software required by libvlc to decode video.
The xserver-xorg-video-nouveau driver does. If you experience problems, you might
try reverting to an earlier hardware driver (nvidia 390 works for me but nvidia 470
does not) or switch to xserver-xorg-video-nouveau. 

Ordinarily, in the VLC app, this can be controlled by the --avcodec-hw=none parameter 
but the libvlc API forbids the developer to do this for reasons that are not adequately 
explained. If you have this problem, rendered video will not play in the editor but 
will play with other video players such as mpv or VLC with the aforementioned parameter.

Ubuntu appears to have dropped support some vdpau wrappers. There are Debian versions here:

http://ftp.debian.org/debian/pool/main/v/vdpau-video/

that may help (be certain to select the correct file. The one you want is probably the
latest for your machine which is likely to be an amd64 architecture.

That said, you can safely ignore error messages of the form:

libva info: VA-API version 1.14.0
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)

These are harmless.

----

Screen Capture

The screen capture option will capture your screen and default audio. For the first few
seconds the audio may be choppy as ffmpeg starts the stream. Also, when you finish, the
capture will continue for a few seconds as the stream shuts down. The resulting file will
be screen-capture.mp4 in the Zippy/videos directory. You will need to rescan the directory
to see it. Screen capture does not work in WSL2 due to how Microsoft simulates the window.

----

How-To Videos

The How-To videos are on a server (https://threadsafebooks.com) in order to reduce the size
of the distro. Internet access is required to view them. The videos will be updated and added
to as time goes by. The list of accessible videos is in the file program.lst in the
Zippy/howto directory.

In general, videos from the Internet can be edited if you have read acces and a URL that 
points to a file whose video format is compatible with the VLC librarty. This does not
mean you can edit a YouTube video with just a YouTube URL. YouTube URLS do not point
to files.

----

Media Entry Box Population

The contents of the media entry boxes are normally derived from the Zippy/videos/program.lst file. 
This file is written when Zippy-bin is exited. Thie entry box contents can be updated by clicking
the Re-Scan Directory button.

When you rescan a directory, the order of the entries will be by date (newest first). You may sort the 
entries by date or alpha by means of the Alpha Asc, Alpha Dsc, Data Asc and Date Dsc buttons.

The order of the entries is only changed if you click on of the sorting buttons or rescan.

If you migrate to another directory, a re-scan will populate the entry boxes with the contents
of the directory selected. 

----

Changing Directories

If you switch directory using the directory chooser button (upper right of entry boxes), the
prior entry box list will be stored to program.lst in the old directory.

Adding Entries

You may drag a file to an entry box. The reference to the file will be coppied, not the file. 
When you delete a file whose entry was dragged and dropped, only the reference to the file
is deleted, not the original file.

If you add an entry by means of the file dialog button (above and to the left of the entry panel),
a copy of the file will be made in the current directory. If you delete this entry, the copy will
be deleted.

------------------------------------------------------------------------------

Windows WSL2

The code now works with Windows 11 with WSL 2 / Ubuntu installed subject to availability of
video libraries (depending on your video card and its support under Windows 11).

Please install the latest version of Ubuntu (22.04 as of this writing). Older versions have
different libraries and may not work.

Due to audio timing issues in libvlc 3 and WSL 2, audio does not play correctly with libvlc 3.
This is corrected in libvlc 4. However, libvlc 4, at this writing, does not have a stable release.
You can use the daily unstable releases, however, be aware that a daily update may cause
problems. They probably won't but you have been warned.

To use libvlc 4, do the following:

	sudo add-apt-repository ppa:videolan/master-daily
	sudo apt update
	sudo apt upgrade

This will update to the daily libvlc 4 channel. Hopefully, a stable version 4 will be
available soon.

The Linux versions will continue to use libvlc 3 until a stable version 4 is in the distro
channels.

Some ffmpeg filters are unavailable in the WSL2 Ubuntu distro at this time. Consequently,
some options may fail.

The maximum audio rates in Windows version are lower than Linux. If the higher rates are used,
the audio will not play. The configure script detects if WSL is present ans sets the audio 
rates lower.

Screen capture does not work in WSL2 due to how Microsoft simulates the window.

---------------------------------------

To limit cpu usage in Linux to keep from over heating. Numbers are cpu core nbrs.

taskset -c 0,1,2,3 command


