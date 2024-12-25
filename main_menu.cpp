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

    // 加载主菜单背景图片
    loadimage(&main_menu_bg, _T("PNG"), MAKEINTRESOURCE(MAINMENU_BG1), window_x, window_y, true);
    Scene::GetScene().SetSceneBackground(Scene::SceneType::MainMenu, &main_menu_bg);

    // 创建主菜单按钮
    // 开始游戏按钮
    RECT startGameRect = { window_x / 4, window_y / 3, window_x * 3 / 4, window_y * 2 / 3 };
    StartGameButton* startGameBtn = new StartGameButton(startGameRect,
        _T("resources/ui/start_game_idle.png"),
        _T("resources/ui/start_game_hovered.png"),
        _T("resources/ui/start_game_pushed.png"));
    
    // 退出游戏按钮
    RECT quitGameRect = { window_x / 4, window_y * 5 / 6, window_x * 3 / 4, window_y * 6 / 6 };
    QuitGameButton* quitGameBtn = new QuitGameButton(quitGameRect,
        _T("resources/ui/quit_game_idle.png"),
        _T("resources/ui/quit_game_hovered.png"),
        _T("resources/ui/quit_game_pushed.png"));
}

void MainMenuProcess() {
    // 在这里处理主菜单界面的渲染逻辑，例如显示分数、标题等
    settextstyle(50, 100, _T("Microsoft YaHei UI"));
    outtextxy(window_x / 2 - 200, window_y / 4, _T("欢迎来到游戏主菜单"));
}