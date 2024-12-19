#pragma once

#include <array>

class Object;
class InputEvent;

class Camera {
public:
	Camera() : center_point({window_x / 2, window_y / 2}), scale(1), angle(0) {}

	void ResetCamera();

	void Update();

	Pos GetZeroPos() const;
	
	Pos GetRelativePos(const Pos& absolute) const;

	Pos GetAbsolutePos(const Pos& relative) const;

	const Pos& GetPos() const;

	void SetPos(const Pos new_pos);

	const double& GetScale() const;

	void SetScale(const double& scale);

	const double& GetAngle() const;

	void SetAngle(const double& angle);
private:
	Pos center_point;
	double scale;
	double angle;
};

class Scene {
public:
	enum class SceneType
	{
		MainMenu = 0, Game, Settings, DieMenu, Void
	};   //Void仅作占位符，不要切换到它，始终保证它在末尾

	static Scene& GetScene() {
		static Scene scene;
		return scene;
	}   //单例模式
	
	void Tick(const int& delta);

	Camera& GetCamera();

	InputEvent& GetInputEvent();

	void Render();
	
	void SetCurrentScene(const SceneType& type);

	void SetSceneBackground(const SceneType& type, IMAGE* background);

	const std::vector<Object*>& GetObjects() const;

	void AddObject(Object* obj);

	void RemoveObject(Object* obj);
	
	void ClearObjects();

private:
	Scene() : current_scene(SceneType::Game) {}

	Scene(const Scene&) = delete;

	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

private:
	SceneType current_scene;
	std::array<std::vector<Object*>, (int)SceneType::Void> scene_obj_list;
	std::array<Camera, (int)SceneType::Void> scene_cam_list;
	std::array<InputEvent, (int)SceneType::Void> scene_inputevent_list;
	std::array<IMAGE*, (int)SceneType::Void> scene_background_list;

	std::vector<Object*>& GetCurrentObjectList();
};