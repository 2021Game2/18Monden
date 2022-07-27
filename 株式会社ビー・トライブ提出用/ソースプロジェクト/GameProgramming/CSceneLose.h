#ifndef CSCENELOSE_H
#define CSCENELOSE_H

#include "CScene.h"
#include "CText.h"

class CSceneLose : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();

	CText mText;
	CTexture mLoseImage;

public:
	CSceneLose();
};

#endif
