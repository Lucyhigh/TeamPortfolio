#include "Stdafx.h"
#include "Animation.h"

Animation::Animation(void) :_frameNum(0),
_frameWidth(0),
_frameHeight(0),
_frameNumWidth(0),
_frameNumHeight(0),
_frameUpdateSec(0),
_elapsedSec(0),
_nowPlayIdx(0),
_isPlay(false),
_loop(false)
{
}

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
	// 가로 프레임 수
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;
	// 세로 프레임 수
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;
	// 총 프레임 수
	_frameNum = _frameNumWidth * _frameNumHeight;
	_frameList.clear();

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}
	//기본 프레임으로 셋팅
	setDefPlayFrame();

	return S_OK;
}

void Animation::release(void) {
	//! Do Notting
}

//기본 프레임 셋팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	//루프 돌건지
	_loop = loop;
	_playList.clear();
	if (reverse)
	{
		if (_loop)
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//올때 프레임
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//갈때 프레임
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//올때 프레임
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//원하는 프레임만 재생
void Animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (_loop)
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}
		for (int i = arrLen - 2; i > 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}
		for (int i = arrLen - 1; i >= 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}

}

// 구간을 잘라서 재생
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();
	if (reverse)
	{
		if (_loop)
		{
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}
			for (int i = end - 2; i > start; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}
			for (int i = end - 2; i >= start; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		for (int i = start; i < end; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animation::setPlayReverseFrame(int start, int end, int framX, bool loop)
{
	_loop = loop;
	_playList.clear();

	int temp = start - (framX); 
	int i = start;
	while (true)
	{
		i--;
		if (i == temp)
		{
			start += framX;   // 23 27 31
			temp = start - (framX); // 20 24 29 
			i = start;
		}
		_playList.push_back(i);

		if (i == end)
		{
			break;
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / static_cast<float>(framePerSec);
}

// 초당 프레임 갱신 횟수
void Animation::setFPS(int framePerSec, int maxSec)
{
	_frameUpdateSec = maxSec / static_cast<float>(framePerSec);
}

// 프레임 업데이트
void Animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트시간이 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_isPlay = false;

				}
			}
		}
	}
}

void Animation::AniStart(void)
{
	_isPlay = true;
	_nowPlayIdx = 0;
}

void Animation::AniStop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void Animation::AniPause(void)
{
	_isPlay = false;
}

void Animation::AniResume(void)
{
	_isPlay = true;
}
