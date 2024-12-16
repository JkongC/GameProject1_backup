#pragma comment(lib, "Msimg32.lib")

#include <vector>
#include <functional>
#include <easyx.h>
#include <ctime>
#include <chrono>
#include "Animation.h"
#include "util.h"

Animation::Animation(IMAGE new_atlas, int width, int height, int interval, int frame_num, int scale)
	:interval(interval), frame_amount(frame_num), current_idx(0), counter(0)
{
	IMAGE* actual;
	this->width = width * scale;
	this->height = height * scale;
	ScalingByPixel(&actual, &new_atlas, frame_num, scale);
	this->atlas = actual;
}

void Animation::Render(int x, int y) {
	putimage_alpha(atlas, x, y, width * current_idx, 0, width, height);
}

void Animation::Tick(const int& delta) {
	this->counter += delta;
	if (counter >= interval) {
		counter = 0;
		current_idx++;
	}
	current_idx %= frame_amount;
}

const int& Animation::GetWidth() {
	return this->width;
}

const int& Animation::GetHeight() {
	return this->height;
}

Animation::~Animation()
{

}