/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+
#+     Glade / Gtk Programming
#+
#+     Copyright (C) 2019 by Kevin C. O'Kane
#+
#+     Kevin C. O'Kane
#+     kc.okane@gmail.com
#+     https://www.cs.uni.edu/~okane
#+     http://threadsafebooks.com/
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// Jan 17, 2024

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/shm.h>

GtkWidget		*window; // main window
GtkWidget		*fixed1;
GtkWidget		*start;
GtkWidget		*encImage;
GtkWidget		*lib264Label;
GtkWidget		*encoderLabel;
GtkWidget		*lib264Image;
GtkWidget		*label1;
GtkWidget		*crf20; 
GtkWidget		*crf25; 
GtkWidget		*crf15; 
GtkWidget		*crf30; 
GtkWidget		*veryfast; 
GtkWidget		*faster; 
GtkWidget		*fast; 
GtkWidget		*medium; 
GtkBuilder		*builder; 

int	crf = 25,
	stpx=0,	X, Y, H, W;

void color_code();

char	preset[64] = "ultrafast";

char	monitor[2048] = "<none>";

char Code_Home[8192], Music_Home_Directory[8192];

gboolean	timer_handler();
void		on_destroy(); 

int main(int argc, char *argv[]) {

	char cmd[2048];
	int i;

	gtk_init(&argc, &argv); // init Gtk

	builder = gtk_builder_new_from_resource ("/part1/part1.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window")); // main window

	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1		= GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	encoderLabel	= GTK_WIDGET(gtk_builder_get_object(builder, "encoderLabel"));
	lib264Label	= GTK_WIDGET(gtk_builder_get_object(builder, "lib264Label"));
	start		= GTK_WIDGET(gtk_builder_get_object(builder, "start"));
	encImage	= GTK_WIDGET(gtk_builder_get_object(builder, "encImage"));
	lib264Image	= GTK_WIDGET(gtk_builder_get_object(builder, "lib264Image"));
	label1		= GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	crf20		= GTK_WIDGET(gtk_builder_get_object(builder, "crf20"));
	crf25		= GTK_WIDGET(gtk_builder_get_object(builder, "crf25"));
	crf15		= GTK_WIDGET(gtk_builder_get_object(builder, "crf15"));
	crf30		= GTK_WIDGET(gtk_builder_get_object(builder, "crf30"));
	veryfast	= GTK_WIDGET(gtk_builder_get_object(builder, "veryfast"));
	faster		= GTK_WIDGET(gtk_builder_get_object(builder, "faster"));
	fast		= GTK_WIDGET(gtk_builder_get_object(builder, "fast"));
	medium		= GTK_WIDGET(gtk_builder_get_object(builder, "medium"));

	g_object_unref(builder);

	gtk_window_set_keep_above (GTK_WINDOW(window), TRUE); // optional

	gtk_widget_show(window);

	gtk_window_move(GTK_APPLICATION_WINDOW(window), 400, 400);

//--------------------------------------------------------------------
//	optional timer disabled
//
//	g_timeout_add_seconds(1, (GSourceFunc) timer_handler, NULL);
//
//--------------------------------------------------------------------

	color_code();	// set background colors

	strcpy(monitor, "pactl get-default-sink");
	FILE *f1 = popen(monitor, "r");

	if (f1 == NULL ) {
		printf("*** pulse source error\n");
		return EXIT_FAILURE;
		}

	fgets(monitor,1024,f1);
	monitor[strlen(monitor)-1] = 0; // new line character chopped
	strcat(monitor, ".monitor");
	fclose(f1);
	printf("Pulse monitor 1  = %s \n", monitor);

        readlink("/proc/self/exe", Code_Home, 1024); // where are we?

        for (i = strlen(Code_Home); i > 0; i--)
                if (Code_Home[i] == '/' ) {
                        Code_Home[i] = 0;
                        break;
                        }

        if (i <= 0) {
                printf("Directory error finding Code_Home\n");
                return EXIT_FAILURE;
                }

        printf("Code home directory: %s\n", Code_Home);
        strcpy(Music_Home_Directory, Code_Home);
        strcat(Music_Home_Directory, "/videos");
        printf("Music Home Directory: %s\n", Music_Home_Directory);

	gtk_main();

	return EXIT_SUCCESS;
	}

void	on_destroy() {	// called when the main window terminates
		char cmd[1024];
		system ("killall --signal 3 ffmpeg");
		system("wait 1");
		gtk_main_quit();
		}

gboolean timer_handler() { // timer
        return TRUE;
        }

gboolean	on_start_state_set(GtkWidget *b) {

	char cmd[2048];

	if (! gtk_switch_get_active(GTK_SWITCH(b))) {
		stpx = 0;
		printf("*** stopping ffmpeg .....\n");
		sleep(5);
		printf("*** stopped\n");
		on_destroy();
		return TRUE;
		}

	W = 1920; H = 1080;

//------------------------------------------------------
//	ultrafast superfast veryfast faster fast medium
//------------------------------------------------------

	     if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(veryfast))) strcpy(preset, "veryfast");
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(faster)))   strcpy(preset, "faster");
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fast)))     strcpy(preset, "fast");
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(medium)))   strcpy(preset, "medium");

	     if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crf15))) crf = 15;
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crf20))) crf = 20;
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crf25))) crf = 25;
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(crf30))) crf = 30;

	sprintf(cmd,
		"ffmpeg -y -hide_banner -loglevel error -threads 0 -thread_queue_size 16384 "
			" -f pulse -i %s "			// monitor
                        " -video_size %dx%d "			// W H
			" -f x11grab -i :0.0+%d,%d "		// X Y
			" -map 1 -map 0:a "
                        " -c:v libx264 "
			" -preset %s "
			" -crf %d "
			" -bufsize 20M "
			" -vf \"format=yuv420p\" "
                        " -f mp4 \"%s/screen-capture.mp4\" &",		// Music_Home_Directoy

		monitor, 
		W, H, X, Y,
		preset,
		crf,
		Music_Home_Directory);

 	system (cmd) ;

	printf("\n*****************************************************\n");
	printf("%s\n", cmd);
	printf("*****************************************************\n\n");

	return FALSE;
	}

void	color_code() {

        GdkColor color; // background colors

        color.red = 0x3333;
        color.green = 0x3333;
        color.blue = 0x9999;

        gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

//-----------------------------
// 	Color the backgrounds
//-----------------------------

        color.red	= 0x6666;
        color.green	= 0xdddd;
        color.blue	= 0xdddd;

	gtk_widget_modify_bg(encImage, GTK_STATE_NORMAL, &color);

        color.red	= 0x7200;
        color.green	= 0x9f00;
        color.blue	= 0xcf00;

	gtk_widget_modify_bg(lib264Image, GTK_STATE_NORMAL, &color);

	}
