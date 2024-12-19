#pragma once

class Arena
{
public:

	static Arena& GetArena() {
		static Arena arena;
		return arena;
	}  //µ¥ÀýÄ£Ê½

	inline bool CheckIfOut(const Pos& pos) {
		double delta_x = pos.x - center.x;
		double delta_y = pos.y - center.y;
		return (delta_x * delta_x / (long_axis * long_axis)) + (delta_y * delta_y / (short_axis * short_axis)) > 1;
	}

	const int long_axis = 300;
	const int short_axis = 170;
	const Pos center = { window_x / 2 + 4, window_y / 2 - 4};
private:
	Arena() = default;
	Arena(const Arena&) = delete;
	~Arena() = default;
	Arena& operator=(const Arena&) = delete;
};