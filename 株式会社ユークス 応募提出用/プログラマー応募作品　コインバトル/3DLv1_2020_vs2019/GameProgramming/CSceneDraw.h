#ifndef CSCENEDRAW_H
#define CSCENEDRAW_H

#include "CScene.h"
#include "CText.h"

class CSceneDraw : public CScene {
public:
	CSceneDraw();

	void Init();
	void Update();
	void Render();
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CText mText;
};

#endif
