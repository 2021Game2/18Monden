#ifndef CCOIN_H
#define CCOIN_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
#include "CCollider.h"
#include "CEffect2.h"

/*
アイテムクラス
キャラクタクラスを継承
*/
class CCoin : private CCharacter {
private:

	int Time;

	//コライダ
	CCollider mCollider;

public:
	//コンストラクタ
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();

	static CCoin *spThis;

	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

	void Render();

	void ColliderRender();

	int CoinRender;
};

#endif