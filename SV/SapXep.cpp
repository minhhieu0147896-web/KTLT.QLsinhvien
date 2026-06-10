// ============================================================
// SapXep.cpp - 3 thuat toan sap xep: Chon, Chen, Noi bot
// ============================================================

#include "CauTruc.h"

// So sanh 2 hoc vien theo khoa. Tra ve 1 neu A < B (dung de sap tang dan)
int SoSanhHocVien(HocVien A, HocVien B, int Khoa) {
    switch (Khoa) {
    case KHOA_MA_LOP:
        return strcmp(A.MaLop, B.MaLop) < 0;
    case KHOA_MA_HOC_VIEN:
        return strcmp(A.MaHocVien, B.MaHocVien) < 0;
    case KHOA_HO_TEN:
        return strcmp(A.HoTen, B.HoTen) < 0;
    case KHOA_NGAY_SINH:
        if (A.NgaySinh.Nam != B.NgaySinh.Nam) return A.NgaySinh.Nam < B.NgaySinh.Nam;
        if (A.NgaySinh.Thang != B.NgaySinh.Thang) return A.NgaySinh.Thang < B.NgaySinh.Thang;
        return A.NgaySinh.Ngay < B.NgaySinh.Ngay;
    case KHOA_DIEM_TBTL:
        return A.DiemTrungBinhTichLuy < B.DiemTrungBinhTichLuy;
    }
    return 0;
}

// Sap xep chon: tim phan tu nho nhat trong doan chua sap roi dua ve dau
void SapXepChon(HocVien DanhSach[], int SoLuong, int Khoa) {
    for (int i = 0; i < SoLuong - 1; i++) {
        int Min = i;
        for (int j = i + 1; j < SoLuong; j++)
            if (SoSanhHocVien(DanhSach[j], DanhSach[Min], Khoa)) Min = j;
        if (Min != i) { HocVien T = DanhSach[i]; DanhSach[i] = DanhSach[Min]; DanhSach[Min] = T; }
    }
}

// Sap xep chen: rut tung phan tu roi chen vao dung vi tri trong doan da sap
void SapXepChen(HocVien DanhSach[], int SoLuong, int Khoa) {
    for (int i = 1; i < SoLuong; i++) {
        HocVien Tam = DanhSach[i];
        int j = i - 1;
        while (j >= 0 && SoSanhHocVien(Tam, DanhSach[j], Khoa)) { DanhSach[j + 1] = DanhSach[j]; j--; }
        DanhSach[j + 1] = Tam;
    }
}

// Sap xep noi bot: duyet tu dau den cuoi, doi cho cac cap ke nhau sai thu tu
void SapXepNoiBot(HocVien DanhSach[], int SoLuong, int Khoa) {
    for (int i = 0; i < SoLuong - 1; i++)
        for (int j = 0; j < SoLuong - i - 1; j++)
            if (SoSanhHocVien(DanhSach[j + 1], DanhSach[j], Khoa)) {
                HocVien T = DanhSach[j];
                DanhSach[j] = DanhSach[j + 1];
                DanhSach[j + 1] = T;
            }
}
