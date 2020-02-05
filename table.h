#ifndef table_h
#define table_h

#include <iostream>

void readTable(std::istream& in, int row[], int numCols);
void writeTable(std::ostream& out, int row[], int numCols);
void saveTables(int table[][9], int numRows);
void printAvailibility(std::ostream& out, int table[][9], int numRows, int party);
bool insertReservedTable(int table[][9], int numRows, int time, int party, int RID);
bool releaseTable(int table[][9], int numRows, int RID);
void loadTables(std::istream& in, int table[][9], int numRows);

#endif /* table_h */
