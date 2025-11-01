#pragma once
#include "../Library/Object3D.h"
#include <vector>

namespace BASESTAGE {
	const int LINE_POS_LEFT = 256;  // 左の線
	const int LINE_POS_RIGHT = 1024; // 右の線
}

class BaseStage : public Object3D {
public:
	BaseStage();
	~BaseStage();
	void Update() override;
	void Draw() override;

	// 当たり判定関連
	int CheckRight(VECTOR3 pos);
	int CheckLeft(VECTOR3 pos);
	int CheckDown(VECTOR3 pos);
	int CheckUp(VECTOR3 pos);

	void ChooseStage(int level); // ランダムな値を入手して次のステージを生成するための変数

	// ゲームオーバー条件関連
	void SetPlayerAlive(bool isAlive) { isPlayerAlive_ = isAlive; }

private:
	void SetStageData(std::vector<std::vector<int>>* stage, const char* filename); // ステージデータをセットするための関数
	void SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX);
	void CreateStage(int number, int level);		// ステージを作成する
	bool IsWall(VECTOR3 pos);						// 壁かどうか

	std::vector<std::vector<int>> baseStage_;		// ステージの両端の部分
	std::vector<std::vector<int>> currentStage_;	// 現在のステージ

	int hModel_;
	bool isPlayerAlive_;
};