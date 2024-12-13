#pragma once

class Object;

class Scene {
public:
	enum class SceneType
	{
		Menu, Game
	};

	void Tick(const int& delta);

	void Render();
	
	void SetCurrentScene(const SceneType& type);

	const std::vector<Object*>& GetObjects() const;

	void AddObject(Object* obj);

	void RemoveObject(Object* obj);
	
	void ClearObjects();

	Scene() : current_scene(SceneType::Menu){}

	~Scene() = default;


private:
	SceneType current_scene;
	std::vector<Object*> menu_objects;
	std::vector<Object*> game_objects;

	std::vector<Object*>& GetCurrentObjectList();
};