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
	
	float myadd; //重力

	float mSpeed; //ダッシュ慣性

	float mCurve; //カーブ慣性

	CVector OldRotate;

	CVector mPoint;	//目標地点

	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);

public:
	//デフォルトコンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();

	static CPlayer* spThis;

	int mTime;

	int mCoinGet; //コイン獲得数

	int mEnemyCoinGet; //敵コイン獲得数

	int mBulletP; //弾数

};

#endif

