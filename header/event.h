#pragma once

//处理WASD按键
class InputEvent {
public:
	void Emit(const ExMessage& msg);

	void AddConcern(Object* obj);

private:
	std::vector<Object*> input_concerned;
};