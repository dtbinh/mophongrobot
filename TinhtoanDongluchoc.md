# Giới thiệu #

Bài toán động học thuận của robot được giải khá đơn giản sử dụng các phép tính với các ma trận thuần nhất. Bài toán động học và động lực học ngược nói chung phức tạp hơn nhiều. Ngoài ra, để mô phỏng robot còn có một bài toán lớn là thiết kế quỹ đạo của khâu tác động cuối. Tuy nhiên, trong phần này tôi chỉ xin giới thiệu hai công cụ miễn phí giúp giải bài toán động học/động lực học robot: Robotics Toolbox for Matlab của P.I. Corke và SpaceLib của Giovanni Legnan, Đại học Brescia, Italia.

## Robotics Toolbox for Matlab ##
Trang thông tin chính của toolbox ở tại địa chỉ sau: http://petercorke.com/Robotics_Toolbox.html. Ngoài ra tôi cũng đã download và gửi kèm [ở đây](http://mophongrobot.googlecode.com/svn/trunk/Kythuat/RoboticsToolbox.v9.zip)
Trước khi tính toán, cần định nghĩa cấu hình robot bằng các tham số DH. Ví dụ, đoạn chương trình sau định nghĩa một robot có các tham số DH như dưới đây:
| **Link** | **ai** | **αi** | **di** | **θi** |
|:---------|:-------|:-------|:-------|:-------|
|1         |1       |0       |0       |θ1      |
|2         |1       |0       |0       |θ2      |

```
>> L1=link([0 1 0 0 0])
L1 =
0.000000 1.000000 0.000000 0.000000 R
>> L2=link([0 1 0 0 0])
L2 =
0.000000 1.000000 0.000000 0.000000 R
>> r=robot({L1 L2})
r =
noname (2 axis, RR)
grav = [0.00 0.00 9.81] standard D&H parameters
alpha A theta D R/P
0.000000 1.000000 0.000000 0.000000 R
0.000000 1.000000 0.000000 0.000000 R

```

Lệnh `fkine()` được dùng để giải bài toán động học thuận, còn lệnh `ikine()` được dùng để giải bài toán động học ngược.

Chi tiết mời các em xem trong tài liệu kèm theo phần mềm.

## SpaceLib ##
Trang thông tin chính thức của gói chương trình có tại http://spacelib.ing.unibs.it/. Tôi cũng đã download và gửi kèm [ở đây](http://mophongrobot.googlecode.com/svn/trunk/Kythuat/SpaceLib3.1.zip).
Gói chương trình này cung cấp các công cụ giải các bài toán động học và động lực học thuận/ngược cho robot, và có cả 3 phiên bản: dành cho Maple, Matlab và C++. Vì vậy có thể dễ dàng tích hợp gói phần mềm này trong chương trình mô phỏng bằng C++.

Đoạn chương trình Maple sau sử dụng thư viện SpaceLib để tính toán phản lực tác động lên các khớp khi mà khâu tác động cuối chịu lực và mô men:
```
# SOLUTION OF THE INVERSE DINAMIC PROBLEM
    EXT:=actoM(fx,fy,fz,cx,cy,cz):
    ACTO[k(nlink+1)]:=trasf_mamt(EXT,T[k(nlink+1)]):
    for kk from nlink by -1 to 1 do
        JO[k(kk)]:=trasf_mamt(J[k(kk)],T[k(kk+1)]):
        Ht:=Hg-HA[k(kk+1)]:
        FI[k(kk)]:=skew(Ht.JO[k(kk)]):
        ACTO[k(kk)]:=FI[k(kk)]+ACTO[k(kk+1)]:
    end do:
```

Chi tiết xem trong tài liệu kèm theo các phần mềm.