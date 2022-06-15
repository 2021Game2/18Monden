#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"

class CSceneTitle : public CScene {
public:
	CSceneTitle();

	void Init();
	void Update();
	void Render();
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CText mText;
};

#endif
