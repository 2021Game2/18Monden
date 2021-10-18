#ifndef CMAKIMONO_H
#define CMAKIMONO_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
#include "CCollider.h"
#include "CEffect.h"

/*
キャラクタクラスを継承
*/
class CMakimono : public CCharacter{
public:
	//コンストラクタ
	CMakimono(CModel* model, CVector position, CVector rotation, CVector scale);
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
};

#endif