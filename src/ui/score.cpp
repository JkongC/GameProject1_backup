#include "score_display.h"
#include <graphics.h>

void DisPlayScore(int score, int x, int y)
{
    char buffer[50];
    sprintf(buffer, "Score: %d", score);
    settextstyle(16, 0, _T("Arial")); // �����ı���ʽ
    settextcolor(RGB(220, 185, 138)); // �����ı���ɫΪ����ɫ
    outtextxy(x, y, buffer); // ��ָ��λ�û����ı�
}