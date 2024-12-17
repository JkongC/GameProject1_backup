#include "stdlibs.h"
#include "general/util.h"

void ScalingByPixel(IMAGE** dst, IMAGE* src, int frame_num, const int& scale) {
	IMAGE temp = *src;

	int src_w = temp.getwidth();
	int src_h = temp.getheight();
	int dst_w = src_w / frame_num * scale * frame_num;

	*dst = new IMAGE(dst_w, src_h * scale);

	DWORD* dst_buffer = GetImageBuffer(*dst);
	DWORD* src_buffer = GetImageBuffer(&temp);

	for (int i = 0; i < src_h; i++) {
		for (int j = 0; j < src_w; j++) {
			int dst_x = j * scale;
			int dst_y = i * scale;

			for (int sub_X = 0; sub_X < scale; sub_X++) {
				for (int sub_Y = 0; sub_Y < scale; sub_Y++) {
					dst_buffer[dst_x + (dst_y + sub_Y) * dst_w + sub_X] = src_buffer[j + i * src_w];
				}
			}
		}
	}
}