#ifndef CSCENELOSE_H
#define CSCENELOSE_H

#include "CScene.h"
#include "CText.h"

class CSceneLose : public CScene {
public:
	CSceneLose();

	void Init();
	void Update();
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();

	CText mText;
};

#endif
