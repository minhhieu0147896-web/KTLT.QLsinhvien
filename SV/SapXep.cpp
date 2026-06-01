// ============================================================
// SapXep.cpp - 4 thuat toan sap xep: Chon, Chen, Quicksort, Mergesort
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

// Quicksort: chon chot -> phan hoach -> de quy 2 ben
void SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai >= Phai) return;
    HocVien Chot = DanhSach[Phai];
    int i = Trai - 1;
    for (int j = Trai; j < Phai; j++)
        if (SoSanhHocVien(DanhSach[j], Chot, Khoa)) { i++; HocVien T = DanhSach[i]; DanhSach[i] = DanhSach[j]; DanhSach[j] = T; }
    HocVien T = DanhSach[i + 1]; DanhSach[i + 1] = DanhSach[Phai]; DanhSach[Phai] = T;
    int ViTriChot = i + 1;
    SapXepNhanh(DanhSach, Trai, ViTriChot - 1, Khoa);
    SapXepNhanh(DanhSach, ViTriChot + 1, Phai, Khoa);
}

// Mergesort: chia doi -> de quy -> tron
static void Tron(HocVien DanhSach[], int Trai, int Giua, int Phai, int Khoa) {
    int n1 = Giua - Trai + 1, n2 = Phai - Giua;
    HocVien* L = (HocVien*)malloc(n1 * sizeof(HocVien));
    HocVien* R = (HocVien*)malloc(n2 * sizeof(HocVien));
    if (!L || !R) { if (L) free(L); if (R) free(R); return; }
    for (int i = 0; i < n1; i++) L[i] = DanhSach[Trai + i];
    for (int j = 0; j < n2; j++) R[j] = DanhSach[Giua + 1 + j];
    int i = 0, j = 0, k = Trai;
    while (i < n1 && j < n2) DanhSach[k++] = SoSanhHocVien(L[i], R[j], Khoa) ? L[i++] : R[j++];
    while (i < n1) DanhSach[k++] = L[i++];
    while (j < n2) DanhSach[k++] = R[j++];
    free(L); free(R);
}

void SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        SapXepTron(DanhSach, Trai, Giua, Khoa);
        SapXepTron(DanhSach, Giua + 1, Phai, Khoa);
        Tron(DanhSach, Trai, Giua, Phai, Khoa);
    }
}
