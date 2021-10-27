#include<iostream>
#include<cstdlib>
#include<time.h>

#ifdef _WIN32
	#include<windows.h>
#elif unix
	#include<unistd.h>
#endif

#define GRID_SIZE 4
#define MEMORY_SECOND 10
#define HEALTH 5

using namespace std;

int fill[GRID_SIZE*2];

void delay(float);
void clearScreen();
void zeroInn(int[][GRID_SIZE]);	//creates a null matrix
void dispGrid(int[][GRID_SIZE],int);	//displays a matrix (with mode 1 or 0)
int randomInstall(int[][GRID_SIZE]);	//inserts random values in matrix
void symbInitialize(int[]);	//inserts all necessery symbols in an array
void gridMaker(int[][GRID_SIZE],int[]); //creates a randomized squire matrix with the given symbols
int checkGrid(int[][GRID_SIZE]);	//Checks if the matrix has all the symbols and if they are in pair 
int GAME(int[][GRID_SIZE]);	//actual game function

int main()
{
	int grid[GRID_SIZE][GRID_SIZE],inpt;
	int symbArr[GRID_SIZE*GRID_SIZE];
	
	symbInitialize(symbArr);
	
	cout<<"Loading the game, Please wait...\n";
	do{
		randomInstall(grid);
		gridMaker(grid,symbArr);
	}while(checkGrid(grid));

	clearScreen();
	cout<<"\tMEMORY GAME\n\t1. Start Game\n\t2. Exit\n\nEnter value: ";
	cin>>inpt;
	switch(inpt)
	{
		case 1:
			clearScreen();
			GAME(grid);
			break;
		default:
			return 0; 
	}
	return 0;
}

void clearScreen()
{
	#ifdef _WIN32
		system("CLS");
	#elif unix
		system("clear");
	#endif
}

void delay(float time)
{
	#ifdef _WIN32
		Sleep(time);
	#elif unix
		usleep(time * 1000);
	#endif
}

void zeroInn(int a[][GRID_SIZE])
{
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
			a[i][j]=0;
}

void dispGrid(int a[][GRID_SIZE],int mode=1)
{
	int l=1;
	for(int i=0;i<GRID_SIZE;i++)
	{
		cout<<"\t  ";
		for(int j=0;j<GRID_SIZE;j++)
			cout<<a[i][j]<<" ";
			
		if(mode==1)
		{
			cout<<"\t\t\t\t";
			for(int k=0;k<GRID_SIZE;k++)
			{
				cout<<l++;
				if(l<=10)
					cout<<"  ";
				else
					cout<<" ";
			}	
		}
		cout<<endl;
	}
}

int randomInstall(int a[][GRID_SIZE])
{
	time_t t;
	unsigned int seed;
	seed = time(&t);
	srand(seed);
//	zeroInn(a);
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
			a[i][j]=rand();
	return 0;	
}

void symbInitialize(int a[])
{
	for(int num=1,i=0;i<(GRID_SIZE*GRID_SIZE);i+=2,num++)
	{
		a[i]=num;
		a[i+1]=a[i];	
	}
}

void gridMaker(int a[][GRID_SIZE],int symbArr[])
{
	int ff,bb;
	int l=(GRID_SIZE*GRID_SIZE)-1,k=1;
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
		{
			ff=bb=1;
			if(a[i][j]%2==0)
			{
				a[i][j] = symbArr[k];
				k+=2;
				ff=0;
			}
			else if(a[i][j]%5==0)
			{
				if(ff)
				{
					a[i][j]=symbArr[k];
					k+=2;
				}
				else
				{
					a[i][j]=symbArr[l];
					l-=2;
				}
			}
			else if(a[i][j]%2!=0)
			{
				a[i][j]=symbArr[l];
				l-=2;
				bb=0;
			}
		}
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
			if(a[i][j]==i+1)
				::fill[i]++;
					
	for(int k=0;k<GRID_SIZE*2;k++)
		if(::fill[k]!=2)
		{
			for(int i=0;i<GRID_SIZE;i++)
				for(int j=0;j<GRID_SIZE;j++)
				{
					if(a[i][j]==0)
						a[i][j]=k+1;
				}
		}			
}

int checkGrid(int a[][GRID_SIZE])
{
	int twoCheck[GRID_SIZE*2];
	for(int i=0;i<GRID_SIZE*2;i++)
		twoCheck[i]=0;
		
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
		{
			if(a[i][j]>30)
				return 1;
				
			for(int k=0;k<GRID_SIZE*2;k++)
				if(a[i][j]==k+1)
					twoCheck[k]++;
		}
	for(int i=0;i<GRID_SIZE*2;i++)
		{
			if(twoCheck[i]!=2)
				return 1;
		}
	return 0;		
}

