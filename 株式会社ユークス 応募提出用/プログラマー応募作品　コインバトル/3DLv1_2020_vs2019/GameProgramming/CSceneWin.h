#ifndef CSCENEWIN_H
#define CSCENEWIN_H

#include "CScene.h"
#include "CText.h"

class CSceneWin : public CScene {
public:
	CSceneWin();

	void Init();
	void Update();
	void Render();
	//次のシーンの取得
	EScene GetNextScene();

	CText mText;
};

#endif
