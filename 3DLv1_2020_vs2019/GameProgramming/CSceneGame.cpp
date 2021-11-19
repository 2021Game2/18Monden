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

CModel mModelHouse;
CModel mModelMakimono;
CModel mModelCoin;

void CSceneGame::Init() {
	mText.LoadTexture("FontWhite.tga",1,64);

	mBackGroundMatrix.Translate(0.0f, 0.0f, -500.0f);

	//�O�p�R���C�_�̊m�F
//	mColliderTriangle.Set(NULL, NULL, CVector(-50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, -50.0f));
//	mColliderTriangle2.Set(NULL, NULL, CVector(50.0f, 0.0f, -50.0f), CVector(-50.0f, 0.0f, 50.0f), CVector(50.0f, 0.0f, 50.0f));

	//C5���f���̓ǂݍ���
	mModelC5.Load("c5.obj", "c5.mtl");

	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load("Car.obj", "Car.mtl");
	mBackGround.Load("sky.obj", "sky.mtl");

	CMatrix matrix;
	matrix.Print();

	mPlayer.mpModel = &mModel;
	mPlayer.mScale = CVector(0.03f, 0.03f, 0.03f);
	//
	mPlayer.mPosition = CVector(0.0f, 0.0f, -3.0f) * mBackGroundMatrix;
	//mPlayer.mPosition = CVector(0.0f, 0.0f, -503.0f);
	mPlayer.mRotation = CVector(0.0f, 180.0f, 0.0f);

	//��
	mModelHouse.Load("City3.obj", "City3.mtl");
	new CCity(&mModelHouse, CVector(0.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(50.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(-50.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(100.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(-100.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	new CCity(&mModelHouse, CVector(-150.0f, -2.0f, -600.0f),
		CVector(), CVector(1.0f, 1.0f, 1.0f));

	//����
	mModelMakimono.Load("bullet.obj", "bullet.mtl");
	new CMakimono(&mModelMakimono, CVector(0.0f, 1.0f, -510.0f),
		CVector(60.0f,0.0f, -50.0f), CVector(7.0f, 7.0f, 7.0f));

	//�R�C��
	mModelCoin.Load("Coin.obj", "Coin.mtl");
	new CCoin(&mModelCoin, CVector(-20.0f, -0.5f, -580.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(0.0f, -0.5f, -580.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(-10.0f, -0.5f, -580.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(10.0f, -0.5f, -580.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	new CCoin(&mModelCoin, CVector(20.0f, -0.5f, -580.0f),
		CVector(0.0f, 0.0f, 0.0f), CVector(2.0f, 2.0f, 2.0f));

	//�G�@�̃C���X�^���X�쐬
	new CEnemy(&mModelC5, CVector(0.0f, 30.0f, -100.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -130.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(0.0f, 10.0f, -600.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy(&mModelC5, CVector(30.0f, 10.0f, -630.0f), CVector(), CVector(0.1f, 0.1f, 0.1f));

//	new CEnemy2(CVector(-15.0f, 15.0f, -90.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
//	new CEnemy2(CVector(15.0f, 15.0f, -150.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	//new CEnemy2(CVector(-5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));
	//new CEnemy2(CVector(5.0f, 1.0f, -10.0f)*mBackGroundMatrix, CVector(), CVector(0.1f, 0.1f, 0.1f));

	//�r���{�[�h�̐���
	//new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�ƍs��͂Ȃ�
	//mColliderMesh.Set(NULL, NULL, &mBackGround);
	mColliderMesh.Set(NULL, &mBackGroundMatrix, &mBackGround);
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
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	if (CKey::Push('D') && Camera.mRotation.mY < 30)
	{
			if (d < 10) {
			d++;
		}
		Camera.mRotation.mY += d/30;
	}

	if (CKey::Push('D') == false && Camera.mRotation.mY > 0) {
		Camera.mRotation.mY--;
	}


	if (CKey::Push('A') && Camera.mRotation.mY > -30)
	{
		if (f > -10) {
			f--;
		}
		Camera.mRotation.mY += f/30;
	}

	if (CKey::Push('A') == false && Camera.mRotation.mY < 0) {
		Camera.mRotation.mY++;
	}

	//	e = CVector(-2.0f, 10.0f, -30.0f) * mPlayer.mMatrix;
	e = CVector(0.0f, 20.0f, -100.0f) * CMatrix().RotateY(Camera.mRotation.mY) * mPlayer.mMatrix;
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
	Camera.Set(e, c, u);
	Camera.Render();
	//	mPlayer.Render();

	mBackGround.Render(mBackGroundMatrix);

//	mPlayer.bullet.Update();
//	mPlayer.bullet.Render();

	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	CTaskManager::Get()->Render();

#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif
	if (CEnemy::sCount == 0)
	{
		//2D�̕`��J�n
		//CUtil::Start2D(-400, 400, -300, 300);
		//�`��F�̐ݒ�i�ΐF�̔������j
		//glColor4f(239.0f / 256.0f, 175.0f / 256.0f, 0.0f, 1.0f);

		//������̕`��
		//mText.DrawString("MISSION CLEAR", -200, 100, 16, 32);

		//2D�̕`��I��
		//CUtil::End2D();
	}

}

