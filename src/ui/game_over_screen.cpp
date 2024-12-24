#include "stdlibs.h"

#include "ui/game_over_screen.h"
#include <graphics.h>
#include "resource.h"
#include "ui/Button.h"
#include "general/scene.h"
#include "general/SD_Music.h"
#include "general/util.h"

void ShowGameOverScreen(int Score)
{
	//����ͼ
	IMAGE game_over_bg;
	loadimage(&game_over_bg, _T("PNG"), MAKEINTRESOURCE(DIEMENU_BG1), window_x, window_y, true);
	Scene::GetScene().SetSceneBackground(Scene::SceneType::DieMenu, &game_over_bg);

	//�ı���ʼ��
	settextstyle(50, 100, _T("Microsoft YaHei UI"));
	outtextxy(window_x / 2 - 200, window_y / 3, _T("��Ϸ����"));
	TCHAR scoreText[50];
	_stprintf_s(scoreText, _T("�÷֣�%d"), Score);
	outtextxy(window_x / 2 - 100, window_y / 2, scoreText);

	//������ť
	//���¿�ʼ��ť
	RECT RePlayRect = { window_x / 4, window_y * 3 / 4, window_x * 3 / 4, window_y * 4 / 4 };
	RestartGameButton* restartBtn = new RestartGameButton(RePlayRect,
		_T("playagain.png.png"),
		_T("playagain.png.png"),
		_T("playagain.png.png"));
}
	//�������˵���ť
	RECT backRect = { window_x / 4, window_y * 5 / 6, window_x * 3 / 4, window_y * 6 / 6 };
	BackButton* BackBtn = new BackButton(backRect,
		_T("back_die.png"),
		_T("back_die.png"),
		_T("back_die.png"));