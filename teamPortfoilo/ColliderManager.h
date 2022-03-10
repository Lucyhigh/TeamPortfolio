#pragma once
#include "GameNode.h"

class ColliderManager  : public GameNode
{
	private:
		vector<pair<float,Image*>> _effect;
		inline void smashCollider();
		void addEffect(RECT);
		void updateEffect();

	public:
		ColliderManager();
		~ColliderManager();
		void update(void);
		void render(void);
};

