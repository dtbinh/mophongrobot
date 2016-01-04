# Mục lục #


# Giới thiệu #

Trang này giới thiệu cách một chương trình C/C++ gọi các hàm tính toán của Matlab. Trình dịch được sử dụng để minh hoạ là Visual C++ 2008, Matlab R2010b.

Tài liệu đọc thêm
  1. **Matlab API to C++**: Bài giới thiệu về lập trình kết nối C/C++ với Matlab của tác giả Christopher Dabney ([download](http://mophongrobot.googlecode.com/svn/trunk/Thamkhao/MatLab.API.to.C++.ppt), [nguồn](http://classes.soe.ucsc.edu/cmps060m/Spring06/ma/cdabney19/MatLab%20API%20to%20C++.ppt))
  1. **Matlab 2011b External Interfaces**: Hướng dẫn lập trình giao tiếp với Matlab, trong đó chương 6 bàn về tương tác với chương trình C/C++ ([download](http://mophongrobot.googlecode.com/svn/trunk/Thamkhao/MatLab.API.to.C++.ppt), [nguồn](http://www.mathworks.ch/help/pdf_doc/matlab/apiext.pdf))
# Chi tiết #

## Các tệp tin cần thiết để lập trình ##
Khi cài đặt Matlab, chương trình cài đặt copy các tệp tin cần thiết để cho phép lập trình kết nối với một chương trình C/C++. Các tệp tin cần thiết là
  * `<installpath>\extern\include\engine.h`
  * `<installpath>\extern\lib\win32\microsoft\libeng.lib`
  * `<installpath>\extern\lib\win32\microsoft\libmx.lib`

Trong đó `<installpath>` là thư mục cài đặt Matlab (ví dụ `"C:\Program Files\MATLAB\R2010b"`).

**Chú ý**: Để Visual C++ tìm được hai tệp engine.h, libeng.lib và libmx.lib ở trên, cần đặt các đường dẫn tương ứng vào trong môi trường phát triển
  1. Trong Visual C++ chọn menu Tools/Options…
  1. Trong cửa sổ hiện ra chọn Projects and Solutions, VC++ Directories
  1. Cần thêm đường **Include files** và **Library files** để trỏ đến các thư mục tương ứng chứa các tệp đó.

Một số ví dụ lập trình có ở thư mục `<installpath>\extern\examples\`

## Các tệp tin cần thiết để chạy chương trình ##
Khi chạy chương trình trên một máy tính, cần cài đặt Matlab Compiler Runtime trước. Bộ cài có tại
`<installpath>\toolbox\compiler\deploy\win32\MCRInstaller.exe`

## Các bước thực hiện ##
### Sử dụng thư viện OpenMaple ###
Cần thêm các dòng lệnh sau vào đầu chương trình C/C++:

```
#include "engine.h"	// Các tiêu đề hàm 

#pragma comment(lib, "libeng.lib")	// để kết nối thư viện cần thiết
#pragma comment(lib, "libmx.lib")	// để kết nối thư viện cần thiết
```

### Gọi một lệnh của Matlab ###

Một chương trình C/C++ cần thực hiện 3 bước sau để có thể gọi lệnh của Matlab:
  1. Gọi hàm `engOpen()` để khởi tạo bộ máy tính toán của Matlab
  1. Gọi hàm `engEvalString()` để thực hiện một lệnh trong Matlab
  1. Gọi hàm `engClose()` sau khi kết thúc tính toán


### Ví dụ ###
Chương trình C/C++ sau sẽ thực hiện lệnh `"X = 1:5";` bằng Matlab. Project chương trình [ở đây](http://code.google.com/p/mophongrobot/source/browse/#svn%2Ftrunk%2FKythuat%2FLinkMatlab).

```
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#define  BUFSIZE 256

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")

int main()
{
   Engine *ep;
   mxArray *T = NULL, *result = NULL;
   char buffer[BUFSIZE+1];

   if (!(ep = engOpen("\0"))) {
      fprintf(stderr, "\nCan't start MATLAB engine\n");
      return EXIT_FAILURE;
   }

   buffer[BUFSIZE] = '\0';
   engOutputBuffer(ep, buffer, BUFSIZE);

   char s[] = "X = 1:5";

   printf("Evaluating: %s!\n", s);
   
   engEvalString(ep, s);

   printf("%s", buffer);

   printf("Done!\n");

   engClose(ep);
   
   return EXIT_SUCCESS;
}
```
