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
class CPlayer : public CCharacter , CVector{
private:
	int mFireCount;
	CCollider mCollider;
	CText mText;
	CText mCoinText;
	CColliderLine mLine; //線分コライダ
	CColliderLine mLine2;
	CColliderLine mLine3;

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

	float t = 1; //ダッシュ慣性

	float curve = 1; //カーブ慣性

	CVector OldRotate;

	CVector mPoint;	//目標地点

	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);

public:
	//デフォルトコンストラクタ
	CPlayer();

	static CPlayer* spThis;

	int Time = 60 * 60; //制限時間

	int CoinGet; //コイン獲得数

	int EnemyCoinGet; //敵コイン獲得数

	int BulletP; //弾数

};

#endif

