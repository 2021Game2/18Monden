#include "CBullet.h"
#include "CCollisionManager.h"

CBullet::CBullet()
: mLife(50)
, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{}

//���Ɖ��s���̐ݒ�
//Set(��, ���s)
void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
}

//�X�V
void CBullet::Update() {
	//�������Ԃ̔���
	if (mLife-- > 0) {
		CTransform::Update();
		//mRotation.mY += 10;
		//�ʒu�X�V
		mPosition = CVector(0.0f, 0.0f, 1.0f)* mMatrix;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}//
}

//�`��
void CBullet::Render() {
//	mCollider.Render();

	mModelShuriken.Load("Shuriken4.obj", "Shuriken4.mtl");
	mModelShuriken.Render(mMatrix);
}

//�Փˏ���
//Collision(�R���C�_1, �R���C�_2)
void CBullet::Collision(CCollider *m, CCollider *o) {
	//���肪�T�[�`�̎��͖߂�
	if (o->mTag == CCollider::ESEARCH)
	{
		return;
	}

	//�R���C�_��m��y���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}

	return;

	if (m->mType == CCollider::ESPHERE
		&& o->mType == CCollider::ESPHERE)
	{
		switch (o->mTag)
		{
		case CCollider::ESEARCH:
			break;
		default:
			//�R���C�_��m��y���Փ˂��Ă��邩����
			if (CCollider::Collision(m, o)) {
				//�Փ˂��Ă��鎞�͖����ɂ���
				mEnabled = false;
			}
		}
	}
}
void CBullet::TaskCollision()
{
	mCollider.ChangePriority();
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}

