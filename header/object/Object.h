﻿#pragma once

class Scene;

class Object
{
protected:
	Object() 
		: width(0), height(0), pos({0, 0}), life(0), show(true), speed({0, 0}), acceleration({0, 0}), life_counter(0), angle(0), scale(1), should_remove(false)
	{};

public:
	virtual ~Object() {};

	virtual void Reset() {};

	virtual void Render() = 0;
	
	virtual void Tick(const int& delta) {};
	
	virtual void InputHandle(const ExMessage& msg) {};

	virtual Pos GetCenter();

	void SetScale(const double& scale);

	void SetAngle(const double& angle);

	virtual void Transform();

	virtual void Untransform();

	int width;
	int height;
	Pos pos;
	int life;
	int life_counter;
	bool show;

	bool should_remove;

	Vec2d speed;
	Vec2d acceleration;

	double scale;
	double angle;
};