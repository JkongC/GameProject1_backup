#include "ui/game_over_screen.h"
#include <graphics.h>
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
#include "resource.h"
#include "general/SD_Music.h"

void ShowGameOverScreen(int score) {
    // 加载并显示游戏结束背景
    IMAGE game_over_bg;

    loadimage(&game_over_bg, _T("PNG"), MAKEINTRESOURCE(DIEMENU_BG1), window_x, window_y, true);
    Scene::GetScene().SetSceneBackground(Scene::SceneType::DieMenu, &game_over_bg);

    // 显示得分
    char buffer[50];
    sprintf(buffer, "Score: %d", score);
    settextstyle(24, 0, _T("Arial"));
    settextcolor(RGB(220, 185, 138)); // 设置文本颜色为背景色
    outtextxy(100, 100, buffer);

    // 显示按钮
    //创建回到主菜单按钮
    RECT backRect = { 100, 400, 300, 450 };
    std::unique_ptr<BackButton> BackBtn = std::make_unique<BackButton>
        (backRect, _T("BACK_idle.png"), _T("BACK_hovered.png"), _T("BACK_pushed.png"));
    scene.AddObject(BackBtn.get());

    //创建重新开始按钮
    RECT RePlayRect = { 100, 300, 300, 450 };
    std::unique_ptr<RestartGameButton> ReplayBtn = std::make_unique<RestartGameButton>
        (RePlayRect, _T("BACK_idle.png"), _T("BACK_hovered.png"), _T("BACK_pushed.png"));
    scene.AddObject(ReplayBtn.get());


    // 这里可以添加按钮的绘制和交互逻辑
    while (true) {

        // 绘制按钮
        BackButton->Render();
        RestartGameButton->Render();
    }
}