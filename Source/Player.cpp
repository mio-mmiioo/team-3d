#include "Player.h"
#include "BaseStage.h"
#include <assert.h>
#include "../Library/Input.h"

namespace PLAYER {
	float moveSpeed = 5.0f; // プレイヤーの移動速度 外部データ化するときに削除する
}

Player::Player(VECTOR3 pos)
{
	hModel_ = MV1LoadModel("data/model/WhiteChara.mv1");
	assert(hModel_ > 0);
	transform_.position_ = pos;
}

Player::~Player()
{
}

void Player::Update()
{
	VECTOR3 move;

	// キーの入力
	{
		if (Input::IsKeepKeyDown(KEY_INPUT_W))
		{
			move.y += 1;
		}
		else if (Input::IsKeepKeyDown(KEY_INPUT_S))
		{
			move.y -= 1;
		}
		else if (Input::IsKeepKeyDown(KEY_INPUT_D))
		{
			move.x += 1;
		}
		else if (Input::IsKeepKeyDown(KEY_INPUT_A))
		{
			move.x -= 1;
		}
	}

	transform_.position_ = transform_.position_ + move * PLAYER::moveSpeed;

	BaseStage* st = FindGameObject<BaseStage>();

	// ステージとの当たり判定・位置修正
	{
		// 左右のめり込み判定

		// 重力をかける
		
		// 上下のめり込み判定

		// 画面外にプレイヤーを行かせないように位置を修正
	}

	// クリア判定など
	{
		// ステージをクリアできたか確認

		// ステージをセット

		// 向かう方向を変更
	}
	MV1SetPosition(hModel_, transform_.position_);
}

void Player::Draw()
{
	MV1DrawModel(hModel_);

	// クリアカウント・レベルアップゲージ

	// HPの表示
}
