#ifndef CCOIN_H
#define CCOIN_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
#include "CCollider.h"
#include "CEffect2.h"

/*
�A�C�e���N���X
�L�����N�^�N���X���p��
*/
class CCoin : private CCharacter {
private:

	int Time;

	//�R���C�_
	CCollider mCollider;

public:
	//�R���X�g���N�^
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();

	static CCoin *spThis;

	//�Փˏ���
	//Collision(�R���C�_�P,�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

	void Render();

	void ColliderRender();

	int CoinRender;
};

#endif