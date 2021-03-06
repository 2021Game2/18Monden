#include "CSceneWin.h"
#include "CKey.h"
#include "CUtil.h"
#include "CSound.h"

CSound fanfare;

#define WIN_IMAGE "Resource\\ResultCoin.png"

CSceneWin::CSceneWin()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
	mWinImage.Load(WIN_IMAGE);
}

void CSceneWin::Init() {
	//シーンの設定
	mScene = EWIN;

	fanfare.Load("Resource\\fanfare.wav");

	fanfare.Play();
}

//更新処理のオーバーライド
void CSceneWin::Update() {

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = ETITLE;
		fanfare.Stop();
	}
	Render();
}

void CSceneWin::Render() {

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	mWinImage.Draw(-400, 400, -300, 300, -500, 0, 300, 0);
	//描画色の設定
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//文字列編集エリアの作成;

	mText.DrawString("WIN", -100, 0, 50, 50);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20);

	//2Dの描画終了
	CUtil::End2D();
}

CScene::EScene CSceneWin::GetNextScene() {
	return mScene;
}