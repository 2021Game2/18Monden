#ifndef CEFFECT2_H
#define CEFFECT2_H
//�r���{�[�h�N���X�̃C���N���[�h
#include "CBillBoard.h"
/*
�G�t�F�N�g�N���X
�e�N�X�`���̃A�j���[�V����
*/
class CEffect2 : public CBillBoard {
private:
	//�s��
	int mRows;
	//��
	int mCols;
	//1�R�}�̃t���[����
	int mFps;
	//�t���[���J�E���^
	int mFrame;
	//�}�e���A��
	static CMaterial sMaterial;

	//�X�V
	void Update();
	//�`��
	void Render();

public:
	//�R���X�g���N�^
//CEffect(�ʒu, ��, ����, �e�N�X�`����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffect2(const CVector& pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
};
#endif