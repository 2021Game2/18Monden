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
class CPlayer : public CCharacter , CVector{
private:
	int mFireCount;
	CCollider mCollider;
	CText mText;
	CText mCoinText;
	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2;
	CColliderLine mLine3;

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

	float t = 1; //�_�b�V������

	float curve = 1; //�J�[�u����

	CVector OldRotate;

	CVector mPoint;	//�ڕW�n�_

	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);

public:
	//�f�t�H���g�R���X�g���N�^
	CPlayer();

	static CPlayer* spThis;

	int Time = 60 * 60; //��������

	int CoinGet; //�R�C���l����

	int EnemyCoinGet; //�G�R�C���l����

	int BulletP; //�e��

};

#endif

