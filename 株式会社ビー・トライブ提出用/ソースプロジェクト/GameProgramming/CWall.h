#ifndef CWALL_H
#define CWALL_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
#include "CColliderMesh.h"

/*
エネミークラス
キャラクタクラスを継承
*/
class CWall : private CCharacter {
	CMatrix mMatrixCol;
private:
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//更新処理
	void Update();

	CColliderMesh ColliderMesh;

public:
	//コンストラクタ
    //CWall(モデル,位置,回転,拡縮)
	CWall(CModel* model, CVector position, CVector rotation, CVector scale);
};

#endif