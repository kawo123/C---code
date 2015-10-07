#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

int main(void)
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;
	int midx, midy;
	int stangle = 0, endangle = 360;
	int xradius = 100, yradius = 50;

	/* initialize graphics, local variables */
	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)
	/* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	/* terminate with an error code */
	}
	delay(4000);
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	int i;
	setcolor(WHITE);
	ellipse(100, midy,90,300,50,70);
	ellipse(100, midy,90,300,0,100);
//	for (i)


	getch();
	closegraph();
	return 0;
}
