#ifndef guest_h
#define guest_h

#include <iostream>

void writeGuest(std::ostream& out, std::string guest[], int numCols);
void readGuest(std::istream& in, std::string guest[], int numCols);
void loadGuests(std::istream& in, std::string guests[][5], int numGuests);
void swapGuestItems(std::string guest[][5], int indexA, int indexB);
std::string getGuestPhone();
void sortGuests(std::string guests[][5], int numItems);
void saveGuests(std::string guests[][5], int numGuests);
bool guestExists(std::string guests[][5], int numGuests, std::string Gname);
void addGuest(std::string guests[][5], int numGuests, std::string row[], int numCols);
std::string genNewGuestID(std::string guests[][5], int numGuests);
std::string GuestNameByGID(std::string guests[][5],int numGuests,int GID);
int getGuestIndex(std::string guests[][5], int numGuests, std::string Gname);

#endif /* guest_h */
