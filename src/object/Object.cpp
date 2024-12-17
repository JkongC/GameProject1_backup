#include "stdlibs.h"
#include "general/util.h"
#include "general/event.h"
#include "general/scene.h"
#include "object/Object.h"

void Object::SetScale(const double& scale) {
	this->scale = scale;
}

void Object::SetAngle(const double& angle) {
	this->angle = angle;
}

Pos Object::GetCenter() {
	return { this->pos.x + this->width / 2, this->pos.y + this->height / 2 };
}