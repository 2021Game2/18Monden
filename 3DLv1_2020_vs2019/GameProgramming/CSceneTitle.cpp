#include "CSceneTitle.h"
#include "CKey.h"
#include "CUtil.h"

CSceneTitle::CSceneTitle()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
}

void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = EGAME;
	}
	Render();
}

void CSceneTitle::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//������ҏW�G���A�̍쐬;

	mText.DrawString("COIN BATTLE", -300, 0, 30, 30);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20);
	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}