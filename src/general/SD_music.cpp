#include "stdlibs.h"

#include <mmsystem.h>
#include "general/SD_Music.h"

//函数
void SD_Music_import(void)
{
	mciSendString(L"open resources/sound/bgm.mp3 alias BGM", NULL, 0, NULL);//打开音频文件
	mciSendString(L"open resources/sound/put_down.mp3 alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open resources/sound/failure_music.mp3 alias FAILURE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/move.mp3 alias MOVE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/pick_up_prop.mp3 alias PROP", NULL, 0, NULL);
	mciSendString(L"open resources/sound/coin.mp3 alias COIN", NULL, 0, NULL);
	mciSendString(L"open resources/sound/first_level.mp3 alias F_BGM", NULL, 0, NULL);
	mciSendString(L"setaudio BGM volume to 700", NULL, 0, NULL);//设置音量为70%
	mciSendString(L"play BGM repeat", NULL, 0, NULL);	//播放对应音频
}

void SD_music_button(void)//
{
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);//关闭播放过的该音效
	mciSendString(L"open resources/sound/put_down.mp3 alias PUT_DOWN", NULL, 0, NULL);//重新打开,相当于重置开始播放时间为零
	mciSendString(L"play PUT_DOWN", NULL, 0, NULL);
}

void SD_music_failure(void)
{
	mciSendString(L"close FAILURE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/failure_music.mp3 alias FAILURE", NULL, 0, NULL);
	mciSendString(L"play FAILURE", NULL, 0, NULL);
}

void SD_music_first_level(void)//切换背景音乐为第一关
{
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"open resources/sound/first_level.mp3 alias F_BGM", NULL, 0, NULL);
	mciSendString(L"play F_BGM repeat", NULL, 0, NULL);
}

void SD_music_bgm(void)//切换背景音乐为主界面音效
{
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"open resources/sound/bgm.mp3 alias BGM", NULL, 0, NULL);
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
}

void SD_music_move(void)
{
	mciSendString(L"close MOVE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/move.mp3 alias MOVE", NULL, 0, NULL);
	mciSendString(L"play MOVE", NULL, 0, NULL);
}

void SD_music_coin(void)
{
	mciSendString(L"close COIN", NULL, 0, NULL);
	mciSendString(L"open resources/sound/coin.mp3 alias COIN", NULL, 0, NULL);
	mciSendString(L"play COIN", NULL, 0, NULL);
}

void SD_music_prop(void)
{
	mciSendString(L"close PROP", NULL, 0, NULL);
	mciSendString(L"open resources/sound/pick_up_prop.mp3 alias PROP", NULL, 0, NULL);
	mciSendString(L"play PROP", NULL, 0, NULL);
}   

void SD_music_close(void)
{
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close PROP", NULL, 0, NULL);
	mciSendString(L"close COIN", NULL, 0, NULL);
	mciSendString(L"close FAILURE", NULL, 0, NULL);
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"close MOVE", NULL, 0, NULL);
}

