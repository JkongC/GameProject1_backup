#pragma once

class Obstacle : public Object
{
public:
	Obstacle(const double& origin_angle);

	~Obstacle();

	void Tick(const int& delta) override;

	void Render();

	bool CheckCollision(Player& player);

	void DamagePlayer(Player& player);
private:
	IMAGE* img;

	const int damage = 1;
	const int damage_cooldown = 1000;
	bool can_damage;
	int counter;

	double R_angle;
};