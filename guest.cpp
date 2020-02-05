#include "guest.h"

#include <fstream>
#include <sstream>

void writeGuest(std::ostream& out, std::string guest[], int numCols)
{
    /// writes a single guest to a stream
    for (int i = 0; i < numCols; ++i)
    {
        out << guest[i];
        if (i < numCols - 1)
        {
            out << " ";
        }
    }
    out << std::endl;
}

void readGuest(std::istream& in, std::string guest[], int numCols)
{
    ///reads a single guest from a line in a stream
    for(int i=0; i<numCols; i++)
    {
        in>>guest[i];
    }
}

void loadGuests(std::istream& in, std::string guests[][5], int numGuests)
{
    /// loads guests from a stream
    for(int i=0; i<numGuests; i++)
    {
        readGuest(in, guests[i], 5);
    }
}

void swapGuestItems(std::string guest[][5], int indexA, int indexB)
{
    ///swaps 2 items in guest by row index
    std::string aux[5];
    for (int i = 0; i < 5; ++i)
    {
        aux[i] =guest[indexA][i];
        guest[indexA][i] = guest[indexB][i];
        guest[indexB][i] = aux[i];
    }
}

std::string getGuestPhone()
{
    ///prompts the user for a guests phone number
    while(true)
    {
        std::string phone="";
        std::cout<<"Enter phone(no punctuation): ";
        std::cin>>phone;
        if(!std::cin || phone.length()!=10 || !(phone.find_first_not_of( "0123456789" ) == std::string::npos))  /// checks phone number is a series of digits of the right length
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            
            return phone;
        }
        
    }
    return "";
}




void sortGuests(std::string guests[][5], int numItems)
{
    ///sorts the guests by guest number
    for(int i=1; i<numItems; i++)
    {
        for(int j=0; j<numItems-i; j++)
        {
            if(atoi(guests[j][0].c_str())>atoi(guests[j+1][0].c_str()))
            {
                swapGuestItems(guests,j,j+1);
            }
        }
    }
    
}


void saveGuests(std::string guests[][5], int numGuests)
{
    /// saves guest array to a file
    std::fstream outFile;
    outFile.open("guests.txt", std::ios::out);
    outFile<<numGuests<<std::endl;
    for(int i=0; i<numGuests; i++)
    {
        writeGuest(outFile, guests[i], 5);
    }
    outFile.close();
}

bool guestExists(std::string guests[][5], int numGuests, std::string Gname)
{
    ///checks to see if a guest exists by their last name
    for( int i=0; i<numGuests; i++)
    {
        if (guests[i][1]==Gname)
        {
            return true;
        }
    }
    return false;
    
}

void addGuest(std::string guests[][5], int numGuests, std::string row[], int numCols)
{
    ///adds a guest held in row[] to a temp array and saves the new array to file
    std::string temp[numGuests+1][5];
    for(int i = 0; i<numGuests; i++)
    {
        for(int j = 0; j<numCols; j++)
        {
            temp[i][j]=guests[i][j];
        }
    }
    for(int i = 0; i<numCols; i++)
    {
        temp[numGuests][i]=row[i];
    }
    saveGuests(temp, numGuests+1);
    
}

std::string genNewGuestID(std::string guests[][5], int numGuests)
{
    ///finds either an empty ID to return or returns a new one
    bool found = false;
    int largest=0;
    int ID=0;
    sortGuests(guests,numGuests);
    ///looks for a gap in the sorted IDs
    for(int i=0; i<numGuests-1; i++)
    {
        if(atoi(guests[i][0].c_str()) < atoi(guests[i+1][0].c_str())-1)
        {
            ID = atoi(guests[i][0].c_str())+1;
            found = true;
            break;
        }
        if(atoi(guests[i][0].c_str())>largest)
        {
            largest = atoi(guests[i][0].c_str());
        }
    }
    ///if a gap was not found, set ID to largest + 1
    if(!found)
    {
        std::stringstream ss;
        ss<<largest+2;
        return ss.str();
    }
    std::stringstream ss;
    ss<<ID;
    return ss.str();
}

std::string GuestNameByGID(std::string guests[][5],int numGuests,int GID)
{
    /// returns a guests name given the GID
    for(int i=0; i<numGuests; i++)
    {
        if(atoi(guests[i][0].c_str())==GID)
        {
            return guests[i][1];
        }
    }
    return "Unknown";
}

int getGuestIndex(std::string guests[][5], int numGuests, std::string Gname)
{
    /// returns the index of a guest given guests name
    for(int i=0; i<numGuests; i++)
    {
        if(guests[i][1]==Gname)
        {
            return i;
        }
    }
    
    return 0;
}
