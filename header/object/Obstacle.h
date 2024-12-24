#pragma once

class Obstacle : public Object
{
public:
	Obstacle(const double& origin_angle);

	~Obstacle() override;

	void Tick(const int& delta) override;

	void Render();

	bool CheckCollision(Player& player);
private:
	IMAGE* img;

	const int damage = 1;

	double R_angle;
};