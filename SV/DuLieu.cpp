// ============================================================
// DuLieu.cpp - Doc/ghi danh sach hoc vien tu file nhi phan
// ============================================================

#include "CauTruc.h"

// Doc danh sach hoc vien tu file nhi phan, tra ve so luong doc duoc
int DocDanhSachTuFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongToiDa) {
    FILE* Tep;
    int SoLuongDocDuoc;

    if (fopen_s(&Tep, TenTep, "rb") != 0) {
        fopen_s(&Tep, TenTep, "wb");
        if (Tep != NULL) fclose(Tep);
        return 0;
    }

    SoLuongDocDuoc = (int)fread(DanhSachHocVien, sizeof(HocVien), SoLuongToiDa, Tep);
    fclose(Tep);
    return SoLuongDocDuoc;
}

// Ghi danh sach hoc vien vao file nhi phan, tra ve 1 neu thanh cong
int GhiDanhSachVaoFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongHocVien) {
    FILE* Tep;
    int SoLuongGhiDuoc;

    if (fopen_s(&Tep, TenTep, "wb") != 0) return 0;

    SoLuongGhiDuoc = (int)fwrite(DanhSachHocVien, sizeof(HocVien), SoLuongHocVien, Tep);
    fclose(Tep);
    return SoLuongGhiDuoc == SoLuongHocVien;
}
