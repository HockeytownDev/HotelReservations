#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "reserved.h"
#include "guest.h"
#include "table.h"

std::string getGuestExpiry();
std::string getGuestCC();
void printAllRID(std::ostream& out, int reservations[][5], int numRIDs, std::string guests[][5], int numGuests);
void cancelReservation(int reservations[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows);
int getTime(int numRows);
int getNumParty();
int menu();
void NewReservation(int reservation[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows);
bool reservationCycle();


int main(int argc, const char * argv[])
{
    bool loop = true;
    while(loop)
    {
        loop = reservationCycle();
    }
    return 0;
}

std::string getGuestExpiry()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    while(true)
    {
        int MM=0;
        int YYYY=0;
        std::cout<<"Enter phone(MM YYYY): ";
        std::cin>>MM;
        std::cin>>YYYY;
        
        ///validates the expiration data against the current date
        if(!std::cin || ((MM<1||MM>12)||(YYYY < (timePtr->tm_year+1900) || YYYY > 9999 ))||(YYYY==(timePtr->tm_year + 1900) && MM < (timePtr->tm_mon + 1)))
        {
            std::cout<<"\r:::Invalid Date!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            ///converts the year to 2 digits
            YYYY= YYYY%100;
            std::stringstream ss;
            ss<<MM<<'/'<<YYYY;
            return ss.str();
        }
        
    }
    
    return "";
}

std::string getGuestCC()
{
    ///prompts the user for a guests credit card number
    while(true)
    {
        std::string CC="";
        std::cout<<"Enter CC#(no punctuation): ";
        std::cin>>CC;
        if(!std::cin || CC.length()!=16 || !(CC.find_first_not_of( "0123456789" ) == std::string::npos))
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            
            return CC;
        }
        
    }
    
    return "";
}


void printAllRID(std::ostream& out, int reservations[][5], int numRIDs, std::string guests[][5], int numGuests)
{
    /// Prints all of the reservations to a stream
    out<<"\n\n:::::::::::::::::::::Reservations::::::::::::::::::::::::::\n"<<std::endl;
    out<<"\n\tIndex\tTime\t"<<std::left<<std::setw(20)<<"Name"<<"Party"<<std::endl;
    for(int i=0; i<numRIDs; i++)
    {
        std::cout<<"\t"<<i+1<<"\t"<<reservations[i][3]<<"\t"<<std::left<<std::setw(20)<<GuestNameByGID(guests,numGuests,reservations[i][1])<<"\t"<<reservations[i][2]<<std::endl;
    }
    
}

void cancelReservation(int reservations[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows)
{
    /// removes reservation from the different arrays
    printAllRID(std::cout, reservations, numRIDs, guests,numGuests);
    int selection =0;
    while(true)
    {
        std::cout<<"Select reservation to cancel(0-"<<numRIDs-1<<"): ";
        std::cin>>selection;
        if(!std::cin || (selection > (numRIDs) || selection< 1))
        {
            std::cout<<":::::Invalid Selection:::::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            break;
        }
    }
    int RID = reservations[selection-1][0];
    deleteRes(reservations, numRIDs, selection-1);
    releaseTable(tables, numRows, RID);
}

int getTime(int numRows)
{
    /// prompts user for time of a reservation
    int time=0;
    while(true)
    {
        std::cout<<"Select a time (0-"<<numRows-1<<")";
        std::cin>>time;
        if(!std::cin || (time<0 || time> (numRows-1)))
        {
            std::cout<<"\r:::::Invalid Selection:::::";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            time = (time * 100)+1700;
            return time;
        }
    }
    return time;
}

int getNumParty()
{
    /// prompts the user for the number in a guests party
    while(true)
    {
        int party=0;
        std::cout<<"Enter size of party: ";
        std::cin>>party;
        if(!std::cin || party > 8 || party < 1)
        {
            std::cout<<"\r:::Invalid Entry!!!:::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return party;
        }
        
    }
    return 0;
}

int menu()
{
    ///displays the menu and returns a users selection
    int selection=0;
    while(true)
    {
        std::cout<<"\n\n:::::::::::::::::::Main Menu::::::::::::::::::::\n"<<std::endl;
        std::cout<<"\t1:\tNew Reservation\n\t2:\tShow Reservations\n\t3:\tCancel Reservation\n\t4:\tExit"<<std::endl;
        std::cout<<"\nEnter Selection: ";
        std::cin>>selection;
        if(!std::cin || (selection < 1 || selection > 4))
        {
            std::cout<<"\r:::::Invalid Selection:::::";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            continue;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256,'\n');
            return selection;
        }
    }
}

