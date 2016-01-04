# Giới thiệu #

Trang này giới thiệu kỹ thuật Đọc và hiển thị file STL bằng OpenGL.

Việc đọc và hiển thị các file STL có thể được thực hiện với sự giúp đỡ của lớp **`CSTL_File`** ([download](http://mophongrobot.googlecode.com/svn/trunk/Kythuat/STL_File.zip)). Đây là một lớp đối tượng C++ do xuất phát từ project AMF tại http://amff.wikispaces.com/STL+to+AMF+converter, đã được tôi sửa đổi để phù hợp với việc mô phỏng robot.

# Các thao tác #
Lớp CSTL\_File có thể thực hiện các thao tác chính sau:
  * Các thao tác chính
  * Đọc file STL (nhị phân & văn bản) vào bộ nhớ
  * Tính toán hình hộp bao
  * Vẽ đối tượng bằng các lệnh OpenGL

## Hướng dẫn sử dụng lớp CSTL\_File ##
  1. Copy 3 file Vec3D.h, STL\_File.h và STL\_File.cpp vào thư mục project
  1. Thêm 3 file Vec3D.h, STL\_File.h và STL\_File.cpp vào project
  1. Thêm dòng **`#include "STL_File.h"`** ở đầu chương trình
  1. Thêm dòng **`CSTL_File stl;`** để khai báo biến stl
  1. Thêm dòng **`stl.Load(“sphere.stl”);`** vào trong hàm **`InitGraphics()`** để đọc tệp **`sphere.stl`**
  1. Thêm hàm **`stl.Draw(false, false);`** để vẽ đối tượng

## Khai báo của lớp CSTL\_File ##
```
class CSTL_File
{
protected:

	std::string ObjectName;
	std::vector<CFacet> Facets;
public:
	CSTL_File(void);
	CSTL_File(void);

	CSTL_File(CSTL_File& s);
	CSTL_File& operator=(const CSTL_File& s);

	bool Load(std::string filename);
	bool Save(std::string filename, bool Binary = true) const;

	void ComputeBoundingBox(Vec3D& pmin, Vec3D& pmax);

	void Clear() { Facets.clear(); ObjectName = "Default";} // clear/reset the list of trianges
	int Size() const { return (int)Facets.size(); }

public:

	// file i/o
	bool LoadBinary(std::string filename);
	bool LoadAscii(std::string filename);

	void Draw(bool bModelhNormals, bool bShaded);
};
```