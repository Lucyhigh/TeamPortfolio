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
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;
	
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

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
	setDefPlayFrame();

	return S_OK;
}

void Animation::release(void) {
	//! Do Notting
}

void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();
	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
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
			start += framX;  
			temp = start - (framX); 
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

void Animation::setFPS(int framePerSec, int maxSec)
{
	_frameUpdateSec = maxSec / static_cast<float>(framePerSec);
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;

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
