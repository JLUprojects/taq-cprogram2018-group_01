#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int height, width; // height and width of the interface.
int bird_x, bird_y; // coordinate of the bird.
int bar1_y, bar1_xDown, bar1_xTop; 
int bar2_y, bar2_xDown, bar2_xTop; 
int score; 
int times; // times of cycle.
int one; // key value to decide the cycle whether to go on.
int two; //key value to decide the cycle whether to go on.
int three;
int delta_x,delta_y,delta_score,action,state;
int arr_R[60][20][2]={0}; 
int arr_Q[60][20][2]={0};
int change_key,state,delta_score,highest_score=0;

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y; 
	SetConsoleCursorPosition(handle, pos);
}

void mode_change_A()
{
	delta_x=bar1_xTop-bird_x+30;
	delta_y=bar1_y-bird_y;
}

void mode_change_B()
{
	delta_x=bar2_xTop-bird_x+30;
	delta_y=bar2_y-bird_y;
}

void startup()  // Make data original 
{
	height = 20;
	width = 30;
	bird_x = 10;
	bird_y = width / 3;
	bar1_y = width;
	srand((unsigned)time(NULL));	
	int temp1 = rand() % (height / 2) +height / 4;	// Make the bar random. 
	bar1_xDown = temp1 - height / 10;
	bar1_xTop = temp1 + height / 10;
	bar2_y = width * 1.5;
	int temp2 = rand() % (height / 2) +height / 4;
	bar2_xDown = temp2 - height / 10;
	bar2_xTop = temp2 + height / 10;
	score = 0;
	times = 0;
	delta_x = bird_x-bar1_xTop+30;
	delta_y = bar1_y-bird_y;
	state = 1;
	delta_score = 0;
}


void show()  // Show the interface.
{
	gotoxy(0,0);  
	int i, j;

	for (i = 0;i<height;i++)
	{
		for (j = 0;j<width;j++)
		{
			if ((i == bird_x) && (j == bird_y))
				printf("@");  //   Print the bird
			else if ((j == bar1_y) && ((i<bar1_xDown) || (i>bar1_xTop)))
				printf("*");  //   Print the bar
			else if ((j == bar2_y) && ((i<bar2_xDown) || (i>bar2_xTop)))
				printf("*");  //   Print the bar
			else
				printf(" ");  
			
		}
		printf("\n");
	}
	for (i = 0;i < height + 1;i++)
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
	printf("Record£º %d\n",highest_score); 

}

void updateWithoutInput() 
{
	char input;
	delta_score=score;
	
	if (bird_x == height)		//Judge whether the bird knock down the ground.
	{
		printf("Game Over!\n");

		two = 0;
		state=0;
		delta_score=score-delta_score;
		return;
	}
	if (bird_y == bar1_y)	
	{
		if ((bird_x >= bar1_xDown) && (bird_x <= bar1_xTop))	// Pass the bar, the bird will get score. 
			{
				score++;
				mode_change_B();
				change_key=1;
			}
		else
		{
			printf("Game Over!\n");	
			two = 0;
			state=0;
			delta_score=score-delta_score;
			return;
		}
	}
	if (bird_y == bar2_y)
	{
		if ((bird_x >= bar2_xDown) && (bird_x <= bar2_xTop))
			{
				score++;
			mode_change_A();
			change_key=0;
			}
		else
		{
			printf("Game Over!\n");           
			two = 0;
			state=0;
			delta_score=score-delta_score;
			return;
		}
	}
	if (bar1_y <= 0)  // A new bar appears
	{
		bar1_y = width;
		int temp1 = rand() % height / 2 + height / 4;
		bar1_xDown = temp1 - height / 10;
		bar1_xTop = temp1 + height / 10;
	}
	if (bar2_y <= 0)  // A new bar appears.
	{
		bar2_y = width;
		int temp2 = rand() % height / 2 + height / 4;
		bar2_xDown = temp2 - height / 10;
		bar2_xTop = temp2 + height / 10;      
	}
	if(change_key==0)
		mode_change_A();
	else
		mode_change_B();
	bird_x++;
	bar1_y--;
	bar2_y--;
	times++;
	delta_score=score-delta_score;
	Sleep(10);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void updateWithInput()  
{
	int action;
	int a;
	srand(time(0)); 
	a=rand()%1000;
	if(a==0)// Make a random number to let the bird fly randomly. 
		{
			a=rand()%2;
			if(a==1)
				{
					bird_x = bird_x - 3;
					action=1;
				}
			else
				action=0; 
		} 
	else
	{
	
		if(arr_Q[delta_x][delta_y][0]>=arr_Q[delta_x][delta_y][1])
			action=0;
		else
			{
				bird_x = bird_x - 3;
				action=1;
			}
		}
}

void _show()  // Show the interface
{
	int three;
	char input;	
	three=1;
	while(three)
	{
	gotoxy(0, 0);  
	int i, j;
	HideCursor();	//Hind the cursor
	for (i = 0;i<20;i++)
	{
		for (j = 0;j<20;j++)
		{
			if ((i ==5) && (j == 10))
				printf("Smart Flappy Bird");  
			else if ((i == 10) && (j == 10))
				printf("Press s to start");  
			
			else
				printf(" ");  

		}
		printf("\n");
	}
			if (_kbhit())  // Juddge whether there is imputting.
		{
			input = _getch();  // There is no need to press Enter, and it will go on automatically  
			if (input == 's')
			{
				three = 0;
			}
			printf("\n");
	}
}

}


void update_arr()
{
	int max;
	if(state==0)
		{
			arr_R[delta_x][delta_y][action]=-1000;
		}
	else
	{
		if(delta_score==1)
			arr_R[delta_x][delta_y][action]=50;
		else
			arr_R[delta_x][delta_y][action]=1; 
	}
	if(arr_Q[delta_x][delta_y][0]>=arr_Q[delta_x][delta_y][1])
		{
				max=arr_Q[delta_x+1][delta_y-1][0];

		}
	else
		{
				max=arr_Q[delta_x-2][delta_y-1][1];
		}
	arr_Q[delta_x][delta_y][action]=arr_Q[delta_x][delta_y][action]+0.8*(arr_R[delta_x][delta_y][action]+0.9*max);
	return;
}



int main()
{	

	_show();
	two = one = 1;
	while (one)
	{	
		startup(); 
		while (two) 
		{
			HideCursor();	
			show();  
			updateWithoutInput();  
			updateWithInput();    
			update_arr();
		}
		if(score>highest_score)
		highest_score=score;
		two=1;
		system("cls");

	}
}
