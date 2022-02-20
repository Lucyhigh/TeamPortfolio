#include "Stdafx.h"
#include "TextDataManager.h"


HRESULT TextDataManager::init(void)
{


    return S_OK;
}

void TextDataManager::release(void) {
}

//한줄짜리 데이터를 담아둘 것
//모든 데이터를 한줄단위로 잘라서 지정(자르기 좋게끔 만듬)
void TextDataManager::save(const char * fileName, vector<string> vStr)
{
    HANDLE file;
    char str[SAVE_BUFFER];
    DWORD write;
    /*
    strcpy:문자열 복사함수
            /기능이 확장됨 복사의 크기를 못정해서 나온것들
    strnpy_s:
    strnpy_s:
    strncpy_s:복사할 크기를 인자로 잡아줄수있다(길이값들어감)-끝에 자동으로 NULL 문자 삽입
    strlen

    */
    strncpy_s(str, SAVE_BUFFER, vectorArrayCombine(vStr), SAVE_BUFFER - 1);

    /*
    createFile(): 파일 입출력 장치를 만들거나 읽어온다.
    ㄴ 반환값은 사용할 수 있는 handle

    인자
    createFile(생성하거나 열 파일의 이름, 파일 접근타입,
    쉐어모드-열려진 파일의 공유여부-0은 공유안하겠다/자식에게 상속여부,
    파일 생성모드옵션, 파일의 옵션값설정(읽기 전용 등등), 파일에 대한 속성 값)

    CREATE_ALWAYS : 새로운 파일 생성, 동일한 파일 존재시 덮어쓰기하겠다.,
    FILE_ATTRIBUTE_NORMAL : 다른 속성값을 가지지 않겠다

    */
    file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    //writeFile(): 
    //1.CreateFile()에서 할당된 핸들
    //2. 파일에 쓰고 싶은 스트링
    //3. 얼마나 읽고 쓸것인지에 대한 크기
    //4. 얼마나 읽고 쓸것인지에 대한 결과값이 저장된다(주소)
    WriteFile(file, str, strlen(str), &write, NULL);

    //핸들은 항상 열면 닫아야한다...!
    CloseHandle(file);
}
//현재 사용할 데이터
//한줄짜리 데이터를 쉼표단위로 띄어서 저장하는 것이 가능하고 그것이 입출력을 할때 편하다.
char * TextDataManager::vectorArrayCombine(vector<string> vArray)
{
    char str[SAVE_BUFFER];

    ZeroMemory(str, sizeof(str));

    for (int i = 0; i < vArray.size(); i++)
    {
        //c_str(): 타입 캐스팅 연산자
        //string 자료형을 char*형으로 변환
        strncat_s(str, SAVE_BUFFER, vArray[i].c_str(), SAVE_BUFFER - 1);

        if (i + 1 < vArray.size()) strcat_s(str, ",");
        //strXXX_s:버퍼 오버플로우 문제로 복사할 크기를 명확하게 잡을 수 있게 추가된 함수***
    }

    return str;
}

vector<string> TextDataManager::load(const char * fileName)
{
    HANDLE file;
    char str[LOAD_BUFFER];
    DWORD read;

    memset(str, 0, LOAD_BUFFER);
    //
    //OPEN_EXISTING:존재하면 연다.
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
    //token : 컴파일러가 인식할 수 있는 기본 요소
    //        연산자,식별, 문장 부호 등등...
    char* tokenA;
    char* tokenB;
    //strtok_s(): 문자열을 토큰으로 분리한다
    //strtok( 문자열을 토큰으로 분리하고 싶은 배열의 메모리 주소, 
    //        분리 사용될 분리 문자,
    //        잘라내기한 후 남은 문자열의 메모리 주소   )
    //자른 놈은 토큰B가 들고있을거임
    tokenA = strtok_s(charArray, separator, &tokenB);
    vArray.push_back(tokenA);
    
    while (NULL != (tokenA = strtok_s(NULL, separator, &tokenB)))
    {
        vArray.push_back(tokenA);
    }
    return vArray;
}