#ifndef CBULLETITEM_H
#define CBULLETITEM_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
#include "CCollider.h"
#include "CEffect.h"

/*
�L�����N�^�N���X���p��
*/
class CBulletItem : private CCharacter{
private:
	//�X�V����
	void Update();

	//�R���C�_
	CCollider mCollider;

	//�Փˏ���
	//Collision(�R���C�_�P,�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);
	int mFx;
	int mFy;

	void TaskCollision();

public:
	//�R���X�g���N�^
	CBulletItem(CModel* model, CVector position, CVector rotation, CVector scale);
};

#endif