#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CCharacter.h"
/*
�r���{�[�h�N���X
��ɃJ�����̕��������l�p�`
*/
class CBillBoard : public CCharacter {
private:
	//�}�e���A��
	CMaterial mMaterial;
	//�R���X�g���N�^
	CBillBoard();
	//�ʒu�Ƒ傫���̐ݒ�
	//Set(�ʒu, ��, ����)
	void Set(CVector pos, float w, float h);

public:
	//�O�p�`2��
	CTriangle mT[2];
	//CBillBoard(�ʒu, ��, ����)
	CBillBoard(CVector pos, float w, float h);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* mpMaterial);
};
#endif
