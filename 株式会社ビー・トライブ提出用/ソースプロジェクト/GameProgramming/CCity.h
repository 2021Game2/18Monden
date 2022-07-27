#ifndef CCITY_H
#define CCITY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
#include "CColliderMesh.h"

/*
キャラクタクラスを継承
*/
class CCity : private CCharacter {
	CMatrix mMatrixCol;
private:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;

	//更新処理
	void Update();

	CColliderMesh ColliderMesh;

public:
	//コンストラクタ
	CCity(CModel* model, CVector position, CVector rotation, CVector scale);
};
#endif