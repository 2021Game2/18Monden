#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//
#include "CBullet.h"
//
#include "CColliderLine.h"
//
#include "CText.h"

#include "CCollider.h"
/*
プレイヤークラス
キャラクタクラスを継承
*/
class CPlayer : public CCharacter {
public:
	int mFireCount;
	CCollider mCollider;
	CText mText;
	static CPlayer *spThis;
	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2;
	CColliderLine mLine3;
	//デフォルトコンストラクタ
	CPlayer();
//	CBullet bullet;
	//更新処理
	void Update();
	//衝突処理
	void Collision(CCollider *m, CCollider *o);
	//衝突処理
	void TaskCollision();
	//描画処理
	void Render();

	int mJump; //ジャンプフラグ
	//重力
	float x = 300.0f;
	float y = 300.0f;
	float yadd;

	//ダッシュ慣性
	float t = 1;

	float c = 1;

	int CoinGet;

	int BulletP;
};

#endif

