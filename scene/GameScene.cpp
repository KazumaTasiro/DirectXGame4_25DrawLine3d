#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"

//ここからアフェイン変換記入
//大きさ



GameScene::GameScene() {}

GameScene::~GameScene() { delete debugCamera_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 400);
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//座標の初期化
	for (int i = 0; i < 8; i++) {
		rotateBox[i] = vertex[i];
		bigBox[i] = vertex[i];
		translationBox[i] = vertex[i];
	}
	//拡大、回転する前に位置を原点にする
	//拡大
	for (int i = 0; i < 8; i++) {
		bigBox[i].x = moveZeroPoint[0].x * bigBox[i].x + moveZeroPoint[0].y * bigBox[i].y +
			moveZeroPoint[0].z * bigBox[i].z + moveZeroPoint[0].w * 1;

		bigBox[i].y = moveZeroPoint[1].x * bigBox[i].x + moveZeroPoint[1].y * bigBox[i].y +
			moveZeroPoint[1].z * bigBox[i].z + moveZeroPoint[1].w * 1;

		bigBox[i].z = moveZeroPoint[2].x * bigBox[i].x + moveZeroPoint[2].y * bigBox[i].y +
			moveZeroPoint[2].z * bigBox[i].z + moveZeroPoint[2].w * 1;
	}
	//回転
	for (int i = 0; i < 8; i++) {
		rotateBox[i].x = moveZeroPoint[0].x * rotateBox[i].x + moveZeroPoint[0].y * rotateBox[i].y +
			moveZeroPoint[0].z * rotateBox[i].z + moveZeroPoint[0].w * 1;

		rotateBox[i].y = moveZeroPoint[1].x * rotateBox[i].x + moveZeroPoint[1].y * rotateBox[i].y +
			moveZeroPoint[1].z * rotateBox[i].z + moveZeroPoint[1].w * 1;

		rotateBox[i].z = moveZeroPoint[2].x * rotateBox[i].x + moveZeroPoint[2].y * rotateBox[i].y +
			moveZeroPoint[2].z * rotateBox[i].z + moveZeroPoint[2].w * 1;
	}


	//拡大
	for (int i = 0; i < 8; i++) {
		bigBox[i].x = scale[0].x * bigBox[i].x + scale[0].y * bigBox[i].y +
			scale[0].z * bigBox[i].z + scale[0].w * 0;

		bigBox[i].y = scale[1].x * bigBox[i].x + scale[1].y * bigBox[i].y +
			scale[1].z * bigBox[i].z + scale[1].w * 0;

		bigBox[i].z = scale[2].x * bigBox[i].x + scale[2].y * bigBox[i].y +
			scale[2].z * bigBox[i].z + scale[2].w * 0;
	}
	//回転するまえに関数を移す場所
	for (int i = 0; i < 8; i++) {
		vertexContainer[i] = rotateBox[i];
	}
	//回転（本番）
	for (int i = 0; i < 8; i++) {
		rotateBox[i].x = rotate[0].x * vertexContainer[i].x + rotate[0].y * vertexContainer[i].y +
			rotate[0].z * vertexContainer[i].z + rotate[0].w * 0;

		rotateBox[i].y = rotate[1].x * vertexContainer[i].x + rotate[1].y * vertexContainer[i].y +
			rotate[1].z * vertexContainer[i].z + rotate[1].w * 0;

		rotateBox[i].z = rotate[2].x * vertexContainer[i].x + rotate[2].y * vertexContainer[i].y +
			rotate[2].z * vertexContainer[i].z + rotate[2].w * 0;
	}
	//平行移動
	for (int i = 0; i < 8; i++) {
		translationBox[i].x = translation[0].x * translationBox[i].x + translation[0].y * translationBox[i].y +
			translation[0].z * translationBox[i].z + translation[0].w * 1;

		translationBox[i].y = translation[1].x * translationBox[i].x + translation[1].y * translationBox[i].y +
			translation[1].z * translationBox[i].z + translation[1].w * 1;

		translationBox[i].z = translation[2].x * translationBox[i].x + translation[2].y * translationBox[i].y +
			translation[2].z * translationBox[i].z + translation[2].w * 1;
	}

}

void GameScene::Update() { debugCamera_->Update(); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	//ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(vertex[eageList[i][0]], vertex[eageList[i][1]], Vector4(0xff, 0xff, 0xff, 0xff));
		PrimitiveDrawer::GetInstance()->DrawLine3d(rotateBox[eageList[i][0]], rotateBox[eageList[i][1]], Vector4(0xff, 0x00, 0x00, 0xff));
		PrimitiveDrawer::GetInstance()->DrawLine3d(bigBox[eageList[i][0]], bigBox[eageList[i][1]], Vector4(0x00, 0x00, 0xff, 0xff));
		PrimitiveDrawer::GetInstance()->DrawLine3d(translationBox[eageList[i][0]], translationBox[eageList[i][1]], Vector4(0x00, 0xff, 0x00, 0xff));
	}

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
