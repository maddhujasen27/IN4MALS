#include<iostream>
#include<vector>
#include<unistd.h>

using namespace std;

void display(vector<vector<std::string>> &);
bool isValid(const int &, const int &);
bool path_blocked(const vector<vector<std::string>> &,const int &,const int &,const int &,const int &);
bool path_blocked_diag(const vector<vector<std::string>> &grid, const int &rowFrom,const int &colFrom, const int &rowTo, const int &colTo, char playerSide);
bool pawn(vector<vector<std::string>> &grid, int rowFrom,int colFrom, int rowTo, int colTo);
bool rook(vector<vector<std::string>> &grid, int rowFrom,int colFrom, int rowTo, int colTo);
bool horse(vector<vector<std::string>> &grid, int rowFrom,int colFrom, int rowTo, int colTo);
bool bishop(vector<vector<std::string>> &grid, int rowFrom,int colFrom, int rowTo, int colTo);
bool queen(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo);
bool king(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo, vector<vector<int>> &kingPos);
bool isKingInCheck(vector<vector<std::string>> &grid,const char &side);

int main()
{
    vector<vector<std::string>> grid = {
                                 {"bR","bH","bB","bQ","bK","bB","bH","bR"},
                                 {"bP","bP","bP","bP","bP","bP","bP","bP"},
                                 {"  ","  ","  ","  ","  ","  ","  ","  "},
                                 {"  ","  ","  ","  ","  ","  ","  ","  "},
                                 {"  ","wB","wK","  ","wQ","  ","  ","  "},
                                 {"  ","  ","  ","  ","  ","  ","  ","  "},                                 
                                 {"wP","wP","wP","wP","wP","wP","wP","wP"},
                                 {"wR","wH","wB","wQ","wK","wB","wH","wR"}};

    vector<vector<int>> kingPos = {{0,4}.{7,4}};

    display(grid);

    bool playing = true;
    while(playing)
    {
        std::string move;
        cout<<"Enter move: ";
        getline(cin,move);
        cout<<move<<endl;

        if(move.size()<4 || move.size()>4) 
        {
            system("clear");
            cout<<"Invalid Inputb!\n\n";
            display(grid);
            continue;
        }

        int rowFrom = (int)(move[0] - 'a');
        int colFrom = (int)(move[1] - '1');

        int rowTo = (int)(move[2] - 'a');
        int colTo = (int)(move[3] - '1');
        
        if(rowTo<0 || rowTo>8 || colTo<0 || colTo>8) continue;

        //bool moved = ;
        if(pawn(grid,rowFrom,colFrom,rowTo,colTo));
        else if(rook(grid,rowFrom,colFrom,rowTo,colTo));
        else if(horse(grid,rowFrom,colFrom,rowTo,colTo));
        else if(bishop(grid,rowFrom,colFrom,rowTo,colTo));
        else if(queen(grid,rowFrom,colFrom,rowTo,colTo));
        else if(king(grid,rowFrom,colFrom,rowTo,colTo,kingPos));
        else {//system("clear");
        cout<<"Invalid Input\n";display(grid);continue;}

       // usleep(3 * 10000);
       // system("clear");

        //cout<<rowFrom<<", "<<colFrom<<endl;
        //cout<<rowTo<<", "<<colTo<<endl;
        display(grid);
    }

    return 0;
}

void display(vector<vector<std::string>> &board)
{
    cout<<"  ";
    for(int i=0;i<8;i++) cout<<"     "<<i+1<<"    ";
    cout<<"\n";
    
    int row = 0, col = 0;

    for(char i='a';i<='h';i++)
    {   cout<<"  ";
        for(int i=0;i<8;i++) cout<<"+---------";
        cout<<"+\n  ";

        for(int i=0;i<8;i++) cout<<"|         ";
        cout<<"|\n"<<i<<" ";

        for(int i=0;i<8;i++) cout<<"|    "<<board[row][col++]<<"   ";
        cout<<"|  "<<i<<"\n  ";

        for(int i=0;i<8;i++) cout<<"|         ";
        cout<<"|\n";
        row++;
        col=0;
    }
    cout<<"  ";
    for(int i=0;i<8;i++) cout<<"+---------";
    cout<<"+\n";
     cout<<"  ";
    for(int i=0;i<8;i++) cout<<"     "<<i+1<<"    ";
    cout<<"\n";
}

