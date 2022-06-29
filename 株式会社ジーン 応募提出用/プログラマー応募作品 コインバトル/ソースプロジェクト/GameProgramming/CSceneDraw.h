#ifndef CSCENEDRAW_H
#define CSCENEDRAW_H

#include "CScene.h"
#include "CText.h"

class CSceneDraw : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CText mText;

public:
	CSceneDraw();
};

#endif
