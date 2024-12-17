#include<Button.h>
#include<globals.h>

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

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
        this->scene_belong->SetCurrentScene(Scene::SceneType::Game);

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
        this->scene_belong->SetCurrentScene(Scene::SceneType::Menu);

    }
};

//返回主菜单按钮
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
        this->scene_belong->SetCurrentScene(Scene::SceneType::MainMenu);
    }
};