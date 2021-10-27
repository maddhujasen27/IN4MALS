#pragma once

namespace ghead{

    //Actual game function
    int GAME(std::vector<std::vector<int>> &grid, int viewTime, int health)
    {
        const int G_SIZE = grid.size();
        
        int life = health;
        int stageCount;
        int score=0;
        int firstPlateInpt,secondPlateInpt;
        int lam_x_1, lam_y_1, lam_x_2, lam_y_2;
        int holdCount=0;

        std::vector<bool> holdCheck(G_SIZE * G_SIZE, false);		//To check which plates have been accepted
        std::vector<std::vector<int>> fillerArray(G_SIZE, std::vector<int> (G_SIZE,0));	//To show solved plates discovered
        
        for(int i=viewTime;i>0;i--)
        {
            std::cout<<"\t\t\t\t\t\tMEOMORY GAME\n";
            std::cout<<"Seconds left: "<<i<<"\n";
            sutil::disp_grid(grid,0);
            lutil::delay(1000);
            lutil::clearScreen();
        }
        
        while(life)
        {
            start:
            lutil::clearScreen();
            std::cout<<"\t\t\t\t\t\tMEMORY GAME\n";
            std::cout<<"\t\t\t\t\t\t-----------\n";
            std::cout<<"Currently solved plates:\t\t\tInput Co-ordinates:\t\tHEALTH: "<<life<<"/"<<health<<"\t\tScore: "<<score<<"\n";
            
            sutil::disp_grid(fillerArray);
            
            while(true)
            {
                std::cout<<"\nChoose First Plate: ";
                std::cin>>firstPlateInpt;

                if(firstPlateInpt == 999)
                {
                    sutil::disp_grid(grid,0);
                    lutil::delay(5000);
                    continue;
                }
            
                if(!(firstPlateInpt<=G_SIZE*G_SIZE && firstPlateInpt>0))
                {
                    std::cout<<"Wrong choice!\n";
                    continue;
                }

                if(holdCheck[firstPlateInpt-1] == true)
                {
                    std::cout<<"Invalid Plate!\n";
                    continue;
                }
                break;
            }	

            stageCount=1;

            for(int i=0;i<G_SIZE;i++)
                for(int j=0;j<G_SIZE;j++)
                {
                    if(fillerArray[i][j]!=0)
                    {
                        j++;
                        stageCount++;
                    }
                    if(stageCount==firstPlateInpt)
                    {
                        fillerArray[i][j]=grid[i][j];
                        lam_x_1=i;
                        lam_y_1=j;
                    }
                    stageCount++;
                }		

            sutil::disp_grid(fillerArray,0);

            stageCount=1;
            
            while(true)
            {
                std::cout<<"Choose Second Plate: ";
                std::cin>>secondPlateInpt;

                if(secondPlateInpt == 999)
                {
                    sutil::disp_grid(grid,0);
                    lutil::delay(5000);
                    continue;
                }
                if(!(secondPlateInpt<=G_SIZE*G_SIZE && secondPlateInpt>0))
                {
                    std::cout<<"Wrong choice!\n";
                    continue;
                }
                if(holdCheck[secondPlateInpt-1] == true || firstPlateInpt == secondPlateInpt)
                {
                    std::cout<<"Invalid Plate!\n";
                    continue;
                }
                break;
            }		

            for(int i=0;i<G_SIZE;i++)
                for(int j=0;j<G_SIZE;j++)
                {
                    if(stageCount == secondPlateInpt)
                    {
                        fillerArray[i][j] = grid[i][j];
                        lam_x_2 = i;
                        lam_y_2 = j;
                    }
                    stageCount++;
                }
            
            sutil::disp_grid(fillerArray,0);
            lutil::delay(3000);
            lutil::clearScreen();

            if(fillerArray[lam_x_1][lam_y_1] != fillerArray[lam_x_2][lam_y_2])
            {
                fillerArray[lam_x_1][lam_y_1] = fillerArray[lam_x_2][lam_y_2] = 0;
                life--;
            }
            else
            {
                score++;
                holdCheck[firstPlateInpt-1] = true;
                holdCheck[secondPlateInpt-1] = true;
            }
            
            if(score>=((grid.size() * 2)))
            {
                std::cout<<"You Win!  	Score: "<<score<<"\n";
                return 86;
            }
        }
        if(life<=0) std::cout<<"Game Over!	Score: "<<score<<"\n";
        return 0;
    }
}
