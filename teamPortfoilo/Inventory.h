#pragma once
#include "GameNode.h"
#include "ItemManager.h"

#define INVENTEXT 3
#define ITEMTEXT 8
#define SCRIPT_MAX_LENGTH 20

class Inventory :public GameNode
{
private:

	AniSceneItem* _ani; // ������ ���ý� �׵θ� �ִϸ��̼�

	ItemManager* _im;

	int _categoryIndex;
	int _cateMax;
	tagOnlyText _InvenTEXT[INVENTEXT];
	

	tagText rosary[ROSARYMAX+5];
	tagText relic[3];
	tagText quest[3];
	tagText meaculpa[3];
	tagText bible[3];
	tagText skill[3];
	tagText collection[3];


	int _selection;

	int _cateItemMax;

	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Inventory() : _InvenTEXT
	{
		L"����",
		L"����",
		L"����",
	},
	rosary
	{
		L"��ѱ� ��",L"������ �ո� ���� �ΰ���. �μ����� ���쳪 ��ȸ���� ������ �ణ �÷��ش�.",
		L"�������� ȭ���� �Ҿ�",L"ȭ���ϰ� ���� �Ҿ�. ��ȸ���� ������ �÷��ش�.",
		L"������",L"������ ���� ������. ��ȸ���� ������ ��緮 �÷��ش�.",
		L" ",L" ",
				L" ",L" ",
						L" ",L" ",
								L" ",L" ",
										L" ",L" "

	},
	relic{	L" ",L" ",
			L" ",L" ",
			L" ",L" " },
	quest{
		L"����",L"�����׶�þƽ��� ���� ����. Į�� �� �Ʒ�. ��Ʋ�� ���� ������ �����ִ�.",
		L"������ ������ ��",L"���� ���ٲ��� ���� ���� ������ ������ ������ ���� û�� �޴��� �ɷ��ִ�.",
		L" ",L" ",
	},
	meaculpa{ L"������ ����",L"��ȸ���� ���� �������� ���ݷ��� �ణ �÷��ش�." ,
	L" ",L" ",
	L" ",L" " },
	bible{ L"���� �����",L"��ȸ���� �ڸ��� õ���� ���� ��ȯ�Ѵ�."
	L" ",L" ",
	L" ",L" " },
	skill{ L" ",L" ",
		  L" ",L" ",
		  L" ",L" " },
	collection{ L"������ Zicher�� ���߻�",L"īŸ����� ù ��° â ���� ������ �߰��� ���߻�"
	L" ",L" ",
	L" ",L" " }
	{}
	~Inventory() {}

	// �����ۻ���(����,����) / �������� / ������ �̹��� ��ġ 
							// ���� ī�װ� , ���� �������� ���� 
	bool checkSelect(int invenCategoryIndex, int selectionNum); // �����ߴ���?
	//void setItem(ItemState state);
	//void setItem(float posX, float posY);
	void setEquip(bool state, float x, float y);
	void setSelect() { _selection = 0; }

};

