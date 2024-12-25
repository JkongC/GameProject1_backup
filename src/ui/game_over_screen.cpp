#include "stdlibs.h"

#include "general/util.h"

#include "ui/game_over_screen.h"
#include "resource.h"
#include "object/Object.h"
#include "ui/Button.h"
#include "general/event.h"
#include "general/scene.h"
#include "general/SD_Music.h"
int score;
IMAGE game_over_bg;

void InitGameOverScreen(const int& Score)
{
	Scene::GetScene().SetCurrentScene(Scene::SceneType::DieMenu);
	score = Score;

	//背景图
	loadimage(&game_over_bg, _T("PNG"), MAKEINTRESOURCE(DIEMENU_BG1), window_x, window_y, true);
	Scene::GetScene().SetSceneBackground(Scene::SceneType::DieMenu, &game_over_bg);

	//创建按钮
	//重新开始按钮
	RECT RePlayRect = { window_x / 5, window_y * 3 / 4, window_x / 5 + 114 * 3, window_y * 3 / 4 + 28 * 3};
	RestartGameButton* restartBtn = new RestartGameButton(RePlayRect,
		_T("resources/ui/playagain.png"),
		_T("resources/ui/playagain.png"),
		_T("resources/ui/playagain.png"));

	//返回主菜单按钮
	RECT backRect = { window_x * 2 / 3, window_y * 3 / 4, window_x * 2 / 3 + 58 * 3, window_y * 3 / 4 + 22 * 3};
	BackButton* BackBtn = new BackButton(backRect,
		_T("resources/ui/back_die.png"),
		_T("resources/ui/back_die.png"),
		_T("resources/ui/back_die.png"));
}

void UpdateScore(const int& Score)
{
	score = Score;
	//死亡音乐
	SD_music_failure();
}

void GameOverScreenProcess()
{
	settextstyle(120, 50, _T("Microsoft YaHei UI"));
	setbkmode(TRANSPARENT);
	TCHAR scoreText[50];
	_stprintf_s(scoreText, _T("%d"), score);
	outtextxy(window_x / 2 - 300, window_y / 2 + 50, scoreText);
}