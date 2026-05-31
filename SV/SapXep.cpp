// ============================================================
// SapXep.cpp - Cac thuat toan sap xep: Selection, Insertion, Quicksort, Mergesort
// ============================================================

#include "CauTruc.h"

// So sanh 2 hoc vien theo ma hoc vien (tang dan)
int SoSanhTheoMaHocVien(HocVien A, HocVien B) {
    return strcmp(A.MaHocVien, B.MaHocVien) < 0;
}

// So sanh 2 hoc vien theo ho ten (tang dan theo bang chu cai)
int SoSanhTheoHoTen(HocVien A, HocVien B) {
    return strcmp(A.HoTen, B.HoTen) < 0;
}

// So sanh 2 hoc vien theo ngay sinh (tang dan: cu hon → tre hon)
int SoSanhTheoNgaySinh(HocVien A, HocVien B) {
    if (A.NgaySinh.Nam != B.NgaySinh.Nam) return A.NgaySinh.Nam < B.NgaySinh.Nam;
    if (A.NgaySinh.Thang != B.NgaySinh.Thang) return A.NgaySinh.Thang < B.NgaySinh.Thang;
    return A.NgaySinh.Ngay < B.NgaySinh.Ngay;
}

// So sanh 2 hoc vien theo diem trung binh tich luy (tang dan)
int SoSanhTheoDiemTrungBinhTichLuy(HocVien A, HocVien B) {
    return A.DiemTrungBinhTichLuy < B.DiemTrungBinhTichLuy;
}

// So sanh 2 hoc vien theo khoa duoc chon (1=ma, 2=ten, 3=ngay sinh, 4=diem)
int SoSanhHocVien(HocVien A, HocVien B, int Khoa) {
    switch (Khoa) {
    case '1': return SoSanhTheoMaHocVien(A, B);
    case '2': return SoSanhTheoHoTen(A, B);
    case '3': return SoSanhTheoNgaySinh(A, B);
    case '4': return SoSanhTheoDiemTrungBinhTichLuy(A, B);
    }
    return 0;
}

// Hoan doi vi tri 2 hoc vien trong mang
void HoanDoiHocVien(HocVien* A, HocVien* B) {
    HocVien Tam = *A;
    *A = *B;
    *B = Tam;
}

// Thuat toan sap xep chon: moi vong tim min trong doan chua sap xep roi dua ve dau
void SapXepChon(HocVien DanhSach[], int SoLuong, int Khoa) {
    for (int i = 0; i < SoLuong - 1; i++) {
        int ViTriNhoNhat = i;
        for (int j = i + 1; j < SoLuong; j++)
            if (SoSanhHocVien(DanhSach[j], DanhSach[ViTriNhoNhat], Khoa))
                ViTriNhoNhat = j;
        if (ViTriNhoNhat != i)
            HoanDoiHocVien(&DanhSach[i], &DanhSach[ViTriNhoNhat]);
    }
}

// Thuat toan sap xep chen: rut tung phan tu roi chen vao dung vi tri trong phan da sap
void SapXepChen(HocVien DanhSach[], int SoLuong, int Khoa) {
    for (int i = 1; i < SoLuong; i++) {
        HocVien KhoaTam = DanhSach[i];
        int j = i - 1;
        while (j >= 0 && SoSanhHocVien(KhoaTam, DanhSach[j], Khoa)) {
            DanhSach[j + 1] = DanhSach[j];
            j--;
        }
        DanhSach[j + 1] = KhoaTam;
    }
}

// Phan hoach Lomuto cho Quicksort: dua phan tu nho hon chot sang trai, lon hon sang phai
int PhanHoach(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    HocVien Chot = DanhSach[Phai];
    int i = Trai - 1;
    for (int j = Trai; j < Phai; j++) {
        if (SoSanhHocVien(DanhSach[j], Chot, Khoa)) {
            i++;
            HoanDoiHocVien(&DanhSach[i], &DanhSach[j]);
        }
    }
    HoanDoiHocVien(&DanhSach[i + 1], &DanhSach[Phai]);
    return i + 1;
}

// Thuat toan Quicksort: chon chot → phan hoach → de quy 2 nua trai & phai
void SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int ViTriChot = PhanHoach(DanhSach, Trai, Phai, Khoa);
        SapXepNhanh(DanhSach, Trai, ViTriChot - 1, Khoa);
        SapXepNhanh(DanhSach, ViTriChot + 1, Phai, Khoa);
    }
}

// Tron 2 mang con da sap xep thanh 1 mang co thu tu
void Tron(HocVien DanhSach[], int Trai, int Giua, int Phai, int Khoa) {
    int KichThuocTrai = Giua - Trai + 1;
    int KichThuocPhai = Phai - Giua;

    HocVien* MangTrai = (HocVien*)malloc(KichThuocTrai * sizeof(HocVien));
    HocVien* MangPhai = (HocVien*)malloc(KichThuocPhai * sizeof(HocVien));
    if (MangTrai == NULL || MangPhai == NULL) {
        if (MangTrai) free(MangTrai);
        if (MangPhai) free(MangPhai);
        return;
    }

    for (int i = 0; i < KichThuocTrai; i++) MangTrai[i] = DanhSach[Trai + i];
    for (int j = 0; j < KichThuocPhai; j++) MangPhai[j] = DanhSach[Giua + 1 + j];

    int i = 0, j = 0, k = Trai;
    while (i < KichThuocTrai && j < KichThuocPhai) {
        if (SoSanhHocVien(MangTrai[i], MangPhai[j], Khoa))
            DanhSach[k++] = MangTrai[i++];
        else
            DanhSach[k++] = MangPhai[j++];
    }
    while (i < KichThuocTrai) DanhSach[k++] = MangTrai[i++];
    while (j < KichThuocPhai) DanhSach[k++] = MangPhai[j++];

    free(MangTrai);
    free(MangPhai);
}

// Thuat toan Mergesort: chia doi mang → de quy → tron 2 nua da sap
void SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        SapXepTron(DanhSach, Trai, Giua, Khoa);
        SapXepTron(DanhSach, Giua + 1, Phai, Khoa);
        Tron(DanhSach, Trai, Giua, Phai, Khoa);
    }
}

// Tra ve ten hien thi cua thuat toan sap xep theo ma chon
const char* LayTenThuatToan(int ThuatToan) {
    switch (ThuatToan) {
    case '1': return "Sap xep chon (Selection Sort)";
    case '2': return "Sap xep chen (Insertion Sort)";
    case '3': return "Quicksort";
    case '4': return "Mergesort";
    }
    return "";
}

// Tra ve ten hien thi cua khoa sap xep theo ma chon
const char* LayTenKhoa(int Khoa) {
    switch (Khoa) {
    case '1': return "Ma hoc vien";
    case '2': return "Ho va ten";
    case '3': return "Ngay sinh";
    case '4': return "Diem trung binh tich luy";
    }
    return "";
}
