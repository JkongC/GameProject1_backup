#include "ui/game_over_screen.h"
#include <graphics.h>
#include "stdlibs.h"
#include "Button.h"

void ShowGameOverScreen(int score) {
    // ���ز���ʾ��Ϸ��������
    IMAGE game_over_bg;
    loadimage(&game_over_bg, _T("game_over_background.png"), window_x, window_y, true);
    putimage(0, 0, &game_over_bg);

    // ��ʾ�÷�
    char buffer[50];
    sprintf(buffer, "Score: %d", score);
    settextstyle(24, 0, _T("Arial"));
    settextcolor(RGB(220, 185, 138)); // �����ı���ɫΪ����ɫ
    outtextxy(100, 100, buffer);

    // ��ʾ��ť
    //�����ص����˵���ť
    RECT backRect = { 100, 400, 300, 450 };
    std::unique_ptr<BackButton> BackBtn = std::make_unique<BackButton>
        (backRect, _T("BACK_idle.png"), _T("BACK_hovered.png"), _T("BACK_pushed.png"));
    scene.AddObject(BackBtn.get());

    //�������¿�ʼ��ť
    RECT RePlayRect = { 100, 300, 300, 450 };
    std::unique_ptr<RestartGameButton> ReplayBtn = std::make_unique<RestartGameButton>
        (RePlayRect, _T("BACK_idle.png"), _T("BACK_hovered.png"), _T("BACK_pushed.png"));
    scene.AddObject(ReplayBtn.get());


    // ���������Ӱ�ť�Ļ��ƺͽ����߼�
    while (true) {

        // ���ư�ť
        BackButton->Render();
        RestartGameButton->Render();
    }
}