#include<iostream>
#include"Cell.h"

///
/// Constructor.
///
Cell::Cell()
	: val(""),
	  size(0),
	  isInt(0), 
	  isBlank(1),
	  isDouble(0), 
	  isString(0),
	  isFormula(0), 
      printSize(0)
{

}

///
/// Destructor.
///
Cell::~Cell() {
	delete[] val;
}

///
/// Set cell value: get a string and evaluate accordingly.
///
void Cell::SetValue(const char* _val) {
	clearVal();
	size = std::strlen(_val);
	val = new char[size+1];
	strcpy_s(val, size+1, _val);
	evaluate();
	setSize();
}

void Cell::SetValue(const char * _val, const size_t _size)
{
	clearVal();
	size = _size;
	val = new char[size+1];

	for (size_t i = 0; i < _size; ++i)
		this->val[i] = _val[i];

	val[size] = '\0';
	evaluate();
	setSize();
}
void Cell::SetValue(const char * _val, const unsigned stPt, const unsigned edPt)
{
	clearVal();

	size = edPt - stPt;
	val = new char[size + 1];

	for (int i = 0; i < size; ++i)
		this->val[i] = _val[stPt+i];

	val[size] = '\0';
	evaluate();
	setSize();
}
///
/// Return the string;
///
const char * Cell::getValue() const{
	return val;
}

// Output to a stream.
void Cell::printValue(std::ostream &striim)
{
	int idx = 0;
	if (val[0] == '"')
		idx = 1;
	while (idx < size) {
		if (val[idx] == '\\' && idx < size - 1)
			if (val[idx + 1] == '"') {
				++idx;
				continue;
			}
		
		if (val[idx] == '"'&&idx == size - 1) {
			++idx;
			continue;
		}
		striim << val[idx];
		++idx;
	}
}

///
/// Convert to double.
///
double Cell::toDouble(const char * _val)
{
	size_t dot = 0;
	while (_val[dot] != '.')
		++dot;
	
	double powerOfTen = 1, value = 0;

	for (size_t i = 0; i < size - dot+1; ++i)
		powerOfTen /= 10;

	for (size_t i = 0; i < size; ++i) {
		if (i != dot) {
			value += (_val[i] - '0') * powerOfTen;
			powerOfTen *= 10;
		}

	}

	return value;
}

///
/// Clear value array.
///
void Cell::clearVal()
{
	if (!isBlank) {
		delete[] val;
		val = nullptr;
	}
}

///
/// Determine the type of the contents.
///
void Cell::evaluate()
{
	switch (val[0]) {
		case '"':
			isBlank = 0;
			isString = 1;
			return;
		case '=':
			isBlank = 0;
			isFormula = 1;
			return;
		default:
			break;
	}

	if (isBlank) {
		if (val[0] <= '9' && val[0] >= '0') {
			for (size_t i = 0; i < size; ++i) {
				if (val[i] == '.') {
					isDouble = 1;
					isBlank = 0;
				}
			}
			if (!isDouble) {
				isInt = 1;
				isBlank = 0;
			}
		}
	}
}

// Set the size of the printable string. (ignore quotes)
void Cell::setSize(){
	int quoteCnt = 0, idx = 1;
	if (isString)
		quoteCnt = 2;

	while (val[idx] != '\0') {
		if (val[idx] == '"' && val[idx - 1] == '\\')
			++quoteCnt;

		++idx;
	}

	printSize = strlen(val) - quoteCnt;
}
///
/// Is Int/Double/String/Formula ?
///
bool Cell::is_Double() const{
	return isDouble;
}


bool Cell::is_Int() const {
	return isInt;
}


bool Cell::is_Formula() const {
	return isFormula;
}


bool Cell::is_String() const {
	return isString;
}
///
/// Get stuff.
///
double Cell::getDoubleValue() const{
	return doubleValue;
}


size_t Cell::getLen() const{
	return printSize;
}


int Cell::getIntValue() const{
	return 0;
}
