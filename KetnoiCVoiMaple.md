# Mục lục #


# Giới thiệu #

Trang này giới thiệu cách một chương trình C/C++ gọi các hàm tính toán của Maple. Trình dịch được sử dụng để minh hoạ là Visual C++ 2008, Maple 13.

Tài liệu đọc thêm
  * **Maple 12 Advanced Programming**: Hướng dẫn lập trình nâng cao trong Maple, trong đó chương 6 mô tả các cách giao tiếp giữa Maple và C/C++ ([download](http://code.google.com/p/mophongrobot/svn/trunk/Thamkhao/Maple-12-Advanced.Programming.pdf), [nguồn](http://www.maplesoft.com/view.aspx?SF=5885/AdvancedProgramming1.pdf))

# Chi tiết #

## Các tệp tin cần thiết để lập trình ##
Khi cài đặt Maple, chương trình cài đặt copy các tệp tin cần thiết để cho phép lập trình kết nối với một chương trình C/C++. Các tệp tin cần thiết là
  * `<installpath>\extern\include\maplec.h`
  * `<installpath>\bin.win\maplec.lib`
Trong đó `<installpath>` là thư mục cài đặt Maple (ví dụ `"C:\Program Files\Maple 13"`).

**Chú ý**: Để Visual C++ tìm được hai tệp maplec.h và maplec.lib ở trên, cần đặt các đường dẫn tương ứng vào trong môi trường phát triển
  1. Trong Visual C++ chọn menu Tools/Options…
  1. Trong cửa sổ hiện ra chọn Projects and Solutions, VC++ Directories
  1. Cần thêm đường **Include files** và **Library files** để trỏ đến các thư mục tương ứng chứa `maplec.h` và `maplec.lib`.

> Một số ví dụ lập trình có ở thư mục `<installpath>\samples\OpenMaple\`

## Các tệp tin cần thiết để chạy chương trình ##
Để có thể chạy chương trình, máy tính cần có Maple cài đặt sẵn.

## Các bước thực hiện ##
### Sử dụng thư viện OpenMaple ###
Cần thêm các dòng lệnh sau vào đầu chương trình C/C++:

```
#include "maplec.h" // Các tiêu đề hàm 

#pragma comment(lib, "maplec.lib") // để kết nối thư viện cần thiết
```

### Gọi một lệnh của Maple ###

Một chương trình C/C++ cần thực hiện 3 bước sau để có thể gọi lệnh của Maple:
  1. Gọi hàm `StartMaple()` để khởi tạo bộ máy tính toán của Maple
  1. Gọi hàm `EvalMapleStatement()` để thực hiện một lệnh trong Maple. Ngoài ra có thể sử dụng các hàm khác trong maplec.h
  1. Gọi hàm `StopMaple()` sau khi kết thúc tính toán

### Ví dụ ###
Chương trình C/C++ sau sẽ thực hiện lệnh `int(x^2+1,x);` để tích phân biểu thức `x^2+1` bằng Maple. Project chương trình [ở đây](http://code.google.com/p/mophongrobot/source/browse/trunk/Kythuat/LinkMaple/).

```
#include <stdio.h>
#include <stdlib.h>
#include "maplec.h"
#pragma comment(lib, "maplec.lib")

/* callback used for directing result output */
static void M_DECL textCallBack( void *data, int tag, char *output )
{
    printf("%s\n",output);
}

int main( int argc, char *argv[] )
{
    char err[2048];      
   MKernelVector kv;  /* Maple kernel handle */
    MCallBackVectorDesc cb = {  textCallBack, 0, 0, 0, 0,  0, 0,  0 };
   ALGEB r, l;  /* Maple data-structures */

   /* initialize Maple */
   if( (kv=StartMaple (argc,argv,&cb,NULL,NULL,err)) == NULL ) {
      printf("Fatal error, %s\n",err);
      return( 1 );
   }

   char s[] = "int(x^2+1,x);";
   printf("Evaluate an integral: %s\n\t", s);
   r = EvalMapleStatement (kv, s);

   StopMaple(kv);

   return( 0 );
}

```
