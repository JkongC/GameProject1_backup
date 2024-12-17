#pragma once

class Scene;

class Object
{
protected:
	Object() 
		: width(0), height(0), pos({0, 0}), life(0), show(true), speed({0, 0}), acceleration({0, 0}), scene_belong(nullptr), life_counter(0)
	{};

public:
	virtual void Render() = 0;
	
	virtual void Tick(const int& delta) = 0;
	
	const Scene* GetScene();
	
	virtual void InputHandle(const ExMessage& msg) {};

	virtual Pos GetCenter() = 0;

	int width;
	int height;
	Pos pos;
	int life;
	int life_counter;
	bool show;

	Vec2d speed;
	Vec2d acceleration;

	Scene* scene_belong;
};