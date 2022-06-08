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
public:
	//�R���X�g���N�^
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//�X�V����
	void Update();

	//�R���C�_
	CCollider mCollider;

	static CCoin *spThis;

	//�Փˏ���
	//Collision(�R���C�_�P,�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);

	int mFx; //X�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:�E�ֈړ�
	int mFy; //Y�������̈ړ� -1:�� 0:�ړ����Ȃ� 1:��ֈړ�wwwwwwww

	void TaskCollision();

	int Time;

	int CoinRender;

	void Render();

	void ColliderRender();
};

#endif