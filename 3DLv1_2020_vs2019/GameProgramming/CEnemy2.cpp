#include "CEnemy2.h"
#include "CEffect.h"
#include "CTaskManager.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

#define OBJ "f16.obj"	//���f���̃t�@�C��
#define MTL "f16.mtl"	//���f���̃}�e���A���t�@�C��

#define HP 3	//�ϋv�l
#define VELOCITY 0.3f	//���x

CModel CEnemy2::mModel;	//���f���f�[�^�쐬

#define FIRECOUNT 15	//���ˊԊu


CEnemy2::CEnemy2()
: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.6f)
, mColSearch(this, &mMatrix, CVector(0.0f, 0.0f, 100.0f), 50.0f)
, mpPlayer(0)
, mHp(HP)
, mFireCount(0)
{
	mTag = EENEMY;
	mColSearch.mTag = CCollider::ESEARCH;	//�^�O�ݒ�

	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
}


//�R���X�g���N�^
//CEnemy(�ʒu, ��], �g�k)
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
	: CEnemy2()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;	//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//�X�V����
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
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = mpPlayer->mPosition - mPosition;
		float dx = vp.Dot(vx); //���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(vy); //��x�N�g���Ƃ̓��ς����߂�
		//X���̂��ꂪ2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y���̂��ꂪ2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f && mFireCount == 0)
			{
				//�e�𔭎�
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
//�Փˏ���
//Collision(�R���C�_�P,�R���C�_�Q)
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	switch (m->mTag)
	{
	case CCollider::EBODY:
		//����̃R���C�_�^�C�v�̔���
		switch (o->mType)
		{
		case CCollider::ESPHERE:
			//����̃R���C�_�����R���C�_�̎�
				if (CCollider::Collision(m, o))
				{
					if (o->mpParent->mTag == EBULLETPLAYER && CPlayer::spThis->EnemyCoinGet > 0) {
						CPlayer::spThis->EnemyCoinGet--;
						new CEffect(o->mpParent->mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
					}
				}
			break;
		case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
			CVector adjust; //�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{	//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
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
