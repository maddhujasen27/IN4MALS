#pragma once

#include<cstdlib>
#include<ctime>

namespace grbl{
    //inserts random values in matrix
    int random_install(std::vector<std::vector<int>> &grid)
    {
        time_t t;
        unsigned int seed;
        seed = time(&t);
        srand(seed);
        for(int i=0;i<grid.size();i++)
            for(int j=0;j<grid.size();j++)
                grid[i][j] = rand();
        return 0;	
    }

    //creates a randomized square matrix with the given symbols
    void grid_maker(std::vector<std::vector<int>> &grid, const std::vector<int> &symbArr)
    {
        const int G_SIZE = grid.size();
        bool ff;
        int l=(symbArr.size())-1;
        int k=1;

        for(int i=0;i<G_SIZE;i++)
        {
            for(int j=0;j<G_SIZE;j++)
            {
                if(grid[i][j]%2==0)	//If the random number present is even then assign symbol[k]
                {
                    grid[i][j] = symbArr[k];
                    k+=2;
                }
                else if(grid[i][j]%5==0)	//else if the random number present is a multiple of 5 and is not even then assign symbol[k]
                {
                    time_t t;
                    srand(time(&t));
                    ff=rand()%1;
                    
                    if(ff)	
                    {
                        grid[i][j]=symbArr[k];
                        k+=2;
                    }
                    else
                    {
                        grid[i][j]=symbArr[l];
                        l-=2;
                    }
                }
                else if(grid[i][j]%2!=0)	//else if the random number present is not a multiple 5 and is odd then assign symbol[l]
                {
                    grid[i][j]=symbArr[l];
                    l-=2;
                }
            }
        }	
    }

    //Checks if the matrix has all the symbols and if they are in pair
    bool check_grid(std::vector<std::vector<int>> &grid)
    {
        const int G_SIZE = grid.size();
        std::vector<int> twoCheck(G_SIZE*2, 0);
            
        for(int i=0;i<G_SIZE;i++)
            for(int j=0;j<G_SIZE;j++)
            {
                if(grid[i][j]>30)
                    return true;
                    
                for(int k=0;k<G_SIZE*2;k++)
                    if(grid[i][j]==k+1)
                        twoCheck[k]++;
            }
        for(int i=0;i<G_SIZE*2;i++)
        {
            if(twoCheck[i]!=2)
                return true;
        }
        return false;		
    }
}
