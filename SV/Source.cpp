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
        "0. Thoat"
    };

    while (DangChay) {
        InTieuDe("MENU CHINH");
        int Chon = ChonMenu(6, MenuChinh, 6, NULL);
        switch (Chon) {
        case 1: XuLyThemHoSo(TenTepNhiPhan);       break;
        case 2: XuLyMenuInDanhSach(TenTepNhiPhan); break;
        case 3: XuLyMenuSapXep(TenTepNhiPhan);     break;
        case 4: XuLyMenuTimKiem(TenTepNhiPhan);    break;
        case 5: XuLyMenuThongKe(TenTepNhiPhan);    break;
        case 0: case 6: case -1: DangChay = 0;      break;
        }
    }

    XoaManHinh();
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
