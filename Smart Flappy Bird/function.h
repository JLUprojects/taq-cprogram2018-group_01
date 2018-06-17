#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <graphics.h>
#pragma   comment(lib, "Winmm.lib ") 

int bird_x, bird_y; // Coordinate of the bird
int i=0,k=0;
int score=0; 
int bar1_x1,bar1_x2;
int bar2_x1,bar2_x2;
int bar1_xDown, bar1_xTop; 
int bar2_xDown, bar2_xTop; 
int bar1_y;
int bar2_y;
int one; // The judgement of cycle--mode1 continues.
int two; // The judgement of cycle--Game continues.
int bar_height; 
int bar_width; 
int bird_height;
int bird_width;	
int height, width; 
int delta_x,delta_y,delta_score,action,state,change_key,x,y,three,four,speed = 10;// The value used in Q-learning arithmetic.
int arr_R[60][30][2];
int arr_Q[60][30][2];
IMAGE background, bird1[2], bird2[2], bird11, score1[10], score2[10],bar_up1,bar_down1,bar_up2,bar_down2,start,ground,gameover,play1,play2;

void startup()  //Make data original.
{
	height = 512;
	width = 288;
	bar_height = 500;
	bar_width = 40;
	bird_height = 22;
	bird_width = 30;
	bird_y = 68;
	bird_x = 18*11;
	bar1_y = width;
	srand((unsigned)time(NULL));
	int temp1 = (rand() % 8)*22 + 154;
	bar1_xDown = temp1 - 88;
	bar1_xTop = temp1 + 88;
	bar1_x1 = bar1_xDown - bar_height;
	bar1_x2 = bar1_xTop;
	bar2_y = 438;
	int temp2 = (rand() % 8)*22 + 154;
	bar2_xDown = temp2 - 88;
	bar2_xTop = temp2 + 88;
	bar2_x1 = bar2_xDown - bar_height;
	bar2_x2 = bar2_xTop;
	score = 0;
	delta_x=(bar1_xTop-bird_x)/22+24;
	delta_y=(bar1_y-bird_y)/10+5;
	delta_score = 0;
	state=1;
	change_key=0;

}


void show()  //Interface
{
	putimage(0,0,&background);
	putimage(bird_y,bird_x,&bird11);
}
 
void load()
{
	loadimage(&background, "F:\\game\\background.jpg");
	loadimage(&start,"F:\\game\\start.jpg"); 
	loadimage(&ground,"F:\\game\\ground.jpg");
	loadimage(&play1,"F:\\game\\play1.jpg");
	loadimage(&play2,"F:\\game\\play2.jpg");
	loadimage(&bird11, "F:\\game\\bird11.jpg");
	loadimage(&bar_up1,"F:\\game\\bar_up1.jpg");
	loadimage(&bar_down1,"F:\\game\\bar_down1.jpg");
	loadimage(&bar_up2,"F:\\game\\bar_up2.jpg");
	loadimage(&bar_down2,"F:\\game\\bar_down2.jpg");
	loadimage(&score1[0], "F:\\game\\0_1.jpg");
	loadimage(&score2[0], "F:\\game\\0_2.jpg");
	loadimage(&score1[1], "F:\\game\\1_1.jpg");
	loadimage(&score2[1], "F:\\game\\1_2.jpg");
	loadimage(&score1[2], "F:\\game\\2_1.jpg");
	loadimage(&score2[2], "F:\\game\\2_2.jpg");
	loadimage(&score1[3], "F:\\game\\3_1.jpg");
	loadimage(&score2[3], "F:\\game\\3_2.jpg");
	loadimage(&score1[4], "F:\\game\\4_1.jpg");
	loadimage(&score2[4], "F:\\game\\4_2.jpg");
	loadimage(&score1[5], "F:\\game\\5_1.jpg");
	loadimage(&score2[5], "F:\\game\\5_2.jpg");
	loadimage(&score1[6], "F:\\game\\6_1.jpg");
	loadimage(&score2[6], "F:\\game\\6_2.jpg");
	loadimage(&score1[7], "F:\\game\\7_1.jpg");
	loadimage(&score2[7], "F:\\game\\7_2.jpg");
	loadimage(&score1[8], "F:\\game\\8_1.jpg");
	loadimage(&score2[8], "F:\\game\\8_2.jpg");
	loadimage(&score1[9], "F:\\game\\9_1.jpg");
	loadimage(&score2[9], "F:\\game\\9_2.jpg");
	loadimage(&gameover,"F:\\game\\gameover.jpg"); 
}
void begin()
{
	mciSendString("open \"F:\\game\\background.mp3\" alias music ", NULL, 0, NULL);
	mciSendString("play music", NULL, 0, NULL);
	initgraph(288,512);//Open windows
	putimage(0,0,&start);
	putimage(0,420,&ground);
}

void bird()
{
	char input;
	if (_kbhit())  // Judge whether there is imputting.
	{
		input = _getch();  // There is no need to press Enter
		if (input == ' ')
		{
			bird_x = bird_x - 4 * bird_height;
		}
	}
	else
	{
		bird_x = bird_x + 0.3* bird_height;
	}
}


void end()
{
	putimage(0,0,&background);
	putimage(50,128,&gameover);
}


