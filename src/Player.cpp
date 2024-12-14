#include <vector>
#include <chrono>
#include <memory>
#include <easyx.h>
#include "Animation.h"
#include "util.h"
#include "object.h"
#include "scene.h"
#include "Player.h"

extern std::unique_ptr<Animation> player_right;

Player::Player(Scene& scene)
	:current_ani_set(0), health(0), space_pressed(false), counter(0), mouse_pos({0, 0})
{
	this->pos = { 500, 500 };
	ani_list.push_back(player_right.get());

	this->width = ani_list[0]->GetWidth();
	this->height = ani_list[0]->GetHeight();
	this->speed = { 0, 0 };
	this->acceleration = { 0, 0 };
	this->belong = &scene;
}

void Player::Render() {
	if (!this->show) return;
	ani_list[current_ani_set]->Render(pos.x, pos.y);
}

void Player::Tick(const int& delta) {
	ani_list[current_ani_set]->Tick(delta);
	counter += delta;

	if (space_pressed && counter >= cooldown) {
		counter = 0;
		POINT center = GetCenter();
		Vec2d direction = { mouse_pos.x - center.x, mouse_pos.y - center.y};
		direction.Normalize(60);
		speed += direction;
		speed.scale = 1.0;
	}
	else if (counter >= 10000) {
		counter = 0;
	}

	if (this->pos.x + speed.x > 0 && this->pos.x + speed.x < window_x - width) {
		pos.x += (int)(speed.x * delta / 100);
	}
	else {
		speed.x = 0;
	}

	if (this->pos.y + speed.y > 0 && this->pos.y + speed.y < window_y - height) {
		pos.y += (int)(speed.y * delta / 100);
	}
	else {
		speed.y = 0;
	}

	speed.Friction(friction);
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
		this->mouse_pos.x = msg.x;
		this->mouse_pos.y = msg.y;
	default:
		break;
	}
}

POINT Player::GetCenter() {
	return { this->pos.x + this->width / 2, this->pos.y + this->health / 2 };
}

Player::~Player() = default;