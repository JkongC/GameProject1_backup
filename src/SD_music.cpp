#include <SD_Music.h>

//函数
void SD_Music_import(void)
{
	mciSendString(L"open bgm.wav alias BGM", NULL, 0, NULL);
	mciSendString(L"open put_down.ogg alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open failure_music.wav alias FAILURE", NULL, 0, NULL);
	mciSendString(L"open move.wav alias MOVE", NULL, 0, NULL);
	mciSendString(L"open pick_up_prop.ogg alias PROP", NULL, 0, NULL);
	mciSendString(L"open coin.wav alias COIN", NULL, 0, NULL);
	mciSendString(L"open first_level.wav alias F_BGM", NULL, 0, NULL);
	mciSendString(L"setaudio BGM volume to 700", NULL, 0, NULL);//设置音量为70%
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
}

void SD_music_button(void)
{
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open put_down.ogg alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"play PUT_DOWN", NULL, 0, NULL);
}

void SD_music_failure(void)
{
	mciSendString(L"close FAILURE", NULL, 0, NULL);
	mciSendString(L"open failure_music.wav alias FAILURE", NULL, 0, NULL);
	mciSendString(L"play FAILURE", NULL, 0, NULL);
}

void SD_music_first_level(void)
{
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"open first_level.wav alias F_BGM", NULL, 0, NULL);
	mciSendString(L"play F_BGM repeat", NULL, 0, NULL);
}

void SD_music_bgm(void)
{
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"open bgm.wav alias BGM", NULL, 0, NULL);
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
}

void SD_music_move(void)
{
	mciSendString(L"close MOVE", NULL, 0, NULL);
	mciSendString(L"open move.wav alias MOVE", NULL, 0, NULL);
	mciSendString(L"play MOVE", NULL, 0, NULL);
}

void SD_music_coin(void)
{
	mciSendString(L"close COIN", NULL, 0, NULL);
	mciSendString(L"open coin.wav alias COIN", NULL, 0, NULL);
	mciSendString(L"play COIN", NULL, 0, NULL);
}

void SD_music_prop(void)
{
	mciSendString(L"close PROP", NULL, 0, NULL);
	mciSendString(L"open pick_up_prop.ogg alias PROP", NULL, 0, NULL);
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

