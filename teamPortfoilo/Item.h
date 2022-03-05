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
	Image* _equipImg;

	int _index; // ��ü ������ �� n��° ������ ����. ���߿� ���ǹ��� ���� ��� 
	int _cateIndex; // ī�װ��� n��° ������
	Category _category; // Y ������ 
	ItemState _state; // �⺻ NONE
	string _name;	// ��������� 
	string _script;  // ��������� 
	bool _equip; // true�� �� ī�װ��� ��� ��ġ���� �̹��� ���� , ��ų�̸� �ر� 
	bool _isSelect;
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
	string _script2;  // ����Ʈ ������ �� ����
	//LPCWSTR  _testScript;
public:
	Item() {}
	virtual ~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void draw(void);

	Category getCategory() { return _category; }
	ItemState getState() { return _state; }
	int getIndex() { return _index; }
	int getCateIndex() { return _cateIndex; }
	string getName() { return _name; }
	string getScript() { return _script; }
	//LPCWSTR getTextScript() { return _testScript; }
	bool getEquip() { return _equip; }
	bool getSelect() { return _isSelect; }

	// �����ۻ���(����,����) / �������� / ������ �̹��� ��ġ 
	void setItemState(ItemState state);
	void setItem(float posX, float posY);
	void setEquip(bool state, float x, float y);
	void setSelect(bool state) { _isSelect = state; }


};
