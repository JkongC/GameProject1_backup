#include "stdlibs.h"

#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "object/Player.h"
#include "object/Arrow.h"
#include "resource.h"

Arrow::Arrow()
	: clockwise(true), angle_start(0), angle_end(0)
{
	this->img = new IMAGE();
	loadimage(this->img, _T("PNG"), MAKEINTRESOURCE(ARROW), 106, 124, false);
	this->width = 106;
	this->height = 124;
}

Arrow::~Arrow()
{
	delete this->img;
}

void Arrow::Render() {
	if (!this->show) return;

	Transform();
	putimage_alpha(this->img, pos.x, pos.y, 0, 0, width, height);
	Untransform();
}

void Arrow::Tick(const int& delta) {
	if (angle_start > angle_end)
		angle_start -= 3.14159 * 2;

	if (this->clockwise) {
		angle -= this->speed * delta / 1000;
		if (angle < angle_start || angle > angle_end) {
			angle = angle_start;
			clockwise = false;
		}
	}
	else {
		angle += this->speed * delta / 1000;
		if (angle > angle_end || angle < angle_start) {
			angle = angle_end;
			clockwise = true;
		}
	}
}

Pos Arrow::GetCenter() {
	return { this->pos.x + 3, this->pos.y + 62 };
}