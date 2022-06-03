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

CPlayer *CPlayer::spThis = 0;

#define FIRECOUNT 10	//���ˊԊu

//CSound�N���X�̃C���N���[�h
#include "CSound.h"
//�O���ϐ��̎Q�Ƃ̍쐬
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
, mJump(0) //0�̓W�����v�\
, BulletP(0)
, yadd(0)
, CoinGet(0)
, EnemyCoinGet(0)
{
	spThis = this;
	//�e�N�X�`���t�@�C���̓ǂݍ��݁i1�s64��j
	mText.LoadTexture("FontWhite.tga", 1, 64);
	mTag = EPLAYER;
}

//�X�V����
void CPlayer::Update() {

	CVector OldRotate = mRotation;

	//��������
	if (Time > 0) {
		Time--;
	}

	//A�L�[���͂ŉ�]
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



	//D�L�[���͂ŉ�]
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

	//�W�����v
	

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
}

void CPlayer::Collision(CCollider *m, CCollider *o) {
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
					new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
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
				yadd = 0;
				mJump = 0;
				if (mJump == 0 && CKey::Once('J'))
				{
					yadd = -0.2f;
					mJump++;
				}
				//�ʒu�̍X�V(mPosition + adjust)
				//mPosition = mPosition - adjust * -1;
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
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "PLAYER:%d", CoinGet);
	//������̕`��
	mText.DrawString(buf, -300, 270, 16, 32);


	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "ENEMY:%d", EnemyCoinGet);
	//������̕`��
	mText.DrawString(buf, 100, 270, 16, 32);

	//Y���W�̕\��
//������̐ݒ�
	sprintf(buf, "TIME:%d", Time/60);
	//������̕`��
	mText.DrawString(buf, -40, 270, 8, 16);

	sprintf(buf, "BULLET:%d", BulletP);
	mText.DrawString(buf, -300, -270, 16, 32);

	//2D�̕`��I��
	CUtil::End2D();

}