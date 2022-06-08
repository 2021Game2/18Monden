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
public:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//コンストラクタ
	CCity(CModel* model, CVector position, CVector rotation, CVector scale);
	//更新処理
	void Update();

	CColliderMesh ColliderMesh;
};
#endif