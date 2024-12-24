#include "stdlibs.h"

#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "general/event.h"
#include "object/Player.h"
#include "ui/Button.h"
#include "general/globals.h"
#include "resource.h"
#include "general/SD_Music.h"
#include "general/scene.h"

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

// 开始游戏按钮
StartGameButton::StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    Scene::GetScene().AddObject(this);
}

StartGameButton::~StartGameButton() = default;

void StartGameButton::OnClick()
{
    SD_music_button();
    Scene::GetScene().SetCurrentScene(Scene::SceneType::Game);
    SD_music_first_level();
    //mciSendString(_T("Play bgm repeat form 0"), NULL, 0, NULL);
}


// 退出游戏按钮
QuitGameButton::QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    Scene::GetScene().AddObject(this);
}

QuitGameButton::~QuitGameButton() = default;

void QuitGameButton::OnClick()
{
    SD_music_button();
    SD_music_close();
    running = false;
}


//打开设置界面按钮
SettingButton::SettingButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    Scene::GetScene().AddObject(this);
}

SettingButton::~SettingButton() = default;

void SettingButton::OnClick()
{
    SD_music_button();
    Scene::GetScene().SetCurrentScene(Scene::SceneType::Settings);

}


//返回主菜单按钮
BackButton::BackButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    Scene::GetScene().AddObject(this);
}

BackButton::~BackButton() = default;

void BackButton::OnClick()
{
    SD_music_button();
    Scene::GetScene().SetCurrentScene(Scene::SceneType::MainMenu);
    SD_music_bgm();
}

//重新开始游戏按钮
RestartGameButton::RestartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    : Button(rect, path_img_idle, path_img_hovered, path_img_pushed){
    Scene::GetScene().AddObject(this);
}

RestartGameButton::~RestartGameButton() = default;

void RestartGameButton::OnClick()
{
    SD_music_button();
    Scene::GetScene().SetCurrentScene(Scene::SceneType::Game);
    SD_music_first_level();
}

