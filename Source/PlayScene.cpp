#include "PlayScene.h"
#include "Axis.h"
#include "Camera.h"
#include "BaseStage.h"

PlayScene::PlayScene()
{
	new Camera();
	new BaseStage();
	new Axis();
}

PlayScene::~PlayScene()
{

}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_R)) {
		SceneManager::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [R]Key To Result", GetColor(255, 255, 255));
}
