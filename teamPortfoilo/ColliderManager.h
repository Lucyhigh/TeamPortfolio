#pragma once
class ColliderManager
{
	private:
		void smashCollider();
		void bodyCollider();

	public:
		ColliderManager();
		~ColliderManager();
		void init() { }
		void update(void);
		void render(void) { };
};

