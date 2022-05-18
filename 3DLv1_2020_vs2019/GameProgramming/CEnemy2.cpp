#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

#define OBJ "f16.obj"	//モデルのファイル
#define MTL "f16.mtl"	//モデルのマテリアルファイル

#define HP 3	//耐久値
#define VELOCITY 0.3f	//速度

CModel CEnemy2::mModel;	//モデルデータ作成

#define FIRECOUNT 15	//発射間隔


CEnemy2::CEnemy2()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.6f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 50.0f)
, mpPlayer(0)
, mHp(HP)
, mFireCount(0)
{
	mTag = EENEMY;
	mColSearch.mTag = CCollider::ESEARCH;	//タグ設定

	//モデルが無いときは読み込む
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
}


//コンストラクタ
//CEnemy(位置, 回転, 拡縮)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
	: CEnemy2()
{
	//位置、回転、拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;	//拡縮の設定
	CTransform::Update();	//行列の更新
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する
	//目標地点の設定
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//更新処理
void CEnemy2::Update() {

	/*CBullet *bullet = new CBullet();
	bullet->Set(0.1f, 1.5f);
	bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
	bullet->mRotation = mRotation;
	bullet->Update();

	CBullet *bullet2 = new CBullet();
	bullet2->Set(0.1f, 1.5f);
	bullet2->mPosition = CVector(10.0f, 0.0f, 10.0f) * mMatrix;
	bullet2->mRotation = mRotation;
	bullet2->Update();
*/
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx);
	float dy = vp.Dot(vy);
	float dz = vp.Dot(vz);
	float margin = 0.1f;

	if (dz < -margin)
	{
		mRotation.mY -= 2.0f;
	}
	else
	{
		if (dx > margin)
		{
			mRotation.mY += 2.0f;
		}
		else if (dx < -margin)
		{
			mRotation.mY -= 2.0f;
		}
	}


	if (mFireCount > 0)
	{
		mFireCount--;
	}

	if (dy > margin)
	{
		mRotation.mX -= 2.0f;
	}
	else if (dy < -margin)
	{
		mRotation.mX += 2.0f;
	}

	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();

	int r = rand() % 180;

	if (mpPlayer)
	{
		//プレイヤーまでのベクトルを求める
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx); //左ベクトルとの内積を求める
		float dy = vp.Dot(vy); //上ベクトルとの内積を求める
		//X軸のずれが2.0以下
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y軸のずれが2.0以下
			if (-2.0f < dy && dy < 2.0f && mFireCount == 0)
			{
				//弾を発射
				mFireCount = FIRECOUNT;
				CBullet* bullet = new CBullet();
				bullet->mTag = EBULLETENEMY;
				bullet->Set(0.1f, 0.5f);
				bullet->mPosition =
					CVector(0.0f, 0.0f, 10.0f) * mMatrix;
				bullet->mRotation = mRotation;
				bullet->Update();
			}
		}
	}
	mpPlayer = 0;
}
#include "CCoin.h"
//衝突処理
//Collision(コライダ１,コライダ２)
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	switch (m->mTag)
	{
	case CCollider::EBODY:
		//相手のコライダタイプの判定
		switch (o->mType)
		{
		case CCollider::ESPHERE:
			//相手のコライダが球コライダの時
				if (CCollider::Collision(m, o))
				{
					if (o->mpParent->mTag == EBULLETPLAYER && CPlayer::spThis->EnemyCoinGet > 0) {
						CPlayer::spThis->EnemyCoinGet--;
						new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
					}
				}
			break;
		case CCollider::ETRIANGLE: //三角コライダの時
			CVector adjust; //調整値
			//三角コライダと球コライダの衝突判定
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{	//衝突しない位置まで戻す
				mPosition = mPosition + adjust;
				mRotation.mY += 10;
				if (mRotation.mX != 0) {
					mRotation.mX = 0;
				}
			}
			break;
		}
		break;
	case CCollider::ESEARCH:
		if (o->mType == CCollider::ESPHERE) {
			if (o->mpParent->mTag == EPLAYER) {
				if (CCollider::Collision(m, o))
				{
					mpPlayer = o->mpParent;
				}
			}
			if (o->mpParent->mTag == ECOIN) {
				if (((CCoin*)o->mpParent)->CoinRender == 0) {
					if (CCollider::Collision(m, o)) {
						mpPlayer = o->mpParent;
						mPoint = mpPlayer->mPosition;
					}
				}
			}
		}
		break;
	}
}

void CEnemy2::TaskCollision()
{
	mCollider.ChangePriority();
	mColSearch.ChangePriority();
//	mCollider3.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
//	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);
}