bool isValid(const int &row, const int &col)
{
    if(row<0 || row>8 || col<0 || col>8) return false;
    return true;
}

bool path_blocked(const vector<vector<std::string>> &grid, const int &rowFrom, const int &colFrom, const int &rowTo, const int &colTo)
{
    if(rowTo == rowFrom)
    {
        for(int i = colFrom+1; i<colTo; i++)
            if(grid[rowTo][i] != "  ") return true;
        
        for(int i = colFrom-1; i>colTo; i--)
            if(grid[rowTo][i] != "  ") return true;
    }
    else if(colTo == colFrom)
    {
        for(int i = rowFrom+1; i<rowTo; i++)
            if(grid[i][colTo] != "  ") return true;
        
        for(int i = rowFrom-1; i>rowTo; i--)
            if(grid[i][colTo] != "  ") return true;
    }
    return false;
}

bool path_blocked_diag(const vector<vector<std::string>> &grid, const int &rowFrom,const int &colFrom, const int &rowTo, const int &colTo, char playerSide)
{
    int i = rowFrom+1;
    int j = colFrom+1;
    bool valid = true;

    while(i<rowTo && j<colTo && isValid(i,j))
    {
        if(((grid[i++][j++]))[0] != ' ')
        {
            valid = false;
            break;
        }
    }

    if(i==rowTo && j==colTo && (grid[i][j])[0] != (grid[rowFrom][colFrom])[0] && valid) return false;

    i = rowFrom-1;
    j = colFrom-1;

    while(i>rowTo && j>colTo && isValid(i,j))
    {
        if(((grid[i--][j--]))[0] != ' ')
        {
            valid = false;
            break;
        }
    }
    if(i==rowTo && j==colTo && (grid[i][j])[0] != (grid[rowFrom][colFrom])[0] && valid) return false;

    i = rowFrom+1;
    j = colFrom-1;

    while(i<rowTo && j>colTo && isValid(i,j))
    {
        if((grid[i++][j--])[0] != ' ')
        {
            valid = false;
            break;
        }
    }
    if(i==rowTo && j==colTo && (grid[i][j])[0] != (grid[rowFrom][colFrom])[0] && valid) return false;

    i = rowFrom-1;
    j = colFrom+1;

    while(i>rowTo && j<colTo && isValid(i,j))
    {
        if(((grid[i--][j++]))[0] != ' ')
        {
            valid = false;
            break;
        }
    }

    if(i==rowTo && j==colTo && (grid[i][j])[0] != (grid[rowFrom][colFrom])[0] && valid) return false;

    return true;
}

bool pawn(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo)
{
    if(grid[rowFrom][colFrom] == "bP")
    {
        if(grid[rowTo][colTo] == "  "&& rowTo == rowFrom + 1 && colTo == colFrom)
        {
            grid[rowTo][colTo] = grid[rowFrom][colFrom];
            grid[rowFrom][colFrom] = "  ";
            return true;
        }
        else if(((grid[rowTo][colTo])[0] == 'w') && rowTo == rowFrom + 1 && (colTo == colFrom+1 || colTo == colFrom-1))
        {
            grid[rowTo][colTo] = grid[rowFrom][colFrom];
            grid[rowFrom][colFrom] = "  ";
            return true;
        } 
    }
    else if(grid[rowFrom][colFrom] == "wP")
    {
        if(grid[rowTo][colTo] == "  "&& rowTo == rowFrom - 1 && colTo == colFrom)
        {
            grid[rowTo][colTo] = grid[rowFrom][colFrom];
            grid[rowFrom][colFrom] = "  ";
            return true;
        }
        else if(((grid[rowTo][colTo])[0] == 'b') && rowTo == rowFrom - 1 && (colTo == colFrom+1 || colTo == colFrom-1))
        {
            grid[rowTo][colTo] = grid[rowFrom][colFrom];
            grid[rowFrom][colFrom] = "  ";
            return true;
        } 
    }
    return false;
}

