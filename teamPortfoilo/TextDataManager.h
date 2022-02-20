#pragma once
#include "SingletonBase.h"
/*
FILE* file;
#include <fstream>
파일에 종속적....인클루드 h가 없는걸 보니 C다.
//Text-쓰기쉽지만 보안취약, XML,
//INI-게임서 자주변경하는값들넣어줌 옵션같은거
//JSON-자바돼지자바스크립트오브젝트노테이트,
//입출력 관련아이들

시간없어서 텍스트만 할거임
*/
#define SAVE_BUFFER 128
#define LOAD_BUFFER 128
class TextDataManager : public SingletonBase<TextDataManager>
{
public:
    HRESULT init(void);
    void release(void);

    void save(const char* fileName, vector<string>vStr);
    char* vectorArrayCombine(vector<string> vArray);
    vector<string> load(const char* fileName);
    vector<string> charArraySeparation(char charArray[]);
public:
    TextDataManager() {}
    ~TextDataManager() {}
};

