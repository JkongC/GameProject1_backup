#include "stdlibs.h"

#include <tchar.h>
#include <ShellScalingApi.h>
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "general/event.h"
#include "general/scene.h"
#include "object/Player.h"
#include "ui/Button.h"
#include "resource.h"

//在这里声明要用到的图片，下面只是例子
IMAGE player_right_img;
std::unique_ptr<Animation> player_right;  //使用智能指针的话，不用手动释放资源

IMAGE game_background;
IMAGE main_menu_background;

inline int LoadResources() 
{
	loadimage(&player_right_img, _T("PNG"), MAKEINTRESOURCE(TEST), 60, 17, false);
	//make_unique的作用是new一个对象然后获取它的unique_ptr
	player_right = std::make_unique<Animation>(player_right_img, 15, 17, 200, 4, 4);

	loadimage(&game_background, _T("PNG"), MAKEINTRESOURCE(GAME_BG1), window_x, window_y, true);
	loadimage(&main_menu_background, _T("PNG"), MAKEINTRESOURCE(GAME_BG1), window_x, window_y, true);
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
	
	initgraph(window_x, window_y, EX_NOCLOSE);
	bool running = true;

	Scene& scene = Scene::GetScene();

	//场景1玩家
	Player p1 = Player();
	scene.GetInputEvent().AddConcern(&p1);  //让玩家关注输入事件
	
	//初始化UI按钮
	//创建开始游戏按钮
	RECT startGameRect = { 100, 100, 300, 150 };
	std::unique_ptr<StartGameButton> startGameBtn = std::make_unique<StartGameButton>
		(startGameRect, _T("start_game_idle.png"), _T("start_game_hovered.png"), _T("start_game_pushed.png"));
	scene.AddObject(startGameBtn.get());

	// 创建退出游戏按钮
	RECT quitGameRect = { 100, 200, 300, 250 };
	std::unique_ptr<QuitGameButton> quitGameBtn = std::make_unique<QuitGameButton>
		(quitGameRect, _T("quit_game_idle.png"), _T("quit_game_hovered.png"), _T("quit_game_pushed.png"));
	scene.AddObject(quitGameBtn.get());

	// 创建设置按钮
	RECT settingsRect = { 100, 300, 300, 350 };
	std::unique_ptr<SettingButton> settingsBtn = std::make_unique<SettingButton>
		(settingsRect, _T("settings_idle.png"), _T("settings_hovered.png"), _T("settings_pushed.png"));
	scene.AddObject(settingsBtn.get());

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

		Pos background = scene.GetCamera().GetRelativePos({ 0, 0 });
		putimage(background.x, background.y, &game_background);
		scene.Render();

		FlushBatchDraw();
		
		auto& time_elapsed = timer.SinceLast();  //计算自从上次调用Start或SinceLast以来，经过的时间

		p1.Tick(time_elapsed);

		if (time_elapsed < 1000 / 144) {
			Sleep(1000 / 144 - time_elapsed);
		}
		
		if (!running) break;
	}
	EndBatchDraw();

	FreeResources();
	return 0;
}