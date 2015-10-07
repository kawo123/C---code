#include <iostream.h>
#include <conio.h>
#include <apstring.cpp>
#include "apvector.h"
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream.h>


void clearwords (void);
void drawchopchop (int x, int y);
void FillScreen (int color);
void intro (void);
void outtro (void);
char getmenu(void);
char submenu(apvector <char> categorywin, int totalround);
int gethighscore (int totalround);

int main ()
{
	int gdriver = DETECT, gmode, errorcode;
	int i,j,l, lost=0, numspace, poly[10],z,k, counter, round=0, holdint, totalround=0;
	char choice, subchoice, choice2;
	apvector <char> wrongletters (26);
	apvector <apstring> phrases (12);
	apvector <char> categorywin (3);
	apstring holdstring;
	apstring name;
	apvector <int> scores (5);
	apvector <apstring> names (5);
	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
	char answer;
	delay(4000);
	intro();
	cleardevice();
	do
	{
		choice=getmenu();
		for (i=0; i<categorywin.length(); i++)
			categorywin[i]=' ';
		cleardevice();
		switch(choice)
		{
			case '1':
			totalround=0;
			round=0;
			do
			{
				randomize();
				subchoice=submenu(categorywin, totalround);
				lost=0;
				round=0;
				while (subchoice!='4'&& lost!=6 && round<12)
				{
					switch(subchoice)
					{
						case '1':
							ifstream infile1 ("e:\\hangman\\kill.dat", ios::in);      //infile
							if (infile1.fail())
							{
								cout<<"Wrong File Path.....";
								getch();
								return 0;
							}
							for (i=0; i<12; i++)
								getline(infile1,phrases[i]);
							infile1.close();
						break;

						case '2':
							ifstream infile2 ("e:\\hangman\\tenvocab.dat", ios::in);
							if (infile2.fail())
							{
								cout<<"Wrong File Path.....";
								getch();
								return 0;
							}
							for (i=0; i<12; i++)
								getline(infile2,phrases[i]);
							infile2.close();
						break;
						case '3':
							ifstream infile3 ("e:\\hangman\\weird.dat", ios::in);
							if (infile3.fail())
							{
								cout<<"Wrong File Path.....";
								getch();
								return 0;
							}
							for (i=0; i<12; i++)
								getline(infile3,phrases[i]);
							infile3.close();
						break;
					}
					for (i=0; i<phrases.length(); i++)      //shuffle
					{
						j=random(phrases.length());
						holdstring=phrases[i];
						phrases[i]=phrases[j];
						phrases[j]=holdstring;
					}
					while (round<12 && lost!=6)           //guessing
					{
						cleardevice();
						apstring message = phrases[round];
						apstring display = message;
						for (i=0; i<wrongletters.length(); i++)
							wrongletters[i]=' ';
						setcolor (LIGHTRED);
						settextstyle (3,0,4);
//						outtextxy(0,0,message.c_str());    //print out the word
						outtextxy(0,0,"Guess the word: ");
						numspace=0;
						for (i=0;i<message.length(); i++)      //making dashes
						{
							if (message[i]<=90&&message[i]>=65 || message[i]<=122&&message[i]>=97)
								display[i]='_';
							else
							{
								display[i]=message[i];
								numspace++;
							}
						}
						lost=0;
						k=10;
						drawchopchop(0,0);
						setcolor (GREEN);
						setfillstyle(SOLID_FILL, GREEN);
						fillellipse(500,378,15,15);
						line(450,385,400,385);         //body
						line(400,385,380,370);         //legs
						line(400,385,380,400);
						line(460,385,475,385);                        //hands
						line(525,373,540,373);
						while(display!=message && lost!=6)
						{
							counter=0;
							char printround[10];     //print round and score
							settextstyle(2,0,8);
							setcolor (BLACK);
							sprintf(printround, "Round: %d", totalround);
							outtextxy(500, 0, printround);
							setcolor(WHITE);
							sprintf(printround, "Round: %d", totalround+1);
							outtextxy(500, 0, printround);
							settextstyle(3,0,3);
							setcolor (YELLOW);
							outtextxy(5,425, "ChopMan");
							outtextxy(5,450, "Created by Ka Wo Fong");
							clearwords();
							settextstyle (3,0,4);
							setcolor(LIGHTMAGENTA);
							outtextxy(20,100,display.c_str());
							answer=tolower(getch());   //errortrap
							while(!(answer<=122&&answer>=97) || wrongletters[answer-97]==answer)
								answer=tolower(getch());
							wrongletters[answer-97]=answer;
							for (j=0; j<message.length(); j++)
							{
								if (toupper(answer)==toupper(message[j]))
								{
									display[j]=message[j];
									counter++;
								}
							}
							if (counter==0)
							{
								lost++;
								drawchopchop(lost,17);
								char printanswer [1];
								setcolor(WHITE);
								sprintf(printanswer, "%c", answer);
								outtextxy(k, 200, printanswer);
								k+=30;
							}
						}
						clearwords();
						setcolor(LIGHTMAGENTA);
						outtextxy(20,100,display.c_str());



						if (lost==6)
						{
							poly[0] = 450; poly[1] = 347;
							poly[2] = 450; poly[3] = 392;
							poly[4] = 550; poly[5] = 392;
							poly[6] = 550; poly[7] = 332;
							poly[8] = poly[0]; poly[9] = poly[1];
							for(i=1,j=2,z=5; i<=7; i++,j+=2,z+=5)       //dropping heads and hands
							{
								setcolor (BLACK);
								setfillstyle(SOLID_FILL, BLACK);
								fillellipse(500+(j-2),378+(i-1)*(i-1),15,15);
								line(460,385+(z-5),475,385+(z-5));
								line(525,373+(z-5),540,373+(z-5));
								setcolor (LIGHTGRAY);
								setfillstyle(SOLID_FILL, LIGHTGRAY);
								drawpoly(5,poly);
								fillpoly(5,poly);
								setcolor (BROWN);
								line(450,410,550,395);
								line(450,240,450,410);    //vertical
								line(550,225,550,395);
								setcolor (GREEN);
								setfillstyle(SOLID_FILL, GREEN);
								fillellipse(500+j,378+i*i,15,15);
								line(460,385+z,475,385+z);
								line(525,373+z,540,373+z);
								delay(100);
							}
							cleardevice();                    //display you lose
							FillScreen(8);
							settextstyle(10,0,8);
							setcolor(YELLOW);
							outtextxy(100,50,"YOU");
							outtextxy(250,250,"LOSE!");
							getch();
							gethighscore(totalround);
							subchoice='0';
						}
						else
						{
							getch();
							cleardevice();                  //display you win
							FillScreen(1);
							settextstyle(10,0,7);
							setcolor(10);               //light green
							outtextxy(100,50,"YOU GOT");
							outtextxy(50,250,"THE WORD!");
							getch();
							if (round==11)
							{
								cleardevice();
								settextstyle(10,0,7);
								setcolor(YELLOW);
								outtextxy(100,50,"YOU WIN");
								settextstyle(10,0,5);
								outtextxy(50,250,"THIS CATAGORY!");
								if (subchoice!='4')
									categorywin[subchoice-49]=subchoice;
								getch();
								subchoice='0';
							}
						}
						round++;
						totalround++;
					}

				}
			}while(totalround<36 && lost!=6 && subchoice!='4');
			if (lost<6 && subchoice!='4')
			{
				cleardevice();                  //display you win
				settextstyle(10,0,10);
				setcolor(10);               //light green
				outtextxy(124,-50,"YOU");
				outtextxy(115,180,"WIN");
				getch();
				gethighscore(totalround);
			}
			break;

			case '2':
				setcolor (LIGHTBLUE);
				settextstyle(1,0,8);
				outtextxy(150,0, "Direction:");
				setcolor (YELLOW);
				outtextxy(200,150,"GUESS");
				outtextxy(120,250,"THE WORD!");
				getch();
			break;

			case '3':
				ifstream infile4 ("e:\\hangman\\hiscores.dat", ios::in);
				ifstream infile5 ("e:\\hangman\\hinames.dat", ios::in);
				if (infile4.fail()||infile5.fail())
				{
					cout<<"Wrong File Path.....";
					getch();
					return 0;
				}
				for (i=0; i<5; i++)
				{
					getline(infile5, names[i]);
					infile4>>scores[i];
				}
				infile4.close();
				infile5.close();
				setcolor (LIGHTBLUE);
				settextstyle(3,0,6);
				outtextxy(175,0,"HIGHSCORES");
				setcolor (YELLOW);
				settextstyle(3,0,4);
				for (i=0; i<5; i++)
				{
					outtextxy(100,50*i+150,names[i].c_str());
					char printscores [2];
					sprintf(printscores,"%d", scores[i]);
					outtextxy(500,50*i+150,printscores);
				}
				getch();
			break;
		}
	}while(choice!='4');
	outtro ();
	getch();
	closegraph();
	return 0;
}
void drawchopchop (int x, int y)
{
	int poly [10];
	setlinestyle(0,0,3);
	setcolor (BROWN);
	line(450,240,550,225);    //horizontal
	line(450,360,550,345);
	line(450,410,550,395);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	poly[0] = 450; poly[1] = 245+((x-1)*y);
	poly[2] = 450; poly[3] = 290+((x-1)*y);
	poly[4] = 550; poly[5] = 290+((x-1)*y);
	poly[6] = 550; poly[7] = 230+((x-1)*y);
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5,poly);
	fillpoly(5,poly);
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	poly[0] = 450; poly[1] = 245+(x*y);
	poly[2] = 450; poly[3] = 290+(x*y);
	poly[4] = 550; poly[5] = 290+(x*y);
	poly[6] = 550; poly[7] = 230+(x*y);
	poly[8] = poly[0]; poly[9] = poly[1];
	drawpoly(5,poly);
	fillpoly(5,poly);
	setcolor(BROWN);
	line(450,240,450,410);    //vertical
	line(550,225,550,395);
	setcolor (GREEN);
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(500,378,15,15);
	line(460,385,475,385);           //hands
	line(525,373,540,373);
}
void clearwords (void)
{
	setfillstyle (SOLID_FILL, BLACK);
	bar(0,50,640,150);
}
void FillScreen (int color)             //fill background with color
{
	setfillstyle(SOLID_FILL,color);
	bar(-5,-5,640,480);
}
void intro (void)
{
	int num, midx=320, midy=240, i;
	char printnum[1];
	settextstyle(9,0,20);
	for (num=5; num>=1; num--)
	{
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(-5,-5,645,485);
		setcolor(BLUE);
		circle(midx,midy,220);
		circle(midx,midy,215);
		for (i=10;i<=360;i+=10)
		{
			setfillstyle(SOLID_FILL, BLACK);
			setcolor(BLACK);
			pieslice(midx, midy,0,i,400);
			setcolor (YELLOW);
			sprintf(printnum, "%d", num);
			outtextxy(260,100,printnum);
			if (i==360)
			{
				if (num==1)
				{
					sound(700);
					delay(500);
					nosound();
				}
				else
				{
					sound(300);
					delay(100);
					nosound();
				}
			}
			delay(15);
		}
	}
}
void outtro (void)
{
	int poly[8], i;
	cleardevice();
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(-5,-5,640,480);
	setcolor (YELLOW);
	setfillstyle(SOLID_FILL,YELLOW);
	poly[0] = 50; poly[1] = 110;
	poly[2] = 50; poly[3] = 290;
	poly[4] = 100; poly[5] = 250;
	poly[6] = 100; poly[7] = 150;
	fillpoly(4, poly);
	setfillstyle(SOLID_FILL, BROWN) ;
	bar(200,300,440,375);
	setcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL, LIGHTGREEN);
	fillellipse(320,200,250,125);
	settextstyle(1,0,8);
	setcolor(8);
	outtextxy(200,140,"ByeBye");
}
char getmenu(void)
{
	char choice;
	cleardevice();
	for (int i=0; i<=1000; i+=5)
	{
		setcolor (BLUE);
		rectangle(5+i,5+i,635-i,475-i);
		delay(5);
	}
	setcolor (WHITE);
	settextstyle(1,0,8);
	outtextxy(150,50, "ChopMan");
	setcolor (LIGHTRED);
	settextstyle(3,0,4);
	outtextxy(215,200,"1. Play Game");
	outtextxy(230,250,"2. Direction");
	setcolor (LIGHTGREEN);
	outtextxy(215,300,"3. High Score");
	outtextxy(265,350,"4. Exit");
	choice=getch();
	while (!(choice=='1'||choice=='2'||choice=='3'||choice=='4'))
		choice=getch();
	return choice;
}
char submenu(apvector <char> categorywin, int totalround)
{
	char choice;
	int i;
	cleardevice();
	settextstyle(10,0,5);
	setcolor (LIGHTMAGENTA);
	outtextxy(10,0,"Choose a Category:");
	settextstyle(1,0,5);
	outtextxy(30,125,"1. Things that can kill you");
	outtextxy(30,200,"2. Sophomore English vocab");
	outtextxy(135,275,"3. Random words");
	outtextxy(25,350,"4. Return to the Main Menu");
	setcolor (BLACK);
	for (i=0; i<categorywin.length(); i++)
	{
		switch(categorywin[i])
		{
			case '1':
				outtextxy(30,125,"1. Things that can kill you");
			break;
			case '2':
				outtextxy(30,200,"2. Sophomore English vocab");
			break;
			case '3':
				outtextxy(135,275,"3. Random words");
			break;
		}
	}
	choice=getch();
	if (choice != '4')
	{
		while (!(choice=='1'||choice=='2'||choice=='3') || choice==categorywin[choice-49])
			choice=getch();
	}
	else
		gethighscore(totalround);
	return choice;
}
int gethighscore (int totalround)
{
	int i,j, holdint;
	apstring holdstring;
	apstring name;
	apvector <int> scores (5);
	apvector <apstring> names (5);

	ifstream infile6 ("e:\\hangman\\hiscores.dat", ios::in);
	ifstream infile7 ("e:\\hangman\\hinames.dat", ios::in);
	if (infile6.fail()||infile7.fail())
	{
		cout<<"Wrong File Path.....";
		getch();
		return 0;
	}
	for (i=0; i<5; i++)
	{
		getline(infile7, names[i]);
		infile6>>scores[i];
	}
	infile6.close();
	infile7.close();
	if (scores[scores.length()-1]<totalround)
	{
		cleardevice();
		setcolor (WHITE);
		settextstyle(10,0,6);
		outtextxy(100,0,"High Score");
		settextstyle(3,0,4);
		outtextxy(10,300,"Enter name: ");
		gotoxy (27,21);
		getline(cin, name);
		scores[scores.length()-1]=totalround;
		names[scores.length()-1]=name;
		for (i = 0 ; i <= scores.length()-2 ; i++)
		{
			for (j = i + 1 ; j <= scores.length()-1 ; j++)
			{
				if (scores[i] < scores[j])
				{
					holdint = scores[j] ;
					scores[j] = scores[i] ;
					scores[i] = holdint ;

					holdstring = names[j] ;
					names[j] = names[i] ;
					names[i] = holdstring ;
				}
			}
		}
		ofstream outfile ("e:\\hangman\\hinames.dat", ios::out);
		ofstream outfile2 ("e:\\hangman\\hiscores.dat", ios::out);
		for (i=0; i<scores.length(); i++)
		{
			outfile<<names[i]<<endl;
			outfile2<<scores[i]<<endl;
		}
		outfile.close();
		outfile2.close();
	}
}