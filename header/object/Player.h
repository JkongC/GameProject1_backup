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

	void Reset();

	void Render() override;

	void Tick(const int& delta) override;

	void InputHandle(const ExMessage& msg) override;

	void Launch();

	void Attach();

	void Damage(const int& dmg);

	inline bool CheckImmunity() { return this->immune_damage; };

	inline void SetImmunity(bool im) { this->immune_damage = im; };

	inline int GetHealth() { return this->health; }

	inline void SetHealth(const int& health) { this->health = health; }

	inline int GetScore() { return this->score; };

	inline void SetScore(const int& score) { this->score = score; };

	inline Status GetStatus() { return this->status; };

	inline void SetStatus(const Status& status) { this->status = status; }

	~Player() override;
private:
	int health;
	int score;

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
	bool immune_damage;
	int im_counter;
	int flash_counter;
};