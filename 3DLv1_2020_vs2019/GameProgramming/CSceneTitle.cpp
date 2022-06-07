#include "CSceneTitle.h"
#include "CKey.h"
#include "CUtil.h"

CSceneTitle::CSceneTitle()
{
	mText.LoadTexture("Resource\\FontWhite.tga", 1, 64);
}

void CSceneTitle::Init() {
	//シーンの設定
	mScene = ETITLE;
}

//更新処理のオーバーライド
void CSceneTitle::Update() {

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
	Render();
}

void CSceneTitle::Render() {

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定（緑色の半透明）
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//文字列編集エリアの作成;

	mText.DrawString("TITLE", -200, 0, 50, 50);
	mText.DrawString("PUSH ENTER", -190, -70, 20, 20);
	//2Dの描画終了
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}