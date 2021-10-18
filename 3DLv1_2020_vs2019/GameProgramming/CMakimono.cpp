#include "CMakimono.h"
#include "CTaskManager.h"
#define VELOCITY 0.11f;
#include "CPlayer.h"
#include "CCollisionManager.h"

//コンストラクタ
CMakimono::CMakimono(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider(this, &mMatrix, CVector(0.15f, 0.0f, 0.0f), 1.0f)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
	mTag = EMAKIMONO;
}


//更新処理
void CMakimono::Update() {
	//行列を更新
	CTransform::Update();

}

//衝突処理
//Collision(コライダ１,コライダ２)
void CMakimono::Collision(CCollider* m, CCollider* o) {
	switch (m->mTag)
	{
	case CCollider::EBODY:
		//相手のコライダタイプの判定
		switch (o->mType)
		{
		case CCollider::ESPHERE:
			if (o->mTag == CCollider::EBODY) {
				if (o->mpParent->mTag == EPLAYER) {
					if (CCollider::Collision(o, m)) {
						mEnabled = false;
					}
				}
			}
			break;
		}
	}
}

void CMakimono::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}