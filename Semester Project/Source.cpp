///
/// OOP project from the second semester.
/// Load a "table" that is basically a TXT file.
/// Each row in the TXT file has "cellls" separated by commas
///	Each cell can be either a string, integer or double. Strings should
/// be put quotes: "[string]"
///
#include<iostream>
#include<fstream>
#include"Cell.h"
#include"Table.h"

/// Things that don't work:
///	saving (for some reason), formula support, saveas

int main() {	
	char buffer[256], address[256];
	Table tab;
	std::fstream file;
	bool fileIsOpen = 0;
	unsigned tempRow=0, tempCol=0;

	std::cout
		<< "Welcome to MonkeyExcel!\n"
		<< "Type 'help' to view the commands.\n";

	bool I_dont_wanna_leave = 1;

	while (I_dont_wanna_leave) {
		std::cout << "\n> ";
		std::cin >> buffer;

		// Open File.
		if (strcmp(buffer, "open")==0){
			std::cin.ignore();
			std::cin.getline(address,256);
			if (fileIsOpen)
				std::cout << "\nError: file is already opened.\n";
			else {
				file.open(address, std::fstream::in | std::fstream::out);
				if (!file)
					std::cout << "\nError: cannot open file.\n";
				else {
					tab.loadFile(file);
					std::cout << "\nSuccesfully opened file.\n";
					fileIsOpen = 1;
				}
			}
		}
		// Close File.
		else 
			if (strcmp(buffer, "close") == 0) {
				if (fileIsOpen) {
					std::cout << "\Closing file.\n";
					file.close();
					fileIsOpen = 0;
				}
				else
					std::cout << "\nError: No file opened.\n";
			}
		
		// Print.
		else
			if (strcmp(buffer, "print") == 0) {
					if (fileIsOpen)
						tab.printTo(std::cout);
					else
						std::cout << "\nError: No file opened.";
				}
		// Edit
		else 
			if (strcmp(buffer, "edit") == 0) {
				if (fileIsOpen) {
					std::cin >> tempRow >> tempCol;
					std::cin.ignore();
					std::cin.getline(buffer, 256);

					buffer[strlen(buffer)] = '\0';

					if (tempRow <= tab.getRowCount() && tempCol <= tab.getColCount()) {
						std::cout
							<< "\nSetting Value at ( " << tempRow << " , " << tempCol << " ).\n";

						tab.setValue(buffer, tempRow - 1, tempCol - 1);
					}
					else
						std::cout << "\nError: Parameters are out of bounds.\n";
				}
				else
					std::cout << "\nError: No file opened.\n";
		}
		// Save.
		else if (strcmp(buffer, "save") == 0){
				if (fileIsOpen) {
					file.close();
					file.open(address, std::fstream::trunc);
					tab.saveTo(file);
					std::cout << "\nSaved changes.\n";
				}
				else
					std::cout << "\nError: No file opened.\n";			
			}
		// Help.
		else if (strcmp(buffer, "help") == 0) {
			printf("\n");
			printf("open [file path]           Open a file in the select directory\n");
			printf("close                      Close the file.\n");
			printf("print                      Print the table\n");
			printf("edit [row] [col] [value]   Edit the value in a given cell. It can be int, double or string\n");
		}
		else
			if (strcmp(buffer, "exit") == 0) {
				std::cout << "\nConfirm exit [ Y / N ]: ";
				std::cin >> buffer;
				if (buffer[0] == 'Y' || buffer[0] == 'y')
					I_dont_wanna_leave = false;
			}
	}

	return 0;
}



/*
E:\Projects\sp\test.txt
*/