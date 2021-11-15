#include "CCoin.h"
#include "CTaskManager.h"
#define VELOCITY 0.11f
#include "CPlayer.h"
#include "CCollisionManager.h"

//�R���X�g���N�^
CCoin::CCoin(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider(this, &mMatrix, CVector(0.0f, 0.2f, 0.0f), 0.7f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����
	mTag = ECOIN;

	CTransform::Update();
	mCollider.ChangePriority();
}


//�X�V����
void CCoin::Update() {
	//�s����X�V
	CTransform::Update();

	mRotation.mY += 3;
}

//�Փˏ���
//Collision(�R���C�_�P,�R���C�_�Q)
void CCoin::Collision(CCollider* m, CCollider* o) {
	switch (m->mTag)
	{
	case CCollider::EBODY:
		//����̃R���C�_�^�C�v�̔���
		switch (o->mType)
		{
		case CCollider::ESPHERE:
			if (o->mTag == CCollider::EBODY) {
				if (o->mpParent->mTag == EPLAYER) {
					if (CCollider::Collision(o, m)) {
						mEnabled = false;
						CPlayer::spThis->CoinGet++;
					}
				}
			}
			break;
		/*/case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
			CVector adjust; //�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{      //�Փ˂��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
				mRotation.mY++;
			}
			break;*/
		}
		break;
	}
}

void CCoin::TaskCollision()
{
	//mCollider.ChangePriority();
	//CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}