echo =================================================================
echo "Zippy Configuration Module Feb 21, 2023"
echo
echo "Copyright (c) 2013, 2015, 2022, 2023 Kevin C. O'Kane, All Rights Reserved"
echo "GNU GPL License Applies"
echo `date`
echo =================================================================
echo "Configure Line Options: [default]"
echo "--with-sqlite        Use Sqlite for the database"
echo "--with-opt=level       Optimization"
echo =================================================================

# August 11, 2024

# /usr/lib/pkgconfig

AC_INIT(Zippy,2.0,okane@uni.edu)

AC_COPYRIGHT([Kevin O'Kane])
AC_REVISION([2.0])

config_date=`date`

echo
echo "--with-system=o      Operating system to target. Options:"
echo "                     fedora"
echo "                     debian (default) - includes Ubuntu, Mint, Debian, etc."
echo "                     arch - includes Manjaro"
echo
echo "--with-fps=int       Default frames per second (25)"

AC_ARG_WITH(system,
   [ --with-opt opt level],
   [ sys="$withval" ],
   [ sys="debian"])

if test "$sys" = "debian"
	then
	echo "System = $sys"
elif test "$sys" = "fedora"
	then
	echo "System = $sys"
elif test "$sys" = "arch"
	then
	echo "System = $sys"
else
	echo "System not recognized"
	exit
fi

if test "$sys" = "debian"
	then
	echo "Debian, Linux Mint or Ubuntu"
	system="#define DEBIAN"
	avformat_include="x86_64-linux-gnu/"
	fedora_avformat=""
	gtk_pkg="\`pkg-config --cflags --libs gtk+-3.0\`"
        gtkmm_pkg="\`pkg-config --cflags --libs gtkmm-3.0\`"
	glib_lib_pkg="\`pkg-config --cflags --libs glibmm-2.4 giomm-2.4\`"
	cairo_pkg="\`pkg-config --cflags --libs cairo\`"
	pango_pkg="\`pkg-config --cflags --libs pango\`"
	atk_pkg="\`pkg-config --cflags --libs atk\`"
	gdkpixbuf_pkg="\`pkg-config --cflags --libs gdk-pixbuf-2.0\`"
	terminal="gnome-terminal --title \\\"Zippy ffmpeg Progress Window\\\" --geometry=120x10+450+200 --hide-menubar --name=zippyTerm --wait -- "
        terminalX="gnome-terminal --title \\\"Zippy ffmpeg Progress Window\\\" --geometry=120x10+150+70 --hide-menubar --name=zippyTerm -- "


elif test "$sys" = "fedora"
	then
	echo "Fedora"
	system="#define FEDORA"
	avformat_include="ffmpeg/"
	fedora_avformat="-I /usr/include/ffmpeg"
	gtk_pkg="\`pkg-config --cflags --libs gtk+-3.0\`"
	glib_lib_pkg="\`pkg-config --cflags --libs glib-2.0\`"
	atk_pkg="\`pkg-config --cflags --libs atk\`"
	cairo_pkg="\`pkg-config --cflags --libs cairo\`"
	gdkpixbuf_pkg="\`pkg-config --cflags --libs gdk-pixbuf-2.0\`"
        gtkmm_pkg="\`pkg-config --cflags --libs gtkmm-3.0\`"
	pango_pkg="\`pkg-config --cflags --libs pango\`"
	terminal=""

elif test "$sys" == "arch"
	then
	echo "arch"
	system="#define ARCH"
	avformat_include=""
	fedora_avformat="-I /usr/include/ffmpeg"
	gtk_pkg="\`pkg-config --cflags --libs gtk+-3.0\`"
	glib_lib_pkg="\`pkg-config --cflags --libs glib-2.0\`"
	atk_pkg="\`pkg-config --cflags --libs atk\`"
	cairo_pkg="\`pkg-config --cflags --libs cairo\`"
	gdkpixbuf_pkg="\`pkg-config --cflags --libs gdk-pixbuf-2.0\`"
        gtkmm_pkg="\`pkg-config --cflags --libs gtkmm-3.0\`"
	pango_pkg="\`pkg-config --cflags --libs pango\`"
	terminal=""

else
	echo "No system detected"
	echo 
	exit
	fi

#	check for Windows WSL version of Linux

echo `grep WSL /proc/version`

if test "`grep WSL /proc/version`" = ""
then 

#	regular Linux (not Windows WSL based) uses a higher bit rate.
#	the following can establishe that bit rate.

	wsl2=0 
	LOSS=" -c:a libopus -b:a 128k -c:v libx264 -preset veryslow -crf 20 "
else 

#	sets up a lower audio bit rate for Windows WSL Linux
#	Windows WSL is not capable of high bit rates at this time

	wsl2=1
   	LOSS=" -c:a libopus -b:a 64k -c:v libx264 -preset veryslow -crf 20 "
fi

AC_ARG_WITH(fps,
   [ --with-opt opt level],
   [ FPS="$withval" ],
   [ FPS="25"])

AC_ARG_WITH(audio-sample-rate,
   [ --with-opt opt level],
   [ AUD="$withval" ],
   [ AUD="44100"])

AC_ARG_WITH(fmt,
   [ --with-opt opt level],
   [ FMT="$withval" ],
   [ FMT="mp4"])

AC_CONFIG_HEADERS([include/zippy/config.h])

AC_PROG_CC([gcc])

if test $CC != "gcc" 
	then
        AC_MSG_ERROR([Missing gcc/g++ compiler])
	fi

INCLUDEDIR=""

AC_CHECK_HEADER([readline/readline.h],[AC_DEFINE(HAVE_UNISTD_H,YES)],[AC_MSG_ERROR([Missing readline.h headers])])

AC_CHECK_HEADER([unistd.h],[AC_DEFINE(HAVE_UNISTD_H,YES)],[AC_MSG_ERROR([Missing unistd.h headers])])

if test "$prefix" = "NONE"; then
	# where to place the software if prefix= not specified
	prefix="$HOME/Zippy"
	fi

vlc4="0"
AC_CHECK_LIB(vlc,libvlc_media_player_stop_async,[AC_DEFINE([HAVE_vlc4]) vlc4="1"],[vlc4="0"])

if test "`grep WSL /proc/version`" != "";
then 

	if test "$vlc4" == "0"
	then
		echo "WSL found but VLC Version 4 is missing"
		AC_MSG_ERROR([Missing VLC 4])
	else
		echo "WSL found; VLC 4 found"
	fi

fi

AC_SUBST(mathLink)
AC_SUBST(mathLink)
AC_SUBST(avformat_include)
AC_SUBST(config_date)
AC_SUBST(fedora_avformat)
AC_SUBST(cairo_pkg)
AC_SUBST(atk_pkg)
AC_SUBST(gtk_pkg)
AC_SUBST(gdkpixbuf_pkg)
AC_SUBST(glib_lib_pkg)
AC_SUBST(gtkmm_pkg)
AC_SUBST(gtkmm_link)
AC_SUBST(pango_pkg)
AC_SUBST(FPS)
AC_SUBST(LOSS)
AC_SUBST(FMT)
AC_SUBST(AUD)
AC_SUBST(terminal)
AC_SUBST(terminalX)
AC_SUBST(wsl2)
AC_SUBST(vlc4)
AC_SUBST(system)

AC_CONFIG_FILES([Zippy.c])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([sgv-code/common/common-compiled-code.c])
AC_CONFIG_FILES([sgv-code/common/common-externs.h])
AC_CONFIG_FILES([sgv-code/common/common-fcn-headers.h])
AC_CONFIG_FILES([sgv-code/common/common-objects.h])
AC_CONFIG_FILES([sgv-code/common/common-widgets.h])
AC_CONFIG_FILES([sgv-code/common/defines.h])
AC_CONFIG_FILES([sgv-code/common/probe-buttons.c])
AC_CONFIG_FILES([sgv-code/common/draw2-draw.c])
AC_CONFIG_FILES([sgv-code/common/edit-panel-scroll.c])
AC_CONFIG_FILES([sgv-code/common/join-clips.c])
AC_CONFIG_FILES([sgv-code/common/file-stat.c])
AC_CONFIG_FILES([sgv-code/common/file-type.c])
AC_CONFIG_FILES([sgv-code/common/gdkkeysyms.h])
AC_CONFIG_FILES([sgv-code/common/gettime.c])
AC_CONFIG_FILES([sgv-code/common/global-vars.h])
AC_CONFIG_FILES([sgv-code/common/includes.h])
AC_CONFIG_FILES([sgv-code/common/load-program.c])
AC_CONFIG_FILES([sgv-code/common/main-timer.c])
AC_CONFIG_FILES([sgv-code/common/media-playback.c])
AC_CONFIG_FILES([sgv-code/common/media-probe.c])
AC_CONFIG_FILES([sgv-code/common/memory-alloc.c])
AC_CONFIG_FILES([sgv-code/common/on-draw4-draw.c])
AC_CONFIG_FILES([sgv-code/common/play-buttons.c])
AC_CONFIG_FILES([sgv-code/common/play-check-box.c])
AC_CONFIG_FILES([sgv-code/common/playclip.c])
AC_CONFIG_FILES([sgv-code/common/program-buttons.c])
AC_CONFIG_FILES([sgv-code/common/rearrange-program.c])
AC_CONFIG_FILES([sgv-code/common/sort.c])
AC_CONFIG_FILES([sgv-code/common/rotators.c])
AC_CONFIG_FILES([sgv-code/common/structures.h])
AC_CONFIG_FILES([sgv-code/common/up-down-buttons.c])
AC_CONFIG_FILES([sgv-code/common/vlc-interface.c])
AC_CONFIG_FILES([sgv-code/common/playback-scrollbar.c])
AC_CONFIG_FILES([sgv-code/common/clip-settings.c])
AC_CONFIG_FILES([sgv-code/common/hot-keys.c])
AC_CONFIG_FILES([sgv-code/common/frame-mode.c])
AC_CONFIG_FILES([sgv-code/common/playback-speed.c])
AC_CONFIG_FILES([sgv-code/common/make-clip.c])
AC_CONFIG_FILES([sgv-code/common/trim-clip.c])
AC_CONFIG_FILES([sgv-code/common/tiled-clips.c])
AC_CONFIG_FILES([sgv-code/common/loop-stream.c])
AC_CONFIG_FILES([sgv-code/common/cut-paste-drag.c])
AC_CONFIG_FILES([sgv-code/common/window-main-fcns.c])
AC_CONFIG_FILES([sgv-code/common/crop-control.c])
AC_CONFIG_FILES([sgv-code/common/audio.c])
AC_CONFIG_FILES([sgv-code/common/query-tooltip.c])
AC_CONFIG_FILES([sgv-code/common/edge-detect.c])
AC_CONFIG_FILES([sgv-code/common/negative.c])
AC_CONFIG_FILES([sgv-code/common/file-choose.c])
AC_CONFIG_FILES([sgv-code/common/dir-choose.c])
AC_CONFIG_FILES([sgv-code/common/file-rename-dialog.c])
AC_CONFIG_FILES([sgv-code/common/insert-text-dialog.c])
AC_CONFIG_FILES([sgv-code/common/delete-dialog.c])
AC_CONFIG_FILES([sgv-code/common/geo-test.c])
AC_CONFIG_FILES([sgv-code/common/adjust-video.c])
AC_CONFIG_FILES([sgv-code/common/sharpen.c])
AC_CONFIG_FILES([sgv-code/common/monochrome.c])
AC_CONFIG_FILES([sgv-code/common/vid-fmt-std.c])
AC_CONFIG_FILES([sgv-code/common/clip-speed.c])
AC_CONFIG_FILES([sgv-code/common/clip-from-still.c])
AC_CONFIG_FILES([sgv-code/common/file-probe.c])
AC_CONFIG_FILES([sgv-code/common/ff-run.c])
AC_CONFIG_FILES([sgv-code/common/gtk-code.c])
AC_CONFIG_FILES([sgv-code/common/pulse.c])
AC_CONFIG_FILES([sgv-code/common/preview-run.c])
AC_CONFIG_FILES([sgv-code/common/vumeter.c])
AC_CONFIG_FILES([sgv-code/common/audio-filters.c])
AC_CONFIG_FILES([sgv-code/common/functions.h])
AC_CONFIG_FILES([sgv-code/common/global-extern-variables.h])
AC_CONFIG_FILES([sgv-code/common/sink.h])
AC_CONFIG_FILES([sgv-code/common/zippy-says.c])
AC_CONFIG_FILES([sgv-code/common/overlay.c])
AC_CONFIG_FILES([sgv-code/common/video-adj-panel.c])
AC_CONFIG_FILES([sgv-code/common/settings-dlg.c])
AC_CONFIG_FILES([sgv-code/common/reverse.c])
AC_CONFIG_FILES([sgv-code/common/stills.c])
AC_CONFIG_FILES([sgv-code/common/halt-program.c])
AC_CONFIG_FILES([sgv-code/common/ffmpeg-filter.c])
AC_CONFIG_FILES([sgv-code/common/duplicate.c])
AC_CONFIG_FILES([sgv-code/common/convert-mkv.c])
AC_CONFIG_FILES([sgv-code/common/convert-mov.c])
AC_CONFIG_FILES([sgv-code/common/convert-mp4.c])
AC_CONFIG_FILES([sgv-code/common/convert-gif.c])
AC_CONFIG_FILES([sgv-code/common/convert-webm.c])
AC_CONFIG_FILES([sgv-code/common/mhd-ref.c])
AC_CONFIG_FILES([sgv-code/common/save-program.c])
AC_CONFIG_FILES([sgv-code/common/new-name.c])
AC_CONFIG_FILES([sgv-code/common/scale-videos.c])
AC_CONFIG_FILES([sgv-code/ScreenEncoder/encoder.c])

AC_OUTPUT

chmod u+x *.script
echo "Now run \"make\" "

echo "Zippy $system config_date = $config_date"
