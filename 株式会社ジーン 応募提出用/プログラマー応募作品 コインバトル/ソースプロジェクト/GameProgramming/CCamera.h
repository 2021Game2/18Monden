#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"
#include "CPlayer.h"
/*
�J�����N���X
*/
#define DEF_CAMERA_DIST 2.5f
#define DEF_CAMERA_HEAD_ADJUST 0.75f
class CCamera : public CCharacter{
private:
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;

	
	CColliderLine mLine; //�����R���C�_

	CMatrix mMatrix;
	CMatrix mProj;

	//�d�����邪�J��������p
	CVector mPos;		//�ʒu
	CVector mTarget;	//�^�[�Q�b�g
	float	mAngleX;	//�A���O��
	float	mAngleY;	//�A���O��
	float	mDist;	//����


	//�J����������
	void Init();


	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

	//�J�����K�p
	void Render();

	//�x�N�g���擾
	CMatrix GetMat();
	//�v���W�F�N�V�����}�g���N�X�擾
	CMatrix GetProjMat();

	//�X�N���[�����W�ϊ�
	//�߂�l �\���͈�
	//pOut ���ʊi�[�p
	//pos 2D�ɕϊ����������[���h���W
	bool WorldToScreen(CVector* pOut, const CVector& pos);

public:
	//���_
	CVector mEye;

	CCamera();

	CVector mRotation;

	//�J�����̐ݒ�
//Set(���_, �����_, �����)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);

	void SetTarget(const CVector& target);

	void SetAddRotate(const CVector& target);


	//�J�����X�V����
	void Update();
	//�J�����K�p
	void Draw();

};

//�J�����̊O���Q��
extern CCamera* Camera;
#endif
