#include "CCity.h"
#include "CTaskManager.h"

//�R���X�g���N�^
CCity::CCity(CModel* model, CVector position,
	CVector rotation, CVector scale)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //�폜����
	CTaskManager::Get()->Add(this); //�ǉ�����

	CTransform::Update();

	//ColliderMesh.Set(this, &mMatrix, mpModel);

	CModel cube;
	cube.Load("Resource\\cube.obj","Resource\\cube.mtl"); 
	mMatrixCol = CMatrix().Scale(17.5f, 15.0f, 16.0f) * mMatrix;
	ColliderMesh.Set(this, &mMatrixCol, &cube);
	mTag = EHOUSE;
}

//�X�V����
void CCity::Update() {
	//�s����X�V
	
}