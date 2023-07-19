#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 128

int readInt(const char* section, const char* keyword, int defaultValue, const char* filePath)
{
	return GetPrivateProfileInt(section, keyword, defaultValue, filePath);
}

bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath)
{
	return GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath);
}

double readDouble(const char* section, const char* keyword, double defaultValue, const char* filePath)
{
	char tmp[CHARBUFF];
	readChar(section, keyword, "None", tmp, filePath);
	if (strcmp("None", tmp) == 0) return defaultValue;
	else return strtod(tmp, NULL);
}

void getCurrentDirectory(char* currentDirectory)
{
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

bool writeChar(const char* section, const char* keyword, const char* returnValue, const char* filePath)
{
	return WritePrivateProfileString(section, keyword, returnValue, filePath);
}

bool writeInt(const char* section, const char* keyword, int returnValue, const char* filePath)
{
	char tmp[CHARBUFF];
	sprintf_s(tmp, "%d", returnValue);
	return writeChar(section, keyword, tmp, filePath);
}

bool writeDouble(const char* section, const char* keyword, double returnValue, const char* filePath)
{
	char tmp[CHARBUFF];
	sprintf_s(tmp, "%f", returnValue);
	return writeChar(section, keyword, tmp, filePath);
}