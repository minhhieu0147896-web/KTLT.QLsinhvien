// ============================================================
// ThongKe.cpp - Thong ke so luong va xep loai hoc vien theo lop
// ============================================================

#include "CauTruc.h"

#define SO_LOAI_HOC_TAP 5

typedef struct {
    char MaLop[SoKyTuToiDaMaLop];
    int TongSo;
    int SoLuongTheoLoai[SO_LOAI_HOC_TAP];
} ThongKeLop;

void SaoChepMaLop(char MaLopDich[], const char* MaLopNguon) {
    int i = 0;

    while (MaLopNguon[i] != '\0' && i < SoKyTuToiDaMaLop - 1) {
        MaLopDich[i] = MaLopNguon[i];
        i++;
    }
    MaLopDich[i] = '\0';
}

int TimViTriLop(ThongKeLop BangThongKe[], int SoLop, const char* MaLop) {
    for (int i = 0; i < SoLop; i++)
        if (strcmp(BangThongKe[i].MaLop, MaLop) == 0)
            return i;
    return -1;
}

int ThemLopNeuChuaCo(ThongKeLop BangThongKe[], int* SoLop, const char* MaLop) {
    int ViTri = TimViTriLop(BangThongKe, *SoLop, MaLop);
    if (ViTri >= 0) return ViTri;

    ViTri = *SoLop;
    SaoChepMaLop(BangThongKe[ViTri].MaLop, MaLop);
    BangThongKe[ViTri].TongSo = 0;
    for (int i = 0; i < SO_LOAI_HOC_TAP; i++)
        BangThongKe[ViTri].SoLuongTheoLoai[i] = 0;

    (*SoLop)++;
    return ViTri;
}

int LayLoaiHocTap(float Diem) {
    if (Diem >= 3.6f) return 0; // Xuat sac
    if (Diem >= 3.2f) return 1; // Gioi
    if (Diem >= 2.5f) return 2; // Kha
    if (Diem >= 2.0f) return 3; // Trung binh
    return 4;                   // Yeu
}

void LapBangThongKeTheoLop(HocVien DanhSach[], int SoLuong,
                                  ThongKeLop BangThongKe[], int* SoLop) {
    *SoLop = 0;

    for (int i = 0; i < SoLuong; i++) {
        int ViTriLop = ThemLopNeuChuaCo(BangThongKe, SoLop, DanhSach[i].MaLop);
        int LoaiHocTap = LayLoaiHocTap(DanhSach[i].DiemTrungBinhTichLuy);

        BangThongKe[ViTriLop].TongSo++;
        BangThongKe[ViTriLop].SoLuongTheoLoai[LoaiHocTap]++;
    }
}

void ThongKeSoLuongTheoLop(HocVien DanhSach[], int SoLuong) {
    ThongKeLop BangThongKe[SoLuongHocVienToiDa];
    int SoLop = 0;

    if (SoLuong == 0) {
        InThongBaoGhiChu("Danh sach hoc vien dang rong.");
        return;
    }

    LapBangThongKeTheoLop(DanhSach, SoLuong, BangThongKe, &SoLop);

    InDongPhanCach(36);
    printf("%-5s %-15s %s\n", "STT", "Ma lop", "So hoc vien");
    InDongPhanCach(36);
    for (int i = 0; i < SoLop; i++)
        printf("%-5d %-15s %d\n", i + 1, BangThongKe[i].MaLop, BangThongKe[i].TongSo);
    InDongPhanCach(36);
}

void ThongKeXepLoaiTheoLop(HocVien DanhSach[], int SoLuong) {
    ThongKeLop BangThongKe[SoLuongHocVienToiDa];
    int SoLop = 0;
    const char* TenLoai[] = { "Xuat sac", "Gioi", "Kha", "Trung binh", "Yeu" };

    if (SoLuong == 0) {
        InThongBaoGhiChu("Danh sach hoc vien dang rong.");
        return;
    }

    LapBangThongKeTheoLop(DanhSach, SoLuong, BangThongKe, &SoLop);

    for (int i = 0; i < SoLop; i++) {
        InNhanMuc("THONG KE THEO LOP");
        printf("Lop %s - tong so: %d hoc vien\n", BangThongKe[i].MaLop, BangThongKe[i].TongSo);
        InDongPhanCach(38);
        printf("%-12s %-10s %s\n", "Xep loai", "So luong", "Ty le");
        InDongPhanCach(38);

        for (int j = 0; j < SO_LOAI_HOC_TAP; j++) {
            float TyLe = BangThongKe[i].SoLuongTheoLoai[j] * 100.0f / BangThongKe[i].TongSo;
            printf("%-12s %-10d %.2f%%\n", TenLoai[j], BangThongKe[i].SoLuongTheoLoai[j], TyLe);
        }
        InDongPhanCach(38);
        printf("\n");
    }

    
}
void XuLiMenuThongKeTopSV(HocVien DSHV[], int SLHV)
{
    while (1)
    {
        HocVien Tam[SoLuongHocVienToiDa];
        HocVien KQ[SoLuongHocVienToiDa];
        int SLKQ = 0;
        bool checkKQ = false;
        for (int i = 0; i < SLHV; i++)
        {
            Tam[i] = DSHV[i];
        }
        float top;
        InTieuDe("M5. THONG KE - SINH VIEN THEO MUC DIEM");
        InNhanMuc("NHAP DIEU KIEN");
        printf("Nhap muc diem can thong ke: ");

        if (NhapDiemHopLe(&top) == 0) return;

        SapXepChon(Tam, SLHV, KHOA_DIEM_TBTL);

        printf("\n");
        InNhanMuc("KET QUA");
        for (int i = SLHV - 1; i >= 0; i--)
        {
            if (Tam[i].DiemTrungBinhTichLuy >= top)
            {
                KQ[SLKQ] = Tam[i];
                SLKQ++;
                checkKQ = true;
            }
        }

        if (checkKQ == false)
        {
            InThongBaoGhiChu("Khong co hoc vien nao dat muc diem da nhap.");
            ChoPhimEscQuayLai();
            continue;
        }
        InBangHocVien(KQ, SLKQ);
        return;
    }
}
