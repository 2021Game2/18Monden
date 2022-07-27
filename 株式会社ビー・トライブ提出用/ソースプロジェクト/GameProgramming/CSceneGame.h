#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CVector.h"
//モデルクラスのインクルード
#include "CModel.h"
//
#include "CCharacter.h"
//
#include "CPlayer.h"
//
#include "CColliderTriangle.h"
//
#include "CColliderMesh.h"
//
#include "CText.h"

#include "CShadowMap.h"
/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	~CSceneGame();

	CText mText;

	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	//三角コライダの作成
	//削除CColliderTriangle mColliderTriangle;
	//削除CColliderTriangle mColliderTriangle2;
	//C5モデル
	CModel mModelC5;
	CModel mBackGround;
	CMatrix mBackGroundMatrix;

	CModel mModelHouse;
	CModel mModelBullet;
	CModel mModelCoin;
	CModel mModelWall;

	//モデルクラスのインスタンス作成
	CModel mModel;
	//
//	CCharacter mCharacter;
	CPlayer*mPlayer;

	CVector mEye;

	CShadowMap mShadowMap;

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	float d = 1;
	float f = 1;

	EScene GetNextScene();

	CTexture sImagebullet;
	CTexture sImagejet;
	CTexture sImageCar;
	CTexture sImageTimer;
};
void Render();

#endif
