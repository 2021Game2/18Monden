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

#include "CSound.h"

#include "CSceneGame.h"

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 10	//発射間隔

//CSoundクラスのインクルード
#include "CSound.h"
//外部変数の参照の作成
extern CSound BombSe;
extern CSound shoot1Se;
extern CSound CarSe;
extern CSound BrakeSe;

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 10.0f, -30.0f), CVector(0.0f, 10.0f, 30.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 30.0f, 0.0f), CVector(0.0f, -1.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(25.0f, 10.0f, -8.0f), CVector(-30.0f, 10.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(-0.5f, 10.0f, -0.5f), 0.4f)
, mFireCount(0)
, mJump(0) //0はジャンプ可能
, BulletP(0)
, yadd(0)
, CoinGet(0)
, EnemyCoinGet(0)
{
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
	mTag = EPLAYER;
}

//更新処理
void CPlayer::Update() {

	CVector OldRotate = mRotation;

	//制限時間
	if (Time > 0) {
		Time--;
	}

	//Aキー入力で回転
	if (CKey::Push('A')) {
		if (curve < 0) {
			curve -= curve * 1 / 3; //逆回転で慣性を抑える
		}

		if (curve < 30) {
			curve++;
		}
		mRotation.mY += curve * 1/5;
	}
	//Aキー離すと慣性で回転
	if (CKey::Push('A') == false && curve > 1) {
		curve--;
		mRotation.mY += curve * 1 / 20;
	}



	//Dキー入力で回転
	if (CKey::Push('D')) {
		if (curve > 0) {
			curve -= curve * 1 / 3; //逆回転で慣性を抑える
		}

		if (curve > -30) {
			curve--;
		}
		mRotation.mY += curve * 1/5;
	}
	//Dキー離すと慣性で回転
	if (CKey::Push('D') == false && curve < -1) {
		curve++;
		mRotation.mY += curve * 1 / 20;
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

	if (t == 3) {
		CarSe.Repeat();
	}

	if (t == 1) {
		CarSe.Stop();
	}

	//Sキーで後退
	if (CKey::Push('S')) {
		if (t > 0) {
			t -= t * 1/10; //ブレーキ
			if (t > 200 && mJump == 0) {
				BrakeSe.Play(); //ブレーキ音再生
			}
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
	

		mPosition.mY -= yadd;
		yadd += 0.01f;


	//弾発射
	if (CKey::Push(VK_SPACE) && mFireCount == 0 && BulletP > 0) {
		shoot1Se.Play();
		BulletP--;
		mFireCount = FIRECOUNT;
		CBullet* bullet = new CBullet();
		bullet->mTag = EBULLETPLAYER;
		bullet->Set(0.1f, 1.5f);
		bullet->mPosition = CVector(0.0f, 10.0f, 50.0f) * mMatrix;
		bullet->mRotation = mRotation;
		bullet->Update();
		//		TaskManager.Add(bullet);
	}

	//行列を更新
	CTransform::Update();

	Camera->SetTarget(mPosition);
	Camera->SetAddRotate(OldRotate - mRotation);
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
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Resource\\exp.tga", 4, 4, 2);
					BombSe.Play();
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
				if (mJump == 0 && CKey::Once('J'))
				{
					yadd = -0.2f;
					mJump++;
				}
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

	//CSceneGame::sImagebullet.Draw(-370, -220, -300, -220, 400, 6000, 3000, 0);
	//CSceneGame::sImagejet.Draw(120, 230, 230, 330, 0, 600, 500, 0);
	//CSceneGame::sImageCar.Draw(-320, -140, 230, 310, 100, 2000, 800, 0);
	//CSceneGame::sImageTimer.Draw(-50, 50, 200, 300, 0, 255, 255, 0);

	//描画色の設定（緑色の半透明）
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//文字列編集エリアの作成
	char buf[64];

	//Y座標の表示
	//文字列の設定
	sprintf(buf, ":%d", CoinGet);
	//文字列の描画 
	mText.DrawString(buf, -150, 270, 16, 32);


	//Y座標の表示
	//文字列の設定
	sprintf(buf, ":%d", EnemyCoinGet);
	//文字列の描画
	mText.DrawString(buf, 250, 270, 16, 32);

	//Y座標の表示
//文字列の設定
	if (Time > 600) {
		sprintf(buf, "%d", Time / 60);
		//文字列の描画
		mText.DrawString(buf, -6, 240, 8, 16);
	}

	if (Time < 600) {
		sprintf(buf, "%d", Time / 60);
		//文字列の描画
		mText.DrawString(buf, 0, 240, 8, 16);
	}


	sprintf(buf, "%d", BulletP);
	mText.DrawString(buf, -200, -260, 16, 32);

	//2Dの描画終了
	CUtil::End2D();

}