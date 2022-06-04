#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CTriangle.h"
#include "CKey.h"
#include "CMatrix.h"
#include "CTransform.h"
#include "CBullet.h"
#include "CTaskManager.h"
//CEnemyクラスのインクルード
#include "CEnemy.h"
#include "CEnemy2.h"
//
#include "CCollisionManager.h"
//
#include "CBillBoard.h"
//
#include "CCamera.h"
//
#include "CUtil.h"

#include "CCity.h"

#include "CMakimono.h"

#include "CCoin.h"

#include "CWall.h"

#include "CGround.h"

//CSoundクラスのインクルード
#include "CSound.h"
//CSoundクラスのインスタンス作成（外部変数作成例）
CSound Bgm;
CSound BombSe;
CSound shoot1Se;
CSound CoinSe;
CSound CarSe;
CSound BulletSe;
CSound shoot2Se;
CSound BrakeSe;

#define TEXWIDTH  8192  //テクスチャ幅
#define TEXHEIGHT  6144  //テクスチャ高さ

#define FONT_IMAGE "FontWhite.tga"
#define ENEMY_MODEL "Resource\\c5.obj","Resourece\\c5.mtl"
#define GROUND_TRANSLATE 0.0f, 0.0f, -500.0f
#define CAR_MODEL "Resource\\Car.obj","Resource\\Car.mtl"
#define HOUSE_MODEL "Resource\\City3.obj","Resource\\City3.mtl"
#define SKY_MODEL "Resource\\sky.obj","Resource\\sky.mtl"
#define COIN_MODEL "Resource\\Coin.obj","Resource\\Coin.mtl"
#define BULLET_MODEL "Resource\\bullet.obj","Resource\\bullet.mtl"

//弾丸画像
#define BULLET_IMAGE "Resource\\bullet.png"

//戦闘機画像
#define JET_IMAGE "Resource\\Jet.png"

//車画像
#define CAR_IMAGE "Resource\\Car.png"

//時計画像
#define TIMER_IMAGE "Resource\\Timer.png"

CSceneGame::~CSceneGame()
{
	CTaskManager::Destroy();
}

