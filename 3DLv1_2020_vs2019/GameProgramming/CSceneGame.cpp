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
//CEnemy�N���X�̃C���N���[�h
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

//CSound�N���X�̃C���N���[�h
#include "CSound.h"
//CSound�N���X�̃C���X�^���X�쐬�i�O���ϐ��쐬��j
CSound Bgm;
CSound BombSe;
CSound shoot1Se;
CSound CoinSe;
CSound CarSe;
CSound BulletSe;
CSound shoot2Se;
CSound BrakeSe;

#define TEXWIDTH  8192  //�e�N�X�`����
#define TEXHEIGHT  6144  //�e�N�X�`������

#define FONT_IMAGE "FontWhite.tga"
#define ENEMY_MODEL "Resource\\c5.obj","Resourece\\c5.mtl"
#define GROUND_TRANSLATE 0.0f, 0.0f, -500.0f
#define CAR_MODEL "Resource\\Car.obj","Resource\\Car.mtl"
#define HOUSE_MODEL "Resource\\City3.obj","Resource\\City3.mtl"
#define SKY_MODEL "Resource\\sky.obj","Resource\\sky.mtl"
#define COIN_MODEL "Resource\\Coin.obj","Resource\\Coin.mtl"
#define BULLET_MODEL "Resource\\bullet.obj","Resource\\bullet.mtl"

//�e�ۉ摜
#define BULLET_IMAGE "Resource\\bullet.png"

//�퓬�@�摜
#define JET_IMAGE "Resource\\Jet.png"

//�ԉ摜
#define CAR_IMAGE "Resource\\Car.png"

//���v�摜
#define TIMER_IMAGE "Resource\\Timer.png"

CSceneGame::~CSceneGame()
{
	CTaskManager::Destroy();
}

void CSceneGame::Init() {
	mPlayer = new CPlayer();
	Camera = new CCamera();

	//�V�[���̐ݒ�
	mScene = EGAME;

	//�T�E���h(wav)�t�@�C���̓ǂݍ���
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

	//BGM�J��Ԃ��Đ�
	Bgm.Repeat();


	mText.LoadTexture(FONT_IMAGE,1,64);

	mBackGroundMatrix.Translate(GROUND_TRANSLATE);

	//�O�p�R���C�_�̊m�F
//	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
//	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, 50.0f));

	//C5���f���̓ǂݍ���
	mModelC5.Load(ENEMY_MODEL);

	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
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

	//��
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

	//�e��
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

	//�R�C��
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

	//��
	mModelWall.Load("wall.obj", "wall.mtl");
	new CWall(&mModelWall, CVector(130.0f, -0.5f, -530.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(100.0f, 100.0f, 1.0f));

	new CWall(&mModelWall, CVector(-130.0f, -0.5f, -530.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(100.0f, 100.0f, 1.0f));

	new CWall(&mModelWall, CVector(0.0f, -0.5f, -580.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(1.0f, 100.0f, 200.0f));

	new CWall(&mModelWall, CVector(0.0f, -0.5f, -520.0f),
		CVector(0.0f, 90.0f, 0.0f), CVector(1.0f, 100.0f, 200.0f));

	//�G�@�̃C���X�^���X�쐬
	new CEnemy(CVector(5.0f, -0.5f, -60.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -600.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -630.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

	new CEnemy2(CVector(0.0f, -0.5f, -80.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	new CEnemy2(CVector(100.0f, -0.5f, -80.0f)* mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	//���R�C����
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

	//����
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

	//���R�C��
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

	//���V��
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

	//���V���R�C��
	new CCoin(&mModelCoin, CVector(15.0f, 4.1f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, 4.1f, -535.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(15.0f, 4.1f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-15.0f, 4.1f, -565.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));


	//�r���{�[�h�̐���
	//new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�ƍs��͂Ȃ�
	//mColliderMesh.Set(NULL, NULL, &mBackGround);
	//mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�


	//	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	e = CVector(0.0f, 31.5f, -100.0f) * CMatrix().RotateY(Camera->mRotation.mY) * mPlayer->mMatrix;
	if (CKey::Push(VK_SPACE))
	{
		e = CVector(0.0f, 20.0f, 100.0f) * mPlayer->mMatrix;
	}
	//�����_�����߂�
	c = mPlayer->mPosition;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer->mMatrixRotate;
	//�J�����̐ݒ�
	//gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	//�J�����N���X�̐ݒ�
	Camera->Set(e, c, u);

	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };  //�e�̐F
	float lightPos[] = { 0.0f, 160.0f, -550.0f };  //�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, Render, shadowColor, lightPos);

}

void CSceneGame::Update() {

	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
//�폜	CCollisionManager::Get()->Collision();
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

	//���_�̐ݒ�
	//gluLookAt(���_X, ���_Y, ���_Z, ���SX, ���SY, ���SZ, ���X, ���Y, ���Z)
	//gluLookAt(mEye.mX, mEye.mY, mEye.mZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

//	mPlayer.Update();
	//�J�����̃p�����[�^���쐬����
/*	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�


	//	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	e = CVector(0.0f, 31.5f, -100.0f) * CMatrix().RotateY(Camera.mRotation.mY) * mPlayer.mMatrix;
	if (CKey::Push(VK_SPACE))
	{
		e = CVector(0.0f, 20.0f, 100.0f) * mPlayer.mMatrix;
	}
	//�����_�����߂�
	c = mPlayer.mPosition;
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f) * mPlayer.mMatrixRotate;
	//�J�����̐ݒ�
	//gluLookAt(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);*/
	//Camera.Render();
	//	mPlayer.Render();

	//mBackGround.Render(mBackGroundMatrix);

//	mPlayer.bullet.Update();
//	mPlayer.bullet.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//CTaskManager::Get()->Render();


	Camera->Draw();

	mShadowMap.Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);

	sImagebullet.Draw(-370, -220, -300, -220, 400, 6000, 3000, 0);
	sImagejet.Draw(120, 230, 230, 330, 0, 600, 500, 0);
	sImageCar.Draw(-320, -140, 230, 310, 100, 2000, 800, 0);
	sImageTimer.Draw(-20, 20, 250, 290, 0, 255, 255, 0);

	//2D�̕`��I��
	CUtil::End2D();

#ifdef _DEBUG
	//�R���C�_�̕`��
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
