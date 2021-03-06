#include "CBullet.h"
#include "CCollisionManager.h"

CBullet::CBullet()
: mLife(10)
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.3f)
{}

//幅と奥行きの設定
//Set(幅, 奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定→3
	mT.SetVertex(CVector(w, 0.0f, 0.0f), CVector(0.0f, 0.0f, -d), CVector(-w, 0.0f, 0.0f));
	//三角形の法線設定
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));
}

//更新
void CBullet::Update() {
	//生存時間の判定
	if (mLife-- > 0) {
		CTransform::Update();
		//mRotation.mY += 10;
		//位置更新
		mPosition = CVector(0.0f, 0.0f, 2.0f)* mMatrix;
	}
	else {
		//無効にする
		mEnabled = false;
	}
}

//描画
void CBullet::Render() {
	//DIFFUSE黄色設定
	float c[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画→12
	mT.Render(mMatrix);

	//mModelShuriken.Load("Shuriken4.obj", "Shuriken4.mtl");
	//mModelShuriken.Render(mMatrix);
}

//衝突処理
//Collision(コライダ1, コライダ2)
void CBullet::Collision(CCollider *m, CCollider *o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}

	//コライダのmとyが衝突しているか判定
	switch (o->mType)
	{
	case CCollider::ESPHERE:
		if (CCollider::Collision(m, o)) {
			if (o->mpParent->mTag == EPLAYER) {
				//衝突している時は無効にする
				mEnabled = false;
			}

			if (o->mpParent->mTag == EENEMY) {
				mEnabled = false;
			}
		}
		case CCollider::ETRIANGLE:
				if (o->mType == CCollider::ETRIANGLE) {
					CVector adjust;//調整用ベクトル
					//三角形と線分の衝突判定
					if (CCollider::CollisionTriangleSphere(o, m, &adjust))
					{
						mEnabled = false;
					}
				}
		
	}

	return;

	if (m->mType == CCollider::ESPHERE
		&& o->mType == CCollider::ESPHERE)
	{
		switch (o->mTag)
		{
		case CCollider::ESEARCH:
			break;
		default:
			//コライダのmとyが衝突しているか判定
			if (CCollider::Collision(m, o)) {
				//衝突している時は無効にする
				mEnabled = false;
			}
		}
	}
}
void CBullet::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

