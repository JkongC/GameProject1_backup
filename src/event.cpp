#include <vector>
#include <easyx.h>
#include <chrono>
#include "util.h"
#include "Object.h"
#include "event.h"

void InputEvent::Emit(const ExMessage& msg) {
	for (Object*& obj : input_concerned) {
		obj->InputHandle(msg);
	}
}

void InputEvent::AddConcern(Object* obj) {
	input_concerned.push_back(obj);
}