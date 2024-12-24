#pragma once

#include <array>

class Object;
class Player;
class Obstacle;
class Score;
class InputEvent;

class Camera {
public:
	Camera();

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

	XFORM& GetBaseTransform();
private:
	Pos center_point;
	double scale;
	double angle;
	XFORM base_transform;
};

class Scene {
public:
	enum class SceneType
	{
		MainMenu = 0, Game, Settings, DieMenu, Void
	};   //Void����ռλ������Ҫ�л�������ʼ�ձ�֤����ĩβ

	static Scene& GetScene() {
		static Scene scene;
		return scene;
	}   //����ģʽ
	
	void Tick(const int& delta);

	Camera& GetCamera();

	InputEvent& GetInputEvent();

	void Render();
	
	void SetCurrentScene(const SceneType& type);

	void SetSceneBackground(const SceneType& type, IMAGE* background);

	const std::vector<Object*>& GetObjects() const;

	void AddObject(Object* obj);

	void SetPlayer(Player* player);

	inline Player* GetPlayer() { return this->player; }

	void RemoveObject(Object* obj);
	
	void ClearObjects();

private:
	Scene() : current_scene(SceneType::Game), scene_obj_list(), scene_cam_list(), scene_inputevent_list(), scene_background_list(), player(nullptr) {}

	Scene(const Scene&) = delete;

	Scene& operator=(const Scene&) = delete;

	~Scene();

private:
	SceneType current_scene;
	std::array<std::vector<Object*>, (int)SceneType::Void> scene_obj_list;
	std::array<Camera, (int)SceneType::Void> scene_cam_list;
	std::array<InputEvent, (int)SceneType::Void> scene_inputevent_list;
	std::array<IMAGE*, (int)SceneType::Void> scene_background_list;
	Player* player;

	std::vector<Object*>& GetCurrentObjectList();
};