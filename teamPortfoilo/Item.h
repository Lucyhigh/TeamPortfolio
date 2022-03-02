#pragma once
#include "GameNode.h"
#include "AniScene.h"

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

class Item : public GameNode
{
public:
	AniSceneItem* _ani; // ������ ���ý� �׵θ� �ִϸ��̼�

	Image* _slotImg; // �̹��� ���Ͽ��� Ŭ���� �� ��. 
	Image* _iconImg;

	int _index; // ������ ����. ���߿� ���ǹ��� ���� ��� 
	Category _category; // Y ������ 
	ItemState _state; // �⺻ NONE
	string _name;	// ��������� 
	string _script;  // ��������� 
	bool _equip; // true�� �� ī�װ��� ��� ��ġ���� �̹��� ���� , ��ų�̸� �ر� 
	int _hp; // �������ο� ���� ���� ����
	int _mp;
	int _att;
	int _dff;
	int _iconX; // ������ �̹��� ��ġ - �ݺ������� �κ��丮�� �ڸ���� -> ����ġ������ ī�װ��� ���� �ڸ� �ٲٱ� 
	int _iconY;
	float _posX; // ������ ��ġ 
	float _posY;
	float _equipPosX; // ���� ������ ��ġ 
	float _equipPosY;

public:
	Item() {}
	virtual ~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void draw(void);
	virtual void animation(void);

	Category getCategory() { return _category; }
	ItemState getState() { return _state; }
	int getIndex() { return _index; }
	string getName() { return _name; }
	string getScript() { return _script; }
	bool getEquip() { return _equip; }


	// �����ۻ���(����,����) / �������� / ������ �̹��� ��ġ 
	virtual void setItem(ItemState state);
	virtual void setEquip(bool state);
	virtual void setItem(float posX, float posY);



};