void judgement() 
{
	delta_score = score;
	if ((bird_x >= height) || (bird_x <= 0))		
	{
		two = 0;
		four = 0;
		state = 0;
		delta_score=score-delta_score;
		end();
		return;
	}

	if (( ( 0 < (bird_y - bar1_y)) && ((bird_y - bar1_y) < bar_width)) || ( (0 < (bar1_y - bird_y)) && ( (bar1_y - bird_y) < bird_width)))
	{
		if ((bird_x > bar1_xDown) && ( (bar1_xTop - bird_x) > bird_height))	
		{	
			if(bird_y==bar1_y+20)
				score++;
		}
		else
		{
			two = 0;
			four = 0;
			state = 0;
			delta_score=score-delta_score;
			end();
			return;
		}
	}

	if (( ( 0 < (bird_y - bar2_y)) && ((bird_y - bar2_y) < bar_width)) || ( (0 < (bar2_y - bird_y)) && ( (bar2_y - bird_y) < bird_width)))
	{
		if ((bird_x > bar2_xDown ) && ((bar2_xTop - bird_x) > bird_height))
		{
			
			if(bird_y==bar2_y+20)
				score++;
		}
		else
		{
			two = 0;
			four = 0;
			state=0;
			delta_score=score-delta_score;
			end();
			return;
		}
	}

	delta_score=score-delta_score;
}
void bar()
{
	if (bar1_y <= 0)  // A new bar appears.
	{
		bar1_y = width;
		int temp1 = (rand() % 8)*22 + 154;
		bar1_xDown = temp1 - 88;
		bar1_xTop = temp1 + 88;
		putimage(bar1_y, bar1_x1, &bar_down1);
		putimage(bar1_y, bar1_x2, &bar_up1);
	}
	if (bar2_y <= 0)  // A new bar appears.
	{
		bar2_y = width;
		int temp2 = (rand() % 8)*22 + 154;
		bar2_xDown = temp2 - 88;
		bar2_xTop = temp2 + 88;
		putimage(bar2_y, bar2_x1, &bar_down2);
		putimage(bar2_y, bar2_x2, &bar_up2);
	}
	bar1_y = bar1_y - 10;
	bar2_y = bar2_y - 10;
	putimage(bar1_y, bar1_xDown-bar_height, &bar_down1);
	putimage(bar1_y, bar1_xTop, &bar_up1);
	putimage(bar2_y, bar2_xDown-bar_height, &bar_down2);
	putimage(bar2_y, bar2_xTop, &bar_up2);

}

void scoreprint()
{
	IMAGE *fig1[6],*fig2[6];
	int he, dig=1, i=0, sdsf=score;
	if(sdsf==0)
	{
		putimage(180,50,&score1[0],NOTSRCERASE);
		putimage(180,50,&score2[0],SRCINVERT);
	}
	while(sdsf>0)
	{
		he=sdsf%10;
		fig1[i]=&score1[he];
		fig2[i]=&score2[he];
		putimage(204-24*dig,50,fig1[i],NOTSRCERASE);
		putimage(204-24*dig,50,fig2[i],SRCINVERT);
		sdsf/=10;
		i++;
		dig++;
	}
}

void update_arr()
{
	int max;
	if(action==0)
	{
		x=delta_x+1;
		y=delta_y+1;
	}
	else
	{
		x=delta_x-1;
		y=delta_y+1;
	}
	if(state==0)//If the bird is alive, state is 1;If the bird is dead, state is 0.
		arr_R[x][y][action]=-5000;
	else
	{
		if(delta_score==1)
			arr_R[x][y][action]=250;
		else
			arr_R[x][y][action]=5; 
	}
		
		if(arr_Q[delta_x][delta_y][0]>=arr_Q[delta_x][delta_y][1])	
			max=arr_Q[delta_x][delta_y][0];
		else
			max=arr_Q[delta_x][delta_y][1];
	
	arr_Q[x][y][action]=0.4*arr_Q[x][y][action]+0.6*(arr_R[x][y][action]+max);
}

void mode_change_A()
{
	delta_x=(bar1_xTop-bird_x)/22+24;
	delta_y=(bar1_y-bird_y)/10+5;
}

void mode_change_B()
{
	delta_x=(bar2_xTop-bird_x)/22+24;
	delta_y=(bar2_y-bird_y)/10+5;
}


void mode_change()
{
	if(bird_y==bar1_y+40)
	{
		mode_change_B();
		change_key = 1;
	}
	if(bird_y==bar2_y+40)
	{
		mode_change_A();
		change_key=0;
	}
	if(change_key==0)
		mode_change_A();
	else
		mode_change_B();
}

void bird_Q()
{
	int a;
	a=rand()%1000;
	if(a=0)
	{
		a=rand()%2;
		if(a==1)
		{
			bird_x=bird_x - 22;	
			action=1;
		}
		else
		{
			bird_x=bird_x + 22;
			action=0;
		}
	}
	else
	{
		
	if(arr_Q[delta_x][delta_y][0]>=arr_Q[delta_x][delta_y][1])
		{
			if(arr_Q[delta_x][delta_y][0]==arr_Q[delta_x][delta_y][1])
			{
				a=rand()%2;
				if(a==0)
				{
					bird_x = bird_x + 22;
					action=0;					
				}
				else
				{
					bird_x = bird_x - 22;
					action=1;				
				}
			}
			else
			{
				bird_x = bird_x + 22;
				action=0;
			}
		}
		else
		{
			bird_x = bird_x - 22;
			action=1;
		}

	}
}

void button()
{
	MOUSEMSG m;
	while(true)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			putimage(36,354,&play1);
			one=two=1;
			Sleep(1000);
			return;
			break;
		case WM_RBUTTONDOWN:
			putimage(168,354,&play2);
			three=four=1;
			Sleep(1000);
			return;
			break;
		}
	}

}

void speed_adjustment()
{
	char input;
	if (_kbhit())  
	{
		input = _getch();  
		if (input == 'w')
			speed = speed - 5;
		if(input == 's')
			speed = speed + 5;
	}
	if (speed <= 0)
		speed = 1;
}