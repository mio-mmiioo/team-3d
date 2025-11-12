#include "App.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Time.h"
#include "Input.h"
#include "../Source/Sound.h"
#include <DxLib.h>

void AppInit()
{
	ObjectManager::Init();
	SceneManager::Init();
	Time::Init();
	Sound::Init();
}

void AppUpdate()
{
	SceneManager::Update();
	ObjectManager::Update();
	Input::KeyStateUpdate();
}

void AppDraw()
{
	Time::Refresh();
	ObjectManager::Draw();
	SceneManager::Draw();
}

void AppRelease()
{
	Time::Release();
	SceneManager::Release();
	ObjectManager::Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}