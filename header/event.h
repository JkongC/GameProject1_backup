#pragma once

//´¦ÀíWASD°´¼ü
class InputEvent {
public:
	void Emit(const ExMessage& msg);

	void AddConcern(Object* obj);

private:
	std::vector<Object*> input_concerned;
};