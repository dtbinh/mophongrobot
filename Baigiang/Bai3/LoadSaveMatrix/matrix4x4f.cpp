#include "matrix4x4f.h"
#include <sstream>


// Đọc dữ liệu từ chuỗi ký tự chứa 16 số thực
std::istream & operator >> (std::istream & ss, matrix4x4f & mat)
{
	for (int i = 0; i < 16; i++)
		ss >> mat.m[i];

	return ss;
}

// Ghi dữ liệu ra chuỗi ký tự dưới dạng 16 số thực cách nhau bằng dấu tab (\t)
std::ostream & operator << (std::ostream & ss, const matrix4x4f & mat)
{
	for (int i = 0; i < 16; i++)
	{
		ss << mat.m[i];

		if (i < 15)
			ss << '\t';
	}

	return ss;
}
