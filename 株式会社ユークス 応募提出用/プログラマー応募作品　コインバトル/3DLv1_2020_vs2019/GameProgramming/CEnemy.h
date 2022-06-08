#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy : private CCharacter {
public:
	int mFireCount;

	CVector mPoint;	//目標地点

	int mHp;	//ヒットポイント

	CCharacter* mpPlayer;	//プレイヤーのポインタ

	//モデルデータ
	static CModel mModel;

	//コライダ
	CCollider mCollider;
	CCollider mColSearch;	//サーチ用コライダ

	//コンストラクタ
	CEnemy();
	//CEnemy(位置, 回転, 拡縮)
	CEnemy(const CVector& position, const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
};

#endif
