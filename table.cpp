#include "table.h"

#include <fstream>

void writeTable(std::ostream& out, int row[], int numCols)
{
    /// writes a single table to a stream
    for(int i = 0; i< numCols; i++)
    {
        out<<row[i]<<" ";
    }
    out<<std::endl;    
}

void saveTables(int table[][9], int numRows)
{
    ///saves tables in table array to a file
    std::fstream outFile;
    outFile.open("tables.txt", std::ios::out);
    outFile<<numRows<<std::endl;
    for(int i=0; i<numRows; i++)
    {
        writeTable(outFile, table[i],9);
    }
    outFile.close();
}

void readTable(std::istream& in, int row[], int numCols)
{
    ///reads a single table row from a line in a stream
    for (int i = 0; i < numCols; ++i)
    {
        int value;
        in >> value;
        row[i] = value;
    }
}

void printAvailibility(std::ostream& out, int table[][9], int numRows, int party)
{
    /// prints the availability of tables based on party size
    for(int i=0; i<numRows; i++)
    {
        out<<"\t"<<i<<"\t"<<table[i][0];
        if(party>2&&party<=4)
        {
            if(table[i][4]==0)
            {
                out<<"\t"<<4<<std::endl;
                continue;
            }
            else
            {
                out<<"\tNA"<<std::endl;
            }
        }
        else if(party > 4 && party <= 8)
        {
            if(table[i][8]==0)
            {
                out<<"\t"<<8<<std::endl;
                continue;
            }
            else
            {
                out<<"\tNA"<<std::endl;
            }
        }
        else
        {
            int counter = 0;
            for(int j=1; j<9; j++)
            {
                if(j==4 || j==8)
                {
                    continue;
                }
                else if(table[i][j]==0)
                {
                    out<<"\t"<<j;
                    counter ++;
                }
            }
            if(counter == 0)
            {
                out<<"\tNA";
            }
            out<<std::endl;
        }
    }
    
}


bool insertReservedTable(int table[][9], int numRows, int time, int party, int RID)
{
    /// adds a reservation to the table array
    for(int i=0; i<numRows; i++)
    {
        if(table[i][0]==time)
        {
            if(party>2 && party <= 4)
            {
                if(table[i][4]==0)
                {
                    table[i][4]=RID;
                    std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                    saveTables(table,numRows);
                    return true;
                }
                
            }
            if(party>4 && party <=8)
            {
                if(table[i][8]==0)
                {
                    table[i][8]=RID;
                    std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                    saveTables(table,numRows);
                    return true;
                }
            }
            else
            {
                for(int j = 1; j<9; j++)
                {
                    if(j == 4 || j == 8)
                    {
                        continue;
                    }
                    else if(table[i][j]==0)
                    {
                        table[i][j]=RID;
                        std::cout<<"\n::::Reservation Completed::::"<<std::endl;
                        saveTables(table,numRows);
                        return true;
                    }
                }
            }
        }
    }
    
    std::cout<<"\n:::Table already Taken!!!:::"<<std::endl;
    return false;
    
    
}


bool releaseTable(int table[][9], int numRows, int RID)
{
    ///releases a table from the table array
    for(int i=0; i< numRows; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(table[i][j]==RID)
            {
                table[i][j]=0;
                std::cout<<"\n::::Reservation Removed::::"<<std::endl;
                saveTables(table,numRows);
                return true;
            }
        }
    }
    std::cout<<"\n::::Reservation Not Found::::"<<std::endl;
    return false;
    
}


void loadTables(std::istream& in, int table[][9], int numRows)
{
    ///loads tables from a stream
    for(int i=0; i<numRows; i++)
    {
        readTable(in, table[i], 9);
    }
}
