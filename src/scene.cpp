﻿#pragma comment(lib, "Gdi32.lib")

#include <vector>
#include <chrono>
#include <easyx.h>
#include <wingdi.h>
#include <cmath>
#include "util.h"
#include "Object.h"
#include "scene.h"

void Camera::ResetCamera() {
	this->center_point = { window_x / 2, window_y / 2 };
	this->scale = 1.0;
	this->angle = 0;
}

void Camera::Update() {
	XFORM transform_scale;
	transform_scale.eM11 = this->scale;
	transform_scale.eM22 = this->scale;
	transform_scale.eM12 = 0;
	transform_scale.eM21 = 0;
	transform_scale.eDx = this->center_point.x - this->center_point.x * this->scale;
	transform_scale.eDy = this->center_point.y - this->center_point.y * this->scale;

	XFORM transform_angle;
	transform_angle.eM11 = cos(this->angle);
	transform_angle.eM21 = -sin(this->angle);
	transform_angle.eM12 = sin(this->angle);
	transform_angle.eM22 = cos(this->angle);
	transform_angle.eDx = 0;
	transform_angle.eDy = 0;

	XFORM result;
	CombineTransform(&result, &transform_scale, &transform_angle);
	
	SetWorldTransform(GetImageHDC(), &result);
}

Pos Camera::GetZeroPos() const {
	return { this->center_point.x - window_x / 2, this->center_point.y - window_y / 2 };
}

Pos Camera::GetRelativePos(const Pos& absolute) const {
	return {absolute.x - (this->center_point.x - window_x / 2), absolute.y - (this->center_point.y - window_y / 2)};
}

Pos Camera::GetAbsolutePos(const Pos& relative) const {
	return { relative.x + (this->center_point.x - window_x / 2), relative.y + (this->center_point.y - window_y / 2) };
}

const Pos& Camera::GetPos() const {
	return this->center_point;
}

void Camera::SetPos(const Pos new_pos) {
	if (new_pos.x - window_x / 2 > 0 && new_pos.x + window_x / 2 < world_x) {
		this->center_point.x = new_pos.x;
	}

	if (new_pos.y - window_y / 2 > 0 && new_pos.y + window_y / 2 < world_y) {
		this->center_point.y = new_pos.y;
	}
}

const double& Camera::GetScale() const {
	return this->scale;
}

void Camera::SetScale(const double& scale) {
	this->scale = scale;
}

const double& Camera::GetAngle() const {
	return this->angle;
}

void Camera::SetAngle(const double& angle) {
	this->angle = angle;
}


void Scene::Tick(const int& delta) {
	for (Object* obj : GetObjects()) {
		obj->Tick(delta);
	}
	this->camera.Update();
}

Camera& Scene::GetCamera() {
	return this->camera;
}

void Scene::Render() {
	for (Object* obj : GetObjects()) {
		obj->Render();
	}
}

void Scene::SetCurrentScene(const SceneType& type) {
	current_scene = type;
}

const std::vector<Object*>& Scene::GetObjects() const {
	switch (current_scene)
	{
	case SceneType::Menu:
		return menu_objects;
		break;
	case SceneType::Game:
		return game_objects;
		break;
	default:
		DebugBreak();
		break;
	}
}

void Scene::AddObject(Object* obj) {
	GetCurrentObjectList().push_back(obj);
}

void Scene::RemoveObject(Object* obj) {
	std::vector<Object*> current = GetCurrentObjectList();
	auto it = std::find(current.begin(), current.end(), obj);
	int obj_index = -1;
	if (it != current.end()) {
		obj_index = (int)std::distance(current.begin(), it);
	}

	if (obj_index != -1) {
		std::swap(current[obj_index], current[current.size() - 1]);
		current.pop_back();
	}
}

void Scene::ClearObjects() {
	GetCurrentObjectList().clear();
}

std::vector<Object*>& Scene::GetCurrentObjectList() {
	switch (current_scene)
	{
	case SceneType::Menu:
		return menu_objects;
		break;
	case SceneType::Game:
		return game_objects;
		break;
	default:
		DebugBreak();
		break;
	}
}