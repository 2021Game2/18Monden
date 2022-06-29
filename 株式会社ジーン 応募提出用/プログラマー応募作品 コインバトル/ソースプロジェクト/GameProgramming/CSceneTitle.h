#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"
#include "CModel.h"

class CSceneTitle : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CModel mBackGround;

	CText mText;

	CTexture mTitleImage;
	
public:
	CSceneTitle();
};

#endif
