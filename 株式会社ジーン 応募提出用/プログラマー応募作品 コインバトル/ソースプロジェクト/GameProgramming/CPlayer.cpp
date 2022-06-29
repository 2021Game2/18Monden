//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
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

#define FIRECOUNT 10	//���ˊԊu

//CSound�N���X�̃C���N���[�h
#include "CSound.h"
//�O���ϐ��̎Q�Ƃ̍쐬
extern CSound BombSe; //��eSe
extern CSound shoot1Se; //����Se
extern CSound CarSe; //��Se
extern CSound BrakeSe; //�}�u���[�LSe
extern CSound CountDownSe; //�J�E���g�_�E��Se

CPlayer::CPlayer()
: mLine(this, &mMatrix, CVector(0.0f, 10.0f, -30.0f), CVector(0.0f, 10.0f, 30.0f))
, mLine2(this, &mMatrix, CVector(0.0f, 30.0f, 0.0f), CVector(0.0f, -1.0f, 0.0f))
, mLine3(this, &mMatrix, CVector(25.0f, 10.0f, -8.0f), CVector(-30.0f, 10.0f, -8.0f))
, mCollider(this, &mMatrix, CVector(-0.5f, 10.0f, -0.5f), 0.4f)
, mFireCount(0)
, mJump(0) //0�̓W�����v�\
, BulletP(0)
, yadd(0)
, CoinGet(0)
, EnemyCoinGet(0)
{
	spThis = this;
	//�e�N�X�`���t�@�C���̓ǂݍ��݁i1�s64��j
	mCoinText.LoadTexture("Resource\\FontGold1.png", 1, 64);
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
	mTag = EPLAYER;
}

//�X�V����
void CPlayer::Update() {
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	CVector vp = mPoint - mPosition;

	CVector OldRotate = mRotation;

	//��������
	if (Time > 0) {
		Time--;
	}

	//A�L�[���͂ō���]
	if (CKey::Push('A')) {
		if (curve < 0) {
			curve -= curve * 1 / 3; //�t��]�Ŋ�����}����
		}

		if (curve < 30) {
			curve++;
		}
		mRotation.mY += curve * 1/5;
	}
	//A�L�[�����Ɗ����ŉ�]
	if (CKey::Push('A') == false && curve > 1) {
		curve--;
		mRotation.mY += curve * 1 / 20;
	}



	//D�L�[���͂ŉE��]
	if (CKey::Push('D')) {
		if (curve > 0) {
			curve -= curve * 1 / 3; //�t��]�Ŋ�����}����
		}

		if (curve > -30) {
			curve--;
		}
		mRotation.mY += curve * 1/5;
	}
	//D�L�[�����Ɗ����ŉ�]
	if (CKey::Push('D') == false && curve < -1) {
		curve++;
		mRotation.mY += curve * 1 / 20;
	}

	//W�L�[�őO�i
	if (CKey::Push('W')) {
		if (t < 300) {
			t++;
		}
		//Z��������1�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}
	//�L�[�����Ɗ����Ŋ���
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

	//S�L�[�Ō��
	if (CKey::Push('S')) {
		if (t > 0) {
			t -= t * 1/10; //�u���[�L
			if (t > 200 && mJump == 0) {
				BrakeSe.Play(); //�u���[�L���Đ�
			}
		}


		if (t > -90) {
			t--;
		}
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}

	//�L�[�����Ɗ����Ŋ���
	if (CKey::Push('S') == false && t < -1) {
		t++;
		mPosition = CVector(0.0f, 0.0f, 0.05f * t) * mMatrix;
	}


	if (mFireCount > 0)
	{
		mFireCount--;
	}

	//CTransform�̍X�V
	CTransform::Update();

	//����
	mPosition.mY -= yadd;
	yadd += 0.01f;


	//�e����
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

	//�s����X�V
	CTransform::Update();

	Camera->SetTarget(mPosition);
	Camera->SetAddRotate(OldRotate - mRotation);
	OldRotate = mRotation;

	if (mRotation.mZ < 0) {
		mRotation.mZ++; //�ԑ̂̌X���C��
	}

	if (mRotation.mZ > 0) {
		mRotation.mZ--; //�ԑ̂̌X���C��
	}

	if (mRotation.mX < 0) {
		mRotation.mX++; //�ԑ̂̌X���C�� 
	}

	if (mRotation.mX > 0) {
		mRotation.mX--; //�ԑ̂̌X���C��
	}

//�J�E���g�_�E��Se�Đ�
	if (Time ==  240){

		CountDownSe.Play();		
	}
	if (Time == 180) {

		CountDownSe.Play();
	}
	if (Time == 120) {

		CountDownSe.Play();
	}
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;

	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//yadd = 0;
				//mJump = 0;
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition - adjust * -1;
				//�s��̍X�V
				CTransform::Update();
			}
		}
		break;
	case CCollider::ESPHERE:
		//����̃R���C�_�����R���C�_�̎�
		if (o->mType == CCollider::ESPHERE) {
			if (CCollider::Collision(m, o))
			{
				if (o->mpParent->mTag == EBULLETENEMY) {
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "Resource\\exp.tga", 4, 4, 2); //��e
					BombSe.Play();
					if (CoinGet > 0) {
						CoinGet--;
					}
				}
			}
		}

		if (o->mType == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				yadd = 0; //���n
				mJump = 0; //�W�����v�\
				if (mJump == 0 && CKey::Once('J')) //�W�����v
				{
					yadd = -0.2f;
					mJump++;
				}
				//�ʒu�̍X�V(mPosition + adjust)
				//mPosition = mPosition - adjust * -1;
				CVector x = o->mV[3].Cross(vz).Normalize();
				CVector z = x.Cross(o->mV[3]).Normalize();
				mRotation.mX = -asin(z.mY) / M_PI * 180;
				//mRotation.mY = atan2(z.mX, z.mZ) / M_PI * 180;
				mRotation.mZ = atan2(x.mY, o->mV[3].mY) / M_PI * 180;
				//�s��̍X�V
				CTransform::Update();
			}
		}
		break;
	}
}
//�Փˏ���
void CPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

