#include "CSceneExplain.h"
#include "CKey.h"
#include "CUtil.h"
#include "CFade.h"

#define EXPLAIN_IMAGE "Resource\\explain.png"

CSceneExplain::CSceneExplain()
: SceneChangeCount(300)
{
	mExplainImage.Load(EXPLAIN_IMAGE);
}

void CSceneExplain::Init() {
	//�V�[���̐ݒ�
	mScene = EEXPLAIN;
	CFade::SetFade(CFade::FADE_IN);
}

//�X�V�����̃I�[�o�[���C�h
void CSceneExplain::Update() {
	SceneChangeCount--;

	if (SceneChangeCount == 0) {
		//���̃V�[���̓Q�[��
		mNextScene = CScene::EGAME;
		mSceneChange = true;
		CFade::SetFade(CFade::FADE_OUT);
	}
	if (mSceneChange) {
		if (CFade::IsFadeEnd()) {
			mScene = mNextScene;
		}
	}
	Render();
}

void CSceneExplain::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);

	mExplainImage.Draw(-400, 400, -300, 300, 0, 2000, 1100, 100);

	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneExplain::GetNextScene() {
	return mScene;
}