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
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CTexture mExplainImage;

	bool CSceneExplain::mSceneChange;

	CScene::EScene CSceneExplain::mNextScene;

	int SceneChangeCount;

public:
	CSceneExplain();
};

#endif
