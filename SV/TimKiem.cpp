// ============================================================
// TimKiem.cpp - Cac thuat toan tim kiem: Tuan tu, Nhi phan
// ============================================================

#include "CauTruc.h"

// So sanh 1 hoc vien voi gia tri tim kiem theo khoa. Tra ve -1, 0, 1 (be hon, bang, lon hon)
int SoSanhTimKiem(HocVien HV, const char* GiaTri, int Khoa) {
    switch (Khoa) {
    case '1': return strcmp(HV.MaLop, GiaTri);
    case '2': return strcmp(HV.MaHocVien, GiaTri);
    case '3': return strcmp(HV.HoTen, GiaTri);
    case '4': { // Ngay sinh (dinh dang dd/mm/yyyy)
        int Ngay, Thang, Nam;
        if (sscanf_s(GiaTri, "%d/%d/%d", &Ngay, &Thang, &Nam) != 3) return -1;
        if (HV.NgaySinh.Nam != Nam) return (HV.NgaySinh.Nam < Nam) ? -1 : 1;
        if (HV.NgaySinh.Thang != Thang) return (HV.NgaySinh.Thang < Thang) ? -1 : 1;
        if (HV.NgaySinh.Ngay != Ngay) return (HV.NgaySinh.Ngay < Ngay) ? -1 : 1;
        return 0;
    }
    case '5': { // Diem TBTL
        float Diem;
        if (sscanf_s(GiaTri, "%f", &Diem) != 1) return -1;
        if (HV.DiemTrungBinhTichLuy < Diem) return -1;
        if (HV.DiemTrungBinhTichLuy > Diem) return 1;
        return 0;
    }
    }
    return 0;
}

// Tim kiem tuan tu: duyet toan bo danh sach, liet ke tat ca hoc vien khop
void TimKiemTuanTu(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;
    for (int i = 0; i < SoLuong; i++)
        if (SoSanhTimKiem(DanhSach[i], GiaTri, Khoa) == 0)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

// Tim kiem nhi phan: sap xep ban sao → binary search → lan trai/phai lay tat ca khop
void TimKiemNhiPhan(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;
    if (SoLuong == 0) return;

    // Tao ban sao va sap xep theo khoa tim kiem
    HocVien* BanSao = (HocVien*)malloc(SoLuong * sizeof(HocVien));
    if (BanSao == NULL) return;
    for (int i = 0; i < SoLuong; i++) BanSao[i] = DanhSach[i];
    SapXepChon(BanSao, SoLuong, Khoa);

    // Binary search
    int Trai = 0, Phai = SoLuong - 1, ViTriThay = -1;
    while (Trai <= Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        int Kq = SoSanhTimKiem(BanSao[Giua], GiaTri, Khoa);
        if (Kq == 0) { ViTriThay = Giua; break; }
        else if (Kq < 0) Trai = Giua + 1;
        else Phai = Giua - 1;
    }

    // Lan sang trai va phai de lay tat ca ket qua trung
    if (ViTriThay >= 0) {
        int i = ViTriThay;
        while (i >= 0 && SoSanhTimKiem(BanSao[i], GiaTri, Khoa) == 0) i--;
        i++;
        while (i < SoLuong && SoSanhTimKiem(BanSao[i], GiaTri, Khoa) == 0)
            KetQua[(*SoKetQua)++] = BanSao[i++];
    }
    free(BanSao);
}
