// ============================================================
// TimKiem.cpp - 2 thuat toan tim kiem: Tuan tu, Nhi phan
// ============================================================

#include "CauTruc.h"

// So sanh 1 hoc vien voi gia tri can tim. Tra ve 0 neu khop, <0 neu be hon, >0 neu lon hon
static int SoSanhTimKiem(HocVien HV, const char* GiaTri, int Khoa) {
    switch (Khoa) {
    case KHOA_MA_LOP:
        return strcmp(HV.MaLop, GiaTri);
    case KHOA_MA_HOC_VIEN:
        return strcmp(HV.MaHocVien, GiaTri);
    case KHOA_HO_TEN:
        return strcmp(HV.HoTen, GiaTri);
    case KHOA_NGAY_SINH: {
        int d, m, y;
        if (sscanf_s(GiaTri, "%d/%d/%d", &d, &m, &y) != 3) return -1;
        if (HV.NgaySinh.Nam != y) return (HV.NgaySinh.Nam < y) ? -1 : 1;
        if (HV.NgaySinh.Thang != m) return (HV.NgaySinh.Thang < m) ? -1 : 1;
        return (HV.NgaySinh.Ngay != d) ? ((HV.NgaySinh.Ngay < d) ? -1 : 1) : 0;
    }
    case KHOA_DIEM_TBTL: {
        float d;
        if (sscanf_s(GiaTri, "%f", &d) != 1) return -1;
        if (HV.DiemTrungBinhTichLuy < d) return -1;
        return (HV.DiemTrungBinhTichLuy > d) ? 1 : 0;
    }
    }
    return 0;
}

// Tim kiem tuan tu: duyet toan bo, liet ke tat ca hoc vien khop
void TimKiemTuanTu(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa,
                   HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;
    for (int i = 0; i < SoLuong; i++)
        if (SoSanhTimKiem(DanhSach[i], GiaTri, Khoa) == 0)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

// Tim kiem nhi phan: sap xep ban sao -> binary search -> lan 2 ben lay het
void TimKiemNhiPhan(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa,
                    HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;
    if (SoLuong == 0) return;

    HocVien* Ban = (HocVien*)malloc(SoLuong * sizeof(HocVien));
    if (!Ban) return;
    for (int i = 0; i < SoLuong; i++) Ban[i] = DanhSach[i];
    SapXepChon(Ban, SoLuong, Khoa);

    int L = 0, R = SoLuong - 1, Tim = -1;
    while (L <= R) {
        int M = L + (R - L) / 2;
        int Kq = SoSanhTimKiem(Ban[M], GiaTri, Khoa);
        if (Kq == 0) { Tim = M; break; }
        else if (Kq < 0) L = M + 1;
        else R = M - 1;
    }

    if (Tim >= 0) {
        int i = Tim;
        while (i >= 0 && SoSanhTimKiem(Ban[i], GiaTri, Khoa) == 0) i--;
        i++;
        while (i < SoLuong && SoSanhTimKiem(Ban[i], GiaTri, Khoa) == 0)
            KetQua[(*SoKetQua)++] = Ban[i++];
    }
    free(Ban);
}
