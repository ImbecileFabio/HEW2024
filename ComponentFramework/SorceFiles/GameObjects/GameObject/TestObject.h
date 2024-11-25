#pragma once

#include "../GameObject.h"
class TestObject :
    public GameObject
{

	public:
		TestObject(GameManager* _gameManager);
		~TestObject(void);
		void UpdateGameObject(void) override;


	private:
		// ���L����R���|�[�l���g
		SpriteComponent* sprite_component_{};

};
