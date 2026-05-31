// ============================================================
// Source.cpp - Diem vao chuong trinh: hien thi menu chinh
// ============================================================

#include "CauTruc.h"

int main(void) {
    int DangChay = 1;
    const char* TenTepNhiPhan = "HocVien.dat";

    const char* MenuChinh[] = {
        "1. Them moi ho so (M1)",
        "2. In danh sach (M2)",
        "3. Sap xep (M3)",
        "4. Tim kiem (M4)",
        "5. Thong ke (M5)",
        "6. Thoat (M6)"
    };

    while (DangChay) {
        InTieuDe("MENU CHINH");
        int Chon = ChonMenu(6, MenuChinh, 6, NULL);
        switch (Chon) {
        case 0: XuLyThemHoSo(TenTepNhiPhan);       break;
        case 1: XuLyMenuInDanhSach(TenTepNhiPhan); break;
        case 2: XuLyMenuSapXep(TenTepNhiPhan);     break;
        case 3: XuLyMenuTimKiem(TenTepNhiPhan);    break;
        case 4: XuLyMenuThongKe(TenTepNhiPhan);    break;
        case 5: case -1: DangChay = 0;              break;
        }
    }

    XoaManHinh();
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
