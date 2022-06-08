#include "CCity.h"
#include "CTaskManager.h"

//コンストラクタ
CCity::CCity(CModel* model, CVector position,
	CVector rotation, CVector scale)
{
	//モデル、位置、回転、拡縮を設定する
	mpModel = model; //モデルの設定
	mPosition = position; //位置の設定
	mRotation = rotation; //回転の設定
	mScale = scale; //拡縮の設定
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this); //削除して
	CTaskManager::Get()->Add(this); //追加する

	CTransform::Update();

	//ColliderMesh.Set(this, &mMatrix, mpModel);

	CModel cube;
	cube.Load("Resource\\cube.obj","Resource\\cube.mtl"); 
	mMatrixCol = CMatrix().Scale(17.5f, 15.0f, 16.0f) * mMatrix;
	ColliderMesh.Set(this, &mMatrixCol, &cube);
	mTag = EHOUSE;
}

//更新処理
void CCity::Update() {
	//行列を更新
	
}