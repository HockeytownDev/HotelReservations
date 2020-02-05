
#include "reserved.h"

#include "guest.h"
#include "table.h"

#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

void swapReserveItems(int reservations[][5], int indexA, int indexB)
{
    ///swaps 2 items in reservation by row index
    for(int j = 0; j<5; j++)
    {
        int temp = reservations[indexA][j];
        reservations[indexA][j]=reservations[indexB][j];
        reservations[indexB][j]=temp;
    }
}

void sortReservations(int reservations[][5], int numItems)
{
    ///sorts the reservations by reservation number(the first element in each row of the array)
    std::qsort(reservations, numItems, sizeof(*reservations),
               [](const void *arg1, const void *arg2)->int
               {
                   int const *a = static_cast<int const*>(arg1);
                   int const *b = static_cast<int const*>(arg2);
                   return a[0] < b[0];
               });
}

void readReservation(std::istream& in, int reservation[], int numCols)
{
    ///reads a single reservation from a stream and loads it into the row reservation[]
    for(int i=0; i<numCols; i++)
    {
        in>>reservation[i];
    }
}

void writeReservation(std::ostream& out, int reservation[], int numCols)
{
    /// writes a single reservation to a stream
    for(int i = 0; i< numCols; i++)
    {
        out<<reservation[i]<<" ";
    }
    out<<std::endl;
}

int genNewResID(int reservation[][5],int numRIDs)
{
    ///finds either an empty ID to return or returns a new one
    bool found = false;
    int largest=0;
    int ID=0;
    sortReservations(reservation,numRIDs);
    ///looks for a gap in the sorted IDs
    for(int i=0; i<numRIDs-1; i++)
    {
        if(reservation[i][0] < reservation[i+1][0]-1)
        {
            ID = reservation[i][0]+1;
            found = true;
            break;
        }
        if(reservation[i][0]>largest)
        {
            largest = reservation[i][0];
        }
    }
    ///if a gap was not found, set ID to largest + 2 (plus one would set it equal to the last item in the list. The last item is never evaluated for largest because of the nature of the for loop used)
    if(!found)
    {
        return largest+2;
    }
    return ID;
}



void loadReservations(std::istream& in, int reservations[][5], int numRIDs)
{
    /// loads reservations to an array from a stream
    for(int i=0; i<numRIDs; i++)
    {
        readReservation(in, reservations[i], 5);
    }
    
}


void saveReservations(int reservations[][5], int numRIDs)
{
    /// saves the array reservations to a file
    std::fstream outFile;
    outFile.open("reserved.txt");
    outFile<<numRIDs<<std::endl;
    for(int i=0; i<numRIDs; i++)
    {
        writeReservation(outFile, reservations[i], 5);
    }
    outFile.close();
}


void deleteRes(int reservation[][5],int numRIDs, int index)
{
    /// swaps a reservation with the end of the reservation array, then saves the array numRIDs-1 to file
    swapReserveItems(reservation,index,numRIDs-1);
    saveReservations(reservation,numRIDs-1);
    
}


void addReservation(int reservations[][5], int numRIDs, int row[], int numCols)
{
    /// adds a reservation to the file
    int temp[numRIDs + 1][5];
    for(int i=0; i<numRIDs; i++)
    {
        for( int j=0; j<numCols; j++)
        {
            temp[i][j]=reservations[i][j];
        }
    }
    for(int i=0; i<numCols; i++)
    {
        temp[numRIDs][i]=row[i];
    }
    saveReservations(temp,numRIDs+1);
}
