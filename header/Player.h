#pragma once

class Player : virtual public Object
{
public:
	Player() = delete;

	Player(Scene& scene);

	void Render() override;

	void Tick(const int& delta) override;

	void InputHandle(const ExMessage& msg) override;

	POINT GetCenter();

	~Player();
private:
	int health;

	const int walk_speed = 6;
	const double friction = 0.01;
	
	std::vector<Animation*> ani_list;
	int current_ani_set;

	bool space_pressed;
	const int cooldown = 1000;
	int counter;
	Vec2d mouse_pos;
};