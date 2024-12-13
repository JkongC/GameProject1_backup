#pragma once

class Animation {
public:
	Animation() = default;
	
	//scale�ǷŴ�������Է�ԭͼ̫С
	Animation(IMAGE new_atlas, int width, int height, int interval, int frame_num, int scale);

	void Render(int x, int y);

	void Tick(const int& delta);

	const int& GetWidth();

	const int& GetHeight();

	~Animation();
private:
	int width;
	int height;
	IMAGE* atlas;
	int frame_amounts;
	int current_idx;
	int interval;
	int counter;
};