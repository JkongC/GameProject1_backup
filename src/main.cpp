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

//����������Ҫ�õ���ͼƬ������ֻ������
IMAGE player_right_img;
std::unique_ptr<Animation> player_right;  //ʹ������ָ��Ļ��������ֶ��ͷ���Դ

IMAGE game_background;

inline int LoadResources() 
{
	loadimage(&player_right_img, _T("PNG"), MAKEINTRESOURCE(GAME_TEST), 60, 17, true);
	//make_unique��������newһ������Ȼ���ȡ����unique_ptr
	player_right = std::make_unique<Animation>(player_right_img, 15, 17, 200, 4, 4);

	loadimage(&game_background, _T("PNG"), MAKEINTRESOURCE(GAME_BACKGROUND), window_x, window_y, true);
	return 0;
}

void FreeResources() 
{
	
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) 
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);  //�ô��ڴ�С����ϵͳ��������Ӱ��

	LoadResources();
	
	initgraph(window_x, window_y, EX_NOCLOSE);
	bool running = true;

	Scene scene;  //����
	InputEvent input;  //�����¼�����ʱֻ����ո�

	Player p1(scene);  //���
	input.AddConcern(&p1);  //����ҹ�ע�����¼�

	BeginBatchDraw();
	Timer timer;  //�����ʱ��
	timer.Start();  //��ʼ��ʱ
	while (true) 
	{
		
		ExMessage msg;

		while (peekmessage(&msg)) 
		{
			if (msg.vkcode == VK_SPACE || msg.message == WM_MOUSEMOVE) {
				input.Emit(msg);  //�ù�ע�����¼��Ķ�����д���
			}
			else if (msg.vkcode == VK_ESCAPE) {
				running = false;
			}
		}

		cleardevice();

		putimage(0, 0, &game_background);
		p1.Render();

		FlushBatchDraw();
		
		auto& time_elapsed = timer.SinceLast();  //�����Դ��ϴε���Start��SinceLast������������ʱ��

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