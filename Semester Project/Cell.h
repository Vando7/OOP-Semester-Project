#pragma once
#include<fstream>

class Cell {
public:
	Cell();
	~Cell();

public:
	void SetValue(const char* _val);
	void SetValue(const char* _val, const size_t size);
	void SetValue(const char* _val, const unsigned, const unsigned);

	bool is_Int() const;
	bool is_Double() const;
	bool is_String() const;
	bool is_Formula() const;
	
	size_t getLen() const;
	int getIntValue() const;
	void printValue(std::ostream&);
	double getDoubleValue() const;
	const char* getValue() const;

private:
	bool isInt, isDouble, isFormula, isString, isBlank;
	double doubleValue;
	char* val;
	int intValue;
	size_t size;

	size_t printSize;

private:
	int toInt(const char* _val);
	void clearVal();
	void evaluate();
	void setSize();
	double toDouble(const char* _val);
};