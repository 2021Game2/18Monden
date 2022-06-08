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
public:
	//コンストラクタ
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();

	//コライダ
	CCollider mCollider;

	static CCoin *spThis;

	//衝突処理
	//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);

	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動wwwwwwww

	void TaskCollision();

	int Time;

	int CoinRender;

	void Render();

	void ColliderRender();
};

#endif