void CPlayer::Render()
{
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);

	//������ҏW�G���A�̍쐬
	char buf[64];

	//������̐ݒ�
	sprintf(buf, ":%d", CoinGet);
	//������̕`��
	if (CoinGet < 10) {
		mCoinText.DrawString(buf, -320, 255, 20, 32); //�v���C���[�R�C���l����
	}
	else
	{
		mCoinText.DrawString(buf, -345, 255, 20, 32);
	}
	mCoinText.DrawString("PLAYER", -310, 290, 6, 12);
	mCoinText.DrawString("COIN", -300, 220, 6, 12);

	//������̐ݒ�
	sprintf(buf, ":%d", EnemyCoinGet);
	//������̕`��
	if (EnemyCoinGet < 10) {
		mCoinText.DrawString(buf, 250, 255, 20, 32); //�G�R�C���l����
	}
	else
	{
		mCoinText.DrawString(buf, 230, 255, 20, 32); //�G�R�C���l����
	}
	mCoinText.DrawString("ENEMY", 270, 290, 6, 12);
	mCoinText.DrawString("COIN", 270, 220, 6, 12);

	//�`��F�̐ݒ�i�ԐF�̔������j
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	if (Time > 600) {
		sprintf(buf, "%d", Time / 60);
		//������̕`��
		mText.DrawString(buf, -6, 240, 8, 16); //��������
	}

	if (Time < 600 && Time > 240) {
		sprintf(buf, "%d", Time / 60);
		//������̕`��
		mText.DrawString(buf, 0, 240, 8, 16);
	}

	if (Time < 240) {
		sprintf(buf, "%d", Time / 60);
		//������̕`��
		mText.DrawString(buf, 0, 0, 24, 48); //���X�g3�J�E���g
	}


	sprintf(buf, "%d", BulletP);
	mText.DrawString(buf, -200, -260, 16, 32); //���e��

	//2D�̕`��I��
	CUtil::End2D();

}