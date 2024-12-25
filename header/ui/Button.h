#pragma once

class Button : public Object
{
public:
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    {
        region = rect;

        img_idle = new IMAGE();
        img_hovered = new IMAGE();
        img_pushed = new IMAGE();

        loadimage(img_idle, path_img_idle);
        ScalingByPixel(&img_idle, img_idle, 1, 3, true);
        loadimage(img_hovered, path_img_hovered);
        ScalingByPixel(&img_hovered, img_hovered, 1, 3, true);
        loadimage(img_pushed, path_img_pushed);
        ScalingByPixel(&img_pushed, img_pushed, 1, 3, true);
    }

    ~Button() {
        delete img_idle;
        delete img_hovered;
        delete img_pushed;
    };

    void InputHandle(const ExMessage& msg) override
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

    void Render()
    {
        switch (status)
        {
        case Status::Idle:
            putimage_alpha(img_idle, region.left, region.top, 0, 0, img_idle->getwidth(), img_idle->getheight());
            break;
        case Status::Hovered:
            putimage_alpha(img_hovered, region.left, region.top, 0, 0, img_hovered->getwidth(), img_hovered->getheight());
            break;
        case Status::Pushed:
            putimage_alpha(img_pushed, region.left, region.top, 0, 0, img_pushed->getwidth(), img_pushed->getheight());
            break;
        }
    }

protected:
    virtual void OnClick() = 0;  // 将处理点击事件

private:
    enum class Status
    {
        Idle = 0,
        Hovered,
        Pushed
    };

private:
    RECT region;
    IMAGE* img_idle;
    IMAGE* img_hovered;
    IMAGE* img_pushed;
    Status status = Status::Idle;

public:
    bool CheckCursorHit(int x, int y)
    {
        return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
    }

};

class RestartGameButton : public Button
{
public:
    RestartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~RestartGameButton();

private:
    void OnClick();
};

class StartGameButton : public Button
{
public:
    StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~StartGameButton();

protected:
    void OnClick();
};

class QuitGameButton : public Button
{
public:
    QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~QuitGameButton();

protected:
    void OnClick();

};

class SettingButton : public Button
{
public:
    SettingButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~SettingButton();

protected:
    void OnClick();

};

class BackButton : public Button
{
public:
    BackButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
    ~BackButton();

protected:
    void OnClick();

};