#include "stdlibs.h"
#include <cmath>
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "general/event.h"
#include "object/Player.h"
#include "object/Obstacle.h"
#include "object/Score.h"
#include "general/scene.h"
#include "general/SD_Music.h"

Camera::Camera()
	: center_point({ window_x / 2, window_y / 2 }), scale(1), angle(0)
{
	base_transform.eM11 = 1;
	base_transform.eM22 = 1;
	base_transform.eM12 = 0;
	base_transform.eM21 = 0;
	base_transform.eDx = 0;
	base_transform.eDy = 0;
}

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

XFORM& Camera::GetBaseTransform() {
	return this->base_transform;
}


void Scene::Tick(const int& delta) {
	auto& lst = GetCurrentObjectList();
	for (size_t idx = 0; idx < lst.size(); idx++)
	{
		if (lst[idx]->should_remove)
		{
			std::swap(lst[idx], lst[lst.size() - 1]);
			delete lst[lst.size() - 1];
			lst.pop_back();
			continue;
		}

		lst[idx]->Tick(delta);
	}

	this->scene_cam_list[(int)current_scene].Update();
}

Camera& Scene::GetCamera() {
	return this->scene_cam_list[(int)current_scene];
}

InputEvent& Scene::GetInputEvent() {
	return this->scene_inputevent_list[(int)current_scene];
}

void Scene::Render() {
	putimage_alpha(this->scene_background_list[(int)current_scene],
		0, 0, 0, 0, window_x, window_y);
	auto& objs = GetObjects();
	for (Object* obj : objs) {
		obj->Render();
	}
}

void Scene::SetCurrentScene(const SceneType& type) {
	current_scene = type;
	SD_music_close();
	switch (current_scene)
	{
	case Scene::SceneType::MainMenu:
		break;
	case Scene::SceneType::Game:
		mciSendString(L"play BGM repeat", NULL, 0, NULL);
		break;
	case Scene::SceneType::Settings:
		break;
	case Scene::SceneType::DieMenu:
		break;
	case Scene::SceneType::Void:
		break;
	default:
		break;
	}
}

void Scene::SetSceneBackground(const SceneType& type, IMAGE* background) {
	this->scene_background_list[(int)type] = background;
}

const std::vector<Object*>& Scene::GetObjects() const {
	return this->scene_obj_list[(int)current_scene];
}

void Scene::AddObject(Object* obj) {
	GetCurrentObjectList().push_back(obj);
}

void Scene::SetPlayer(Player* player) {
	this->player = player;
	GetCurrentObjectList().push_back(static_cast<Object*>(player));
}

void Scene::RemoveObject(Object* obj) {
	auto& current = GetCurrentObjectList();
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
	for (Object*& obj : GetCurrentObjectList()) {
		delete obj;
	}
	GetCurrentObjectList().clear();
}

std::vector<Object*>& Scene::GetCurrentObjectList() {
	return this->scene_obj_list[(int)current_scene];
}

void Scene::IterateObjects(std::function<void(Object*)> proc) {
	for (Object*& obj : GetCurrentObjectList()) {
		proc(obj);
	}
}

Scene::~Scene() {
	for (auto& lst : scene_obj_list) {
		for (Object*& obj : lst) {
			delete obj;
		}
	}
}