#include "CSceneLose.h"
#include "CKey.h"
#include "CUtil.h"
#include "CSound.h"

CSound LoseSe;

CSceneLose::CSceneLose()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
}

void CSceneLose::Init() {
	//�V�[���̐ݒ�
	mScene = ELOSE;

	LoseSe.Load("Resource\\Lose.wav");

	LoseSe.Play();
}

//�X�V�����̃I�[�o�[���C�h
void CSceneLose::Update() {

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = ETITLE;
	}
	Render();
}

void CSceneLose::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//������ҏW�G���A�̍쐬;

	mText.DrawString("LOSE", -150, 0, 50, 50);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20); 

	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneLose::GetNextScene() {
	return mScene;
}