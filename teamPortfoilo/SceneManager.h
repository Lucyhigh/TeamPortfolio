#pragma once

#include "SingletonBase.h"

class GameNode;

class SceneManager :public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;
private:
	//안전을 위한 static
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가
	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	//씬 교체
	HRESULT changeScene(string sceneName);

	//로딩 스레드 함수
	//보이드 포인트
	//LPVOID: void*형 (어떤 타입으로도 변환 가능)
	//friend 들어온 이유는 단 하나 씬 전환을 위해서  현재신 로딩신 레디신...
	//ㄴ 상속관계를 무시하기위해서임
	//콜백을 무시했음 컴파일러에선 무시됨
	friend DWORD CALLBACK loadingThread(LPVOID prc);
public:
	SceneManager() {}
	~SceneManager() {}
};

