#include "BaseStage.h"
#include <assert.h>
#include "../Library/CsvReader.h"
#include "Player.h"

namespace BASESTAGE {
	char filename[64];					// 生成するcurrentStage_のファイル名
	const float MODEL_WIDTH = 64.0f;	// モデルの横幅
	const float MODEL_HEIGHT = 64.0f;	// モデルの縦幅
	const float MODEL_SCALE = 0.64f;	// モデルのスケール
	const float STAGE_START_X = 4;		// 切り替わるステージの開始位置のx座標
	const float STAGE_START_Y = 4;		// 切り替わるステージの開始位置のy座標
}

BaseStage::BaseStage()
{
	hModel_ = MV1LoadModel("data/model/RedBrickBlock.mv1");
	assert(hModel_ > 0);
	transform_.scale_ = transform_.scale_ * BASESTAGE::MODEL_SCALE; // 試作品2Dとサイズを合わせる
	MV1SetScale(hModel_, transform_.scale_);
	isPlayerAlive_ = true; // プレイヤー生きてる
	SetStageData(&baseStage_, "data/stage/baseStage.csv");
	SetStageData(&currentStage_, "data/stage/stage000.csv", BASESTAGE::STAGE_START_X, BASESTAGE::STAGE_START_Y);
}

BaseStage::~BaseStage()
{
}

void BaseStage::Update()
{
}

void BaseStage::Draw()
{
	for (int y = 0; y < baseStage_.size(); y++) {
		for (int x = 0; x < baseStage_[y].size(); x++) {
			int c = baseStage_[y][x];
			VECTOR3 pos1 = VECTOR3(x * BASESTAGE::MODEL_WIDTH + BASESTAGE::MODEL_WIDTH / 2, (baseStage_.size() - y - 1) * BASESTAGE::MODEL_HEIGHT, 0.0f);
			switch (baseStage_[y][x])
			{
			case 2:
				MV1SetPosition(hModel_, pos1);
				MV1DrawModel(hModel_);
				break;
			// データの種類が増えた場合ここに追加
			}			
		}
	}

	// 基準線を描画 不要になったら消す
	for (int y = 0; y < baseStage_.size() + 1; y++) {
		for (int x = 0; x < baseStage_[0].size() + 1; x++) {
			VECTOR3 pos1 = { x * BASESTAGE::MODEL_WIDTH, 0, -32.0f };
			VECTOR3 pos2 = { x * BASESTAGE::MODEL_WIDTH, baseStage_.size() * BASESTAGE::MODEL_HEIGHT, -32.0f };
			VECTOR3 pos3 = { 0, y * BASESTAGE::MODEL_HEIGHT, -32.0f };
			VECTOR3 pos4 = { baseStage_[0].size() * BASESTAGE::MODEL_WIDTH, y * BASESTAGE::MODEL_HEIGHT, -32.0f };
			DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
			DrawLine3D(pos3, pos4, GetColor(255, 255, 255));
		}
	}
}

float BaseStage::CheckRight(VECTOR3 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}

	int x = pos.x / BASESTAGE::MODEL_WIDTH;
	float dx = pos.x - x * BASESTAGE::MODEL_WIDTH;
	return dx + 1;
}

float BaseStage::CheckLeft(VECTOR3 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}

	int x = pos.x / BASESTAGE::MODEL_WIDTH;
	float dx = pos.x - x * BASESTAGE::MODEL_WIDTH;
	return dx - BASESTAGE::MODEL_WIDTH;
}

float BaseStage::CheckDown(VECTOR3 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}

	int y = pos.y / BASESTAGE::MODEL_HEIGHT;
	float dy = pos.y - y * BASESTAGE::MODEL_HEIGHT;

	return dy - BASESTAGE::MODEL_HEIGHT;
}

float BaseStage::CheckUp(VECTOR3 pos)
{
	if (IsWall(pos) == false) {
		return 0;
	}

	int y = pos.y / BASESTAGE::MODEL_HEIGHT;
	float dy = pos.y - y * BASESTAGE::MODEL_HEIGHT;

	return dy + 1;
}

void BaseStage::ChooseStage(int level)
{
}

void BaseStage::SetStageData(std::vector<std::vector<int>>* stage, const char* filename)
{
	CsvReader* csv = new CsvReader(filename);
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		stage->push_back(mapLine);
	}
	delete csv;

	for (int y = 0; y < stage->size(); y++) {
		for (int x = 0; x < (*stage)[y].size(); x++) {
			int c = (*stage)[stage->size() - y - 1][x];
			if (c == 0) {
				float posX = x * BASESTAGE::MODEL_WIDTH;
				float posY = y * BASESTAGE::MODEL_HEIGHT;
				new Player(VECTOR3(posX, posY, 0.0f));
			}
		}
	}
}

void BaseStage::SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX, int startY)
{
	stage->clear();
	CsvReader* csv = new CsvReader(filename);
	for (int line = 0; line < csv->GetLines(); line++) {
		std::vector<int> mapLine;
		for (int column = 0; column < csv->GetColumns(line); column++) {
			int c = csv->GetInt(line, column);
			mapLine.push_back(c);
		}
		stage->push_back(mapLine);
	}
	delete csv;

	for (int y = 0; y < stage->size(); y++) {
		for (int x = 0; x < (*stage)[y].size(); x++) {
			baseStage_[stage->size() - y - 1 + startY][x + startX] = (*stage)[stage->size() - y - 1][x];
		}
	}
}

void BaseStage::CreateStage(int number, int level)
{
	// playerの現在のレベルなどからステージを選択する player作成後にnextStageNumberに値を代入する 
	// ※引数のどちらかはいらなくなる予定
	int nextStageNumber = 0;

	sprintf_s<64>(BASESTAGE::filename, "data/stage/stage%03.csv", nextStageNumber);
	SetStageData(&currentStage_, BASESTAGE::filename, BASESTAGE::STAGE_START_X, BASESTAGE::STAGE_START_Y);
}

bool BaseStage::IsWall(VECTOR3 pos)
{
	// チップの場所を特定する
	int x = pos.x / BASESTAGE::MODEL_WIDTH;
	int y = pos.y / BASESTAGE::MODEL_HEIGHT;
	if (y < 0 || y >= baseStage_.size()) {
		return false;
	}
	if (x < 0 || x >= baseStage_[y].size()) {
		return false;
	}
	// チップの番号を見て、壁かどうか確定する
	switch (baseStage_[baseStage_.size() - y - 1][x]) {
	case 0:
	case 1:
		return false;
	}
	return true;
}
