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
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CText mText;
};

#endif
