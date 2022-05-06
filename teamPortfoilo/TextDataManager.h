#pragma once
#include "SingletonBase.h"
#define SAVE_BUFFER 1280
#define LOAD_BUFFER 1280
class TextDataManager : public SingletonBase<TextDataManager>
{
public:
    HRESULT init(void);
    void release(void);

    void save(const char* fileName, vector<string>vStr);
    char* vectorArrayCombine(vector<string> vArray);
    vector<string> load(const char* fileName);
    vector<string> charArraySeparation(char charArray[]);
	vector<string> loadFstream(const char* fileName);

public:
    TextDataManager() {}
    ~TextDataManager() {}
};

