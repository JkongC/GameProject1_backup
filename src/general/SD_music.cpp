#include "stdlibs.h"

#include <mmsystem.h>
#include "general/SD_Music.h"

//����
void SD_Music_import(void)
{
	mciSendString(L"open resources/sound/bgm.mp3 alias BGM", NULL, 0, NULL);//����Ƶ�ļ�
	mciSendString(L"open resources/sound/put_down.mp3 alias PUT_DOWN", NULL, 0, NULL);
	mciSendString(L"open resources/sound/failure_music.mp3 alias FAILURE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/move.mp3 alias MOVE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/pick_up_prop.mp3 alias PROP", NULL, 0, NULL);
	mciSendString(L"open resources/sound/coin.mp3 alias COIN", NULL, 0, NULL);
	mciSendString(L"open resources/sound/first_level.mp3 alias F_BGM", NULL, 0, NULL);
	mciSendString(L"setaudio BGM volume to 700", NULL, 0, NULL);//��������Ϊ70%
	mciSendString(L"play BGM repeat", NULL, 0, NULL);	//���Ŷ�Ӧ��Ƶ
}

void SD_music_button(void)//
{
	mciSendString(L"close PUT_DOWN", NULL, 0, NULL);//�رղ��Ź��ĸ���Ч
	mciSendString(L"open resources/sound/put_down.mp3 alias PUT_DOWN", NULL, 0, NULL);//���´�,�൱�����ÿ�ʼ����ʱ��Ϊ��
	mciSendString(L"play PUT_DOWN", NULL, 0, NULL);
}

void SD_music_failure(void)
{
	mciSendString(L"close FAILURE", NULL, 0, NULL);
	mciSendString(L"open resources/sound/failure_music.mp3 alias FAILURE", NULL, 0, NULL);
	mciSendString(L"play FAILURE", NULL, 0, NULL);
}

void SD_music_first_level(void)//�л���������Ϊ��һ��
{
	mciSendString(L"close F_BGM", NULL, 0, NULL);
	mciSendString(L"close BGM", NULL, 0, NULL);
	mciSendString(L"open resources/sound/first_level.mp3 alias F_BGM", NULL, 0, NULL);
	mciSendString(L"play F_BGM repeat", NULL, 0, NULL);
}

void SD_music_bgm(void)//�л���������Ϊ��������Ч
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

