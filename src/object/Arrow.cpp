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
	loadimage(this->img, _T("PNG"), MAKEINTRESOURCE(ARROW), 106, 124, false);
	this->width = 106;
	this->height = 124;
}

void Arrow::Render() {
	if (!this->show) return;

	putimage_alpha(this->img, this->pos.x, this->pos.y, 0, 0, this->width, this->height);
}

void Arrow::Tick(const int& delta) {
	if (angle_start > angle_end)
		angle_start -= 3.14159 * 2;

	if (this->clockwise) {
		angle -= this->speed * delta / 1000;
		if (angle < angle_start || angle > angle_end) {
			angle = angle_end;
			clockwise = false;
		}
	}
	else {
		angle += this->speed * delta / 1000;
		if (angle > angle_end || angle < angle_start) {
			angle = angle_start;
			clockwise = true;
		}
	}
}

Pos Arrow::GetCenter() {
	return { this->pos.x + 3, this->pos.y + 62 };
}

void Arrow::Transform() {
	Pos center = GetCenter();
	
	XFORM transform_scale;
	transform_scale.eM11 = this->scale;
	transform_scale.eM22 = this->scale;
	transform_scale.eM12 = 0;
	transform_scale.eM21 = 0;
	transform_scale.eDx = center.x - center.x * this->scale;
	transform_scale.eDy = center.y - center.y * this->scale;

	XFORM transform_angle;
	transform_angle.eM11 = cos(this->angle);
	transform_angle.eM21 = -sin(this->angle);
	transform_angle.eM12 = sin(this->angle);
	transform_angle.eM22 = cos(this->angle);
	transform_angle.eDx = 0;
	transform_angle.eDy = 0;

	XFORM result;
	CombineTransform(&result, &transform_scale, &transform_angle);

	SetWorldTransform(GetImageHDC(this->img), &result);
}