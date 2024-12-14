#include <vector>
#include <chrono>
#include <easyx.h>
#include "util.h"
#include "Object.h"
#include "scene.h"

void Scene::Tick(const int& delta) {
	for (Object* obj : GetObjects()) {
		obj->Tick(delta);
	}
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