#include "CMakimono.h"
#include "CTaskManager.h"
#define VELOCITY 0.11f;
#include "CPlayer.h"
#include "CCollisionManager.h"

//�R���X�g���N�^
CMakimono::CMakimono(CModel* model, CVector position,
	CVector rotation, CVector scale)
	: mCollider(this, &mMatrix, CVector(0.15f, 0.0f, 0.0f), 1.0f)
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
	mTag = EMAKIMONO;
}


//�X�V����
void CMakimono::Update() {
	//�s����X�V
	CTransform::Update();

}

//�Փˏ���
//Collision(�R���C�_�P,�R���C�_�Q)
void CMakimono::Collision(CCollider* m, CCollider* o) {
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
					}
				}
			}
			break;
		}
	}
}

void CMakimono::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}