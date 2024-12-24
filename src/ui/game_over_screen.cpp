#include "stdlibs.h"

#include "general/util.h"

#include "ui/game_over_screen.h"
#include "resource.h"
#include "object/Object.h"
#include "ui/Button.h"
#include "general/event.h"
#include "general/scene.h"

int score;
IMAGE game_over_bg;

void ShowGameOverScreen(int Score)
{
	Scene::GetScene().SetCurrentScene(Scene::SceneType::DieMenu);
	score = Score;

	//����ͼ
	loadimage(&game_over_bg, _T("PNG"), MAKEINTRESOURCE(DIEMENU_BG1), window_x, window_y, true);
	Scene::GetScene().SetSceneBackground(Scene::SceneType::DieMenu, &game_over_bg);

	//������ť
	//���¿�ʼ��ť
	RECT RePlayRect = { window_x / 4, window_y * 3 / 4, window_x * 3 / 4, window_y * 4 / 4 };
	RestartGameButton* restartBtn = new RestartGameButton(RePlayRect,
		_T("resources/ui/playagain.png"),
		_T("resources/ui/playagain.png"),
		_T("resources/ui/playagain.png"));

	//�������˵���ť
	RECT backRect = { window_x / 4, window_y * 5 / 6, window_x * 3 / 4, window_y * 6 / 6 };
	BackButton* BackBtn = new BackButton(backRect,
		_T("resources/ui/back_die.png"),
		_T("resources/ui/back_die.png"),
		_T("resources/ui/back_die.png"));
}

void GameOverScreenProcess()
{
	settextstyle(50, 100, _T("Microsoft YaHei UI"));
	outtextxy(window_x / 2 - 200, window_y / 3, _T("��Ϸ����"));
	TCHAR scoreText[50];
	_stprintf_s(scoreText, _T("�÷֣�%d"), score);
	outtextxy(window_x / 2 - 100, window_y / 2, scoreText);
}