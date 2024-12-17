#include "stdlibs.h"
#include "object/Animation.h"
#include "general/util.h"
#include "object/object.h"
#include "general/event.h"
#include "general/scene.h"
#include "object/Player.h"
#include "object/Arrow.h"
#include "ui/Arena.h"

extern std::unique_ptr<Animation> player_right;

Player::Player()
	:current_ani_set(0), health(0), space_pressed(false), counter(0), mouse_pos({0, 0}), lock_camera(false), status(Status::Attached), R_angle(0)
{
	this->pos = { 500, 500 };
	ani_list.push_back(player_right.get());

	this->width = ani_list[0]->GetWidth();
	this->height = ani_list[0]->GetHeight();
	this->speed = { 0, 0 };
	this->acceleration = { 0, 0 };

	this->arrow = new Arrow();

	Scene::GetScene().AddObject(this);

	Attach();
}

void Player::Render() {
	if (!this->show) return;
	Pos relative = Scene::GetScene().GetCamera().GetRelativePos(this->pos);
	ani_list[current_ani_set]->Render(relative.x, relative.y);

	switch (this->status)
	{
	case Status::Attached:
		break;
	case Status::Flying:
		break;
	default:
		break;
	}
}

void Player::Tick(const int& delta) {
	ani_list[current_ani_set]->Tick(delta);
	counter += delta;

	Pos after = { pos.x + speed.x, pos.y + speed.y };
	switch (this->status)
	{
	case Status::Attached:
		if (space_pressed && counter < cooldown) {
			Launch();
		}
		else {
			Pos arrow_offset = { 3, 62 };
			this->arrow->pos = this->GetCenter() - arrow_offset;
			this->arrow->Tick(delta);
		}
		break;

	case Status::Flying:
		if (after.GetDistanceFrom(Arena::GetArena().center) > Arena::GetArena().radius) {
			Attach();
		}
		else {
			pos.x += (long)speed.x;
			pos.y += (long)speed.y;
		}
		break;

	default:
		break;
	}
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

	Vec2d direction = {cos(this->arrow->angle), sin(this->arrow->angle)};
	direction.Normalize(50);

	this->speed += direction;
}

void Player::Attach() {
	this->status = Status::Attached;
	Vec2d speed_norm = speed;
	speed_norm.Normalize();

	while (this->pos.GetDistanceFrom(Arena::GetArena().center) < Arena::GetArena().radius) {
		pos.x += speed_norm.x;
		pos.y += speed_norm.y;
	}
}

Player::~Player() {
	delete this->arrow;
};