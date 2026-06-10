// ============================================================
// TimKiem.cpp - 2 thuat toan tim kiem: Tuan tu, Nhi phan
// ============================================================

#include "CauTruc.h"

int ChuyenChuoiThanhDiem(const char* Chuoi, float* Diem) {
    int i = 0;
    int CoChuSo = 0;
    int CoDauCham = 0;

    if (Chuoi[0] == '\0') return 0;

    while (Chuoi[i] != '\0') {
        if (isdigit((unsigned char)Chuoi[i])) {
            CoChuSo = 1;
        } else if (Chuoi[i] == '.' && !CoDauCham) {
            CoDauCham = 1;
        } else {
            return 0;
        }
        i++;
    }

    if (!CoChuSo) return 0;

    *Diem = (float)atof(Chuoi);
    return 1;
}

int SoSanhNgaySinh(Date A, Date B) {
    if (A.Nam < B.Nam) return -1;
    if (A.Nam > B.Nam) return 1;

    if (A.Thang < B.Thang) return -1;
    if (A.Thang > B.Thang) return 1;

    if (A.Ngay < B.Ngay) return -1;
    if (A.Ngay > B.Ngay) return 1;

    return 0;
}

int SoSanhDiem(float A, float B) {
    if (A < B) return -1;
    if (A > B) return 1;
    return 0;
}

// So sanh 1 hoc vien voi gia tri can tim.
// - Ma lop, ma hoc vien, ho ten: khop neu co chua chuoi can tim, khong phan biet hoa/thuong.
// - Diem: so sanh dung gia tri.
// Tra ve 0 neu khop.
int SoSanhTimKiem(HocVien HV, const char* GiaTri, int Khoa) {
    const char* ChuoiTrongDanhSach = NULL;

    switch (Khoa) {
    case KHOA_MA_LOP:
    case KHOA_MA_HOC_VIEN:
    case KHOA_HO_TEN:
        if (Khoa == KHOA_MA_LOP)
            ChuoiTrongDanhSach = HV.MaLop;
        else if (Khoa == KHOA_MA_HOC_VIEN)
            ChuoiTrongDanhSach = HV.MaHocVien;
        else
            ChuoiTrongDanhSach = HV.HoTen;

        if (GiaTri[0] == '\0') return 1;

        for (int i = 0; ChuoiTrongDanhSach[i] != '\0'; i++) {
            int j = 0;

            while (GiaTri[j] != '\0' &&
                   ChuoiTrongDanhSach[i + j] != '\0' &&
                   tolower((unsigned char)ChuoiTrongDanhSach[i + j]) == tolower((unsigned char)GiaTri[j])) {
                j++;
            }

            if (GiaTri[j] == '\0') return 0;
        }

        return 1;
    case KHOA_DIEM_TBTL: {
        float d;
        if (!ChuyenChuoiThanhDiem(GiaTri, &d)) return -1;
        return SoSanhDiem(HV.DiemTrungBinhTichLuy, d);
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

    // Tim kiem nhi phan chi phu hop voi gia tri can tim dung hoan toan.
    // Voi chuoi khop mot phan, can duyet tuan tu de khong bo sot ket qua.
    if (Khoa == KHOA_MA_LOP || Khoa == KHOA_MA_HOC_VIEN || Khoa == KHOA_HO_TEN) {
        TimKiemTuanTu(DanhSach, SoLuong, GiaTri, Khoa, KetQua, SoKetQua);
        return;
    }

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

void TimKiemTuanTuTheoNgaySinh(HocVien DanhSach[], int SoLuong, Date NgaySinh,
                               HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;

    for (int i = 0; i < SoLuong; i++)
        if (SoSanhNgaySinh(DanhSach[i].NgaySinh, NgaySinh) == 0)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

void TimKiemNhiPhanTheoNgaySinh(HocVien DanhSach[], int SoLuong, Date NgaySinh,
                                HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;
    if (SoLuong == 0) return;

    HocVien* Ban = (HocVien*)malloc(SoLuong * sizeof(HocVien));
    if (!Ban) return;

    for (int i = 0; i < SoLuong; i++)
        Ban[i] = DanhSach[i];

    SapXepChon(Ban, SoLuong, KHOA_NGAY_SINH);

    int Trai = 0;
    int Phai = SoLuong - 1;
    int ViTriTimThay = -1;

    while (Trai <= Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        int KetQuaSoSanh = SoSanhNgaySinh(Ban[Giua].NgaySinh, NgaySinh);

        if (KetQuaSoSanh == 0) {
            ViTriTimThay = Giua;
            break;
        } else if (KetQuaSoSanh < 0) {
            Trai = Giua + 1;
        } else {
            Phai = Giua - 1;
        }
    }

    if (ViTriTimThay >= 0) {
        int i = ViTriTimThay;
        while (i >= 0 && SoSanhNgaySinh(Ban[i].NgaySinh, NgaySinh) == 0)
            i--;
        i++;

        while (i < SoLuong && SoSanhNgaySinh(Ban[i].NgaySinh, NgaySinh) == 0) {
            KetQua[(*SoKetQua)++] = Ban[i];
            i++;
        }
    }

    free(Ban);
}

void TimKiemTheoNgayTrongThang(HocVien DanhSach[], int SoLuong, int Ngay,
                               HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;

    for (int i = 0; i < SoLuong; i++)
        if (DanhSach[i].NgaySinh.Ngay == Ngay)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

void TimKiemTheoThangSinh(HocVien DanhSach[], int SoLuong, int Thang,
                          HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;

    for (int i = 0; i < SoLuong; i++)
        if (DanhSach[i].NgaySinh.Thang == Thang)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

void TimKiemTheoNamSinh(HocVien DanhSach[], int SoLuong, int Nam,
                        HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;

    for (int i = 0; i < SoLuong; i++)
        if (DanhSach[i].NgaySinh.Nam == Nam)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}

void TimKiemTheoNgayVaThang(HocVien DanhSach[], int SoLuong, int Ngay, int Thang,
                            HocVien KetQua[], int* SoKetQua) {
    *SoKetQua = 0;

    for (int i = 0; i < SoLuong; i++)
        if (DanhSach[i].NgaySinh.Ngay == Ngay && DanhSach[i].NgaySinh.Thang == Thang)
            KetQua[(*SoKetQua)++] = DanhSach[i];
}
