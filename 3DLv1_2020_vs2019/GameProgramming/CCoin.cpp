#include "CCoin.h"
#include "CTaskManager.h"
#define VELOCITY 0.11f
#include "CPlayer.h"
#include "CCollisionManager.h"

CCoin* CCoin::spThis = 0;

//コンストラクタ
CCoin::CCoin(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider(this, &mMatrix, CVector(0.0f, 0.2f, 0.0f), 0.7f)
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
	mTag = ECOIN;

	spThis = this;

	CTransform::Update();
	mCollider.ChangePriority();
	Time = 100;
	CoinRender = 0;

}


//更新処理
void CCoin::Update() {
	//行列を更新
	CTransform::Update();

	mRotation.mY += 3;

	if (CoinRender > 0)
	{
		CoinRender--;
	}
}

void CCoin::Render() {
	if (CoinRender == 0) {
		CCharacter::Render();
	}
}

//衝突処理
//Collision(コライダ１,コライダ２)
void CCoin::Collision(CCollider* m, CCollider* o) {
	if (CoinRender > 0) {
		return;
	}

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
						CoinRender = 300;
						CPlayer::spThis->CoinGet++;
					}
				}
				if (o->mpParent->mTag == EENEMY) {
					if (CCollider::Collision(o, m)) {
						CoinRender = 300;
						}
					}
				}
			}
			break;
			
		case CCollider::ETRIANGLE: //三角コライダの時
			CVector adjust; //調整値
			//三角コライダと球コライダの衝突判定
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{      //衝突しない位置まで戻す
				mPosition = mPosition + adjust;
				mRotation.mY++;
			}
			break;
	}
}

void CCoin::TaskCollision()
{
	//mCollider.ChangePriority();
	//CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}