#include "CSceneTitle.h"
#include "CKey.h"
#include "CUtil.h"
#include "CSound.h"
#include "CFade.h"

CSound TitleBgm;

#define TITLE_IMAGE "Resource\\TitleImage.png"

CSceneTitle::CSceneTitle()
{
	mText.LoadTexture("Resource\\FontGold1.png", 1, 64);
	mTitleImage.Load(TITLE_IMAGE);
}

void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;

	TitleBgm.Load("Resource\\TitleBGM.wav");

	TitleBgm.Repeat();

}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {

	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[������
		//mScene = CScene::EEXPLAIN;
		mSceneChange = true;
		CFade::SetFade(CFade::FADE_OUT);
		TitleBgm.Stop();
	}
	if (mSceneChange) {
		if (CFade::IsFadeEnd()) {
			mScene = CScene::EEXPLAIN;
		}
	}
	Render();
}

void CSceneTitle::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	mTitleImage.Draw(-400, 400, -300, 300, -2000, 2000, 1500, -1500);

	//������ҏW�G���A�̍쐬;
	mText.DrawString("COIN BATTLE", -300, 0, 30, 30);

	mText.DrawString("PUSH ENTER", -190, -70, 20, 20);
	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}