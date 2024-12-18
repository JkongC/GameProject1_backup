#pragma once

class Arena
{
public:

	static Arena& GetArena() {
		static Arena arena;
		return arena;
	}  //µ¥ÀıÄ£Ê½

	const int radius = 250;
	const Pos center = { window_x / 2, window_y / 2 };
private:
	Arena() = default;
	Arena(const Arena&) = delete;
	~Arena() = default;
	Arena& operator=(const Arena&) = delete;
};