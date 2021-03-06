#ifndef CSCENEDRAW_H
#define CSCENEDRAW_H

#include "CScene.h"
#include "CText.h"

class CSceneDraw : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//次のシーンの取得
	EScene GetNextScene();

	CText mText;

public:
	CSceneDraw();
};

#endif
