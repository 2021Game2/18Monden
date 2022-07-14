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

#define _USE_MATH_DEFINES

#include <math.h>

#include <stdio.h>

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 10	//発射間隔

//CSoundクラスのインクルード
#include "CSound.h"
//外部変数の参照の作成
extern CSound BombSe; //被弾Se
extern CSound shoot1Se; //発射Se
extern CSound CarSe; //車Se
extern CSound BrakeSe; //急ブレーキSe
extern CSound CountDownSe; //カウントダウンSe

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 10.0f, -30.0f), CVector(0.0f, 10.0f, 30.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 30.0f, 0.0f), CVector(0.0f, -1.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(25.0f, 10.0f, -8.0f), CVector(-30.0f, 10.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(-0.5f, 10.0f, -0.5f), 0.4f)
, mFireCount(0)
, mJump(0) //0はジャンプ可能
, mBulletP(0)
, myadd(0)
, mTime(60 * 60)
, mCoinGet(0)
, mEnemyCoinGet(0)
, mSpeed(0)
, mCurve(0)
{
	spThis = this;
	//テクスチャファイルの読み込み（1行64列）
	mCoinText.LoadTexture("Resource\\FontGold1.png", 1, 64);
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
	mTag = EPLAYER;
}

CPlayer::~CPlayer()
{
}

//更新処理
void CPlayer::Update() {
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	CVector vp = mPoint - mPosition;

	CVector OldRotate = mRotation;

	//制限時間
	if (mTime > 0) {
		mTime--;
	}

	//Aキー入力で左回転
	if (CKey::Push('A')) {
		if (mCurve < 0) {
			mCurve -= mCurve * 1 / 3; //逆回転で慣性を抑える
		}

		if (mCurve < 30) {
			mCurve++;
		}
		mRotation.mY += mCurve * 1/5;
	}
	//Aキー離すと慣性で回転
	if (CKey::Push('A') == false && mCurve > 1) {
		mCurve--;
		mRotation.mY += mCurve * 1 / 20;
	}



	//Dキー入力で右回転
	if (CKey::Push('D')) {
		if (mCurve > 0) {
			mCurve -= mCurve * 1 / 3; //逆回転で慣性を抑える
		}

		if (mCurve > -30) {
			mCurve--;
		}
		mRotation.mY += mCurve * 1/5;
	}
	//Dキー離すと慣性で回転
	if (CKey::Push('D') == false && mCurve < -1) {
		mCurve++;
		mRotation.mY += mCurve * 1 / 20;
	}

	//Wキーで前進
	if (CKey::Push('W')) {
		if (mSpeed < 300) {
			mSpeed++;
		}
		//Z軸方向に1進んだ値を回転移動させる
		mPosition = CVector(0.0f, 0.0f, 0.05f * mSpeed) * mMatrix;
	}
	//キー離すと慣性で滑る
	if (CKey::Push('W') == false && mSpeed > 1) {
		mSpeed--;
		mPosition = CVector(0.0f, 0.0f, 0.05f * mSpeed) * mMatrix;
	}

	if (mSpeed == 3) {
		CarSe.Repeat();
	}

	if (mSpeed == 1) {
		CarSe.Stop();
	}

	//Sキーで後退
	if (CKey::Push('S')) {
		if (mSpeed > 0) {
			mSpeed -= mSpeed * 1/10; //ブレーキ
			if (mSpeed > 200 && mJump == 0) {
				BrakeSe.Play(); //ブレーキ音再生
			}
		}


		if (mSpeed > -90) {
			mSpeed--;
		}
		mPosition = CVector(0.0f, 0.0f, 0.05f * mSpeed) * mMatrix;
	}

	//キー離すと慣性で滑る
	if (CKey::Push('S') == false && mSpeed < -1) {
		mSpeed++;
		mPosition = CVector(0.0f, 0.0f, 0.05f * mSpeed) * mMatrix;
	}


	if (mFireCount > 0)
	{
		mFireCount--;
	}

	//CTransformの更新
	CTransform::Update();

	//落下
	mPosition.mY -= myadd;
	myadd += 0.01f;


	//弾発射
	if (CKey::Push(VK_SPACE) && mFireCount == 0 && mBulletP > 0) {
		shoot1Se.Play();
		mBulletP--;
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

	if (mRotation.mZ < 0) {
		mRotation.mZ++; //車体の傾き修正
	}

	if (mRotation.mZ > 0) {
		mRotation.mZ--; //車体の傾き修正
	}

	if (mRotation.mX < 0) {
		mRotation.mX++; //車体の傾き修正 
	}

	if (mRotation.mX > 0) {
		mRotation.mX--; //車体の傾き修正
	}

//カウントダウンSe再生
	if (mTime ==  240){

		CountDownSe.Play();		
	}
	if (mTime == 180) {

		CountDownSe.Play();
	}
	if (mTime == 120) {

		CountDownSe.Play();
	}

	if (mPosition.mY < -2) {
		mPosition.mY = 1;
	}
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;

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
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Resource\\exp.tga", 4, 4, 2); //被弾
					BombSe.Play();
					if (mCoinGet > 0) {
						mCoinGet--;
					}
				}
			}
		}

		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				myadd = 0; //着地
				mJump = 0; //ジャンプ可能
				if (mJump == 0 && CKey::Once('J')) //ジャンプ
				{
					myadd = -0.2f;
					mJump++;
				}
				//位置の更新(mPosition + adjust)
				//mPosition = mPosition - adjust * -1;
				CVector x = o->mV[3].Cross(vz).Normalize();
				CVector z = x.Cross(o->mV[3]).Normalize();
				mRotation.mX = -asin(z.mY) / M_PI * 180;
				//mRotation.mY = atan2(z.mX, z.mZ) / M_PI * 180;
				mRotation.mZ = atan2(x.mY, o->mV[3].mY) / M_PI * 180;
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

	//文字列編集エリアの作成
	char buf[64];

	//文字列の設定
	sprintf(buf, ":%d", mCoinGet);
	//文字列の描画
	if (mCoinGet < 10) {
		mCoinText.DrawString(buf, -320, 255, 20, 32); //プレイヤーコイン獲得数
	}
	else
	{
		mCoinText.DrawString(buf, -345, 255, 20, 32);
	}
	mCoinText.DrawString("PLAYER", -310, 290, 6, 12);
	mCoinText.DrawString("COIN", -300, 220, 6, 12);

	//文字列の設定
	sprintf(buf, ":%d", mEnemyCoinGet);
	//文字列の描画
	if (mEnemyCoinGet < 10) {
		mCoinText.DrawString(buf, 250, 255, 20, 32); //敵コイン獲得数
	}
	else
	{
		mCoinText.DrawString(buf, 230, 255, 20, 32); //敵コイン獲得数
	}
	mCoinText.DrawString("ENEMY", 270, 290, 6, 12);
	mCoinText.DrawString("COIN", 270, 220, 6, 12);

	//描画色の設定（赤色の半透明）
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	if (mTime > 600) {
		sprintf(buf, "%d", mTime / 60);
		//文字列の描画
		mText.DrawString(buf, -6, 240, 8, 16); //制限時間
	}

	if (mTime < 600 && mTime > 240) {
		sprintf(buf, "%d", mTime / 60);
		//文字列の描画
		mText.DrawString(buf, 0, 240, 8, 16);
	}

	if (mTime < 240) {
		sprintf(buf, "%d", mTime / 60);
		//文字列の描画
		mText.DrawString(buf, 0, 0, 24, 48); //ラスト3カウント
	}


	sprintf(buf, "%d", mBulletP);
	mText.DrawString(buf, -200, -260, 16, 32); //装弾数

	//2Dの描画終了
	CUtil::End2D();

}