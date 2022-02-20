#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
//널포인트 선언이유를 알아야함
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID prc)
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	// 현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	// 로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;
	// 로딩클래스를 만들어 로딩씬과 연결 필요
	return 0;
}
HRESULT SceneManager::init(void)
{
	 SceneManager::_currentScene = nullptr;
	 SceneManager::_loadingScene = nullptr;
	 SceneManager::_readyScene = nullptr;
	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	// 로딩 씬 >> 교체 대기 중인 씬 >> 현재 씬
	//4개이상(스타트신,게임씬,상점씬,보스씬,엔딩씬,,,,,)
	//많아도 10개?일거기 때문에
	//for 문을 쓰는게 맞는지 while문이 맞는지를 고민하는것보다
	//반복횟수가 많지 않기때문에 반복문보다는 do while로 하는게 나음
	//현재씬 뽑고 나서 생각하겠다!
	for (; miSceneList != _mSceneList.end();)
	{	
		//안전을 위한 이중묻기
		if (miSceneList->second != nullptr)
		{
			if(miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
	/*
	for each(auto scene in _mSceneList)
	{

	}
	SAFE_DELETE(miSceneList->second);
	miSceneList = _mSceneList.erase(miSceneList);
	*/
}

void SceneManager::update(void)
{
	// 현재 씬이 존재하면 현재 씬만 갱신
	if(_currentScene)_currentScene->update();
}

void SceneManager::render(void)
{
	// 현재 씬이 존재하면 현재 씬만 렌더
	if (_currentScene)_currentScene->render();
}
// 씬 추가
GameNode * SceneManager::addScene(string sceneName, GameNode * scene)
{
	//일단 물어보자
	//씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

GameNode * SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return nullptr;
}
//씬 변경
HRESULT SceneManager::changeScene(string sceneName)
{
	//변경하려고 하는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;
	//신을 초기화를 하고 바꿔주고있다.
	//상점으로 나갔다가 다시 마을로 왔을때 돈이 만원이었는데 0원일수도?
	//변수의 초기화가 발생하지않도록 전역처리하던 전역변수로 하던 잘 짜라
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

