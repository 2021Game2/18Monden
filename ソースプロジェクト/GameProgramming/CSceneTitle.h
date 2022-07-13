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
	//���̃V�[���̎擾
	EScene GetNextScene();

	CModel mBackGround;

	CText mText;
 
	CTexture mTitleImage;

	bool CSceneTitle::mSceneChange;

	CScene::EScene CSceneTitle::mNextScene;
	
public:
	CSceneTitle();
};

#endif
