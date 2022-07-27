#include "CGround.h"
#include "CTaskManager.h"

//�R���X�g���N�^
//CEnemy(���f��,�ʒu,��],�g�k)
CGround::CGround(CModel* model, CVector position,
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
	ColliderMesh.Set(this, &mMatrix, mpModel);
}


//�X�V����
void CGround::Update() {
	//�s����X�V

}
