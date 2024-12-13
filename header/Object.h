#pragma once

class Scene;

class Object
{
protected:
	Object() 
		: width(0), height(0), pos({0, 0}), life(0), show(true), speed({0, 0}), acceleration({0, 0}), belong(nullptr)
	{};

public:
	virtual void Render() = 0;
	
	virtual void Tick(const int& delta) = 0;
	
	const Scene* GetScene();
	
	virtual void InputHandle(const ExMessage& msg) {};

	int width;
	int height;
	POINT pos;
	int life;
	bool show;

	Vec2d speed;
	Vec2d acceleration;

	Scene* belong;
};