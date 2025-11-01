#include "BaseStage.h"

namespace BASESTAGE {
	char filename[64]; // ê∂ê¨Ç∑ÇÈcurrentStage_ÇÃÉtÉ@ÉCÉãñº
}

BaseStage::BaseStage()
{
}

BaseStage::~BaseStage()
{
}

void BaseStage::Update()
{
}

void BaseStage::Draw()
{
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
}

void BaseStage::SetStageData(std::vector<std::vector<int>>* stage, const char* filename, int startX, int startY)
{
}

void BaseStage::CreateStage(int number, int level)
{
}

bool BaseStage::IsWall(VECTOR3 pos)
{
	return false;
}
