/*
 * RAWC-CONVERT
 * Copyright (C) 2009 Simeon Voelkel <simeon_voelkel at arcor dot de>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

//copied raw_struct from svg.C in cinelerra's plugins/svg/ directory
struct raw_struct {
        char rawc[5];			// Null terminated "RAWC" string
        int32_t struct_version;		// currently 1 (bumped at each destructive change) 
        int32_t struct_size;		// size of this struct in bytes
        int32_t width;			// logical width of image
        int32_t height;
        int32_t pitch;			// physical width of image in memory
        int32_t color_model;		// as BC_ constant, currently only BC_RGBA8888 is supported
        int64_t time_of_creation;	// in milliseconds - calculated as (tv_sec * 1000 + tv_usec / 1000);
					// we can't trust date on the file, due to different reasons
};



int main(int argc, char *argv[])
{
	char filename_png[4096];
	char filename_rgba[4096];
	char filename_info[4096];
	char filename_raw[4096];

	char command[4096];

	// require exactly 3 arguments:
	// filename_png, filename_rgba and filename_raw 

	if (argc != 4)
	{
		fprintf(stderr, "%s requires exactly three filenames as arguments!\n", argv[0]);
		fprintf(stderr, "USAGE: %s <filename_png> <filename_rgba> <filename_raw>\n", argv[0]);

		return -1;
	}

	strncpy (filename_png, argv[1], 4095);
	strncpy (filename_rgba, argv[2], 4095);
	strncpy (filename_info, argv[2], 4095);
	strncpy (filename_raw, argv[3], 4095);
	strcat (filename_info, ".info");

	int sysstat;

	// generate a rgba file out of the png using convert from the imagemagick suite
	sprintf(command,
		"convert \"%s\" \"%s\"",
		filename_png, filename_rgba);
	fprintf(stderr, "Running command %s\n", command);
	sysstat = system(command);

	// print the relevant information about the png and rgba into an info file
	sprintf(command,
		"identify -format \"%%w %%h \" \"%s\" > \"%s\"", 
		filename_png, filename_info);
	fprintf(stderr, "Running command %s\n", command);
	sysstat = system(command);

	// read that info file 
	
	char *infostring = (char*) malloc( sizeof(char) * 4096);
	char *tok;
	char *saveptr;
	FILE *in = fopen (filename_info, "r");

	if (!in)
	{
		fprintf(stderr, "Couldn't load infofile \"%s\"!\n", filename_info);
		return -2;
	}

	fgets(infostring, 4095, in);

	
	fclose (in);

	// fill the struct
	raw_struct rawc_header;

	// read first part: width of image
	tok = strtok_r(infostring, " ", &saveptr);
	rawc_header.width = atoi (tok);

	// for files created by convert from the imagemagick suite pitch equals width:
	rawc_header.pitch = atoi (tok);

	// read second part: height of image
	tok = strtok_r(NULL, " ", &saveptr);
	rawc_header.height = atoi (tok);

	// Now fill the other parts of the struct:
	strcpy(rawc_header.rawc, "RAWC");
	rawc_header.struct_version = 1;
	rawc_header.struct_size = sizeof (raw_struct);
	rawc_header.color_model = 10; // BC_RGBA8888 // FIXME: better include quicktime/colormodels.h instead of using a hardcoded value. However, this is the only supported one.

	// finally calculate the time of creation and set it
	timeval tv;
	gettimeofday(&tv, NULL);

	rawc_header.time_of_creation = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	// now write the struct to a file and cat that file with the rgba file into a rawc .raw file
	
	FILE *out = fopen(filename_raw, "w");
	if (!out)
	{
		fprintf(stderr, "Couldn't open rawfile \"%s\" for writing!\n", filename_raw);
		return -3;
	}

	size_t stat;
	stat = fwrite(&rawc_header, rawc_header.struct_size, 1, out);

	in = fopen(filename_rgba, "r");
	if (!in)
	{
		fprintf(stderr, "Couldn't open rgbafile \"%s\" for reading!\n", filename_rgba);
		return -3;
	}

	size_t n;
	unsigned char buf[4096];
	while ( (n = fread(&buf, 1, 4096, in)) > 0 )
	{
//		fprintf (stderr, "%i\n", n);
		stat = fwrite(&buf, 1, n, out);
	}

	fclose (in);
	fclose (out);
	
	free(infostring);

	return 0;
}


