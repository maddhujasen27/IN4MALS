#include<iostream>
#include<cstring>
#include<cmath>
#include<cfloat>
#include<stack>
#include<set>

#define ROW 9
#define COL 10

using namespace std;

using Pair = pair<int, int>;
using poPair = pair<double, pair<int, int> >;

struct cell {
	int parent_i, parent_j;
	double fCost, gCost, hCost;
};

bool isValid(int row, int col)
{
	return (row >= 0) && (col >= 0) && (row < ROW) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col)
{
	// Returns false if the cell is blocked else true
	return grid[row][col];
}

bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)  return true;
	return false;
}

double calculateHValue(int row, int col, Pair dest)
{
	return ((double)sqrt(pow((row - dest.first),2.0) + pow((col - dest.second),2.0)));
}

void display(cell properties[][COL], Pair dest)
{
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(properties[row][col].parent_i == row
			&& properties[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = properties[row][col].parent_i;
		int temp_col = properties[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty())
    {
		pair<int, int> p = Path.top();
		Path.pop();
		printf("->(%d,%d)", p.first, p.second);
	}
    cout<<"\n";
	return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	if(!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) 
    {
		printf("Source or destination is invalid\n");
		return;
	}

	if(!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second))
    {
		printf("Source or the destination is blocked\n");
		return;
	}

	if(isDestination(src.first, src.second, dest)) 
    {
		printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which means that no cell has been visited yet. 
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure cell to hold the properties of that cell
	cell properties[ROW][COL];

	for(int i = 0; i < ROW; i++)
		for(int j = 0; j < COL; j++) 
        {
			properties[i][j].fCost = FLT_MAX;
			properties[i][j].gCost = FLT_MAX;
			properties[i][j].hCost = FLT_MAX;
			properties[i][j].parent_i = -1;
			properties[i][j].parent_j = -1;
		}

	// Initialising the parameters of the starting node
	int i = src.first, j = src.second;
	properties[i][j].fCost = 0.0;
	properties[i][j].gCost = 0.0;
	properties[i][j].hCost = 0.0;
	properties[i][j].parent_i = i;
	properties[i][j].parent_j = j;

	set<poPair> openList;

	// Put the starting cell on the open list and set its 'fCost' as 0
	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;
	while(!openList.empty()) 
    {
        // Take the node from open list
		poPair p = *openList.begin();
		openList.erase(openList.begin());

		// Add this node to the closed list
		int i = p.second.first;
		int j = p.second.second;
		closedList[i][j] = true;

		// Calculate the properties of the 8 adjecent nodes
        for(int newX = -1; newX <= 1; newX++)
            for (int newY = -1; newY <= 1; newY++)
            {
		        double gNew, hNew, fNew;
                if (isValid(i + newX, j + newY)) 
                {
                    // If destination is reached then update the properties
                    if (isDestination(i + newX, j + newY, dest))
                    {
                        properties[i + newX][j + newY].parent_i = i;
                        properties[i + newX][j + newY].parent_j = j;
                        display(properties, dest);
                        foundDest = true;
                        return;
                    }
                    else if (!closedList[i + newX][j + newY] && isUnBlocked(grid, i + newX, j + newY))
                    {
                        gNew = properties[i][j].gCost + 1.0;
                        hNew = calculateHValue(i + newX, j + newY, dest);
                        fNew = gNew + hNew;

                        if(properties[i + newX][j + newY].fCost == FLT_MAX || properties[i + newX][j + newY].fCost > fNew) 
                        {
                            openList.insert(make_pair(fNew, make_pair(i + newX, j + newY)));

                            // Update the properties of this cell
                            properties[i + newX][j + newY].fCost = fNew;
                            properties[i + newX][j + newY].gCost = gNew;
                            properties[i + newX][j + newY].hCost = hNew;
                            properties[i + newX][j + newY].parent_i = i;
                            properties[i + newX][j + newY].parent_j = j;
                        }
                    }
                }
            }
    }

	if(!foundDest) cout<<"Destination cell could not be found!\n";
	return;
}

// Driver program to test above function
int main()
{
	/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked */
	int grid[ROW][COL]
		= { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

	// Source is the left-most bottom-most corner
	Pair src = make_pair(8, 0);

	// Destination is the left-most top-most corner
	Pair dest = make_pair(0, 0);

	aStarSearch(grid, src, dest);

	return (0);
}