int GAME(int grid[][GRID_SIZE])
{
	int life=HEALTH;
	int stageCount;
	int score=0;
	int x,y;
	int lam_x_1,lam_y_1,lam_x_2,lam_y_2;
	int holdCheck[GRID_SIZE*GRID_SIZE], holdCount=0;
	int fillerArray[GRID_SIZE][GRID_SIZE];
	zeroInn(fillerArray);
	
	for(int i=0;i<GRID_SIZE*GRID_SIZE;i++)
		holdCheck[i]=0;
	
	for(int i=MEMORY_SECOND;i>0;i--)
	{
		cout<<"\t\t\t\t\t\tMEOMORY GAME\n";
		cout<<"Seconds left: "<<i<<endl;
		dispGrid(grid,0);
		delay(1000);
		clearScreen();
	}
		
	start:
	clearScreen();
	cout<<"\t\t\t\t\t\tMEMORY GAME\n";
	cout<<"\t\t\t\t\t\t-----------\n";
	cout<<"Current solved plates:\t\t\tInput Co-ordinates:\t\tHEALTH: "<<life<<"/"<<HEALTH<<"\t\tScore: "<<score<<endl;
	dispGrid(fillerArray);
	cout<<"\nChoose First Plate: ";
	cin>>x;
	if(x==999)
	{
		dispGrid(grid,0);
		delay(5000);
		goto start;
	}
	for(int i=0;i<GRID_SIZE*GRID_SIZE;i++)
	{
		if(holdCheck[i]==x)
		{
			cout<<"Invalid Plate!\n";
			goto start;
		}
		if(holdCheck[i]==0)
			break;
	}
	if(!(x<=GRID_SIZE*GRID_SIZE&&x>0))
		{
			cout<<"Wrong choice!\n";
			goto start;
		}
	
	stageCount=1;
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
		{
			if(fillerArray[i][j]!=0)
			{
				j++;
				stageCount++;
			}
			if(stageCount==x)
			{
				fillerArray[i][j]=grid[i][j];
				lam_x_1=i;
				lam_y_1=j;
			}
			stageCount++;
		}		
	dispGrid(fillerArray,0);
	
	stageCount=1;
	secondStart:		//Goto start here
	cout<<"Choose Second Plate: ";
	cin>>y;
	if(y==999)
	{
		dispGrid(grid,0);
		delay(5000);
		goto secondStart;
	}
	if(x!=y)
		for(int i=0;i<GRID_SIZE*GRID_SIZE;i++)
		{
			if(holdCheck[i]==y)
			{
				cout<<"Invalid Plate!\n";
				goto secondStart;
			}
			if(holdCheck[i]==0)
				break;
		}
	else
		{
			cout<<"Invalid Plate!\n";
			goto secondStart;
		}
		
	for(int i=0;i<GRID_SIZE;i++)
		for(int j=0;j<GRID_SIZE;j++)
		{
			if(stageCount==y)
			{
				fillerArray[i][j]=grid[i][j];
				lam_x_2=i;
				lam_y_2=j;
			}
			stageCount++;
		}
	dispGrid(fillerArray,0);
	delay(3000);
	clearScreen();
	if(fillerArray[lam_x_1][lam_y_1]!=fillerArray[lam_x_2][lam_y_2])
		{
			fillerArray[lam_x_1][lam_y_1]=fillerArray[lam_x_2][lam_y_2]=0;
			life--;
	//		delay(3000);
		}
	else
	{
		score++;
		holdCheck[holdCount++]=x;
		holdCheck[holdCount++]=y;
	}
	if(life)
		goto start;
	else
		cout<<"Game Over	Score: "<<score<<endl;
	
	if(score>=((GRID_SIZE*2)))
	{
		cout<<"You Win  	Score: "<<score<<endl;
		return 86;
	}
	return 0;
}
















































































































































































































//By Rudrashish Das
//Release time and date: 8:10 PM      14/10/2021
//Version 1.1.2

/*____Change log____
----------------------------------------------------------------------------------------------------------------------------------
Version 1.0.0
	-> Release version

Version 1.0.1
	-> Increased randommness of the grid by introducing a multiple of 5
	
Version 1.0.2
	-> Faster response time with symbol array out of check loop
	-> Faster response time with zeroInn function out of randomInstall function
	
Version 1.1.0
	-> Introduced cheat code(Hint: k-1)
*/
