#include "score_display.h"
#include <graphics.h>

void DisPlayScore(int score, int x, int y)
{
    char buffer[50];
    sprintf(buffer, "Score: %d", score);
    settextstyle(16, 0, _T("Arial")); // 设置文本样式
    settextcolor(RGB(220, 185, 138)); // 设置文本颜色为背景色
    outtextxy(x, y, buffer); // 在指定位置绘制文本
}