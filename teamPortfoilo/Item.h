#pragma once

enum class Category
{
	// �κ��丮 ����
	NONE, ROSARY, RELIC, QUEST, MEACULPA, BIBLE, SKILL, COLLECTION
};

class Item
{
public:
	Item() {}
	~Item() {}

	int index;
	Category type;
	string name;
	string script;
	int imageNum;


	void setItemData();

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