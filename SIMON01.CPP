// Kawo Fong
// Date:
//
/* Description  */

//include file section
#include <iostream.h>
#include <conio.h>
#include <apstring.cpp>
#include "apvector.h"
#include <dos.h>
#include <graphics.h>
#include <stdio.h>

void DrawBoard(void);
void BlinkBoard (int x);
void PrintMountain (void);
void Sliding (void);
void Closing (void);
void PrintTitle (int x, apstring name);
char getmenu (void);
void DisplayYouLose (int x, int y, apstring statement);
char getdifficulty(void);
void FillScreen (int color);
void PrintCredits (int x, int y, apstring statement);
void DrawHorizontalLine (int x1, int y1, int x2, int y2);
void DrawVerticalLine (int x1, int y1, int x2, int y2);

int main ()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
	delay(4000);
	randomize();                                //randomize based on time
	int numsimon=5;
	apvector <int> simon (numsimon);
	int round=1, i,j, numdelay, basescore, score;
	char answer,flag='1', choice, difficulty;
	PrintMountain ();
	Sliding ();
	choice=getmenu();
	while (choice!='4')
	{
		score=0;                     // initialzing score and flag
		flag='1';
		cleardevice();
		switch (choice)
		{
			case'1':                          //direction
			cleardevice();
			settextstyle(1,0,4);
			setcolor (WHITE);
			outtextxy(250, 0, "Direction");
			setcolor (YELLOW);
			outtextxy(115,200,"Follow the patterns shown");
			outtextxy(85,250,"You can NEVER beat this game!");
			getch();
			break;

			case '2':                           //game
			difficulty=getdifficulty();
			switch (difficulty)                  // choosing difficulty
			{
				case '1':
				numdelay=90;
				basescore=10;
				break;
				case '2':
				numdelay=50;
				basescore=20;
				break;
				case '3':
				numdelay=10;
				basescore=30;
				break;
			}
			cleardevice();
			for (i=0; i < simon.length(); i++)      //randomize each pattern
			{
				simon[i]=random(4)+1;
			}
			round=1;
			DrawBoard();
			delay(100);
			do
			{
				char printround [10], printscore[10];       //print round #
				settextstyle (2,0,8 );                      //and score
				setcolor (BLACK);
				sprintf(printround, "Round: %d", round-1);
				outtextxy(0,0,printround);
				setcolor (YELLOW);
				sprintf(printround, "Round: %d", round);
				outtextxy(0,0,printround);
				setcolor (BLACK);
				sprintf(printscore, "Score: %d", score-basescore);
				outtextxy(450,0,printscore);
				setcolor (YELLOW);
				sprintf(printscore, "Score: %d", score);
				outtextxy(450,0,printscore);
				for (i=0; i<round; i++)              //blink out the pattern
				{
					BlinkBoard(simon[i]);
					delay(numdelay);
				}
				i=0;
				do
				{
					answer=getch();
					while (!(answer=='1'||answer=='2'||answer=='3'||answer=='4'))
						answer=getch();                //errortrap
					BlinkBoard(answer-48);
					if (simon[i]!=answer-48)

						flag='0';                   //exit loop
					else
						i++;
				}while( i<round && flag=='1' );
				delay(500);
				if (round%5==4)                 // increase the amount of pattern
				{
					numsimon=numsimon+5;
					simon.resize (numsimon);
					for (i=numsimon-5; i<numsimon; i++)
					{
						simon[i]=random(4)+1;
					}
				}
				round++;
				score += basescore;
			}while (flag=='1');

			if (flag=='0')                    //display you lose
			{                                    //and losing sound
				sound(700);
				delay(500);
				sound(500);
				delay(300);
				sound(400);
				delay(200);
				sound(200);
				delay(400);
				sound(100);
				delay(600);
				nosound();
				cleardevice();
				DisplayYouLose(135,85,"You");
				DisplayYouLose(300,250,"Lose!");
				getch();
				cleardevice();
				for (i=0; i< round-1; i++)          //display answer
				{
					DrawBoard();
					char printround [10], printscore[10];
					settextstyle (2,0,8);
					setcolor (LIGHTGRAY);
					sprintf(printround, "Round: %d", round-1);
					outtextxy(5,5,printround);
					outtextxy(200,0,"Correct Pattern");
					sprintf(printscore, "Score: %d", score-basescore);
					outtextxy(450,0,printscore);
					BlinkBoard(simon[i]);
					delay(100);
					randomize();             //random the pattern after you lose
				}
				getch();
			}
			break;

			case '3':                      //credits
			cleardevice();
			FillScreen(15);
			setcolor(BLACK);
			settextstyle(1,0,4);
			for (i=1; i<=5; i++)
			{                                 //print credits
				setcolor (WHITE);
				settextstyle(1,0,i-1);
				outtextxy(260,0, "Credits");
				setcolor(BLACK);
				settextstyle(1,0,i);
				outtextxy(260,0, "Credits");
				delay(100) ;
			}
			settextstyle(1,0,3);
			for (i=-100; i<=220; i+=10)
			{
				setcolor (WHITE);
				outtextxy(i-10,100,"Creator: Ka Wo Fong");
				setcolor (BLACK);
				outtextxy(i,100,"Creator: Ka Wo Fong");
				delay(50);
			}
			PrintCredits(260,160,"And");        //display thank you one by one
			PrintCredits(80,250,"Thank");
			PrintCredits(280,250,"You");
			PrintCredits(435,250, "To");
			PrintCredits(60,350,"Players like YOU!");
			getch();
			cleardevice();
			FillScreen(8);
			setcolor (WHITE);
			settextstyle(3,0,12);
			outtextxy(135,100,"This is");
			outtextxy(20,250,"NOT NOVA");
			getch();
			break;
		}
		cleardevice();
		choice=getmenu();
	}
	Closing();
	closegraph();
	return 0 ;
}
void DrawBoard(void)                   //draw the simon board
{
	int poly [10];
	int midx,midy;
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	setfillstyle(4, RED);
	bar(midx-200 ,midy-200 , midx, midy);
	setfillstyle(4, BLUE);
	bar(midx,midy-200,midx+200,midy);
	setfillstyle(4, YELLOW);
	bar(midx-200,midy,midx,midy+200);
	setfillstyle(4, GREEN);
	bar(midx,midy,midx+200,midy+200);
	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT, 0, 4);
	outtextxy(midx+20,midy-40, "2");
	outtextxy(midx-30,midy+5, "4");
	outtextxy(midx-30,midy-40, "1");
	outtextxy(midx+20,midy+5, "3");

}
void BlinkBoard (int x)
{                                  //blink the pattern
	int midx, midy;
	int poly [10];
	midx = getmaxx() / 2;
	midy = getmaxy() / 2;
	switch(x)
	{
		case 1:                         //blink 1
		  sound(100);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL, RED);
		  bar(midx-200 ,midy-200 , midx, midy);
		  delay(100);
		  nosound();
		  setfillstyle(4, RED);
		  bar(midx-200 ,midy-200 , midx, midy);
		  setcolor(WHITE);
		  settextstyle(TRIPLEX_FONT, 0, 4);
		  outtextxy(midx-30,midy-40, "1");
		break;

		case 2:                     //blink 2
		  sound(200);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL, BLUE);
		  bar(midx,midy-200,midx+200,midy);
		  delay(100);
		  nosound();
		  setfillstyle(4, BLUE);
		  bar(midx,midy-200,midx+200,midy);
		  setcolor(WHITE);
		  settextstyle(TRIPLEX_FONT, 0, 4);
		  outtextxy(midx+20,midy-40, "2");
		  break;

		case 4:                    //blink 4
		  sound(300);
		  setcolor(BLACK);
		  setfillstyle(SOLID_FILL, YELLOW);
		  bar(midx-200,midy,midx,midy+200);
		  delay(100);
		  nosound();
		  setfillstyle(4, YELLOW);
		  bar(midx-200,midy,midx,midy+200);
		  setcolor(WHITE);
		  settextstyle(TRIPLEX_FONT, 0, 4);
		  outtextxy(midx-30,midy+5, "4");
		break;

		case 3:                         //blink 3
			sound(400);
			setcolor(BLACK);
			setfillstyle(SOLID_FILL, GREEN);
			bar(midx,midy,midx+200,midy+200);
			delay(100);
			nosound();
			setfillstyle(4, GREEN);
			bar(midx,midy,midx+200,midy+200);
			setcolor(WHITE);
			settextstyle(TRIPLEX_FONT, 0, 4);
			outtextxy(midx+20,midy+5, "3");
		break;
	}
}
void DisplayYouLose (int x, int y, apstring statement)
{
	int i;
	for (i=1;i<=6; i++)                //enlarging YOU LOSE!
	{
		setcolor(BLACK);
		settextstyle (BOLD_FONT,0,i-1);
		outtextxy(x,y,statement.c_str());
		setcolor(CYAN);
		settextstyle (BOLD_FONT, 0, i);
		outtextxy(x,y,statement.c_str());
		delay(50);
	}
}
char getmenu (void)
{
	int midx, midy;                //print out menu and let user enter choice
	char choice;
	PrintMountain();
	midx=getmaxx()/2;
	midy= getmaxy()/2;
	PrintTitle(170,"The");
	PrintTitle(240,"Game");
	PrintTitle(340,"Of");
	PrintTitle(390,"Simon");
	settextstyle(3,0,3);
	setcolor(WHITE);
	outtextxy(midx-70, midy, "1. Direction");
	outtextxy(midx-70, midy+25, "2. Play Simon");
	outtextxy(midx-70, midy+50, "3. Credits");
	outtextxy(midx-70, midy+75, "4. Quit");
	outtextxy(midx-70, midy+150, "Enter Choice: ");
	setcolor(LIGHTRED);
	outtextxy(360,440,"Created by Ka Wo Fong");
	choice=getch();                   //enter choice of menu
	while (!(choice=='1'||choice=='2'||choice=='3'||choice=='4'))
	{
		choice=getch();
	}
	return choice;
}
void PrintTitle (int x, apstring name)      // print The Game of Simon
{
	int i;
	for (i=10; i>=4; i--)
	{
		setcolor (BLACK);
		settextstyle (1, 0,i+1);
		outtextxy(x,10,name.c_str());
		setcolor (LIGHTCYAN);
		settextstyle (1, 0,i);
		outtextxy(x,10,name.c_str());
		delay(50);
	}
}
void PrintMountain (void)
{                                           //print the mountain background
	int poly [10];
	setfillstyle(SOLID_FILL, YELLOW);
	setcolor(YELLOW);
	pieslice(0,200,45,135,50);
	poly[0] = 36; poly[1] = 165;
	poly[2] = 83; poly[3] = 231;
	poly[4] = 0; poly[5] =365 ;
	poly[6] = 0;  poly[7] = 200;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);

	setfillstyle(SOLID_FILL, GREEN);
	setcolor(GREEN);
	pieslice (150,215,45,135,50);
	poly[0] = 115; poly[1] = 180;
	poly[2] = 0; poly[3] = 365;
	poly[4] = 300; poly[5] =365 ;
	poly[6] = 185;  poly[7] = 180;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);

	setfillstyle(SOLID_FILL, BLUE);
	setcolor(BLUE);
	pieslice (315,185,45,135,50);
	poly[0] = 279; poly[1] = 151;
	poly[2] = 230; poly[3] = 250;
	poly[4] = 400; poly[5] =250;
	poly[6] = 350;  poly[7] = 151;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);
	poly[0] = 230; poly[1] = 250;
	poly[2] = 400; poly[3] = 250;
	poly[4] = 350; poly[5] =365;
	poly[6] = 300;  poly[7] = 365;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);

	setfillstyle(SOLID_FILL, RED);
	setcolor(RED);
	pieslice (450,249,45,135,50);
	line (415,215,350,365);
	line(485,215,600,365);
	poly[0] = 415; poly[1] = 215;
	poly[2] = 485; poly[3] = 215;
	poly[4] = 600; poly[5] =365;
	poly[6] = 350;  poly[7] = 365;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);

	setfillstyle(SOLID_FILL, MAGENTA);
	setcolor(MAGENTA);
	pieslice(620,250,45,135,50);
	poly[0] = 585; poly[1] = 215;
	poly[2] = 550; poly[3] = 300;
	poly[4] = 640; poly[5] =300;
	poly[6] = 640;  poly[7] = 215;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);
	poly[0] = 640; poly[1] = 300;
	poly[2] = 640; poly[3] = 365;
	poly[4] = 600; poly[5] =365;
	poly[6] = 550;  poly[7] = 300;
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5, poly);
	fillpoly (5,poly);
}
void Sliding (void)                    //slide the superman across the screen
{
	int x1,x2,x4,x5,x6,x7,x8,x9;
	for (x1=-3,x2=0,x4=-38,x5=-13,x6=-10,x7=-43;
	 x7<700;x1++,x2++,x4++,x5++,x6++,x7++)
	{
		setcolor(BLACK);
		circle(x1-1,75,10);
		circle(x2-1,74,2);
		line(x6-1,82,x6-29,82);
		line(x4-1,82,x4-16,77);
		line(x4-1,82,x4-16,87);
		line(x5-1,82,x5+3,91);
		line(x5-1,82,x5+10,91);             //
		line(x6-1,82,x6-32,75);           //cape
		line(x6-1,82,x6-32,76);
		line(x6-1,82,x6-32,77);
		line(x6-1,82,x6-32,78);
		line(x7-1,75,x7-1,78);

		setcolor(YELLOW);
		circle(x1,75,10);
		circle(x2,74,2);
		setcolor(LIGHTBLUE);
		line(x6,82,x6-28,82);
		line(x4,82,x4-15,77);
		line(x4,82,x4-15,87);
		line(x5,82,x5+4,91);
		line(x5,82,x5+11,91);
		setcolor(RED);
		line(x6,82,x6-33,75);           //cape
		line(x6,82,x6-33,76);
		line(x6,82,x6-33,77);
		line(x6,82,x6-33,78);
		line(x7,75,x7,78);
		delay(3);
	}
}
void Closing (void)           //write out GG!
{
	int i;
	cleardevice();
	setcolor(YELLOW);
	for (i=35; i<=330; i++)
	{
		ellipse(200,200,35,i,100,150);
		delay(3);
	}
	DrawHorizontalLine(215,276,286,276);
	DrawVerticalLine(286,276,286,346);
	for (i=35; i<=330; i++)
	{
		ellipse(400,200,35,i,100,150);
		delay(3);
	}
	DrawHorizontalLine(415,276,486,276);
	DrawVerticalLine(486,276,486,346);
	DrawVerticalLine(550,50,550,325);
	for (i=0;i<=360; i++)
	{
		arc(550,350,0,i,3);
		delay(3);
	}
	getch();
}
char getdifficulty(void)          //choose difficulty
{
	char choice;
	FillScreen (2);
	setcolor (BLACK);
	settextstyle (1,0,4);
	outtextxy(170,0,"Choose a Difficulty");
	outtextxy(260,100,"1. Easy");
	outtextxy(240,150,"2. Medium");
	outtextxy(260,200,"3. Hard");
	settextstyle(0,0,13);
	outtextxy(255,300,"");
	setcolor(WHITE);
	outtextxy(100,300,"");
	setcolor (YELLOW);
	outtextxy(410,300,"");
	choice=getch();
	while (!(choice=='1'||choice=='2'||choice=='3'))
	{
		choice=getch();
	}
	return choice;
}
void FillScreen (int color)             //fill background with color
{
	setfillstyle(SOLID_FILL,color);
	bar(-5,-5,640,480);
}
void PrintCredits (int x, int y, apstring statement)
{
	 for (int i=1; i<=5;i++)             //enlarge the credits statements
	 {
		 setcolor (WHITE);
		 settextstyle(9,0,i-1);
		 outtextxy(x,y, statement.c_str());
		 setcolor (BLUE);
		 settextstyle(9,0,i);
		 outtextxy(x,y, statement.c_str());
		 delay(80);
	 }
}
void DrawHorizontalLine (int x1, int y1, int x2, int y2)
{
	for (int i=x1; i<=x2; i++)            //draw horizontal line
	{
		line (x1,y1,i,y2);
		delay(3);
	}
}
void DrawVerticalLine (int x1, int y1, int x2, int y2)
{
	for (int i=y1; i<=y2; i++)        //draw vertical line
	{
		line (x1,y1,x2,i);
		delay(3);
	}
}