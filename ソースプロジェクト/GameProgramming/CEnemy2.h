#ifndef CENEMY2_H
#define CENEMY2_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
/*
エネミークラス
キャラクタクラスを継承
*/
class CEnemy2 : private CCharacter {
private:
	int mFireCount;

	CVector mPoint;	//目標地点

	CCharacter *mpPlayer;	//プレイヤーのポインタ

	//モデルデータ
	static CModel mModel;

	//コライダ
	CCollider mCollider;
	CCollider mColSearch;	//サーチ用コライダ

	//コンストラクタ
	CEnemy2();
	//デストラクタ
	~CEnemy2();

	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();

public:
	//CEnemy(位置, 回転, 拡縮)
	CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale);
};

#endif
