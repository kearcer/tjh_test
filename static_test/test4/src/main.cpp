#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "change.h"
#define  NUM  6  //用于指定数组大小 

char *balance[] = {
		"CHANGE_MEDIATYPE_NONE",
		"CHANGE_WIDTHHEIGHT",
		"CHANGE_ASPECT",
		"CHANGE_COLOR",
		"CHANGE_FRAMERATE",
		"CHANGE_INTERLACE",
		"CHANGE_DEVICE",
		"CHANGE_BUFFERMODE",
		"CHANGE_STRIDE",
		"CHANGE_TRIMOUT",
		"CHANGE_MOSAIC",
		"CHANGE_WIDTHHEIGHT_OUT",
		"CHANGE_LOGOIMAGE_PARAM",
		"CHANGE_DYNIMAGE_PARAM",
		"CHANGE_DYNSUBTITLES_PARAM",
		"CHANGE_LOGODETECT_PARAM",
		"CHANGE_HDRINFO",
		"CHANGE_PROPRESS",
		"CHANGE_ENCODER_PARAM",
		"CHANGE_GRABIMAGE_PARAM",
		"CHANGE_DEHAZE_PARAM",
		"CHANGE_FACEBEAUTY_PARAM",
		"CHANGE_DESCRATCH_PARAM",
		};
int value[] = {
		0x00000000,
		0x00000001,
		0x00000002,
		0x00000004,
		0x00000008,
		0x00000010,
		0x00000020,
		0x00000040,
		0x00000080,
		0x00000100,
		0x00000200,
		0x00000400,
		0x00000800,
		0x00001000,
		0x00002000,
		0x00004000,
		0x00008000,
		0x00010000,
		0x01000000,
		0x02000000,
		0x04000000,
		0x08000000,
		0x10000000,
		0x20000000,
};

int main()
{	
	
	int ulChange = 848;
	for (int i = 0; i <= sizeof(value); i++)
	{
		if (ulChange & value[i])
			printf("CHANGE:%s mode, the index is %d\n", balance[i], value[i]);
	}
	return 0;
}