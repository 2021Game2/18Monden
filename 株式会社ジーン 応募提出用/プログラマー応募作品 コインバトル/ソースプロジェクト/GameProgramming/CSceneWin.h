#ifndef CSCENEWIN_H
#define CSCENEWIN_H

#include "CScene.h"
#include "CText.h"

class CSceneWin : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();

	CText mText;
	CTexture mWinImage;

public:
	CSceneWin();
};

#endif
