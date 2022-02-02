#include "DxLib.h"
#include<time.h>
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_31_ワタナベライキ";

// ウィンドウ横幅
const int WIN_WIDTH = 640;

// ウィンドウ縦幅
const int WIN_HEIGHT = 740;

double easeOutBounce(double x) {
	const int n1 = 7.5625;
	const int d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int block = LoadGraph("block.png");

	int title = LoadGraph("Light.png");
	// ゲームループで使う変数の宣言

	//マップ
	int map[20][20] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	//シェイク
	int randX[6] = {};
	int randY[6] = {};
	int shakeMax = 35;
	int shakeCount = 0;
	int isShake = 0;
	//タイトル
	int ismove = 1;
	double frame = 0.0;
	double endframe = 200;
	double start = 300;
	double end = 100;
	int titleX = 0;
	int titleY = 270;

	//切り替え
	int scene = 0;

	//自機
	int playerPosX = 120;
	int playerPosY = 120;
	int playerSpeed = 5;
	int playerMapX = 0;
	int playerMapY = 0;

	//マウス位置
	int mouseX = 0;
	int mouseY = 0;

	//エミッター位置
	int emitterX = 0;
	int emitterY = 0;
	int emitterR = 60;

	//パーティクル
	const int particleMax = 300;
	int particleX[particleMax] = {};
	int particleY[particleMax] = {};
	int particleIsActive[particleMax] = {};
	int particleSpeed[particleMax] = {};
	int particleMapX[particleMax] = {};
	int particleMapY[particleMax] = {};
	int particleR = 6;

	//演出4の変数
	int startX = 200;
	int startY = 0;
	int endX = 200;
	int endY = 640;
	int startXMap = startX / 32;
	int startYMap = startY / 32;
	int endXMap = endX / 32;
	int endYMap = endY / 32;
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//初期化ボタン
		srand(time(NULL));
		if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0) {
			playerPosX = 120;
			playerPosY = 120;
			scene = 0;
			frame = 0;
			titleX = 0;
			ismove = 1;
			shakeCount = 0;
			for (int i = 0; i < 6; i++) {
				randX[i] = 0;
				randY[i] = 0;
			}
			for (int i = 0; i < particleMax; i++) {
				particleIsActive[i] = 0;
			}
		}

		switch (scene) {

		case 0:
			//演出変更
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 1;
			}
			if (frame == endframe) {
				ismove = 0;
			}
			if (ismove == 1) {
				frame++;
			}

			/*if (ismove == 0&&shakeCount!=shakeMax) {
				randX = GetRand(150 - shakeCount) - shakeMax;
				randY = GetRand(150 - shakeCount) - shakeMax;
				shakeCount += 1;
			}*/
			titleX = start + (end - start) * easeOutBounce(frame / endframe);
			break;

		case 1:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 2;
			}
			if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0) {
				isShake = 1;
				shakeCount = 0;
			}
			if (isShake == 1) {
				for (int i = 0; i < 6; i++) {
					randX[i] = GetRand(70 - shakeCount) - shakeMax;
				}
				shakeCount += 1;
			}
			if (shakeCount >= shakeMax) {
				isShake = 0;
			}
			break;
		case 2:
			//演出変更
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 3;
			}

			//移動処理
			if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT]) {
				if (playerPosX > 16) {
					playerPosX -= playerSpeed;
				}
			}
			if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT]) {
				if (playerPosX < 624) {
					playerPosX += playerSpeed;
				}
			}
			if (keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP]) {
				if (playerPosY > 16) {
					playerPosY -= playerSpeed;
				}
			}
			if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN]) {
				if (playerPosY < 624) {
					playerPosY += playerSpeed;
				}
			}

			playerMapX = playerPosX / 32;
			playerMapY = playerPosY / 32;
			break;
			//演出2
		case 3:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 4;
			}

			GetMousePoint(&emitterX, &emitterY);

			//アクティブ化
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 0) {
					particleIsActive[i] = 1;
					particleX[i] = emitterX + GetRand(emitterR);
					particleY[i] = emitterY + GetRand(emitterR);
					particleSpeed[i] = 10;
					break;
				}
			}

			//移動処理
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					particleY[i] += particleSpeed[i];
				}
			}

			//一番下まで行った際の処理
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					if (particleY[i] + particleR >= 640) {
						particleIsActive[i] = 0;
					}
				}
			}

			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					particleMapX[i] = particleX[i] / 32;
					particleMapY[i] = particleY[i] / 32;
				}
			}

			break;
		case 4:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 1;
			}
			startXMap = startX / 32;
			startYMap = startY / 32;
			endXMap = endX / 32;
			endYMap = endY / 32;
			break;
		}


		///////////
		//描画処理//
		///////////

		switch (scene) {
		case 0:
			DrawGraph(titleX, titleY, title, true);
			break;
		case 1:
			if (isShake == 1) {
				//緑
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(0, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(0, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//赤
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(128, 0, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(128, 0, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//青
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(0, 0, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(0, 0, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//水色
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(0, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(0, 128, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//白
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(128, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(100, 100, 100), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//黄色
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(128, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(128, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
			else {
				//緑
				DrawLine(300, 0, 300, 320, GetColor(0, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 0, 300, 320, GetColor(0, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
				DrawLine(300, 0, 300, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//赤
				DrawLine(100, 0, 100, 320, GetColor(128, 0, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100, 0, 100, 320, GetColor(128, 0, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100, 0, 100, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//青
				DrawLine(500, 0, 500, 320, GetColor(0, 0, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500, 0, 500, 320, GetColor(0, 0, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500, 0, 500, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//水色
				DrawLine(100, 320, 100, 640, GetColor(0, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100, 320, 100, 640, GetColor(0, 128, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100, 320, 100, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//白
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
				DrawLine(300, 320, 300, 640, GetColor(128, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 320, 300, 640, GetColor(100, 100, 100), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 320, 300, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//黄色
				DrawLine(500, 320, 500, 640, GetColor(128, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500, 320, 500, 640, GetColor(128, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500, 320, 500, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
			//操作説明
			DrawFormatString(10, 650, GetColor(255, 255, 255), "シェイク:S");
			break;
			//演出1
		case 2:
			//暗闇にする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++) {
					if (map[y][x] == 1) {
						DrawGraph(x * 32, y * 32, block, true);
					}
				}
			}

			//自機の周りのみうっすらと見えるようにする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
			for (int y = -1; y < 2; y++) {
				for (int x = -1; x < 2; x++) {
					if (map[playerMapY - y][playerMapX - x] == 1) {
						DrawGraph((playerMapX - x) * 32, (playerMapY - y) * 32, block, true);
					}
				}
			}

			//自機ははっきりと見えるようにする
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawCircle(playerPosX, playerPosY, 16, GetColor(255, 255, 255), true, true);

			//操作説明
			DrawFormatString(10, 650, GetColor(255, 255, 255), "自機の移動:WASD");
			break;

			//演出2
		case 3:
			//暗闇にする
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++) {
					if (map[y][x] == 1) {
						DrawGraph(x * 32, y * 32, block, true);
					}
				}
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					if (map[particleMapY[i]][particleMapX[i]] == 1) {
						DrawGraph(particleMapX[i] * 32, particleMapY[i] * 32, block, true);
					}
				}
			}


			SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					DrawCircle(particleX[i], particleY[i], particleR, GetColor(255, 255, 255), true);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "マウスカーソルの位置からパーティクル");
			break;

		case 4:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++) {
					if (map[y][x] == 1) {
						DrawGraph(x * 32, y * 32, block, true);
					}
				}
			}
			//暗闇
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap; i < endYMap; i++) {
					if (map[i][startXMap-x] == 1) {
						DrawGraph((startXMap - x) * 32, i * 32, block, true);
					}
				}
			}

			//水色
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX, startY, endX, endY, GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX, startY, endX, endY, GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX, startY, endX, endY, GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap);

			break;
		}
		//操作ボタン
		DrawLine(0, 640, 640, 640, GetColor(255, 255, 255), 1);
		DrawFormatString(10, 670, GetColor(255, 255, 255), "初期化ボタン:R");
		DrawFormatString(10, 690, GetColor(255, 255, 255), "SPACEで演出切り替え");

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
