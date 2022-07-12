#ifndef CSCENEEXPLAIN_H
#define CSCENEEXPLAIN_H

#include "CScene.h"
#include "CText.h"
#include "CModel.h"

class CSceneExplain : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();

	CTexture mExplainImage;

public:
	CSceneExplain();
};

#endif
