#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

// Global variables
int height, width; // size of screen
int bird_x, bird_y; // coordinate of bird
int bar1_y, bar1_xDown, bar1_xTop; // coordinate of barrier1
int bar2_y, bar2_xDown, bar2_xTop; // coordinate of barrier2
int score, record; //record the score and the history
int times; //for the 
int one; //for while cyclic sentence
int two; //for while cyclic sentence
int three; // for while cyclic sentence

void gotoxy(int x, int y)//move the cursor
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()  // initialization the data
{
	int temp1 = rand() % (height / 2) + height / 4;	// randomized the bar
	int temp2 = rand() % (height / 2) + height / 4; // randomized the bar
	height = 20;
	width = 30;
	bird_x = 0;
	bird_y = width / 3;
	bar1_y = width;
	srand((unsigned)time(NULL));	//sow the seed
	bar1_xDown = temp1 - height / 15;
	bar1_xTop = temp1 + height / 15;
	bar2_y = width * 1.5;
	bar2_xDown = temp2 - height / 15;
	bar2_xTop = temp2 + height / 15;
	score = 0;
	times = 0;
}


void show()  
{
	int i, j;
	gotoxy(0, 0);  // move the cursor
	for (i = 0;i<height;i++)
	{
		for (j = 0;j<width;j++)
		{
			if ((i == bird_x) && (j == bird_y))
				printf("@");  //   print the bird
			else if ((j == bar1_y) && ((i<bar1_xDown) || (i>bar1_xTop)))
				printf("*");  //   print the bar1
			else if ((j == bar2_y) && ((i<bar2_xDown) || (i>bar2_xTop)))
				printf("*");  //   print the bar2
			else
				printf(" ");  //   print blanks

		}
		printf("\n");
	}
	for (i = 0;i < height + 1;i++) //print the locomotive ground
	{
		for (j = 0;j < width;j++)
		{
			if (i == height)
			{
				if (times % 2)
				{
					if (j % 2)
						printf("/");
					else
						printf(" ");	
				}
				else
				{
					if (j % 2)
						printf(" ");
					else
						printf("/");
				}
			}
		}
	}
	printf("\n");
	printf("Score: %d\n", score);
	printf("Record: %d\n", record);

}

void updateWithoutInput()  
{
	int temp1 = rand() % height / 2 + height / 4;
	int temp2 = rand() % height / 2 + height / 4;	
	if (bird_x == height)		// judgment of death
	{
		printf("Game over£¡\npress r to restart\npress others except space to exit");
		two = 0;
		if (score > record)
			record = score;
		return;
	}
	if (bird_y == bar1_y)
	{
		if ((bird_x >= bar1_xDown) && (bird_x <= bar1_xTop))	
			score++;
		else
		{
			printf("Game over£¡\npress r to restart\npress others except space to exit");	
			two = 0;
			if (score > record)
				record = score;
			return;
		}
	}
	if (bird_y == bar2_y)
	{
		if ((bird_x >= bar2_xDown) && (bird_x <= bar2_xTop))
			score++;
		else
		{
			printf("Game over£¡\npress r to restart\npress others except space to exit");
			two = 0;
			if (score > record)
				record = score;
			return;
		}
	}
	if (bar1_y <= 0)  // reset a bar
	{
		bar1_y = width;
		bar1_xDown = temp1 - height / 15;
		bar1_xTop = temp1 + height / 15;
	}
	if (bar2_y <= 0)  // reset a bar
	{
		bar2_y = width;
		bar2_xDown = temp2 - height / 15;
		bar2_xTop = temp2 + height / 15;
	}
	bird_x++;
	bar1_y--;
	bar2_y--;
	times++;
	Sleep(150);
}

void HideCursor() // hide the cursor
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void updateWithInput()  
{
	char input;
	if (_kbhit())  // judge if there is input
	{
		input = _getch();  // no need to press Enter
		if (input == ' ')
		{
			bird_x = bird_x - 2;
		}

	}
}

void _show()  
{
	int i, j;	
	const char*t = "Smart Flappy Bird";
	const char*s = "press s to start";	
	gotoxy(0, 0);  // similar to cls
	HideCursor();	
	for (i = 0;i<20;i++)
	{
		for (j = 0;j<20;j++)
		{
			if ((i == 5) && (j == (width + strlen(t)) / 2))
				printf("Smart Flappy Bird");  
			else if ((i == 11) && (j == (width + strlen(s)) / 2))
				printf("press s to start");  
			else
				printf(" ");  
		}
		printf("\n");
	}

}

void start()
{	
	char input;
	if (_kbhit())  // judge if there is any input
	{
		input = _getch();  // enter is not necessary
		if (input == 's')
		{
			three = 0;
		}
	}
}

void restart()
{	
	char input;
	if (_kbhit())
	{
		input = _getch();  // input without enter
		if (input == 'r')
		{
			two = 1;	//restart the game
			system("cls");
		}
		else if (input == ' ')
			;
		else
			one = 0;	//exit the program
	}
}

int main()
{
	one = two = three = 1;
	while (three)
	{
		_show();
		start();
	}
	while (one)
	{
		startup();  
		while (two)  
		{
			HideCursor();	
			show();  
			updateWithoutInput();  
			updateWithInput();     
		}
		restart();
	}
}

