#include <iostream>

#define     ngat            break
#define     truonghop       case
#define     bat             catch
#define     cloi            cerr
#define     kytu            char
#define     cvao            cin
#define     lop             class
#define     hang            const
#define     tieptuc         continue
#define     cra             cout
#define     macdinh         default
#define     xoa             delete
#define     thuchien        do
#define     sothuckep       double
#define     khongthi        else
#define     hetdong         endl
#define     lietke          enum
#define     tuongminh       explicit
#define     sai             false
#define     sothucdon       float
#define     doivoi          for
#define     diden           goto
#define     neu             if
#define     noituyen        inline
#define     songuyen        int
#define     songuyendai     long
#define     khonggianten    namespace
#define     moi             new
#define     toantu          operator
#define     riengtu         private
#define     baove           protected
#define     congcong        public
#define     chinh           main
#define     trave           return
#define     songuyenngan    short
#define     codau           signed
#define     kichcocua       sizeof
#define     tinh            static
#define     chuan           std
#define     cautruc         struct
#define     khuonmau        template
#define     cainay          this
#define     quang           throw
#define     dung            true
#define     thu             try
#define     dinhnghiakieu   typedef
#define     tenkieu         typename
#define     khongdau        unsigned
#define     sudung          using
#define     ao              virtual
#define     hukhong         void
#define     kyturong        wchar_t
#define     trongkhi        while

sudung khonggianten chuan;

songuyen khongdau giaithua(songuyen n) {
    neu (n < 0) {
        trave 0;
    } khongthi neu (n == 0) {
        trave 1;
    } khongthi {
        trave n * giaithua(n - 1);
    }
}

songuyen chinh(songuyen sothamso, kytu** thamso) {
    songuyen n;
    cra << "Nhap so nguyen: ";
    cvao >> n;
    cra << n << "! = " << giaithua(n) << hetdong;
    trave 0;
}
