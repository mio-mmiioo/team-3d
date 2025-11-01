#include "BaseStage.h"
#include <assert.h>
#include "../Library/CsvReader.h"

namespace BASESTAGE {
	char filename[64]; // 生成するcurrentStage_のファイル名
	const float MODEL_WIDTH = 64.0f;
	const float MODEL_HEIGHT = 64.0f;
}

BaseStage::BaseStage()
{
	hModel_ = MV1LoadModel("data/model/RedBrickBlock.mv1");
	assert(hModel_ > 0);
	transform_.scale_ = VECTOR3(0.64f, 0.64f, 0.64f); // 試作品2Dとサイズを合わせる
	isPlayerAlive_ = true; // プレイヤー生きてる
	SetStageData(&baseStage_, "data/stage/baseStage.csv");
	SetStageData(&currentStage_, "data/stage/stage000.csv", 4);
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
			VECTOR3 pos1 = VECTOR3(x * 64.0f, (baseStage_.size() - y - 1) * 640.0f, 0);
			VECTOR3 pos2 = pos1 + VECTOR3(64.0f, 64.0f, 64.0f);
			if (c == 3) {
				MV1SetPosition(hModel_, pos1);
				MV1DrawModel(hModel_);
			}
			else if (c == 4)
			{
				MV1SetPosition(hModel_, pos1);
				MV1DrawModel(hModel_);
			}
		}
	}
}

int BaseStage::CheckRight(VECTOR3 pos)
{
	return 0;
}

int BaseStage::CheckLeft(VECTOR3 pos)
{
	return 0;
}

int BaseStage::CheckDown(VECTOR3 pos)
{
	return 0;
}

int BaseStage::CheckUp(VECTOR3 pos)
{
	return 0;
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
			int c = (*stage)[y][x];
			if (c == 1) {
				int px = x * BASESTAGE::MODEL_WIDTH + BASESTAGE::MODEL_WIDTH / 2.0f;
				int py = y * BASESTAGE::MODEL_HEIGHT + BASESTAGE::MODEL_HEIGHT / 2.0f;
				// Player生成
			}
		}
	}
}

void BaseStage::SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX)
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
			int c = (*stage)[y][x];
			baseStage_[y][x + startX] = (*stage)[y][x];
			/*if (c == 1) {
				int px = x * imageSize_.x + imageSize_.x / 2.0f;
				int py = y * imageSize_.y + imageSize_.y / 2.0f;
				new Player(VECTOR2(px, py));
			}*/
		}
	}
}

void BaseStage::CreateStage(int number, int level)
{
}

bool BaseStage::IsWall(VECTOR3 pos)
{
	return false;
}
