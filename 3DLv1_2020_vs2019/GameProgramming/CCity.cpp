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
	cube.Load("cube.obj","cube.mtl");
	mMatrixCol = CMatrix().Scale(18.0f, 23.0f, 17.0f) * mMatrix;
	ColliderMesh.Set(this, &mMatrixCol, &cube);
}


//�X�V����
void CCity::Update() {
	//�s����X�V
	
}