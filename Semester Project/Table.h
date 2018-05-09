#pragma once
#include"Cell.h"
#include<fstream>

class Table {
public:
	Table();
	~Table();

	void loadFile(std::fstream &);
	void addRow(const char* row, unsigned);
	unsigned short amountOfData();

	void printTo(std::ostream&);
	void saveTo(std::ostream&);
	void setValue(const char*, const unsigned, const unsigned);

	unsigned  getRowCount() const;
	unsigned  getColCount() const;

private:
	void clearCells();
private:
	unsigned  
		rows, 
		cols,
		nonBlankCells;
	
	Cell** cells;
	
private:
	unsigned short cells_In_Row(const char*);
};