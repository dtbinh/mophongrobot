# Giới thiệu #
Các hệ điều hành Windows kể từ phiên bản Windows XP hỗ trợ đầy đủ các chương trình sử dụng mã [Unicode](http://vi.wikipedia.org/wiki/Unicode).
Bộ công cụ lập trình C/C++ phổ biến là Visual C++ 6.0 không hỗ trợ việc soạn thảo các tài nguyên (như menu hay hộp thoại Unicode) nên gây khó khăn trong việc lập trình chương trình Unicode. Các phiên bản mới của bộ công cụ này không gặp khó khăn này.
Tuy nhiên một cách mặc định, các tệp tin chương trình (.h, .cpp...) cũng như tệp tin tài nguyên (.rc) vẫn được ghi dưới dạng [ASCII](http://vi.wikipedia.org/wiki/ASCII). Vì vậy, trước khi nhập các đoạn văn bản Unicode (ví dụ cho tiếng Việt) vào trong tệp chương trình hoặc trong trình soạn thảo tài nguyên (Resource Editor), việc cần làm là lưu lại các tệp tin này dưới định dạng file Unicode (Code Page 1200).
Các bước thực hiện như sau:

1. Trong Visual C++, bấm phím phải chuột trên tên tệp tin cần lưu trong danh sách tệp tin Solution Explorer và chọn View Code

![http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.ViewCode.png](http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.ViewCode.png)

2. Lưu lại tệp tin với định dạng Unicode: Chọn File, Save As...

![http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveAs.png](http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveAs.png)

3. Trong hộp thoại hiện ra, chọn Save with Encoding

![http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveWithEncoding.png](http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveWithEncoding.png)

4. Chọn bộ mã Unicode (Code Page 1200) trong hộp thoại và bấm OK.

![http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveFileAsOption.png](http://mophongrobot.googlecode.com/svn/trunk/Web/Uni.SaveFileAsOption.png)

Bây giờ bạn có thể tự do nhập văn bản Unicode trong tệp tin.