#include"Table.h"
#include"Cell.h"
#include<fstream>
#include<iostream>

Table::Table()
{
	cells = nullptr;
	cols = 0;
	rows = 0;
	nonBlankCells = 0;
}

Table::~Table() {
	clearCells();
}

void Table::loadFile(std::fstream & file)
{
	//clearCells();
	//cells = nullptr;
	char buffer[4096];
	unsigned short tempValue=0;
	rows = 0;
	cols = 0;
	// Get the max number of rows and columns.
	while (file) {
		file.getline(buffer, 4096);
		tempValue = cells_In_Row(buffer);
		if (tempValue > cols)
			cols = tempValue;
		++rows;
	}
	--rows;

	// Initialize 2D array of cells.
	cells = new Cell*[rows];
	
	for (int i = 0; i < rows; ++i) {
		cells[i] = new Cell[cols];
	}

	// Reset file pointer to its first position.
	file.clear();
	file.seekg(0);

	// Fill the cell array.
	unsigned rowIdx = 0;
	while (file) {
		file.getline(buffer, 4096);
		addRow(buffer,rowIdx);
		++rowIdx;
	}
}

void Table::addRow(const char * buffer, unsigned rowIdx)
{
	/// If we have this example row:
	/// ...,123,....
	/// It will send the index of the 1 and the 3 to the
	/// setValue cell method.
 	int idx = 0, stPt = 0, edPt = 0, cell_idx = 0;
	bool quoteFlag = 0;

	while (buffer[idx] != '\0'&&idx<strlen(buffer)) {
		if (buffer[idx] != ' ') {
			//---| Determine the start point and the end point.
			stPt = idx;

		
			
			// In case we stumble upon a comma from the start.
			if (buffer[stPt] == ',')
			{
				idx = stPt + 1;
				++cell_idx;
				continue;
			}

			edPt = stPt;

			if (buffer[edPt] == '"') {
				++edPt;
				while (buffer[edPt] != '\0') {
					if (buffer[edPt] == '"')
						if (buffer[edPt - 1] != '\\')
							break;
					++edPt;
				}
				++edPt;
			}
			else
				while (
					buffer[edPt] != ' ' && 
					buffer[edPt] != ',' && 
					buffer[edPt] != '\t'&&
					buffer[edPt] != '\0')
					++edPt;

			idx = edPt+1 ;

			cells[rowIdx][cell_idx].SetValue(buffer, stPt, edPt);
			++cell_idx;
			idx = edPt + 1;
		}
		else
			++idx;
	}
	
}

unsigned short Table::amountOfData(){
	return nonBlankCells;
}

void Table::printTo(std::ostream & strim)
{
	// Store the max cell length in each column.
	int* maxCellLen = new int[cols];
	for (int i = 0; i < cols; ++i)
		maxCellLen[i] = 0;
	
	for (int i = 0; i < cols; ++i)
		for (int j = 0; j < rows; ++j)
			if (cells[j][i].getLen() > maxCellLen[i])
				maxCellLen[i] = cells[j][i].getLen();
	// Print.
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (cells[i][j].getLen() < maxCellLen[j] && j > 0) {
				for (int e = 0; e < (maxCellLen[j] - cells[i][j].getLen()); ++e)
					strim << " ";
				cells[i][j].printValue(strim);
			}
			else {
				cells[i][j].printValue(strim);
				for (int e = 0; e < (maxCellLen[j] - cells[i][j].getLen()); ++e)
					strim << " ";

			}			
				strim<<" | ";
		}
		strim << "\n";
	}

	delete[] maxCellLen;
}

void Table::saveTo(std::ostream &strim){
	//strim.clear();
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cells[i][j].printValue(strim);
			strim << ",";
		}
		strim << "\n";
	}
}

void Table::setValue(const char * buffer, const unsigned _row, const unsigned _col)
{
	cells[_row][_col].SetValue(buffer);
}

unsigned Table::getRowCount() const
{
	return rows;
}

unsigned Table::getColCount() const
{
	return cols;
}


void Table::clearCells()
{
/*	for (int i = 0; i < rows; ++i) {
		delete[] cells[i];
	}*/
	
	delete[] cells;
}

// Number of cells in a row.
unsigned short Table::cells_In_Row(const char *row)
{
	int idx = 0, cells=0;
	bool quoteFlag = 0, contentFlag = 0;

	while (row[idx] != '\0') {
		if (row[idx] == ',' && !quoteFlag) {
			++cells;
			if (contentFlag) {
				contentFlag = 0;
			}
			++idx;
			continue;
		}

		if (row[idx] != ' ' ) {
			if(!contentFlag)
				++nonBlankCells;
			contentFlag = 1;

		}

		if (row[idx] == '"') {
			if (row[idx - 1] != '\\')
				if (quoteFlag)
					quoteFlag = 0;
				else
					quoteFlag = 1;
		}

		++idx;
	}
	++cells;

	return cells;
}


