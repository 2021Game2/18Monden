#ifndef CBULLETITEM_H
#define CBULLETITEM_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
#include "CCollider.h"
#include "CEffect.h"

/*
キャラクタクラスを継承
*/
class CBulletItem : private CCharacter{
private:
	//更新処理
	void Update();

	//コライダ
	CCollider mCollider;

	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);
	int mFx;
	int mFy;

	void TaskCollision();

public:
	//コンストラクタ
	CBulletItem(CModel* model, CVector position, CVector rotation, CVector scale);
};

#endif