void CSceneGame::Init() {
	mPlayer = new CPlayer();
	Camera = new CCamera();

	//シーンの設定
	mScene = EGAME;

	//サウンド(wav)ファイルの読み込み
	Bgm.Load("Resource\\BGM.wav");
	BombSe.Load("Resource\\bomb.wav");
	shoot1Se.Load("Resource\\shoot1.wav");
	CoinSe.Load("Resource\\coin.wav");
	CarSe.Load("Resource\\driving.wav");
	BulletSe.Load("Resource\\bullet.wav");
	shoot2Se.Load("Resource\\shoot2.wav");
	BrakeSe.Load("Resource\\brake.wav");

	sImagebullet.Load(BULLET_IMAGE);
	sImagejet.Load(JET_IMAGE);
	sImageCar.Load(CAR_IMAGE);
	sImageTimer.Load(TIMER_IMAGE);

	//BGM繰り返し再生
	Bgm.Repeat();


	mText.LoadTexture(FONT_IMAGE,1,64);

	mBackGroundMatrix.Translate(GROUND_TRANSLATE);

	//三角コライダの確認
//	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
//	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, 50.0f));

	//C5モデルの読み込み
	mModelC5.Load(ENEMY_MODEL);

	mEye = CVector(1.0f, 2.0f, 3.0f);
	//モデルファイルの入力
	mModel.Load(CAR_MODEL);


	mBackGround.Load(SKY_MODEL);
	new CGround(&mBackGround, CVector(0.0f, 0.0f, -500.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	CMatrix matrix;
	matrix.Print();

	mPlayer->mpModel = &mModel;
	mPlayer->mScale = CVector(0.03f, 0.03f, 0.03f);
	//
	mPlayer->mPosition = CVector(0.0f, 0.0f, -25.0f) * mBackGroundMatrix;
	//mPlayer.mPosition = CVector(0.0f, 0.0f, -503.0f);
	mPlayer->mRotation = CVector(0.0f, 180.0f, 0.0f);

	//家
	mModelHouse.Load(HOUSE_MODEL);
	/*new CCity(&mModelHouse, CVector(0.0f, -2.0f, -550.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));*/

	new CCity(&mModelHouse, CVector(50.0f, -2.0f, -550.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(-50.0f, -2.0f, -550.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(100.0f, -2.0f, -550.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(-100.0f, -2.0f, -550.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	//弾丸
	mModelMakimono.Load(BULLET_MODEL);
	new CMakimono(&mModelMakimono, CVector(-123.0f, 0.5f, -550.0f),
		CVector(60.0f,0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	new CMakimono(&mModelMakimono, CVector(-73.0f, 0.5f, -550.0f),
		CVector(60.0f, 0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	new CMakimono(&mModelMakimono, CVector(-23.0f, 0.5f, -550.0f),
		CVector(60.0f, 0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	new CMakimono(&mModelMakimono, CVector(27.0f, 0.5f, -550.0f),
		CVector(60.0f, 0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	new CMakimono(&mModelMakimono, CVector(77.0f, 0.5f, -550.0f),
		CVector(60.0f, 0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	new CMakimono(&mModelMakimono, CVector(123.0f, 0.5f, -550.0f),
		CVector(60.0f, 0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	//コイン
	mModelCoin.Load(COIN_MODEL);
	new CCoin(&mModelCoin, CVector(-120.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-100.0f, 1.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-80.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-60.0f, 1.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-40.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-20.0f, 1.5f, -530.0f),
			CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	/*new CCoin(&mModelCoin, CVector(0.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));*/

	new CCoin(&mModelCoin, CVector(20.0f, 1.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(40.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(60.0f, 1.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(80.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(100.0f, 1.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(120.0f, -0.5f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-120.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-100.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-80.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-60.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-40.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-20.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	/*new CCoin(&mModelCoin, CVector(0.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));*/

	new CCoin(&mModelCoin, CVector(20.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(40.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(60.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(80.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(100.0f, -0.5f, -575.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(120.0f, -0.5f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	//壁
	mModelWall.Load("wall.obj", "wall.mtl");
	new CWall(&mModelWall, CVector(130.0f, -0.5f, -530.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(100.0f, 100.0f, 1.0f));

	new CWall(&mModelWall, CVector(-130.0f, -0.5f, -530.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(100.0f, 100.0f, 1.0f));

	new CWall(&mModelWall, CVector(0.0f, -0.5f, -580.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(1.0f, 100.0f, 200.0f));

	new CWall(&mModelWall, CVector(0.0f, -0.5f, -520.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(1.0f, 100.0f, 200.0f));

	//敵機のインスタンス作成
	new CEnemy(CVector(5.0f, -0.5f, -60.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -600.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -630.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy2(CVector(0.0f, -0.5f, -80.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy2(CVector(100.0f, -0.5f, -80.0f)* mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	//◇コイン列
	new CCoin(&mModelCoin, CVector(5.0f, -0.5f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(10.0f, -0.5f, -540.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(15.0f, -0.5f, -545.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(20.0f, -0.5f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-5.0f, -0.5f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-10.0f, -0.5f, -540.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, -0.5f, -545.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-20.0f, -0.5f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(5.0f, -0.5f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(10.0f, -0.5f, -560.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(15.0f, -0.5f, -555.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	/*new CCoin(&mModelCoin, CVector(20.0f, -0.5f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));*/

	new CCoin(&mModelCoin, CVector(-5.0f, -0.5f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-10.0f, -0.5f, -560.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, -0.5f, -555.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	/*new CCoin(&mModelCoin, CVector(-20.0f, -0.5f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));*/

	//足場
	new CWall(&mModelWall, CVector(0.0f, 0.0f, -570.0f),
		CVector(-20.0f, 0.0f, 0.0f), CVector(2.0f, 0.1f, 10.0f));

	new CWall(&mModelWall, CVector(0.0f, 0.0f, -530.0f),
		CVector(20.0f, 0.0f, 0.0f), CVector(2.0f, 0.1f, 10.0f));

	new CWall(&mModelWall, CVector(-20.0f, 0.0f, -550.0f),
		CVector(0.0f, 0.0f, 20.0f), CVector(10.0f, 0.1f, 2.0f));

	new CWall(&mModelWall, CVector(20.0f, 0.0f, -550.0f),
		CVector(0.0f, 0.0f, -20.0f), CVector(10.0f, 0.1f, 2.0f));

	new CWall(&mModelWall, CVector(0.0f, 3.3f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(10.5f, 0.1f, 10.5f));

	//台上コイン
	new CCoin(&mModelCoin, CVector(0.0f, 3.4f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(5.0f, 3.4f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-5.0f, 3.4f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(10.0f, 3.4f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-10.0f, 3.4f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(0.0f, 3.4f, -555.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(0.0f, 3.4f, -545.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(0.0f, 3.4f, -560.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(0.0f, 3.4f, -540.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	//浮遊台
	new CWall(&mModelWall, CVector(15.0f, 4.0f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(3.0f, 0.1f, 3.0f));
	new CWall(&mModelWall, CVector(-15.0f, 4.0f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(3.0f, 0.1f, 3.0f));
	new CWall(&mModelWall, CVector(15.0f, 4.0f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(3.0f, 0.1f, 3.0f));
	new CWall(&mModelWall, CVector(-15.0f, 4.0f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(3.0f, 0.1f, 3.0f));

	new CWall(&mModelWall, CVector(-73.0f, 4.0f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(50.0f, 0.1f, 2.0f));
	new CWall(&mModelWall, CVector(73.0f, 4.0f, -530.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(50.0f, 0.1f, 2.0f));
	new CWall(&mModelWall, CVector(-73.0f, 4.0f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(50.0f, 0.1f, 2.0f));
	new CWall(&mModelWall, CVector(73.0f, 4.0f, -570.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(50.0f, 0.1f, 2.0f));

	new CWall(&mModelWall, CVector(-123.0f, 4.0f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 0.1f, 22.0f));
	new CWall(&mModelWall, CVector(123.0f, 4.0f, -550.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 0.1f, 22.0f));

	//浮遊台上コイン
	new CCoin(&mModelCoin, CVector(15.0f, 4.1f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, 4.1f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(15.0f, 4.1f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, 4.1f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));


	//ビルボードの生成
	//new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//背景モデルから三角コライダを生成
	//親インスタンスと行列はなし
	//mColliderMesh.Set(NULL, NULL, &mBackGround);
	//mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める


	//	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	e = CVector(0.0f, 31.5f, -100.0f) * CMatrix().RotateY(Camera->mRotation.mY) * mPlayer->mMatrix;
	if (CKey::Push(VK_SPACE))
	{
		e = CVector(0.0f, 20.0f, 100.0f) * mPlayer->mMatrix;
	}
	//注視点を求める
	c = mPlayer->mPosition;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;
	//カメラの設定
	//gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	//カメラクラスの設定
	Camera->Set(e, c, u);

	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };  //影の色
	float lightPos[] = { 0.0f, 160.0f, -550.0f };  //光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, Render, shadowColor, lightPos);

}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
//削除	CCollisionManager::Get()->Collision();
	CTaskManager::Get()->TaskCollision();


	if (CKey::Push('L'))
	{
		mEye.mX += 0.2f;
	}
	if (CKey::Push('J'))
	{
		mEye.mX -= 0.1f;
	}
	if (CKey::Push('I'))
	{
		mEye.mZ -= 0.1f;
	}
	if (CKey::Push('K'))
	{
		mEye.mZ += 0.1f;
	}
	if (CKey::Push('O'))
	{
		mEye.mY += 0.1f;
	}
	if (CKey::Push('M'))
	{
		mEye.mY -= 0.1f;
	}

	//視点の設定
	//gluLookAt(視点X, 視点Y, 視点Z, 中心X, 中心Y, 中心Z, 上向X, 上向Y, 上向Z)
	//gluLookAt(mEye.mX, mEye.mY, mEye.mZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//	mPlayer.Update();
	//カメラのパラメータを作成する
/*	CVector e, c, u;//視点、注視点、上方向
	//視点を求める


	//	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	e = CVector(0.0f, 31.5f, -100.0f) * CMatrix().RotateY(Camera.mRotation.mY) * mPlayer.mMatrix;
	if (CKey::Push(VK_SPACE))
	{
		e = CVector(0.0f, 20.0f, 100.0f) * mPlayer.mMatrix;
	}
	//注視点を求める
	c = mPlayer.mPosition;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.mMatrixRotate;
	//カメラの設定
	//gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	//カメラクラスの設定
	Camera.Set(e, c, u);*/
	//Camera.Render();
	//	mPlayer.Render();

	//mBackGround.Render(mBackGroundMatrix);

//	mPlayer.bullet.Update();
//	mPlayer.bullet.Render();

	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//CTaskManager::Get()->Render();


	Camera->Draw();

	mShadowMap.Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);

	sImagebullet.Draw(-370, -220, -300, -220, 400, 6000, 3000, 0);
	sImagejet.Draw(120, 230, 230, 330, 0, 600, 500, 0);
	sImageCar.Draw(-320, -140, 230, 310, 100, 2000, 800, 0);
	sImageTimer.Draw(-20, 20, 250, 290, 0, 255, 255, 0);

	//2Dの描画終了
	CUtil::End2D();

#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif

	if (CPlayer::spThis->Time < 1 && CPlayer::spThis->CoinGet > CPlayer::spThis->EnemyCoinGet) {
		mScene = EWIN;
	}

	if (CPlayer::spThis->Time < 1 &&  CPlayer::spThis->EnemyCoinGet > CPlayer::spThis->CoinGet) {
		mScene = ELOSE;
	}

	if (CPlayer::spThis->Time < 1 && CPlayer::spThis->EnemyCoinGet == CPlayer::spThis->CoinGet) {
		mScene = EDRAW;
	}

}

void Render()
{
	CTaskManager::Get()->Render();

}

CScene::EScene CSceneGame::GetNextScene()
{
	return mScene;
}
