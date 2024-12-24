#include "stdlibs.h"
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "object/Player.h"
#include "general/event.h"
#include "ui/Arena.h"
#include "object/Obstacle.h"
#include "general/scene.h"

extern IMAGE obstacle;

Obstacle::Obstacle(const double& origin_angle)
	: img(&obstacle), R_angle(origin_angle)
{
	this->width = img->getwidth();
	this->height = img->getheight();
	this->life = -1;

	Scene::GetScene().AddObject(this);
}

Obstacle::~Obstacle() = default;

void Obstacle::Tick(const int& delta)
{
	angle += PI / 180 * delta / 10;
	if (angle > 2 * PI) angle -= 2 * PI;

	R_angle += PI / 180 * delta / 50;
	if (R_angle > 2 * PI) R_angle -= 2 * PI;

	int arena_long = Arena::long_axis * 1.1;
	int arena_short = Arena::short_axis * 1.1;
	const Pos& arena_center = Arena::center;

	this->pos = {(long)(arena_long * cos(R_angle) - width / 2 + arena_center.x), (long)(arena_short * sin(R_angle) - height / 2 + arena_center.y)};
	
	Player& player = *Scene::GetScene().GetPlayer();
	if (CheckCollision(player) && !player.CheckImmunity()) {
		player.Damage(1);
		player.SetImmunity(true);
	}
}

void Obstacle::Render()
{
	Transform();
	putimage_alpha(img, pos.x, pos.y, 0, 0, width, height);
	Untransform();
}

bool Obstacle::CheckCollision(Player& player)
{
	if (this->GetCenter().GetDistanceFrom(player.GetCenter()) < this->width / 2 + player.width / 2 - 10) {
		return true;
	}

	return false;
}