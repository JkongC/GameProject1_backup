#include <vector>
#include <chrono>
#include <easyx.h>
#include "util.h"
#include "event.h"
#include "scene.h"
#include "Object.h"

const Scene* Object::GetScene() {
	return this->scene_belong;
}