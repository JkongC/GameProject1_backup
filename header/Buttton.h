#pragma once

#include <Windows.h>
#include <tchar.h>
#include <easyx.h>
#include <ShellScalingApi.h>
#include <wingdi.h>
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

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

class Button : public Object
{
public:
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    {
        region = rect;

        loadimage(&img_idle, path_img_idle);
        loadimage(&img_hovered, path_img_hovered);
        loadimage(&img_pushed, path_img_pushed);
    }

    ~Button() = default;

    void ProcessEvent(const ExMessage& msg)
    {
        switch (msg.message)
        {
        case WM_MOUSEMOVE:
            if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
                status = Status::Hovered;
            else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
                status = Status::Idle;
            break;
        case WM_LBUTTONDOWN:
            if (CheckCursorHit(msg.x, msg.y))
                status = Status::Pushed;
            break;
        case WM_LBUTTONUP:
            if (status == Status::Pushed)
                OnClick();
            break;
        default:
            break;
        }
    }

    void Draw()
    {
        switch (status)
        {
        case Status::Idle:
            putimage(region.left, region.top, &img_idle);
            break;
        case Status::Hovered:
            putimage(region.left, region.top, &img_hovered);
            break;
        case Status::Pushed:
            putimage(region.left, region.top, &img_pushed);
            break;
        }
    }

protected:
    virtual void OnClick() = 0;

private:
    enum class Status
    {
        Idle = 0,
        Hovered,
        Pushed
    };

private:
    RECT region;
    IMAGE img_idle;
    IMAGE img_hovered;
    IMAGE img_pushed;
    Status status = Status::Idle;

private:
    // 检测鼠标点击
    bool CheckCursorHit(int x, int y)
    {
        return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
    }

};

// 开始游戏按钮
class StartGameButton : public Button
{
public:
    StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~StartGameButton() = default;

protected:
    void OnClick()
    {
        is_game_started = true;

        mciSendString(_T("Play bgm repeat form 0"), NULL, 0, NULL);
    }
};

// 退出游戏按钮
class QuitGameButton : public Button
{
public:
    QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~QuitGameButton() = default;

protected:
    void OnClick()
    {
        running = false;
    }
};

//打开设置界面按钮
class SettingButton : public Button
{
public:
    SettingButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~SettingButton() = default;

protected:
    void OnClick()
    {

    }
};

//返回按钮
class BackButton : public Button
{
public:
    BackButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~BackButton() = default;

protected:
    void OnClick()
    {

    }
};