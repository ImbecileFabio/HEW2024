#pragma once

#include "../GameObject.h"
class BackGround :
    public GameObject
{

	public:
		BackGround(GameManager* _gameManager);
		~BackGround(void);

		void InitGameObject(void) override;
		void UpdateGameObject(void) override;


	private:
		// 所有するコンポーネント
		class RenderComponent* sprite_component_{};

};

