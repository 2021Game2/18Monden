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
	
	float myadd; //�d��

	float mSpeed; //�_�b�V������

	float mCurve; //�J�[�u����

	CVector OldRotate;

	CVector mPoint;	//�ڕW�n�_

	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* adjust);

public:
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();

	static CPlayer* spThis;

	int mTime;

	int mCoinGet; //�R�C���l����

	int mEnemyCoinGet; //�G�R�C���l����

	int mBulletP; //�e��

};

#endif

