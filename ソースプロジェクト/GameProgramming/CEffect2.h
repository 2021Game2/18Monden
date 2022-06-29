#ifndef CEFFECT2_H
#define CEFFECT2_H
//ビルボードクラスのインクルード
#include "CBillBoard.h"
/*
エフェクトクラス
テクスチャのアニメーション
*/
class CEffect2 : public CBillBoard {
private:
	//行数
	int mRows;
	//列数
	int mCols;
	//1コマのフレーム数
	int mFps;
	//フレームカウンタ
	int mFrame;
	//マテリアル
	static CMaterial sMaterial;

	//更新
	void Update();
	//描画
	void Render();

public:
	//コンストラクタ
//CEffect(位置, 幅, 高さ, テクスチャ名, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffect2(const CVector& pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
};
#endif