#pragma once

class BaseData;

class ColliderManager
{
	private:
		BaseData* _user;
		vector<BaseData*> _monster;

		void smashCollider();
		void bodyCollider();

	public:
		ColliderManager();
		~ColliderManager();
		void init(BaseData*,vector<BaseData*>);
		void update(void);
		void render(void) { };
};

