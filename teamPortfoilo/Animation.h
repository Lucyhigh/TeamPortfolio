#pragma once

class Animation
{
private:
	typedef vector <POINT> _vFrameList;
	typedef vector <INT> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;			
	int _frameWidth;		
	int _frameHeight;		
	int _frameNumWidth;		
	int _frameNumHeight;	

	float _frameUpdateSec;	
	float _elapsedSec;		

	bool _isPlay;
	bool _loop;
	DWORD _nowPlayIdx;

public:

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);


	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void setPlayReverseFrame(int start, int end, int framX, bool loop);

	void setFPS(int framePerSec);
	void setFPS(int framePerSec, int maxSec);

	void frameUpdate(float elpasedTime);
	void AniStart(void);
	void AniStop(void);
	void AniPause(void);
	void AniResume(void);

	inline bool isPlay(void) { return _isPlay; }

	inline POINT getFramePos(void) 
	{ 
		if (0 > _nowPlayIdx || _nowPlayIdx >= size(_playList)) 
			return POINT{ 0,0 };
		int frameListIndex = _playList[_nowPlayIdx];
		if (0 > frameListIndex || frameListIndex >= size(_frameList))
			return POINT{ 0,0 };

		return _frameList[_playList[_nowPlayIdx]]; 
	}
	
	inline int getFrame(void) { return _nowPlayIdx; }

	inline int getFrameIdx(void)
	{
		POINT ptPOS = getFramePos();
		int frameX = ptPOS.x / _frameWidth;
		int frameY = ptPOS.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }

	Animation();
	~Animation() {};
};



