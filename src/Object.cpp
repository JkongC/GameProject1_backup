#include <vector>
#include <chrono>
#include <easyx.h>
#include "util.h"
#include "scene.h"
#include "Object.h"

const Scene* Object::GetScene() {
	return this->belong;
}