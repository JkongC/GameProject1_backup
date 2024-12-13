#pragma comment(lib, "Shcore.lib")

#include <Windows.h>
#include <tchar.h>
#include <easyx.h>
#include <ShellScalingApi.h>
#include <chrono>
#include <memory>
#include <vector>
#include "util.h"
#include "Animation.h"
#include "Object.h"
#include "scene.h"
#include "Player.h"
#include "event.h"
#include "resource.h"

//在这里声明要用到的图片，下面只是例子
IMAGE player_right_img;
std::unique_ptr<Animation> player_right;  //使用智能指针的话，不用手动释放资源

IMAGE game_background;

inline int LoadResources() 
{
	loadimage(&player_right_img, _T("PNG"), MAKEINTRESOURCE(GAME_TEST), 60, 17, true);
	//make_unique的作用是new一个对象然后获取它的unique_ptr
	player_right = std::make_unique<Animation>(player_right_img, 15, 17, 200, 4, 4);

	loadimage(&game_background, _T("PNG"), MAKEINTRESOURCE(GAME_BACKGROUND), window_x, window_y, true);
	return 0;
}

void FreeResources() 
{
	
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) 
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);  //让窗口大小不受系统缩放设置影响

	LoadResources();
	
	initgraph(window_x, window_y, EX_NOCLOSE);
	bool running = true;

	Scene scene;  //场景
	InputEvent input;  //输入事件，暂时只处理空格

	Player p1(scene);  //玩家
	input.AddConcern(&p1);  //让玩家关注输入事件

	BeginBatchDraw();
	Timer timer;  //毫秒计时器
	timer.Start();  //开始计时
	while (true) 
	{
		
		ExMessage msg;

		while (peekmessage(&msg)) 
		{
			if (msg.vkcode == VK_SPACE || msg.message == WM_MOUSEMOVE) {
				input.Emit(msg);  //让关注输入事件的对象进行处理
			}
			else if (msg.vkcode == VK_ESCAPE) {
				running = false;
			}
		}

		cleardevice();

		putimage(0, 0, &game_background);
		p1.Render();

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