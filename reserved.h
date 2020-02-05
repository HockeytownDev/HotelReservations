//
//  reserved.h
//  part_b
//
//  Created by Sergio Vieira on 29/05/2018.
//  Copyright © 2018 Sergio Vieira. All rights reserved.
//

#ifndef reserved_h
#define reserved_h

#include <iostream>

void swapReserveItems(int reservations[][5], int indexA, int indexB);
void sortReservations(int reservations[][5], int numItems);
void readReservation(std::istream& in, int reservation[], int numCols);
void writeReservation(std::ostream& out, int reservation[], int numCols);
int genNewResID(int reservation[][5],int numRIDs);
void loadReservations(std::istream& in, int reservations[][5], int numRIDs);
void saveReservations(int reservations[][5], int numRIDs);
void deleteRes(int reservation[][5],int numRIDs, int index);
void addReservation(int reservations[][5], int numRIDs, int row[], int numCols);

#endif /* reserved_h */