void NewReservation(int reservation[][5], int numRIDs, std::string guests[][5], int numGuests, int tables[][9], int numRows)
{
    ///allows a user to enter a new reservation
    std::string Gname="";
    int GID=0;
    std::cout<<"Enter the guests last name: ";
    std::cin>>Gname;
    std::cin.clear();
    std::cin.ignore(256,'\n');
    if(!guestExists(guests,numGuests,Gname))
    {
        std::string Grow[5];
        Grow[0]=genNewGuestID(guests,numGuests);
        Grow[1]=Gname;
        Grow[2]=getGuestPhone();
        Grow[3]=getGuestCC();
        Grow[4]=getGuestExpiry();
        addGuest(guests,numGuests,Grow, 5);
        GID=atoi(Grow[0].c_str());
        
    }
    else
    {
        std::cout<<":::Guest already Exists :):::"<<std::endl;
        GID = atoi(guests[getGuestIndex(guests,numGuests,Gname)][0].c_str());
    }
    int Rrow[5];
    Rrow[0]=genNewResID(reservation, numRIDs);
    Rrow[1]=GID;
    Rrow[2]=getNumParty();
    
    int time =0;
    while(true)
    {
        printAvailibility(std::cout,tables, numRows, Rrow[2]);
        time = getTime(numRows);
        if(!insertReservedTable(tables,numRows,time,Rrow[2],Rrow[0]))
        {
            std::cout<<":::Time not available:::";
        }
        else
        {
            break;
        }
    }
    Rrow[3]=time;
    Rrow[4]=0;
    addReservation(reservation,numRIDs, Rrow, 5);
    
}

bool reservationCycle()
{
    ///handles the menu and general function calls
    int numGuests=0;
    int numRIDs=0;
    int numRows=0;
    std::fstream inFile;
    inFile.open("reserved.txt",std::ios::in);
    inFile>>numRIDs;
    if(!inFile)
    {
        std::cout<<":::File \"reserved.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    int reservations[numRIDs][5];
    loadReservations(inFile, reservations,numRIDs);
    inFile.close();
    inFile.open("guests.txt",std::ios::in);
    inFile>>numGuests;
    if(!inFile)
    {
        std::cout<<":::File \"guests.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    std::string guests[numGuests][5];
    loadGuests(inFile,guests,numGuests);
    inFile.close();
    inFile.open("tables.txt", std::ios::in);
    inFile>>numRows;
    if(!inFile)
    {
        std::cout<<"\n"<<numRows<<std::endl;
        std::cout<<":::File \"tables.txt\" missing or corrupted:::"<<std::endl;
        return false;
    }
    int tables[numRows][9];
    loadTables(inFile, tables, numRows);
    inFile.close();
    int selection = menu();
    switch(selection)
    {
        case 1:
            NewReservation(reservations,numRIDs,guests,numGuests, tables, numRows);
            return true;
        case 2:
            printAllRID(std::cout, reservations,numRIDs, guests, numGuests);
            return true;
        case 3:
            cancelReservation(reservations,numRIDs, guests, numGuests, tables, numRows);
            return true;
        case 4:
            return false;
    }
    return false;
}
