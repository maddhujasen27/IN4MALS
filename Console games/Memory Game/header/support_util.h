#pragma once

namespace sutil{
    //displays a matrix (with mode 1 or 0)
    void disp_grid(std::vector<std::vector<int>> &grid, int mode=1)
    {
        const int G_SIZE = grid.size();
        int l=1;

        for(int i=0;i<G_SIZE;i++)
        {
            std::cout<<"\t  ";
            for(int j=0;j<G_SIZE;j++)
            {
                std::cout<<grid[i][j];
                if(G_SIZE<5)
                {
                    std::cout<<" ";
                    continue;
                }
                if(grid[i][j] > 9) std::cout<<" ";
                else std::cout<<"  ";
            }	
            if(mode == 1)
            {
                std::cout<<"\t\t\t\t";
                for(int k=0;k<G_SIZE;k++)
                {
                    std::cout<<l++;
                    if(l <= 10) std::cout<<"  ";
                    else std::cout<<" ";
                }	
            }
            std::cout<<"\n";
        }
    }
    
    //inserts all necessery symbols in an array
    void symb_initialize(std::vector<int> &arr)
    {
        for(int num=1,i=0;i<arr.size();i += 2,num++)
        {
            arr[i]=num;
            arr[i+1]=num;	
        }
    }
}