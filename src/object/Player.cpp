#include <stdlib.h>

#include "stdlibs.h"
#include "object/Animation.h"
#include "general/util.h"
#include "object/object.h"
#include "general/event.h"
#include "object/Player.h"
#include "object/Arrow.h"
#include "ui/Arena.h"
#include "ui/game_over_screen.h"
#include "general/scene.h"
#include "general/globals.h"

extern std::unique_ptr<Animation> player_right;

Player::Player()
	:current_ani_set(0), health(5), score(0), space_pressed(false), counter(0), mouse_pos({0, 0}), lock_camera(false), status(Status::Attached), R_angle(0), immune_damage(false), im_counter(0), flash_counter(0)
{
	this->pos = { window_x / 2 - Arena::long_axis, window_y / 2 - 50};
	ani_list.push_back(player_right.get());

	this->width = ani_list[0]->GetWidth();
	this->height = ani_list[0]->GetHeight();
	this->speed = { 0, 0 };
	this->acceleration = { 0, 0 };

	this->arrow = new Arrow();
	this->life = -1;

	Scene::GetScene().SetPlayer(this);

	Attach();

	srand(time(NULL));
}

void Player::Render() {
	TCHAR health_bar[10];
	_stprintf_s(health_bar, _T("玩家生命值：%d"), this->health);
	setbkmode(TRANSPARENT);
	settextstyle(50, 20, _T("Microsoft YaHei UI"));
	outtextxy(0, 0, health_bar);

	TCHAR score_bar[10];
	_stprintf_s(score_bar, _T("玩家分数：%d"), this->score);
	setbkmode(TRANSPARENT);
	settextstyle(50, 20, _T("Microsoft YaHei UI"));
	outtextxy(0, 50, score_bar);
	
	if (!this->show) return;

	Pos relative = Scene::GetScene().GetCamera().GetRelativePos(this->pos);
	Transform();
	ani_list[current_ani_set]->Render(relative.x, relative.y);
	Untransform();

	switch (this->status)
	{
	case Status::Attached:
		this->arrow->Render();
		break;
	case Status::Flying:
		break;
	default:
		break;
	}
}

void Player::Tick(const int& delta) {
	if (health <= 0) {
		ShowGameOverScreen(GetScore());
		return;
	}

	if (immune_damage) {
		im_counter += delta;
		if (im_counter >= 1500) {
			im_counter = 0;
			immune_damage = false;
			show = true;
		}

		flash_counter += delta;
		if (flash_counter >= 200) {
			flash_counter = 0;
			show = show ? false : true;
		}
	}
	
	ani_list[current_ani_set]->Tick(delta);
	counter += delta;
	
	angle += 3.14159 / 180 * delta / 20;
	if (angle > 2 * 3.14159) angle -= 2 * 3.14159;

	switch (this->status)
	{
	case Status::Attached:
		if (space_pressed && counter > cooldown) {
			Launch();
			counter = 0;
		}
		else {
			this->arrow->Tick(delta);
		}
		break;

	case Status::Flying:
	{
		Pos center = this->GetCenter();
		Pos after = { center.x + this->speed.x, center.y + this->speed.y };
		if (Arena::GetArena().CheckIfOut(after)) {
			Attach();
		}
		else {
			pos.x += (long)speed.x * delta / 10;
			pos.y += (long)speed.y * delta / 10;
		}
	}
		break;

	default:
		break;
	}

	counter %= 10000;
}

void Player::InputHandle(const ExMessage& msg) {
	switch (msg.message)
	{
	case WM_KEYDOWN:
		this->space_pressed = true;
		break;
	case WM_KEYUP:
		this->space_pressed = false;
		break;
	case WM_MOUSEMOVE:
		this->mouse_pos = Scene::GetScene().GetCamera().GetAbsolutePos({msg.x, msg.y});
		break;
	default:
		break;
	}
}

void Player::Launch() {
	this->status = Status::Flying;
	this->flying = true;

	Vec2d direction = {cos(this->arrow->angle), -sin(this->arrow->angle)};
	direction.Normalize(7);

 	this->speed += direction;
}

void Player::Attach() {
	this->status = Status::Attached;
	this->flying = false;

	Vec2d speed_norm = speed;
	speed_norm.Normalize(3);

	Pos center = this->GetCenter();
	while (speed.x != 0 && speed.y != 0 && !Arena::GetArena().CheckIfOut(this->GetCenter())) {
		pos.x += speed_norm.x;
		pos.y += speed_norm.y;
	}  //位置修正

	double arena_long = Arena::long_axis;  //场地椭圆长轴
	double arena_short = Arena::short_axis;  //场地椭圆短轴
	
	Pos delta = this->GetCenter() - Arena::center;  //玩家位置到圆心的方向向量
	double k1 = (double)delta.y / (double)delta.x;  //方向向量所在直线的斜率
	double temp_angle;
	if (k1) {
		double k2 = -(arena_short * arena_short / (arena_long * arena_long)) / k1;  //切线的斜率

		temp_angle = atan(k2) + PI / 2;  //变为切线的中垂线的倾斜角
		if (delta.x * cos(temp_angle) > 0 && delta.y * sin(temp_angle) > 0) 
			temp_angle += PI;  //让角向着椭圆内方向

		temp_angle = -temp_angle;  //这一步是因为窗口坐标系y轴反转
	}
	else {
		if (delta.x > 0) {
			temp_angle = PI;
		}
		else {
			temp_angle = 0;
		}
	}

	arrow->angle = temp_angle;
	arrow->angle_end = arrow->angle + PI / 180 * 70;  //设置指针转动范围
	arrow->angle_start = arrow->angle - PI / 180 * 70;
	Pos arrow_offset = { 3, 62 };
	arrow->pos = this->GetCenter() - arrow_offset;

	switch (rand() % 2) //随机让指针从顺时针或逆时针开始转动
	{
	case 0:
		arrow->clockwise = true;
		break;
	case 1:
		arrow->clockwise = false;
		break;
	default:
		break;
	}

	this->speed = { 0,0 };
}

void Player::Damage(const int& dmg) {
	this->health -= dmg;
}

Player::~Player() {
	delete this->arrow;
};