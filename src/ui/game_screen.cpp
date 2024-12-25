#include "stdlibs.h"

#include "ui/game_screen.h"
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "object/Player.h"
#include "object/Obstacle.h"
#include "object/Score.h"
#include "ui/Button.h"
#include "general/event.h"
#include "general/scene.h"
#include "resource.h"

extern IMAGE game_background;
bool Init = false;

void InitGameScreen()
{
	Scene& scene = Scene::GetScene();
	
	scene.SetCurrentScene(Scene::SceneType::Game);

	scene.SetSceneBackground(Scene::SceneType::Game, &game_background);
	
	if (!Init) {
		new Player();
		new Obstacle(0.8 * PI);
		new Obstacle(0.5 * PI);
		new Obstacle(-0.6 * PI);
		Init = true;
	}
	else {
		scene.IterateObjects([](Object* obj) {obj->Reset();});
	}
}

void GameProcess(const int& delta)
{
	ScoreGenerator::GetGenerator().TryGenerate(delta);
}
