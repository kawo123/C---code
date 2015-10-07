// Kawo Fong
// Date:
//
/* Description  */

//include file section
#include <iostream.h>
#include <conio.h>
#include <apstring.cpp>
#include <dos.h>

char getmenu (void);
void clearspace (void);
void endcredit (void);
void drawstick (void);
int takestick (int sticktaken, int x);

apstring name1, name2;

int main ()
{
	randomize ();
	int x2,sticktaken, player = random(2)+1, x=46, totalsticks=15, numberwon1=0, numberwon2=0 ;
	int first;
	char choice, chsticktaken, choice2='1';
	do
	{
		clrscr () ;
		choice = getmenu();
		switch (choice)
		{
			case '1':    //direction
			textcolor (WHITE);
			clearspace();
			gotoxy (35,10);
			cout<<"Direction";
			gotoxy (22, 12);
			cout<<"Same rules as in \"Game of Nimh\" but";
			gotoxy (23,13);
			cout<<"you take out troll people instead";
			getch();
			break;

			case '2':    //game
			player=random(2)+1;
			first=player;
			numberwon1=0, numberwon2=0;
			clearspace();
			gotoxy (3,12);
			cout<<"Enter the name of Player1: ";
			cin>>name1;
			gotoxy (3,13);
			cout<<"Enter the name of Player2: ";
			cin>>name2;
			do
			{
				if (first==1)                     //alternate between players
				{
					first=2;
					player=2;
				}
				else
				{
					first=1;
					player=1;
				}
				if (choice2=='1')
				{
					gotoxy (3,18);
					cout<<"                                 ";
					gotoxy (3,19);
					cout<<"                                  ";
				}
				totalsticks=15;
				x=46;
				drawstick();
				while (totalsticks > 1)
				{

					if (player == 1)
					{
						gotoxy (3,16);              //player1's turn
						cout<<" ";
						gotoxy (4,15);
						cout<<name1<<", type in your number: ";
						gotoxy (3,15);
						cout<<"";                          // indicator
						chsticktaken=getch();
						sticktaken=chsticktaken-48;
						while (totalsticks<=3 && sticktaken >= totalsticks)
						{
							gotoxy (4,15);
							cout<<name1<<", type in your number: ";
							gotoxy (3,15);
							cout<<"";
							chsticktaken=getch();
							sticktaken=chsticktaken-48;
						}
						while (!(chsticktaken=='1' || chsticktaken=='2' || chsticktaken=='3'))
						{
							gotoxy (4,15);
							cout<<name1<<", type in your number: ";
							gotoxy (3,15);
							cout<<"";
							chsticktaken=getch();
							sticktaken=chsticktaken-48;
						}
						totalsticks-=sticktaken;
						player=2;
					}
					else
					{
						gotoxy (3,15);
						cout<<" ";
						gotoxy (4,16);
						cout<<name2<<", type in your number: ";
						gotoxy (3,16);
						cout<<"";                     //indicator
						chsticktaken=getch();
						sticktaken=chsticktaken-48;
						while (totalsticks<=3 && sticktaken >= totalsticks)
						{
							gotoxy (4,16);
							cout<<name1<<", type in your number: ";
							gotoxy (3,16);
							cout<<"";
							chsticktaken=getch();
							sticktaken=chsticktaken-48;
						}
						while (!(chsticktaken=='1' || chsticktaken=='2' || chsticktaken=='3'))
						{
							gotoxy (4,15);
							cout<<name1<<", type in your number: ";
							gotoxy (3,15);
							cout<<"";
							chsticktaken=getch();
							sticktaken=chsticktaken-48;
						}

						totalsticks-=sticktaken;
						player=1;
					}
					x=takestick(sticktaken,x);
				}
				if (player==1)
				{
					gotoxy (3,18);
					cout<<name2<<" is the winner!";
					numberwon2++;
				}
				else
				{
					gotoxy (3,18);
					cout<<name1<<" is the winner!";
					numberwon1++;
				}
				if (choice2=='1')
				{
					gotoxy (50,10);
					cout<<name1<<" won "<<numberwon1<<" games";
					gotoxy (50,11);
					cout<<name2<<" won "<<numberwon2<<" games";

				}
				gotoxy (3, 19);
				cout<<"Want to play again (1-Yes, 2-No) ?";
				choice2=getch();
				while (!(choice2=='1' || choice2=='2'))
				{
					choice2=getch();
				}
			}while ( choice2!='2');
			break;
		}
	} while (choice!='3');
	endcredit();
	return 0 ;
}
char getmenu (void)
{
	textcolor (YELLOW);
	textbackground (BLACK);
	clrscr () ;
	int x, y;
	char choice;

	gotoxy(1,1);
	cprintf("Ú");     	//cout<<(char)214Ö;          //cout<<char(218)Ú
	gotoxy(1,25);
	cprintf("À");			//cout<<(char)211Ó;       //cout<<char(192)À
	gotoxy(79,1);
	cprintf("¿");			//cout<<(char)183·;      //cout<<char(191)¿
	gotoxy(79,25);
	cprintf("Ù");			//cout<<(char)189½;    //cout<<char(217)Ù

	for (x=2; x<=78; x++)
	{
		 textcolor(BLUE);
		 gotoxy (x,1);
		 cprintf("Ä");
		 gotoxy (x,25);
		 cprintf("Ä");
	}

	for (y=2;y<=24;y++)
	{
		textcolor(RED);
		gotoxy (1,y);
		cprintf("³");         //cout<<(char)179
		gotoxy (79,y);
		cprintf("³");
	}

	gotoxy(5,3);
	cprintf("Ý");         //char(221 Ý)
	gotoxy(5,7);
	cprintf("Ý");
	gotoxy(75,3);
	cprintf("Ý");
	gotoxy(75,7);
	cprintf("Ý");

	for (x=6;x<=74;x++)
	{
		gotoxy (x,3);
		cprintf("Ý");
		gotoxy (x,7);
		cprintf("Ý");
	}
	for (y=3;y<=6;y+=2)
	{
		gotoxy (5,y);
		cprintf("Ý");
		gotoxy (75,y);
		cprintf("Ý");
	}
	textcolor (YELLOW);
	gotoxy(27,14);
	cprintf("É");         //char(221 Ý)
	gotoxy(27,23);
	cprintf("È");          //187»   201É   200È    188¼
	gotoxy(52,14);
	cprintf("»");
	gotoxy(52,23);
	cprintf("¼");

	for (x=28;x<=51;x++)
	{
		gotoxy (x,14);
		cprintf("Í");
		gotoxy (x,23);
		cprintf("Í");
	}
	for (y=15;y<=22;y++)
	{
		gotoxy (27,y);
		cprintf("º");
		gotoxy (52,y);
		cprintf("º");
	}
	textcolor (GREEN);
	gotoxy (57, 23);
	cprintf("Created by Ka Wo Fong");
	gotoxy (57, 24);
	cprintf("Created on 1/24/2012");


	textcolor(GREEN);
	gotoxy (32, 5);
	cout<<"The Game of Nihm";
	gotoxy (28,16) ;
	cout<<"1. Direction";
	gotoxy (28,17) ;
	cout<<"2. Play Nihm";
	gotoxy (28,18) ;
	cout<<"3. Quit";
	gotoxy (28,19) ;
	cout<<"Enter choice: ";
	choice=getch();
	while (!(choice=='1' || choice == '2' || choice=='3'))
	{
		choice=getch();
	}
	return choice ;
}
void clearspace (void)
{
	int y;
	for (y=10; y<=23; y++)
	{
		gotoxy (2,y);
		cout<<"                                                       ";
	}

}
void endcredit (void)
{
	int y,y1,y3,y4,y5,y6,y2;
	clrscr();
	for (y=25,y1=27,y2=29,y3=31,y4=33,y5=35,y6=47; y5>=1; y--,y1--,y2--,y3--,y4--,y5--,y6--)
	{
		textcolor (LIGHTMAGENTA);
		clrscr();
		if (y>=1)
		{
			gotoxy (36,y);
			cout<<"End Credit";
		}
		if (y1>=1 && y1<=25)
		{
			gotoxy (31,y1);
			cout<<"Producer : Ka Wo Fong";
		}
		if (y2>=1 && y2<=25)
		{
			gotoxy (31,y2);
			cout<<"Advisor : Ricky Diep";
		}
		if (y3>=1 && y3<=25)
		{
			gotoxy (30,y3);
			cout<<"Mi Amigo : Jingjun Chen";
		}
		if (y4>=1 && y4<=25)
		{
			gotoxy (32,y4);
			cout<<"Pervert : Sheng Li";
		}
		if (y5>=1 && y5<=25)
		{
			gotoxy (34,y5);
			cout<<"I LOVE WALMART!";
		}
		if (y6>=1 && y6<=25)
		{
			gotoxy (29,y6);
			cout<<"THANK YOU FOR PLAYING!";
		}
		delay (50);
		gotoxy (30,1);
		cout<<"                          ";
	}
	gotoxy (29,13);
	cout<<"THANK YOU FOR PLAYING!";
	getch();

}
void drawstick (void)
{
	int x=46, x2=46;
	textcolor (YELLOW);
	for (x2=46; x2<=74; x2+=2)
	{
		gotoxy (x2,16);
		cprintf("");
		gotoxy (x2,17);
		cprintf("Å");
		gotoxy (x2,18);
		cprintf("^");
		delay (50);
	}
}
int takestick (int sticktaken, int x)
{
	for (; sticktaken>0; sticktaken--, x+=2)
	{
		gotoxy(x, 16);
		cout<<" ";
		gotoxy (x,17);
		cout<<" ";
		gotoxy (x,18);
		cout<<" ";
	}
	return x;
}