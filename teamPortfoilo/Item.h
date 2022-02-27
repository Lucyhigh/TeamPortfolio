#pragma once
#include "GameNode.h"

enum class Category
{
	// �κ��丮 ����
	NONE, 
	ROSARY, 
	RELIC, 
	QUEST, 
	MEACULPA, 
	BIBLE, 
	
	SKILL, COLLECTION
};

enum class ItemState
{
	// �̽���, ����, ����, �޾����� �̼���
	NONE, HAVE, SELECT, MEACULPANONE
};

/*
struct tagItemInfo
{
	int index; // ������ ����. ���߿� ���ǹ��� ���� ���
	int imageNum; // Y ������
	Category type;
	ItemState state; // �⺻ NONE
	float posX; // ���� ��ġ - �ݺ������� �κ��丮�� �ڸ���� -> ����ġ������ ī�װ��� ���� �ڸ� �ٲٱ�
	float posY;
	string name;	// ���������
	string script;  // ���������
	bool equip; // true�� �� ī�װ��� ��� ��ġ���� �̹��� ���� , ��ų�̸� �ر�
};
*/

class Item : public GameNode
{
public:
	Image* _img; // �̹��� ���Ͽ��� Ŭ���� �� ��. 

	int _index; // ������ ����. ���߿� ���ǹ��� ���� ��� 
	Category _category; // Y ������ 
	ItemState _state; // �⺻ NONE
	float _posX; // ���� ��ġ - �ݺ������� �κ��丮�� �ڸ���� -> ����ġ������ ī�װ��� ���� �ڸ� �ٲٱ� 
	float _posY;
	//	int _frameXNum; // �̹��� ��Ʈ���� �̹��� ��ġ 
	//	int _frameYNum;
	string _name;	// ��������� 
	string _script;  // ��������� 
	bool _equip; // true�� �� ī�װ��� ��� ��ġ���� �̹��� ���� , ��ų�̸� �ر� 
	int _hp; // �������ο� ���� ���� ����
	int _mp;
	int _att;
	int _dff;

	
public:
	Item() {}
	~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void draw(void);
	void animation(void);

	void setItemData(int index,	Category category, ItemState state,	float posX, float posY,
	string name,string script,bool equip,int hp, int mp, int att, int dff );

	// ������ ������� ����

	// ������ ���ÿ��� ����

	// 


};

/*
X �ִ� 17
--������ ���� Y1 
�����̸�->���ϸ��̼�
������ ����ĭ���� 2��,
�κ��丮 �� ������ĭ�� 3��
�κ��丮 ���� ������ĭ�� 7��

-------------
����ǰ Y2~Y5
�޾����� Y7
�⵵�� Y8
���� Y10~Y14
����Ʈ������ Y15~Y18
*/