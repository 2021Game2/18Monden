#include "CSceneLose.h"
#include "CKey.h"
#include "CUtil.h"
#include "CSound.h"

#define LOSE_IMAGE "Resource\\ResultBomb.png"

CSound LoseSe;

CSceneLose::CSceneLose()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
	mLoseImage.Load(LOSE_IMAGE);
}

void CSceneLose::Init() {
	//シーンの設定
	mScene = ELOSE;

	LoseSe.Load("Resource\\Lose.wav");

	LoseSe.Play();
}

//更新処理のオーバーライド
void CSceneLose::Update() {

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = ETITLE;
	}
	Render();
}

void CSceneLose::Render() {

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	mLoseImage.Draw(-400, 400, -300, 300, 2500, 0, 1000, 0);
	//描画色の設定
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//文字列編集エリアの作成;

	mText.DrawString("LOSE", -150, 0, 50, 50);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20); 

	//2Dの描画終了
	CUtil::End2D();
}

CScene::EScene CSceneLose::GetNextScene() {
	return mScene;
}