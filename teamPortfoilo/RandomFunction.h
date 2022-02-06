#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction()
	{
		// API �����Լ� : GetTickCount (���� Ÿ�̸Ӱ� ������ �ȵǾ��פ��� ȯ���̸� ������ �����)
		// GetTickCount : OS �� ���õ� ���� ��� �ð��� üũ
		// - �⺻������ �и����� ������ üũ�� �����ϸ� �и����� ������ �ð� ���� ��ȯ�ϱ⿡ ������ �����ϴ�
		srand(GetTickCount());
	}

	HRESULT init() { return 0; }

	~RandomFunction() {}

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getline(int num)
	{
		return rand() % num;
	}


	//���ǻ��� 0�� ������ ������
	inline int getFromInTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	
	// ���ÿ� ���������
	float getFloat(void)
	{
		return rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd*(toNum - fromNum) + fromNum);
	}

private:

};