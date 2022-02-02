#include "DxLib.h"
#include<time.h>
// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1B_31_���^�i�x���C�L";

// �E�B���h�E����
const int WIN_WIDTH = 640;

// �E�B���h�E�c��
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
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int block = LoadGraph("block.png");

	int title = LoadGraph("Light.png");
	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//�}�b�v
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

	//�V�F�C�N
	int randX[6] = {};
	int randY[6] = {};
	int shakeMax = 35;
	int shakeCount = 0;
	int isShake = 0;
	//�^�C�g��
	int ismove = 1;
	double frame = 0.0;
	double endframe = 200;
	double start = 300;
	double end = 100;
	int titleX = 0;
	int titleY = 270;

	//�؂�ւ�
	int scene = 0;

	//���@
	int playerPosX = 120;
	int playerPosY = 120;
	int playerSpeed = 5;
	int playerMapX = 0;
	int playerMapY = 0;

	//�}�E�X�ʒu
	int mouseX = 0;
	int mouseY = 0;

	//�G�~�b�^�[�ʒu
	int emitterX = 0;
	int emitterY = 0;
	int emitterR = 60;

	//�p�[�e�B�N��
	const int particleMax = 300;
	int particleX[particleMax] = {};
	int particleY[particleMax] = {};
	int particleIsActive[particleMax] = {};
	int particleSpeed[particleMax] = {};
	int particleMapX[particleMax] = {};
	int particleMapY[particleMax] = {};
	int particleR = 6;

	//���o4�̕ϐ�
	int startX = 200;
	int startY = 0;
	int endX = 200;
	int endY = 640;
	int startXMap = startX / 32;
	int startYMap = startY / 32;
	int endXMap = endX / 32;
	int endYMap = endY / 32;
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�������{�^��
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
			//���o�ύX
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
			//���o�ύX
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 3;
			}

			//�ړ�����
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
			//���o2
		case 3:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				scene = 4;
			}

			GetMousePoint(&emitterX, &emitterY);

			//�A�N�e�B�u��
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 0) {
					particleIsActive[i] = 1;
					particleX[i] = emitterX + GetRand(emitterR);
					particleY[i] = emitterY + GetRand(emitterR);
					particleSpeed[i] = 10;
					break;
				}
			}

			//�ړ�����
			for (int i = 0; i < particleMax; i++) {
				if (particleIsActive[i] == 1) {
					particleY[i] += particleSpeed[i];
				}
			}

			//��ԉ��܂ōs�����ۂ̏���
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
		//�`�揈��//
		///////////

		switch (scene) {
		case 0:
			DrawGraph(titleX, titleY, title, true);
			break;
		case 1:
			if (isShake == 1) {
				//��
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(0, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(0, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
				DrawLine(300 + randX[0], 0, 300 + randX[0], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(128, 0, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(128, 0, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100 + randX[1], 0, 100 + randX[1], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(0, 0, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(0, 0, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500 + randX[2], 0, 500 + randX[2], 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//���F
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(0, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(0, 128, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100 + randX[3], 320, 100 + randX[3], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(128, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(100, 100, 100), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300 + randX[4], 320, 300 + randX[4], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//���F
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(128, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(128, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500 + randX[5], 320, 500 + randX[5], 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
			else {
				//��
				DrawLine(300, 0, 300, 320, GetColor(0, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 0, 300, 320, GetColor(0, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 220);
				DrawLine(300, 0, 300, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				DrawLine(100, 0, 100, 320, GetColor(128, 0, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100, 0, 100, 320, GetColor(128, 0, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100, 0, 100, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				DrawLine(500, 0, 500, 320, GetColor(0, 0, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500, 0, 500, 320, GetColor(0, 0, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500, 0, 500, 320, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//���F
				DrawLine(100, 320, 100, 640, GetColor(0, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(100, 320, 100, 640, GetColor(0, 128, 128), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(100, 320, 100, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
				DrawLine(300, 320, 300, 640, GetColor(128, 128, 128), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 320, 300, 640, GetColor(100, 100, 100), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(300, 320, 300, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);

				//���F
				DrawLine(500, 320, 500, 640, GetColor(128, 128, 0), 50);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
				DrawLine(500, 320, 500, 640, GetColor(128, 128, 0), 35);
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				DrawLine(500, 320, 500, 640, GetColor(255, 255, 255), 10);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			}
			//�������
			DrawFormatString(10, 650, GetColor(255, 255, 255), "�V�F�C�N:S");
			break;
			//���o1
		case 2:
			//�Èłɂ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 20; x++) {
					if (map[y][x] == 1) {
						DrawGraph(x * 32, y * 32, block, true);
					}
				}
			}

			//���@�̎���݂̂�������ƌ�����悤�ɂ���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
			for (int y = -1; y < 2; y++) {
				for (int x = -1; x < 2; x++) {
					if (map[playerMapY - y][playerMapX - x] == 1) {
						DrawGraph((playerMapX - x) * 32, (playerMapY - y) * 32, block, true);
					}
				}
			}

			//���@�͂͂�����ƌ�����悤�ɂ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawCircle(playerPosX, playerPosY, 16, GetColor(255, 255, 255), true, true);

			//�������
			DrawFormatString(10, 650, GetColor(255, 255, 255), "���@�̈ړ�:WASD");
			break;

			//���o2
		case 3:
			//�Èłɂ���
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
			DrawFormatString(10, 650, GetColor(255, 255, 255), "�}�E�X�J�[�\���̈ʒu����p�[�e�B�N��");
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
			//�È�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap; i < endYMap; i++) {
					if (map[i][startXMap-x] == 1) {
						DrawGraph((startXMap - x) * 32, i * 32, block, true);
					}
				}
			}

			//���F
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
		//����{�^��
		DrawLine(0, 640, 640, 640, GetColor(255, 255, 255), 1);
		DrawFormatString(10, 670, GetColor(255, 255, 255), "�������{�^��:R");
		DrawFormatString(10, 690, GetColor(255, 255, 255), "SPACE�ŉ��o�؂�ւ�");

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
