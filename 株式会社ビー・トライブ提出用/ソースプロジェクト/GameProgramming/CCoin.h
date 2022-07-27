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
	//�R���C�_
	CCollider mCollider;

	//�X�V����
	void Update();

	void Render();

	//�Փˏ���
//Collision(�R���C�_�P,�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

public:
	static CCoin* spThis;

	//�R���X�g���N�^
	CCoin(CModel* model, CVector position, CVector rotation, CVector scale);
	//�f�X�g���N�^
	~CCoin();

	int CoinRender;
};

#endif