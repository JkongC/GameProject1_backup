﻿#include "stdlibs.h"
#include "general/util.h"
#include "general/event.h"
#include "object/Object.h"
#include "general/scene.h"

void Object::SetScale(const double& scale) {
	this->scale = scale;
}

void Object::SetAngle(const double& angle) {
	this->angle = angle;
}

Pos Object::GetCenter() {
	return { this->pos.x + this->width / 2, this->pos.y + this->height / 2 };
}

void Object::Transform() {
	Pos center = GetCenter();
	
	XFORM transform_angle;
	transform_angle.eM11 = cos(this->angle);
	transform_angle.eM21 = sin(this->angle);
	transform_angle.eM12 = -sin(this->angle);
	transform_angle.eM22 = cos(this->angle);
	transform_angle.eDx = -center.x * cos(this->angle) - center.y * sin(this->angle) + center.x;
	transform_angle.eDy = center.x * sin(this->angle) - center.y * cos(this->angle) + center.y;

	XFORM transform_scale;
	transform_scale.eM11 = this->scale;
	transform_scale.eM22 = this->scale;
	transform_scale.eM12 = 0;
	transform_scale.eM21 = 0;
	transform_scale.eDx = center.x - center.x * this->scale;
	transform_scale.eDy = center.y - center.y * this->scale;

	XFORM result;
	CombineTransform(&result, &transform_angle, &transform_scale);

	XFORM& base = Scene::GetScene().GetCamera().GetBaseTransform();
	CombineTransform(&result, &base, &result);

	SetWorldTransform(GetImageHDC(), &result);
}

void Object::Untransform() {
	SetWorldTransform(GetImageHDC(), &Scene::GetScene().GetCamera().GetBaseTransform());
}