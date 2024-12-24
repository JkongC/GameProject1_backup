#include "stdlibs.h"

#include <tchar.h>
#include <ShellScalingApi.h>
#include "general/globals.h"
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "general/event.h"
#include "object/Player.h"
#include "ui/Button.h"
#include "ui/Arena.h"
#include "object/Obstacle.h"
#include "object/Score.h"
#include "general/scene.h"
#include "ui/game_over_screen.h"
#include "resource.h"
#include "general/SD_Music.h"

//在这里声明要用到的图片，下面只是例子
IMAGE player_right_img;
std::unique_ptr<Animation> player_right;  //使用智能指针的话，不用手动释放资源

IMAGE game_background;
IMAGE main_menu_background;

IMAGE obstacle;
IMAGE score_5;
IMAGE score_10;
IMAGE score_20;

bool running;

inline int LoadResources() 
{
	loadimage(&player_right_img, _T("PNG"), MAKEINTRESOURCE(PLAYER), 76, 76, false);
	//make_unique的作用是new一个对象然后获取它的unique_ptr
	player_right = std::make_unique<Animation>(player_right_img, 76, 76, 0, 1, 1);

	loadimage(&game_background, _T("PNG"), MAKEINTRESOURCE(GAME_BG1), window_x, window_y, true);
	Scene::GetScene().SetSceneBackground(Scene::SceneType::Game, &game_background);

	loadimage(&obstacle, _T("PNG"), MAKEINTRESOURCE(OBSTACLE), 90, 90, false);
	loadimage(&score_5, _T("PNG"), MAKEINTRESOURCE(SCORE_5), 56, 56, false);
	loadimage(&score_10, _T("PNG"), MAKEINTRESOURCE(SCORE_10), 56, 56, false);
	loadimage(&score_20, _T("PNG"), MAKEINTRESOURCE(SCORE_20), 56, 56, false);
	Score::img_list[0] = &score_5;
	Score::img_list[1] = &score_10;
	Score::img_list[2] = &score_20;

	return 0;
}

void FreeResources() 
{
	
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) 
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);  //让窗口大小不受系统缩放设置影响
	SetGraphicsMode(GetImageHDC(), GM_ADVANCED);

	LoadResources();
	
	//初始化音乐
	SD_Music_import();
	
	initgraph(window_x, window_y, EX_NOCLOSE);
	running = true;

	Scene& scene = Scene::GetScene();

	new Player();
	new Obstacle(0.8 * PI);
	new Obstacle(0.5 * PI);
	new Obstacle(-0.6 * PI);
	
	//初始化UI按钮
	//创建开始游戏按钮
	RECT startGameRect = { 100, 100, 300, 150 };
	StartGameButton* startGameBtn = new StartGameButton(startGameRect, _T("start_game_idle.png"), _T("start_game_hovered.png"), _T("start_game_pushed.png"));

	// 创建退出游戏按钮
	RECT quitGameRect = { 100, 200, 300, 250 };
	QuitGameButton* quitGameBtn = new QuitGameButton(quitGameRect, _T("quit_game_idle.png"), _T("quit_game_hovered.png"), _T("quit_game_pushed.png"));

	// 创建设置按钮
	RECT settingsRect = { 100, 300, 300, 350 };
	SettingButton* settingsBtn = new SettingButton(settingsRect, _T("settings_idle.png"), _T("settings_hovered.png"), _T("settings_pushed.png"));

	BeginBatchDraw();
	Timer timer;  //毫秒计时器
	timer.Start();  //开始计时
	while (running) 
	{
		
		ExMessage msg;

		//消息处理
		while (peekmessage(&msg)) 
		{
			if (msg.vkcode == VK_SPACE || msg.message == WM_MOUSEMOVE) {
				scene.GetInputEvent().Emit(msg);  //让关注输入事件的对象进行处理
			}
			else if (msg.vkcode == VK_ESCAPE) {
				running = false;
			}
		}

		cleardevice();
		scene.Render();  //场景批量渲染

		FlushBatchDraw();
		
		const int& time_elapsed = timer.SinceLast();  //计算自从上次调用Start或SinceLast以来，经过的时间

		scene.Tick(time_elapsed);  //场景批量更新

		//场景专属操作
		switch (scene.GetCurrentScene())
		{
		case Scene::SceneType::Game:
			ScoreGenerator::GetGenerator().TryGenerate(time_elapsed);
			break;
		case Scene::SceneType::DieMenu:
			GameOverScreenProcess();
			break;
		default:
			break;
		}

		//帧数控制
		if (time_elapsed < 1000 / 144) {
			Sleep(1000 / 144 - time_elapsed);
		}
		
		if (!running) break;
	}
	EndBatchDraw();

	FreeResources();
	return 0;
}