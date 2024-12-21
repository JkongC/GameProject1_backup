#include "stdlibs.h"
#include <stdio.h>
#include "ui/score_display.h"
#include <graphics.h>

void DisPlayScore(const int& score, int x, int y)
{
    TCHAR score_msg[50];
    _stprintf_s(score_msg, _T("Score: %d"), score);
    settextstyle(16, 0, _T("Arial")); // �����ı���ʽ
    settextcolor(RGB(220, 185, 138)); // �����ı���ɫΪ����ɫ
    outtextxy(x, y, score_msg); // ��ָ��λ�û����ı�
}