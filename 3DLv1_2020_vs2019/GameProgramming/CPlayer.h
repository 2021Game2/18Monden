#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//
#include "CBullet.h"
//
#include "CColliderLine.h"
//
#include "CText.h"

#include "CCollider.h"
/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter {
public:
	int mFireCount;
	CCollider mCollider;
	CText mText;
	static CPlayer *spThis;
	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2;
	CColliderLine mLine3;
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
//	CBullet bullet;
	//�X�V����
	void Update();
	//�Փˏ���
	void Collision(CCollider *m, CCollider *o);
	//�Փˏ���
	void TaskCollision();
	//�`�揈��
	void Render();

	int mJump; //�W�����v�t���O
	//�d��
	float x = 300.0f;
	float y = 300.0f;
	float yadd;

	//�_�b�V������
	float t = 1;

	float c = 1;

	int CoinGet;

	int BulletP;
};

#endif

