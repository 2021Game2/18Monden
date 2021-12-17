#include "CCoin.h"
#include "CTaskManager.h"
#define VELOCITY 0.11f
#include "CPlayer.h"
#include "CCollisionManager.h"

CCoin* CCoin::spThis = 0;

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

	spThis = this;

	CTransform::Update();
	mCollider.ChangePriority();
	Time = 100;
	CoinRender = 0;

}


//�X�V����
void CCoin::Update() {
	//�s����X�V
	CTransform::Update();

	mRotation.mY += 3;

	if (CoinRender > 0)
	{
		CoinRender--;
	}
}

void CCoin::Render() {
	if (CoinRender == 0) {
		CCharacter::Render();
	}
}

//�Փˏ���
//Collision(�R���C�_�P,�R���C�_�Q)
void CCoin::Collision(CCollider* m, CCollider* o) {
	if (CoinRender > 0) {
		return;
	}

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
						CoinRender = 300;
						CPlayer::spThis->CoinGet++;
					}
				}
				if (o->mpParent->mTag == EENEMY) {
					if (CCollider::Collision(o, m)) {
						CoinRender = 300;
						}
					}
				}
			}
			break;
			
		case CCollider::ETRIANGLE: //�O�p�R���C�_�̎�
			CVector adjust; //�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{      //�Փ˂��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
				mRotation.mY++;
			}
			break;
	}
}

void CCoin::TaskCollision()
{
	//mCollider.ChangePriority();
	//CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}