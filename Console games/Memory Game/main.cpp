#include<iostream>
#include<vector>

#define GRID_SIZE 4
#define MEMORY_SECOND 10
#define HEALTH 5

#include "header/low_util.h"			//lutil
#include "header/support_util.h"		//sutil
#include "header/grid_building.h"		//grbl
#include "header/game_head.h"			//ghead

using namespace std;

int main()
{
	int inpt;

	vector<vector<int>> grid(GRID_SIZE , vector<int> (GRID_SIZE, 0));
	vector<int> symbArr(GRID_SIZE * GRID_SIZE);	

	sutil::symb_initialize(symbArr);
	
	cout<<"Loading the game, Please wait...  (This can take a few minutes)\n";
	do{
		grbl::random_install(grid);
		grbl::grid_maker(grid,symbArr);
	}while(grbl::check_grid(grid));

	lutil::clearScreen();
	
	cout<<"\tMEMORY GAME\n\t1. Start Game\n\t2. Exit\n\nEnter value: ";
	cin>>inpt;

	switch(inpt)
	{
		case 1:
			lutil::clearScreen();
			ghead::GAME(grid,MEMORY_SECOND,HEALTH);
			break;
		default:
			break;
	}
	return 0;
}