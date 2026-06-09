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

static void SaoChepMaLop(char MaLopDich[], const char* MaLopNguon) {
    int i = 0;

    while (MaLopNguon[i] != '\0' && i < SoKyTuToiDaMaLop - 1) {
        MaLopDich[i] = MaLopNguon[i];
        i++;
    }
    MaLopDich[i] = '\0';
}

static int TimViTriLop(ThongKeLop BangThongKe[], int SoLop, const char* MaLop) {
    for (int i = 0; i < SoLop; i++)
        if (strcmp(BangThongKe[i].MaLop, MaLop) == 0)
            return i;
    return -1;
}

static int ThemLopNeuChuaCo(ThongKeLop BangThongKe[], int* SoLop, const char* MaLop) {
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

static int LayLoaiHocTap(float Diem) {
    if (Diem >= 3.6f) return 0; // Xuat sac
    if (Diem >= 3.2f) return 1; // Gioi
    if (Diem >= 2.5f) return 2; // Kha
    if (Diem >= 2.0f) return 3; // Trung binh
    return 4;                   // Yeu
}

static void LapBangThongKeTheoLop(HocVien DanhSach[], int SoLuong,
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
        printf("Danh sach hoc vien dang rong.\n");
        return;
    }

    LapBangThongKeTheoLop(DanhSach, SoLuong, BangThongKe, &SoLop);

    printf("%-5s %-15s %s\n", "STT", "Ma lop", "So hoc vien");
    printf("--------------------------------\n");
    for (int i = 0; i < SoLop; i++)
        printf("%-5d %-15s %d\n", i + 1, BangThongKe[i].MaLop, BangThongKe[i].TongSo);
}

void ThongKeXepLoaiTheoLop(HocVien DanhSach[], int SoLuong) {
    ThongKeLop BangThongKe[SoLuongHocVienToiDa];
    int SoLop = 0;
    const char* TenLoai[] = { "Xuat sac", "Gioi", "Kha", "Trung binh", "Yeu" };

    if (SoLuong == 0) {
        printf("Danh sach hoc vien dang rong.\n");
        return;
    }

    LapBangThongKeTheoLop(DanhSach, SoLuong, BangThongKe, &SoLop);

    for (int i = 0; i < SoLop; i++) {
        printf("Lop %s - tong so: %d hoc vien\n", BangThongKe[i].MaLop, BangThongKe[i].TongSo);
        printf("%-12s %-10s %s\n", "Xep loai", "So luong", "Ty le");
        printf("----------------------------------\n");

        for (int j = 0; j < SO_LOAI_HOC_TAP; j++) {
            float TyLe = BangThongKe[i].SoLuongTheoLoai[j] * 100.0f / BangThongKe[i].TongSo;
            printf("%-12s %-10d %.2f%%\n", TenLoai[j], BangThongKe[i].SoLuongTheoLoai[j], TyLe);
        }
        printf("\n");
    }

    
}
void XuLiMenuThongKeTopSV(HocVien DSHV[], int SLHV)
{
    HocVien Tam[SoLuongHocVienToiDa];
    for (int i = 0; i < SLHV; i++)
    {
        Tam[i] = DSHV[i];
    }
    float top;
    InTieuDe("M5_THONG KE_ SO SV THEO MUC DIEM:");
    printf("Nhap muc diem can thong ke :  ");
    
    if (NhapDiemHopLe(&top) == 0) return;
    
    SapXepChon(Tam, SLHV, KHOA_DIEM_TBTL);
    int j = 1;
    printf("\n\n\n");
    for (int i = SLHV-1; i >=0 ; i--)
    {
        if (Tam[i].DiemTrungBinhTichLuy >= top)
        {
            InMotHocVien(Tam[i], j);
            j++;
        }
        
    }

}
