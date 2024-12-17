#pragma once

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

#define window_x 1629
#define window_y 1184

#define world_x 3000
#define world_y 3000

#include <cmath>

struct Pos
{
	LONG x = 0;
	LONG y = 0;

	inline double GetDistanceFrom(const Pos& another) {
		return sqrt((this->x - another.x) * (this->x - another.x) + (this->y - another.y) * (this->x - another.x));
	}
	
	Pos operator+(const Pos& another) {
		return { this->x + another.x, this->y + another.y };
	}

	Pos& operator+=(const Pos& another) {
		this->x += another.x;
		this->y += another.y;
		return *this;
	}

	Pos operator-(const Pos& another) {
		return { this->x - another.x, this->y - another.y };
	}

	Pos& operator-=(const Pos& another) {
		this->x -= another.x;
		this->y -= another.y;
		return *this;
	}
};

struct Vec2d 
{
	double x = 0.0;
	double y = 0.0;
	double scale = 1.0;

	void Friction(double friction) {
		double new_scale = scale*(1 - friction);
		if (new_scale < 0.2) {
			x = 0;
			y = 0;
			return;
		}

		x *= new_scale / scale;
		y *= new_scale / scale;
		scale = new_scale;
	}

	double Length() {
		return sqrt(x * x + y * y);
	}
	
	void Normalize() {
		double length = Length();
		x /= length;

		y /= length;
	}

	void Normalize(double scale) {
		double length = Length();
		x /= length;
		x *= scale;

		y /= length;
		y *= scale;
	}

	Vec2d operator+(const Vec2d& another) const {
		return {this->x + another.x, this->y + another.y};
	}

	Vec2d& operator+=(const Vec2d& another) {
		this->x += another.x;
		this->y += another.y;
		return *this;
	}

	template<typename T>
	Vec2d operator*(T scalar) {
		return { this->x * scalar, this->y * scalar };
	}

	template<typename T>
	Vec2d& operator*=(T scalar) {
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}
};

template<typename T>
Vec2d operator*(T scalar, const Vec2d& another) {
	return { another.x * scalar, another.y * scalar };
}

struct Timer
{
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	int elapsed = 0;

	void Start() {
		begin = std::chrono::steady_clock::now();
		end = begin;
	}

	const int& SinceLast() {
		auto now = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(now - end).count();
		end = now;
		return elapsed;
	}

	void End() {
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end - begin).count();
	}
};

struct Scoped_Timer
{
	std::chrono::steady_clock::time_point begin;
	int& elapsed_result;

	Scoped_Timer(int& result)
		: elapsed_result(result)
	{
		begin = std::chrono::steady_clock::now();
	}

	~Scoped_Timer()
	{
		auto end = std::chrono::steady_clock::now();
		elapsed_result = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end - begin).count();
	}
};

void ScalingByPixel(IMAGE** dst, IMAGE* src, int frame_num, const int& scale);

inline void putimage_alpha(IMAGE* image, int x, int y, int xsrc, int ysrc, int width, int height) {
	AlphaBlend(GetImageHDC(), x, y, width, height, GetImageHDC(image),
		xsrc, ysrc, width, height, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}