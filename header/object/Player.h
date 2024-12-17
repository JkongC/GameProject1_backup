#pragma once

class Arrow;

class Player : virtual public Object
{
public:
	enum class Status
	{
		Attached = 0, Flying
	};
	
	Player();

	void Render() override;

	void Tick(const int& delta) override;

	void InputHandle(const ExMessage& msg) override;

	void Launch();

	void Attach();

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
	Pos mouse_pos;

	Status status;
	Arrow* arrow;
	int R_angle;

	bool lock_camera;
};