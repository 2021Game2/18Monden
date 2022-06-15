#include "CSceneWin.h"
#include "CKey.h"
#include "CUtil.h"

CSceneWin::CSceneWin()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
}

void CSceneWin::Init() {
	//�V�[���̐ݒ�
	mScene = EWIN;
}

//�X�V�����̃I�[�o�[���C�h
void CSceneWin::Update() {

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mScene = ETITLE;
	}
	Render();
}

void CSceneWin::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//������ҏW�G���A�̍쐬;

	mText.DrawString("WIN", -100, 0, 50, 50);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20);

	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneWin::GetNextScene() {
	return mScene;
}