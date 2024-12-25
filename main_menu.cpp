#include "stdlibs.h"

#include "main_menu.h"
#include "general/util.h"
#include "resource.h"
#include "object/Object.h"
#include "ui/Button.h"
#include "general/event.h"
#include "general/scene.h"

IMAGE main_menu_bg;

void ShowMainMenu()
{
    Scene::GetScene().SetCurrentScene(Scene::SceneType::MainMenu);

    // �������˵�����ͼƬ
    loadimage(&main_menu_bg, _T("PNG"), MAKEINTRESOURCE(MAINMENU_BG1), window_x, window_y, true);
    Scene::GetScene().SetSceneBackground(Scene::SceneType::MainMenu, &main_menu_bg);

    // �������˵���ť
    // ��ʼ��Ϸ��ť
    RECT startGameRect = { window_x / 4, window_y / 3, window_x * 3 / 4, window_y * 2 / 3 };
    StartGameButton* startGameBtn = new StartGameButton(startGameRect,
        _T("resources/ui/start_game_idle.png"),
        _T("resources/ui/start_game_hovered.png"),
        _T("resources/ui/start_game_pushed.png"));
    
    // �˳���Ϸ��ť
    RECT quitGameRect = { window_x / 4, window_y * 5 / 6, window_x * 3 / 4, window_y * 6 / 6 };
    QuitGameButton* quitGameBtn = new QuitGameButton(quitGameRect,
        _T("resources/ui/quit_game_idle.png"),
        _T("resources/ui/quit_game_hovered.png"),
        _T("resources/ui/quit_game_pushed.png"));
}

void MainMenuProcess() {
    // �����ﴦ�����˵��������Ⱦ�߼���������ʾ�����������
    settextstyle(50, 100, _T("Microsoft YaHei UI"));
    outtextxy(window_x / 2 - 200, window_y / 4, _T("��ӭ������Ϸ���˵�"));
}