bool rook(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo)
{ 
    if((rowTo == rowFrom || colTo == colFrom) && (grid[rowFrom][colFrom])[1] == 'R')
    {
        if(path_blocked(grid, rowFrom, colFrom, rowTo, colTo)) return false;

        if(grid[rowFrom][colFrom] == "bR")
        {
            if(((grid[rowTo][colTo])[0] == 'w')||(grid[rowTo][colTo] =="  "))
            {
                grid[rowTo][colTo] = grid[rowFrom][colFrom];
                grid[rowFrom][colFrom] = "  ";
                return true;
            }
        }
        else if(grid[rowFrom][colFrom] == "wR")
        {
            if(((grid[rowTo][colTo])[0] == 'b')||(grid[rowTo][colTo] =="  "))
            {
                grid[rowTo][colTo] = grid[rowFrom][colFrom];
                grid[rowFrom][colFrom] = "  ";
                return true;
            }
        }
    }
    return false;
}

bool horse(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo) //knight
{
    if((grid[rowFrom][colFrom])[1] == 'H')
    {
        int arr[] = {-1,+2,/**/ +1,-2,/**/ -1,-2,/**/ +1,+2};       //Improve
        for(int i=0;i<8;i++)
        {
           for(int j=1;j<8;j++)
            {
                if((rowTo == (rowFrom + arr[i])) && (colTo == (colFrom + arr[j])))
                {
                    if((grid[rowFrom][colFrom])[0] == 'w')
                    {
                        if((grid[rowTo][colTo])[0] !=  'w')
                        {
                            grid[rowTo][colTo] = grid[rowFrom][colFrom];
                            grid[rowFrom][colFrom] = "  ";
                            return true;
                        }
                    }
                    else if((grid[rowFrom][colFrom])[0] == 'b')
                    {
                        if((grid[rowTo][colTo])[0] != 'b')
                        {
                            grid[rowTo][colTo] = grid[rowFrom][colFrom];
                            grid[rowFrom][colFrom] = "  ";
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool bishop(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo) 
{
    if((grid[rowFrom][colFrom])[1] == 'B')
    {
        if((grid[rowFrom][colFrom])[0] == 'w')
        {
           if(!path_blocked_diag(grid,rowFrom,colFrom,rowTo,colTo, 'w'))
           {
                grid[rowTo][colTo] = grid[rowFrom][colFrom];
                grid[rowFrom][colFrom] = "  ";
                return true;
           }           
        }
        else if((grid[rowFrom][colFrom])[0] == 'b')
        {
           if(!path_blocked_diag(grid,rowFrom,colFrom,rowTo,colTo, 'b'))
           {
                grid[rowTo][colTo] = grid[rowFrom][colFrom];
                grid[rowFrom][colFrom] = "  ";
                return true;
           }           
        }
    }
    return false;
}

bool queen(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo)
{
    if((grid[rowFrom][colFrom])[1] == 'Q')
    {
        if((grid[rowFrom][colFrom])[0] == 'w')
        {
            if(!path_blocked_diag(grid,rowFrom,colFrom,rowTo,colTo, 'w') || (!path_blocked(grid, rowFrom, colFrom,rowTo, colTo) && ((rowFrom == rowTo) || (colFrom == colTo)) && (grid[rowTo][colTo])[0] != 'w'))
            {
                    grid[rowTo][colTo] = grid[rowFrom][colFrom];
                    grid[rowFrom][colFrom] = "  ";
                    return true;
            }

        }
        else if((grid[rowFrom][colFrom])[0] == 'b')
        {
            if(!path_blocked_diag(grid,rowFrom,colFrom,rowTo,colTo, 'b') || (!path_blocked(grid, rowFrom, colFrom, rowTo, colTo) && ((rowFrom == rowTo) || (colFrom == colTo)) && (grid[rowTo][colTo])[0] != 'b'))
            {
                    grid[rowTo][colTo] = grid[rowFrom][colFrom];
                    grid[rowFrom][colFrom] = "  ";
                    return true;
            }    
        }
    }
    return false;
}

bool king(vector<vector<std::string>> &grid, int rowFrom, int colFrom, int rowTo, int colTo, vector<vector<int>> &kingPos)
{
    if((grid[rowFrom][colFrom])[1] == 'K')
    {
        if((grid[rowFrom][colFrom])[0] == 'w' && (grid[rowTo][colTo])[0] != 'w')
        {
            for(int i=-1;i<=1;i++)
            {   
                for(int j=-1;j<=1;j++)
                {   
                    if(rowFrom + i == rowTo && colFrom + j == colTo)
                    {
                        grid[rowTo][colTo] = grid[rowFrom][colFrom];
                        grid[rowFrom][colFrom] = "  ";
                        kingPos[0][0] = rowTo;
                        kingPos[0][1] = colTo;;
                        return true;
                    }
                }
            }
        }
        else if((grid[rowFrom][colFrom])[0] == 'b' && (grid[rowTo][colTo])[0] != 'b')
        {
            for(int i=-1;i<=1;i++)
            {   
                for(int j=-1;j<=1;j++)
                {   
                    if(rowFrom + i == rowTo && colFrom + j == colTo)
                    {
                        grid[rowTo][colTo] = grid[rowFrom][colFrom];
                        grid[rowFrom][colFrom] = "  ";
                        kingPos[1][0] = rowTo;
                        kingPos[1][1] = colTo;;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool util_diag_check_king(vector<vector<std::string>> &grid,const char &side, vector<vector<int>> &kingPos)
{
    char opponent;
    int currRow,currCol;

    if(side == 'w') 
    {
        opponent = 'b';
        currRow  = kingPos[0][0];
        currCol = kingPos[0][1];
    }
    else 
    {
        opponent = 'w';
        currRow  = kingPos[1][0];
        currCol = kingPos[1][1];
    }

    int i = currRow;
    int j = currCol;
    
    while(isValid(++i,++j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'B' || (grid[i][j])[1] == 'Q') return true;
    }

    i = currRow; j = currCol;
    while(isValid(--i,++j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'B' || (grid[i][j])[1] == 'Q') return true;
    }
    
    i = currRow; j = currCol;
    while(isValid(++i,--j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'B' || (grid[i][j])[1] == 'Q') return true;
    }
    
    i = currRow; j = currCol;
    while(isValid(--i,--j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'B' || (grid[i][j])[1] == 'Q') return true;    
    }
    return false;
}

bool util_sides_check_king(vector<vector<std::string>> &grid,const char &side, vector<vector<int>> &kingPos)
{
    char opponent;
    int currRow,currCol;

    if(side == 'w') 
    {
        opponent = 'b';
        currRow  = kingPos[0][0];
        currCol = kingPos[0][1];
    }
    else 
    {
        opponent = 'w';
        currRow  = kingPos[1][0];
        currCol = kingPos[1][1];
    }

    int i = currRow;
    int j = currCol;

    while(isValid(i,j++))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'R' || (grid[i][j])[1] == 'Q') return true;
    }

    j = currCol;
    while(isValid(i++,j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'R' || (grid[i][j])[1] == 'Q') return true;
    }

    i = currRow; 
    while(isValid(i,j--))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'R' || (grid[i][j])[1] == 'Q') return true;
    }

    j = currCol; 
    while(isValid(i--,j))
    {
        if((grid[i][j])[0] == side) return false;
        else if((grid[i][j])[0] == opponent && ((grid[i][j])[1] == 'R' || (grid[i][j])[1] == 'Q') return true;
    }

    return false;
}

bool util_horse_check_king(vector<vector<std::string>> &grid,const char &side, vector<vector<int>> &kingPos)
{
    char opponent;
   int currRow,currCol;

    if(side == 'w') 
    {
        opponent = 'b';
        currRow  = kingPos[0][0];
        currCol = kingPos[0][1];
    }
    else 
    {
        opponent = 'w';
        currRow  = kingPos[1][0];
        currCol = kingPos[1][1];
    }

    int i = currRow;
    int j = currCol;

    if((grid[i+2][j+1])[1] == 'H' && (grid[i+2][j+1])[0] == opponent) return true;
    if((grid[i-2][j-1])[1] == 'H' && (grid[i-2][j-1])[0] == opponent) return true;
    if((grid[i-2][j+1])[1] == 'H' && (grid[i-2][j+1])[0] == opponent) return true;
    if((grid[i+2][j-1])[1] == 'H' && (grid[i+2][j-1])[0] == opponent) return true;

    return false;
}

bool isKingInCheck(vector<vector<std::string>> &grid,const char &side, vector<vector<int>> &kingPos)
{
    if(util_diag_check_king(grid,side,kingPos)) return true;
    else if(util_sides_check_king(grid,side,kingPos)) return true;
    else if(util_sides_check_king(grid,side,kingPos)) return true;
    return false;
}