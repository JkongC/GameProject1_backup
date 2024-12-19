#pragma once

class Player;

class Arrow : public Object
{
	friend class Player;
private:
	Arrow();
	~Arrow();

	void Render();

	void Tick(const int& delta);

	Pos GetCenter() override;

private:
	IMAGE* img;
	bool clockwise;

	double angle_start;
	double angle_end;

	const double speed = 3.14159 / 180 * 95;
};