#ifndef CCITY_H
#define CCITY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
#include "CColliderMesh.h"

/*
�L�����N�^�N���X���p��
*/
class CCity : private CCharacter {
	CMatrix mMatrixCol;
private:
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle> mTriangles;

	//�X�V����
	void Update();

	CColliderMesh ColliderMesh;

public:
	//�R���X�g���N�^
	CCity(CModel* model, CVector position, CVector rotation, CVector scale);
};
#endif