#pragma once

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
		Menu, Game
	};

	void Tick(const int& delta);

	Camera& GetCamera();

	InputEvent& GetInputEvent();

	void Render();
	
	void SetCurrentScene(const SceneType& type);

	const std::vector<Object*>& GetObjects() const;

	void AddObject(Object* obj);

	void RemoveObject(Object* obj);
	
	void ClearObjects();

	Scene() : current_scene(SceneType::Menu), menu_camera(), game_camera(), menu_inputevent(), game_inputevent() {}

	~Scene() = default;


private:
	SceneType current_scene;
	std::vector<Object*> menu_objects;
	std::vector<Object*> game_objects;
	Camera menu_camera;
	Camera game_camera;
	InputEvent menu_inputevent;
	InputEvent game_inputevent;

	std::vector<Object*>& GetCurrentObjectList();
};