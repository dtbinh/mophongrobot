# Giới thiệu #

Để thao tác với mô hình mô phỏng bằng chuột theo kiểu phần mềm [[Maya|http://en.wikipedia.org/wiki/Autodesk_Maya]] của Autodesk, có thể sử dụng lớp [MayaCamera](http://mophongrobot.googlecode.com/svn/trunk/Kythuat/MayaCamera/MayaCamera.h) do tôi viết trong chương trình. Khi đó, các thao tác điều khiển camera với chuột như sau:
  * phím trái chuột để xoay mô hình
  * phím phải chuột để thu phóng mô hình
  * phím giữa để tịnh tiến mô hình

![http://mophongrobot.googlecode.com/svn/trunk/Web/mayacamera.png](http://mophongrobot.googlecode.com/svn/trunk/Web/mayacamera.png)

# Cách sử dụng #
  * Copy toàn bộ nội dung tệp tin [MayaCamera](http://mophongrobot.googlecode.com/svn/trunk/Kythuat/MayaCamera/MayaCamera.h) vào đầu chương trình
  * Khai báo một biến tổng thể ở đầu chương trinh
```
MayaCamera g_mc;
```
  * Thêm dòng lệnh dưới đây vào trong hàm DrawGraphics()
```
g_mc.UpdateView();	
```
  * Thêm đoạn chương trình sau vào trong hàm MainWndProc() để xử lý sự kiện người dùng bấm chuột
```
case WM_MOUSEMOVE: 
   g_mc.UpdateOnMouseMove(wParam, lParam);
   break;
```