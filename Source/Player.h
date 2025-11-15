#pragma once
#include "../Library/Object3D.h"

class Player : public Object3D {
public:
	Player(VECTOR3 pos);
	~Player();
	void Update() override;
	void Draw() override;
private:
	bool IsClear();

	int hp_;
	float moveSpeed_;

	bool isOnGround_; // 地面についている→true
	float velocityY_; // y方向に加わる力
	float gravity_; // 重力
	float jumpHeight_;
	float jumpV0_;

	// 音関連
	void SoundShuttleRun();

	float timer_;			// 9の倍数にして
	float soundTimer_;		// timer_を9等分したくらいの時間
	int soundCounter_;		// 音階で鳴らすためのカウンター

	// カウント関連
	bool isGoRight_;		// true→右に進んでいる false→左に進んでいる
	int counter_;			// ステージをクリアしたカウント
};