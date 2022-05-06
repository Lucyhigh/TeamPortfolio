#include "Stdafx.h"
#include "TextDataManager.h"


HRESULT TextDataManager::init(void)
{


    return S_OK;
}

void TextDataManager::release(void) {
}

void TextDataManager::save(const char * fileName, vector<string> vStr)
{
    HANDLE file;
    char str[SAVE_BUFFER];
    DWORD write;
    strncpy_s(str, SAVE_BUFFER, vectorArrayCombine(vStr), SAVE_BUFFER - 1);

    file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    WriteFile(file, str, strlen(str), &write, NULL);

    CloseHandle(file);
}

char * TextDataManager::vectorArrayCombine(vector<string> vArray)
{
    char str[SAVE_BUFFER];

    ZeroMemory(str, sizeof(str));

    for (int i = 0; i < vArray.size(); i++)
    {
        strncat_s(str, SAVE_BUFFER, vArray[i].c_str(), SAVE_BUFFER - 1);

        if (i + 1 < vArray.size()) strcat_s(str, ",");
    }

    return str;
}

vector<string> TextDataManager::load(const char * fileName)
{
    HANDLE file;
    char str[LOAD_BUFFER];
    DWORD read;

    memset(str, 0, LOAD_BUFFER);
    file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

    ReadFile(file, str, LOAD_BUFFER, &read, NULL);
    CloseHandle(file);
    return charArraySeparation(str);
}

vector<string> TextDataManager::charArraySeparation(char charArray[])
{

    vector<string> vArray;
    char* temp;
    char* separator = ",";
    char* tokenA;
    char* tokenB;
    tokenA = strtok_s(charArray, separator, &tokenB);
    vArray.push_back(tokenA);
    
    while (NULL != (tokenA = strtok_s(NULL, separator, &tokenB)))
    {
        vArray.push_back(tokenA);
    }
    return vArray;
}

vector<string> TextDataManager::loadFstream(const char* fileName)
{
	std::ifstream in(fileName, ios::in);
	string str;
	string token;
	int size;

	if (in.is_open())
	{
		in.seekg(0, ios::end);
		size = in.tellg();
		str.resize(size);
		in.seekg(0, ios::beg);
		in.read(&str[0], size);
	}
	else
	{
		cout << "파일 로드 실패" << endl;
	}

	char* cstr = new char[size + 1];
	copy(str.begin(), str.end(), cstr);

	vector<string> vArray;
	char* separator = ",";
	char* tokenA;
	char* tokenB;

	tokenA = strtok_s(cstr, separator, &tokenB);
	vArray.push_back(tokenA);

	while (NULL != (tokenA = strtok_s(NULL, separator, &tokenB)))
	{
		vArray.push_back(tokenA);
	}

	delete[] cstr;

	return vArray;
}
