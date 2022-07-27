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
	//コライダ
	CCollider mCollider;

	//更新処理
	void Update();

	void Render();

	//衝突処理
//Collision(コライダ１,コライダ２)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

public:
	static CCoin* spThis;

	//コンストラクタ
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//デストラクタ
	~CCoin();

	int CoinRender;
};

#endif