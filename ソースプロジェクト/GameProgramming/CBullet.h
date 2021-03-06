#ifndef CBULLET_H
#define CBULLET_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//三角形クラスのインクルード
#include "CTriangle.h"
//
#include "CCollider.h"
/*
弾クラス
三角形を飛ばす
*/
class CBullet : public CCharacter {
private:
	CCollider mCollider;
	//生存時間
	int mLife;
	//三角形
	CTriangle mT;
	//描画
	void Render();
	//衝突処理
	//Collision(コライダ1, コライダ2)
	void Collision(CCollider *m, CCollider *o);
	void TaskCollision();

public:
	CBullet();
	//Set(幅, 奥行)
	void Set(float w, float d);
	//更新
	void Update();
};

#endif
