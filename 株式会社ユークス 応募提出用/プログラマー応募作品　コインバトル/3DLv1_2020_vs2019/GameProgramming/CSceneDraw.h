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
	//���̃V�[���̎擾
	EScene GetNextScene();

	CText mText;
};

#endif
