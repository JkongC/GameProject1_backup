#include "stdlibs.h"
#include "general/util.h"
#include "object/Object.h"
#include "general/event.h"

void InputEvent::Emit(const ExMessage& msg) {
	for (Object*& obj : input_concerned) {
		obj->InputHandle(msg);
	}
}

void InputEvent::AddConcern(Object* obj) {
	input_concerned.push_back(obj);
}