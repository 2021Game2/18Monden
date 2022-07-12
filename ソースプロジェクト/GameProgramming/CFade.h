#ifndef CFADE_H
#define CFADE_H

class CFade
{
public:
	enum eFadeMode {
		FADE_IN = 0, //�t�F�[�h�C��
		FADE_OUT, //�t�F�[�h�A�E�g
	};
private:
	float mFade; //�t�F�[�h�ϓ��l
	float mFadeSpeed; //�t�F�[�h�ϓ����x
	bool mbFade; //�t�F�[�h�t���O
	eFadeMode mFadeType; //�t�F�[�h���
	static CFade* gInst; //�C���X�^���X�ێ�

public:
	//�R���X�g���N�^
	CFade();

	//�t�F�[�h�ݒ�
	static void SetFade(eFadeMode type, float speed = 0.01f);
	//�t�F�[�h�����m�F�p
	static bool IsFadeEnd();
	void Update(); //�X�V
	void Render(); //�`��
};

#endif