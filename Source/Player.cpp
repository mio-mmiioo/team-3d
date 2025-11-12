#include "Player.h"
#include "BaseStage.h"
#include <assert.h>
#include "../Library/Input.h"
#include "Screen.h"

// 外部データ化するときに削除される
namespace PLAYER {
	const float MOVE_SPEED = 5.0f;		// プレイヤーの移動速度
	const float WIDTH = 30.0f;			// プレイヤーの横幅
	const float HEIGHT = 60.0f;			// プレイヤーの縦幅

	const float GRAVITY = 0.098f;
	const int JUMP_BLOCK_HEIGHT = 3;	// ブロック何個分

	// プレイヤーの移動制限
	const float LEFT_LIMIT = 0.0f + PLAYER::WIDTH / 2;					// 左( x )
	const float RIGHT_LIMIT = (float)Screen::WIDTH - PLAYER::WIDTH / 2; // 右( x )
}

Player::Player(VECTOR3 pos)
{
	hModel_ = MV1LoadModel("data/model/WhiteChara.mv1");
	assert(hModel_ > 0);
	transform_.position_ = pos;
	transform_.scale_ = transform_.scale_ * 0.4f;
	MV1SetScale(hModel_, transform_.scale_);

	moveSpeed_ = PLAYER::MOVE_SPEED;
	isOnGround_ = false;
	velocityY_ = 0.0f;
	gravity_ = PLAYER::GRAVITY;
	jumpHeight_ = (float)PLAYER::JUMP_BLOCK_HEIGHT * 64.0f; // ( 飛べる高さ ) = ( マスの数 ) * ( 1マスのサイズ )
	jumpV0_ = -sqrtf(2.0f * gravity_ * jumpHeight_);

}

Player::~Player()
{
}

void Player::Update()
{
	VECTOR3 move;

	// キーの入力
	{
		// ジャンプ
		if (isOnGround_ == true)
		{
			if (Input::IsKeepKeyDown(KEY_INPUT_SPACE))
			{
				velocityY_ = jumpV0_;
			}
		}

		// 左右移動
		if (Input::IsKeepKeyDown(KEY_INPUT_D))
		{
			move.x += 1;
		}
		else if (Input::IsKeepKeyDown(KEY_INPUT_A))
		{
			move.x -= 1;
		}
	}

	// 位置のセット
	transform_.position_ = transform_.position_ + move * moveSpeed_;
	
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
		transform_.position_.y -= velocityY_;
		velocityY_ += gravity_;
		isOnGround_ = false;

		// 上下のめり込み判定
		if (velocityY_ < 0.0f)
		{
			push = baseStage->CheckUp(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0));//右上
			if (push > 0)
			{
				velocityY_ = 0.0f;
				transform_.position_.y -= push + 1;
			}

			push = baseStage->CheckUp(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, PLAYER::HEIGHT, 0));//左上
			if (push > 0)
			{
				velocityY_ = 0.0f;
				transform_.position_.y -= push + 1;
			}
		}
		else
		{
			push = baseStage->CheckDown(transform_.position_ + VECTOR3(PLAYER::WIDTH / 2, 0 - 1, 0));//右下
			if (push < 0)
			{
				isOnGround_ = true;
				velocityY_ = 0.0f;
				transform_.position_.y -= push;
			}

			push = baseStage->CheckDown(transform_.position_ + VECTOR3(-PLAYER::WIDTH / 2, 0 - 1, 0));//左下
			if (push < 0)
			{
				isOnGround_ = true;
				velocityY_ = 0.0f;
				transform_.position_.y -= push;
			}
		}

		// 画面外にプレイヤーを行かせないように位置を修正 (x軸のみ)
		{
			if (transform_.position_.x < PLAYER::LEFT_LIMIT)
			{
				transform_.position_.x = PLAYER::LEFT_LIMIT;
			}
			else if (transform_.position_.x > PLAYER::RIGHT_LIMIT)
			{
				transform_.position_.x = PLAYER::RIGHT_LIMIT;
			}
		}
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

	// こえる線の表示
	VECTOR3 lineLeftTop = { BASESTAGE::LINE_POS_LEFT, 0, -32 };
	VECTOR3 lineRightTop = { BASESTAGE::LINE_POS_RIGHT, 0, -32 };
	DrawLine3D(lineLeftTop, lineLeftTop + VECTOR3(0, Screen::HEIGHT, 0), GetColor(255, 0, 0));
	DrawLine3D(lineRightTop, lineRightTop + VECTOR3(0, Screen::HEIGHT, 0), GetColor(255, 0, 0));

	// クリアカウント・レベルアップゲージ

	// HPの表示
}
