#include "CCamera.h"
#include "Ckey.h"
#include "glut.h"
#include <corecrt_math.h>
#include <stdio.h>
#include "CInput.h"
#include "main.h"
#include "CCollisionManager.h"

#define _USE_MATH_DEFINES

//�J�����̊O���ϐ�
CCamera*Camera;


CCamera::CCamera()
	: mLine(this, nullptr, CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f))
{
	mPriority = 0;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CCamera::Init()
{
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Set(e, c, u);

}
void CCamera::Set(const CVector& eye, const CVector& center,
	const CVector& up) {
	mEye = eye;
	mCenter = center;
	mUp = up;

	mPos = eye;
	mTarget = center;
	mAngleX = 0.0f;
	mAngleY = 1.0f;
	mDist = DEF_CAMERA_DIST;

}
void CCamera::SetTarget(const CVector& target)
{
	mTarget = target;
}
//�~����M_PI��L���ɂ���
#define USE_MATH_DEFINES
//���w�֐��̃C���N���[�h
#include <math.h>

void CCamera::SetAddRotate(const CVector& rotate)
{
	mAngleX -= rotate.mY / 180.0f * M_PI;
}


void CCamera::Update() {
	static int oldMouseX(0), oldMouseY(0);
	int mouseX(0), mouseY(0);
	CInput::GetMousePos(&mouseX, &mouseY);


	float moveX = (float)(oldMouseX - mouseX);
	float moveY = (float)(oldMouseY - mouseY);


	if (CInput::GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (moveX != 0) mAngleX += (moveX * 0.01f);
		if (moveY != 0) mAngleY += (moveY * 0.01f);
	}

	int wheel = CInput::GetWheelValue();
	if (wheel != 0) {
		mDist -= (float)(wheel) * 0.5f;
	}


	//X���{��]
	//if (CKey::Push('K')) {
	//	Matrix = Matrix * CMatrix().RotateX(1);
	//}
	//if (CKey::Push('I')) {
	//	Matrix = Matrix * CMatrix().RotateX(-1);
	//}
	////Y���{��]
	//if (CKey::Push('L')) {
	//	Matrix = Matrix * CMatrix().RotateY(1);
	//}
	//if (CKey::Push('J')) {
	//	Matrix = Matrix * CMatrix().RotateY(-1);
	//}

	if (CKey::Push(VK_RIGHT)) {
		mAngleX += 0.1f;
	}
	if (CKey::Push(VK_LEFT)) {
		mAngleX -= 0.1f;
	}
	if (CKey::Push(VK_UP)) {
		mAngleY += 0.01f;
	}
	if (CKey::Push(VK_DOWN)) {
		mAngleY -= 0.01f;
	}

	//Y������ 0�`3.14��180�x�͈�
	if (mAngleY < 0.05f) mAngleY = 0.05f;
	if (mAngleY > 3.12f) mAngleY = 3.12f;

	mPos.mX = mTarget.mX + (sinf(mAngleX)) * (mDist * sinf(mAngleY));
	mPos.mY = mTarget.mY + cosf(mAngleY) * mDist;
	mPos.mZ = mTarget.mZ + (cosf(mAngleX)) * (mDist * sinf(mAngleY));


	mCenter = mTarget;
	mCenter.mY += DEF_CAMERA_HEAD_ADJUST;//����␳
	mEye = mPos;

	//mJump.Play();

	//�s��ݒ�
//	glMultMatrixf(Matrix.mF);
//	Camera.mEye = CVector(1.0f, 2.0f, 10.0f) * Matrix;

	mLine.Set(this, nullptr, mEye, mCenter);

	oldMouseX = mouseX;
	oldMouseY = mouseY;
	CInput::InputReset();

}

void CCamera::Draw() {
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
		mCenter.mX, mCenter.mY, mCenter.mZ,
		mUp.mX, mUp.mY, mUp.mZ);

	//�J�����s��i�[
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.mF);
}

void CCamera::Render() {
	//gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
		//mCenter.mX, mCenter.mY, mCenter.mZ,
		//mUp.mX, mUp.mY, mUp.mZ);

	//�J�����s��i�[
	//glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.mF);
	//glGetFloatv(GL_PROJECTION_MATRIX, mProj.mF);

}

CMatrix CCamera::GetMat() {
	return mMatrix;
}
CMatrix CCamera::GetProjMat() {
	return mProj;
}

bool CCamera::WorldToScreen(CVector* pOut, const CVector& pos)
{
	//���W�ϊ�
	CVector	screen_pos = mMatrix * pos;

	//��ʊO�Ȃ̂Ń��^�[��
	if (screen_pos.mZ >= 0.0f) {
		return false;
	}
	//���W����
	screen_pos = screen_pos / -screen_pos.mZ;

	//	printf("%f,%f,%f\n", screen_pos.mX, screen_pos.mY, screen_pos.mZ);

	//�X�N���[���ϊ�
	pOut->mX = (1.0f + screen_pos.mX) * WINDOW_WIDTH * 0.5f;
	pOut->mY = (1.0f + screen_pos.mY) * WINDOW_HEIGHT * 0.5f;
	pOut->mZ = screen_pos.mZ;

	return true;
}

void CCamera::Collision(CCollider* m, CCollider* o)
{
	m->mType = CCollider::ELINE;

	if (o->mType == CCollider::ETRIANGLE) {
		CVector adjust;
		if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
			mEye += (adjust + adjust.Normalize() * 0.5f);
			mLine.Set(this, nullptr, mEye, mCenter);
		}
	}
}

void CCamera::TaskCollision() {
	mLine.ChangePriority();
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
}