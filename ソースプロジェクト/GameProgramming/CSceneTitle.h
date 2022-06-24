#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"
#include "CModel.h"

class CSceneTitle : public CScene {
public:
	CSceneTitle();

	void Init();
	void Update();
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();

	CModel mBackGround;

	CText mText;

	CTexture mTitleImage;
};

#endif
