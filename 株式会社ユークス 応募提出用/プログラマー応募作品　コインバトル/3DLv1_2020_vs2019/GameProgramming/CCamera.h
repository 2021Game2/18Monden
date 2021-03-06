#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"
#include "CPlayer.h"
/*
カメラクラス
*/
#define DEF_CAMERA_DIST 2.5f
#define DEF_CAMERA_HEAD_ADJUST 0.75f
class CCamera : public CCharacter{
public:
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;

	CCamera();
	CColliderLine mLine; //線分コライダ

	CMatrix mMatrix;
	CMatrix mProj;

	//重複するがカメラ制御用
	CVector mPos;		//位置
	CVector mTarget;	//ターゲット
	CVector mRotation;
	float	mAngleX;	//アングル
	float	mAngleY;	//アングル
	float	mDist;	//距離

	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);

	void SetTarget(const CVector& target);

	void SetAddRotate(const CVector& target);

	//カメラ初期化
	void Init();
	//カメラ更新処理
	void Update();
	//カメラ適用
	void Draw();

	//衝突処理
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();

	//カメラ適用
	void Render();

	//ベクトル取得
	CMatrix GetMat();
	//プロジェクションマトリクス取得
	CMatrix GetProjMat();

	//スクリーン座標変換
	//戻り値 表示範囲
	//pOut 結果格納用
	//pos 2Dに変換したいワールド座標
	bool WorldToScreen(CVector* pOut, const CVector& pos);

};

//カメラの外部参照
extern CCamera* Camera;
#endif
