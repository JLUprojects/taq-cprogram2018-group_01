#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <graphics.h>
#pragma   comment(lib, "Winmm.lib ") 
#include "function.h"


void main()
{
	char input;
	load();
	begin();
	button();
	while (one)
	{
		startup();  // Make data original 
		while (two)  // The beginning of cycle
		{
			show();
			bird();
	    	bar();
			Sleep(20);
			judgement();
			scoreprint();
		}

		if (_kbhit())  // Judge whether there is importing.
		{
			input = _getch();  // There is no need to input Enter.
			if (input == 'r')
			{
				two = 1;	// Restart the game.
				system("cls");
				continue;
			}
			else if (input == ' ')
				;
			else
				one = 0;	//Game ends.
		}
	}

	while (three)// The cycle of Q-learning mode.
	{
		startup();  
		while (four) 
		{
			show();
					
			bird_Q();
	    	bar();
			scoreprint();// Make sure we can see the score all the time.
			Sleep(speed);
			mode_change();
			judgement();
			update_arr();
			speed_adjustment();
		}
		four = 1;
		system("cls");

		}
}
