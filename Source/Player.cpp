#include "Player.h"
#include "BaseStage.h"
#include <assert.h>
#include "../Library/Input.h"

namespace PLAYER {
	float moveSpeed = 5.0f; // プレイヤーの移動速度 外部データ化するときに削除する
	const float WIDTH = 30.0f; // プレイヤーの横幅
	const float HEIGHT = 60.0f; // プレイヤーの縦幅
}

Player::Player(VECTOR3 pos)
{
	hModel_ = MV1LoadModel("data/model/WhiteChara.mv1");
	assert(hModel_ > 0);
	transform_.position_ = pos;
	transform_.scale_ = transform_.scale_ * 0.4f;
	MV1SetScale(hModel_, transform_.scale_);
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

	BaseStage* baseStage = FindGameObject<BaseStage>();

	// ステージとの当たり判定・位置修正
	{
		float push;

		// 左右のめり込み判定
		if (move.x > 0)
		{
			push = baseStage->CheckRight(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0));//右上
			if (push > 0)
				transform_.position_.x -= push;

			push = baseStage->CheckRight(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, 0, 0));//右下
			if (push > 0)
				transform_.position_.x -= push; // ＋１
		}
		if (move.x < 0)
		{
			push = baseStage->CheckLeft(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, PLAYER::HEIGHT , 0));//左上
			if (push < 0)
				transform_.position_.x -= push;

			push = baseStage->CheckLeft(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, 0, 0));//左下
			if (push < 0)
				transform_.position_.x -= push; // -1
		}

		// 重力をかける
		
		// 上下のめり込み判定 後に重力関連の処理

		if (move.y > 0)
		{
			push = baseStage->CheckUp(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0));//右上
			if (push > 0)
			{
				transform_.position_.y -= push + 1;
			}

			push = baseStage->CheckUp(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0));//左上
			if (push > 0)
			{
				transform_.position_.y -= push + 1;
			}
		}
		else
		{
			push = baseStage->CheckDown(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, 0 - 1, 0));//右下
			if (push < 0)
			{
				transform_.position_.y -= push - 1;
			}

			push = baseStage->CheckDown(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, 0 - 1, 0));//左下
			if (push < 0)
			{
				transform_.position_.y -= push - 1;
			}
		}

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

	// プレイヤーの当たり判定の枠
	VECTOR3 leftTop = transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0);
	DrawLine3D(leftTop, leftTop + VECTOR3(PLAYER::WIDTH, 0, 0), GetColor(255, 0, 0)); // 上辺
	DrawLine3D(leftTop, leftTop + VECTOR3(0, -PLAYER::HEIGHT, 0), GetColor(255, 0, 0)); // 左辺
	DrawLine3D(leftTop + VECTOR3(PLAYER::WIDTH, 0, 0), leftTop + VECTOR3(PLAYER::WIDTH, -PLAYER::HEIGHT, 0), GetColor(255, 0, 0)); // 右辺
	DrawLine3D(leftTop + VECTOR3(0, -PLAYER::HEIGHT, 0), leftTop + VECTOR3(PLAYER::WIDTH, -PLAYER::HEIGHT, 0), GetColor(255, 0, 0)); // 底辺

	// クリアカウント・レベルアップゲージ

	// HPの表示
}
