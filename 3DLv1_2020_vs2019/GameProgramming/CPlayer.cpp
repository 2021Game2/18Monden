//プレイヤークラスのインクルード
#include "CPlayer.h"
//キー入力クラスのインクルード
#include "CKey.h"
//
#include "CBullet.h"
//
#include "CTaskManager.h"
//
#include "CCollisionManager.h"
//
#include "CUtil.h"
//
#include "CEffect.h"

#include "CCamera.h"

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 15	//発射間隔


CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -28.0f), CVector(0.0f, -3.0f, -18.0f))
, mLine3(this, &mMatrix, CVector(25.0f, 0.0f, -8.0f), CVector(-30.0f, 0.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(-0.5f, 1.0f, -0.5f), 0.4f)
, mFireCount(0)
, mJump(0) //0はジャンプ可能
, yadd(0)
, CoinGet(0)
, BulletP(0)
, EnemyCoinGet(30)
{
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mText.LoadTexture("FontWhite.tga", 1, 64);
	mTag = EPLAYER;
}

//更新処理
void CPlayer::Update() {
	static CVector OldRotate = mRotation;

	if (Time > 0) {
		Time--;
	}

	//Aキー入力で回転
	if (CKey::Push('A')) {
		if (c < 0) {
			c -= c * 1 / 10;
		}

		if (c < 30) {
			c++;
		}
		mRotation.mY += c * 1/10;
	}
	//Aキー離すと慣性で回転
	if (CKey::Push('A') == false && c > 1) {
		c--;
		mRotation.mY += c * 1 / 20;
	}



	//Dキー入力で回転
	if (CKey::Push('D')) {
		if (c > 0) {
			c -= c * 1 / 10; //逆回転で慣性を抑える
		}

		if (c > -30) {
			c--;
		}
		mRotation.mY += c * 1/10;
	}
	//Dキー離すと慣性で回転
	if (CKey::Push('D') == false && c < -1) {
		c++;
		mRotation.mY += c * 1 / 20;
	}


	//Wキーで前進
	if (CKey::Push('W')) {
		if (t < 300) {
			t++;
		}
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}
	//キー離すと慣性で滑る
	if (CKey::Push('W') == false && t > 1) {
		t--;
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}

	//Sキーで後退
	if (CKey::Push('S')) {
		if (t > 0) {
			t -= t * 1/10; //ブレーキ
		}

		if (t > -90) {
			t--;
		}
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}

	//キー離すと慣性で滑る
	if (CKey::Push('S') == false && t < -1) {
		t++;
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}


	if (mFireCount > 0)
	{
		mFireCount--;
	}

	//CTransformの更新
	CTransform::Update();

	//ジャンプ
	if (mJump == 0 && CKey::Once('J'))
	{
		yadd = -0.2f;
		mJump++;
	}

		mPosition.mY -= yadd;
		yadd += 0.01f;


	//弾発射
	if (CKey::Push('I') && mFireCount == 0 && BulletP > 0) {
		BulletP--;
		mFireCount = FIRECOUNT;
		CBullet* bullet = new CBullet();
		bullet->mTag = EBULLETPLAYER;
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 0.0f, 50.0f) * mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
		//		TaskManager.Add(bullet);
	}

	//行列を更新
	CTransform::Update();

	Camera.SetTarget(mPosition);
	Camera.SetAddRotate(OldRotate - mRotation);
	OldRotate = mRotation;
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	//相手がサーチの時は戻る
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//自身のコライダタイプの判定
	switch (m->mType) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//yadd = 0;
				//mJump = 0;
				//位置の更新(mPosition + adjust)
				mPosition = mPosition - adjust * -1;
				//行列の更新
				CTransform::Update();
			}
		}
		break;
	case CCollider::ESPHERE:
		//相手のコライダが球コライダの時
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				if (o->mpParent->mTag == EBULLETENEMY) {
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
					if (CoinGet > 0) {
						CoinGet--;
					}
				}
			}
		}

		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				yadd = 0;
				mJump = 0;
				//位置の更新(mPosition + adjust)
				//mPosition = mPosition - adjust * -1;
				//行列の更新
				CTransform::Update();
			}
		}
		break;
	}
}
//衝突処理
void CPlayer::TaskCollision()
{
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PLAYER:%d", CoinGet);
	//文字列の描画
	mText.DrawString(buf, -300, 270, 16, 32);


	//Y座標の表示
	//文字列の設定
	sprintf(buf, "ENEMY:%d", EnemyCoinGet);
	//文字列の描画
	mText.DrawString(buf, 100, 270, 16, 32);

	//Y座標の表示
//文字列の設定
	sprintf(buf, "TIME:%d", Time/60);
	//文字列の描画
	mText.DrawString(buf, -40, 270, 8, 16);

	sprintf(buf, "BULLET:%d", BulletP);
	mText.DrawString(buf, -300, -270, 16, 32);

	//2Dの描画終了
	CUtil::End2D();

}