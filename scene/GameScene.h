#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"
#include <math.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	double M_PI = 3.141592;
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//頂点の配列
	Vector3 vertex[8] =
	{
		{0,0,0},
		{5,0,0},
		{5,0,5},
		{0,0,5},
		{0,5,0},
		{5,5,0},
		{5,5,5},
		{0,5,5}
	};
	//拡大した箱
	Vector3 bigBox[8];
	//回転する箱
	Vector3 rotateBox[8];
	//平行移動する箱
	Vector3 translationBox[8];

	//回転のときの避難先
	Vector3 vertexContainer[8] =
	{
		{0,0,0},
		{5,0,0},
		{5,0,5},
		{0,0,5},
		{0,5,0},
		{5,5,0},
		{5,5,5},
		{0,5,5}
	};

	int eageList[12][2] = {
		{0,1},
		{1,2},
		{2,3},
		{3,0},
		{0,4},
		{1,5},
		{2,6},
		{3,7},
		{4,5},
		{5,6},
		{6,7},
		{7,4}

	};
	//大きさ
	Vector4 scale[4] = {
		{2,0,0,0},
		{0,3,0,0},
		{0,0,2,0},
		{0,0,0,1}
	};
	//Y軸の回転
	Vector4 rotate[4] = {
		{cosf(M_PI/4),0,sinf(M_PI/4),0},
		{0,1,0,0,},
		{-sinf(M_PI/4),0,cosf(M_PI/4),0},
		{0,0,0,1}
	};

	//平行移動
	//元の位置に戻す
	Vector4 translation[4] = {
		{1,0,0,5},
		{0,1,0,5},
		{0,0,1,5},
		{0,0,0,1}
	};

	//原点に移動させる
	Vector4 moveZeroPoint[4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
};
