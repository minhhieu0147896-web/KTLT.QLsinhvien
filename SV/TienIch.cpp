// ============================================================
// TienIch.cpp - Cac ham tien ich: man hinh, nhap lieu, mau sac, menu UI
// ============================================================

#include "CauTruc.h"

// Lay handle console hien tai
HANDLE LayConsole() {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

// Dat mau sac cho van ban
void DatMauSac(int Mau) {
    SetConsoleTextAttribute(LayConsole(), Mau);
}

// Tra ve mau mac dinh (trang/den)
void DatMauMacDinh() {
    DatMauSac(MAU_MAC_DINH);
}

// Di chuyen con tro den toa do (X, Y) - X=cot, Y=dong
void GotoXY(int X, int Y) {
    COORD ToaDo;
    ToaDo.X = X;
    ToaDo.Y = Y;
    SetConsoleCursorPosition(LayConsole(), ToaDo);
}

// In 1 dong trong khung: "|  {NoiDung}..." roi can le phai + dong khung
void InDongKhung(const char* NoiDung, int MauChu) {
    DatMauSac(MAU_VIEN);
    printf("|");
    DatMauSac(MauChu);
    printf("  %-46s", NoiDung);
    DatMauSac(MAU_VIEN);
    printf("|\n");
}

// In duong ke ngang cua khung (dung ky tu ASCII)
void InDuongKeNgang(char KyTuGocTrai, char KyTuNoi, char KyTuGocPhai) {
    DatMauSac(MAU_VIEN);
    printf("%c", KyTuGocTrai);
    for (int i = 0; i < 48; i++) printf("=");
    printf("%c\n", KyTuGocPhai);
}

// Xoa man hinh console
void XoaManHinh(void) {
    system("cls");
}

// In tieu de man hinh voi khung dep + mau sac
void InTieuDe(const char* TieuDe) {
    XoaManHinh();
    InDuongKeNgang('+', '=', '+');
    InDongKhung("CHUONG TRINH QUAN LY HOC VIEN", MAU_TIEU_DE);
    InDuongKeNgang('+', '=', '+');
    InDongKhung(TieuDe, MAU_TIEU_DE);
    InDuongKeNgang('+', '=', '+');
    DatMauMacDinh();
    printf("\n");
}

// Doi nguoi dung nhan ESC de quay lai menu truoc
void ChoPhimEscQuayLai(void) {
    int Phim;
    printf("\nNhan ESC de quay lai...");
    do {
        Phim = _getch();
    } while (Phim != 27);
}

// Menu dieu huong bang phim mui ten: ↑↓ chon, ENTER xac nhan, ESC thoat, phim so nhay nhanh
// DongBatDau: dong bat dau in menu (0-based). Tra ve chi so chon (0-based), -1 neu ESC
int ChonMenu(int DongBatDau, const char* CacLuaChon[], int SoLuong, const char* ThongTinBoSung) {
    int LienTiep = 0;
    int Cu = 0;
    int DongThongTin = DongBatDau;

    if (ThongTinBoSung != NULL) {
        DatMauSac(MAU_TIEU_DE);
        GotoXY(0, DongThongTin);
        printf("  %s\n", ThongTinBoSung);
        DongBatDau++;
    }

    for (int i = 0; i < SoLuong; i++) {
        GotoXY(0, DongBatDau + i);
        if (i == LienTiep) DatMauSac(MAU_DONG_CHON);
        else DatMauMacDinh();
        printf("  %-48s", CacLuaChon[i]);
    }

    while (1) {
        int Phim = _getch();
        if (Phim == 224) {
            Phim = _getch();
            Cu = LienTiep;
            if (Phim == 72) LienTiep = (LienTiep - 1 + SoLuong) % SoLuong;
            else if (Phim == 80) LienTiep = (LienTiep + 1) % SoLuong;
            if (LienTiep != Cu) {
                GotoXY(0, DongBatDau + Cu);
                DatMauMacDinh();
                printf("  %-48s", CacLuaChon[Cu]);
                GotoXY(0, DongBatDau + LienTiep);
                DatMauSac(MAU_DONG_CHON);
                printf("  %-48s", CacLuaChon[LienTiep]);
            }
        } else if (Phim == 13) {
            DatMauMacDinh();
            printf("\n");
            return LienTiep;
        } else if (Phim == 27) {
            DatMauMacDinh();
            return -1;
        } else if (Phim >= '1' && Phim <= '9') {
            int ChiSo = Phim - '1';
            if (ChiSo < SoLuong) {
                DatMauMacDinh();
                printf("\n");
                return ChiSo;
            }
        }
    }
}

// Sao chep chuoi an toan (dung strncpy_s)
void SaoChepChuoi(char* ChuoiDich, size_t KichThuocChuoiDich, const char* ChuoiNguon) {
    strncpy_s(ChuoiDich, KichThuocChuoiDich, ChuoiNguon, _TRUNCATE);
}

// Nhap chuoi ky tu, ho tro Backspace va ESC de huy bo
int NhapDongCoEsc(const char* Nhan, char* BoDem, int KichThuoc) {
    int DoDai = 0;
    BoDem[0] = '\0';
    printf("%s", Nhan);
    while (1) {
        int Phim = _getch();
        if (Phim == 27) { BoDem[0] = '\0'; printf("\n"); return 0; }
        if (Phim == 13) { BoDem[DoDai] = '\0'; printf("\n"); return 1; }
        if (Phim == 8) { if (DoDai > 0) { DoDai--; printf("\b \b"); } continue; }
        if (isprint((unsigned char)Phim) && DoDai < KichThuoc - 1) {
            BoDem[DoDai++] = (char)Phim;
            printf("%c", Phim);
        }
    }
}

// Nhap ho ten va tu dong chuan hoa: viet hoa chu cai dau moi tu, con lai viet thuong
int NhapHoTenChuanHoa(const char* Nhan, char* BoDem, int KichThuoc) {
    int DoDai = 0;
    BoDem[0] = '\0';
    printf("%s", Nhan);
    while (1) {
        int Phim = _getch();
        if (Phim == 27) { BoDem[0] = '\0'; printf("\n"); return 0; }
        if (Phim == 13) {
            if (DoDai > 0 && BoDem[DoDai - 1] != ' ') { BoDem[DoDai] = '\0'; printf("\n"); return 1; }
            continue;
        }
        if (Phim == 8) { if (DoDai > 0) { DoDai--; BoDem[DoDai] = '\0'; printf("\b \b"); } continue; }
        if (Phim == ' ') {
            if (DoDai > 0 && BoDem[DoDai - 1] != ' ' && DoDai < KichThuoc - 1) {
                BoDem[DoDai++] = ' '; printf(" ");
            }
            continue;
        }
        if (isalpha((unsigned char)Phim) && DoDai < KichThuoc - 1) {
            bool CanVietHoa = (DoDai == 0 || BoDem[DoDai - 1] == ' ');
            char KyTu = CanVietHoa ? (char)toupper(Phim) : (char)tolower(Phim);
            BoDem[DoDai++] = KyTu;
            printf("%c", KyTu);
        }
    }
}

// Kiem tra nam nhuan: tra ve 1 neu nam nhuan, 0 neu khong
int LaNamNhuan(int Nam) {
    if (Nam % 400 == 0) return 1;
    if (Nam % 100 == 0) return 0;
    return Nam % 4 == 0;
}

// Kiem tra ngay sinh hop le (ngay/thang/nam dung va nam < 2008)
int KiemTraNgaySinhHopLe(Date NgaySinh) {
    int SoNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (LaNamNhuan(NgaySinh.Nam)) SoNgayTrongThang[1] = 29;
    if (NgaySinh.Thang > 0 && NgaySinh.Thang <= 12)
        if (NgaySinh.Ngay > 0 && NgaySinh.Ngay <= SoNgayTrongThang[NgaySinh.Thang - 1])
            if (NgaySinh.Nam < 2008)
                return 1;
    return 0;
}

// In ngay sinh theo dinh dang dd/mm/yyyy
void InNgaySinh(Date NgaySinh) {
    printf("%02d/%02d/%04d", NgaySinh.Ngay, NgaySinh.Thang, NgaySinh.Nam);
}

// Chuyen chuoi sang so nguyen, tra ve 0 neu that bai
int ChuyenChuoiThanhSoNguyen(const char* Chuoi, int* GiaTri) {
    char KyTuThua;
    if (sscanf_s(Chuoi, "%d%c", GiaTri, &KyTuThua, 1) != 1) return 0;
    return 1;
}

// Nhap so nguyen, lap den khi nhap dung hoac bam ESC
int NhapSoNguyenCoEsc(const char* Nhan, int* GiaTri) {
    char Chuoi[20];
    while (1) {
        if (!NhapDongCoEsc(Nhan, Chuoi, sizeof(Chuoi))) return 0;
        if (ChuyenChuoiThanhSoNguyen(Chuoi, GiaTri)) return 1;
        printf("Gia tri phai la so nguyen. Vui long nhap lai.\n");
    }
}

// Nhap ngay sinh va kiem tra hop le (gom kiem tra roi rac + kiem tra tong the)
int NhapNgaySinhHopLe(Date* NgaySinh) {
    while (1) {
        printf("Nhap ngay sinh: \n");
        if (!NhapSoNguyenCoEsc("Ngay : ", &NgaySinh->Ngay)) return 0;
        if (NgaySinh->Ngay < 1 || NgaySinh->Ngay > 31) {
            printf("Ngay phai tu 1 den 31. Vui long nhap lai ngay sinh.\n"); continue;
        }
        if (!NhapSoNguyenCoEsc("Thang: ", &NgaySinh->Thang)) return 0;
        if (NgaySinh->Thang < 1 || NgaySinh->Thang > 12) {
            printf("Thang phai tu 1 den 12. Vui long nhap lai ngay sinh.\n"); continue;
        }
        if (!NhapSoNguyenCoEsc("Nam  : ", &NgaySinh->Nam)) return 0;
        if (NgaySinh->Nam < 1900 || NgaySinh->Nam > 2026) {
            printf("Nam phai tu 1900 den 2026. Vui long nhap lai ngay sinh.\n"); continue;
        }
        if (KiemTraNgaySinhHopLe(*NgaySinh)) return 1;
        printf("Ngay thang khong hop le. Vui long nhap lai ngay sinh.\n");
    }
}

// Kiem tra ma HV co dung dinh dang: 2024xxx (7 ky tu, xxx tu 001-999)
int KiemTraMaHocVienHopLe(const char* MaHocVien) {
    if (strlen(MaHocVien) != 7) return 0;
    if (strncmp(MaHocVien, "2024", 4) != 0) return 0;
    if (!isdigit((unsigned char)MaHocVien[4]) || !isdigit((unsigned char)MaHocVien[5]) || !isdigit((unsigned char)MaHocVien[6]))
        return 0;
    int SoThuTu = atoi(MaHocVien + 4);
    return SoThuTu >= 1 && SoThuTu <= 999;
}

// Kiem tra ma HV co bi trung trong danh sach hay khong
int KiemTraTrungMaHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien, const char* MaHocVien) {
    for (int ViTri = 0; ViTri < SoLuongHocVien; ViTri++)
        if (strcmp(DanhSachHocVien[ViTri].MaHocVien, MaHocVien) == 0) return 1;
    return 0;
}

// Nhap ma HV, kiem tra hop le + khong trung, cho phep ESC huy
int NhapMaHocVienHopLe(char* MaHocVien, int KichThuoc, HocVien DanhSachHocVien[], int SoLuongHocVien) {
    while (1) {
        if (!NhapDongCoEsc("Ma hoc vien (2024001-2024999): ", MaHocVien, KichThuoc)) return 0;
        if (!KiemTraMaHocVienHopLe(MaHocVien)) {
            printf("Ma hoc vien phai co dang 2024***, trong do *** tu 001 den 999.\n"); continue;
        }
        if (KiemTraTrungMaHocVien(DanhSachHocVien, SoLuongHocVien, MaHocVien)) {
            printf("Ma hoc vien da ton tai. Vui long nhap ma khac.\n"); continue;
        }
        return 1;
    }
}

// Kiem tra chuoi diem co hop le khong (so thuc trong khoang 0.0 - 4.0)
int KiemTraDiemHopLe(const char* ChuoiDiem, float* Diem) {
    char KyTuThua;
    if (sscanf_s(ChuoiDiem, "%f%c", Diem, &KyTuThua, 1) != 1) return 0;
    return *Diem >= 0.0f && *Diem <= 4.0f;
}

// Nhap diem TBTL, lap den khi nhap dung (0.0 - 4.0) hoac ESC
int NhapDiemHopLe(float* Diem) {
    char ChuoiDiem[20];
    while (1) {
        if (!NhapDongCoEsc("Diem TBTL (0.0 - 4.0): ", ChuoiDiem, sizeof(ChuoiDiem))) return 0;
        if (KiemTraDiemHopLe(ChuoiDiem, Diem)) return 1;
        printf("Diem khong hop le. Vui long nhap lai.\n");
    }
}

// In 1 dong thong tin hoc vien theo dinh dang bang
void InMotHocVien(HocVien ThongTinHocVien, int SoThuTu) {
    printf("%-5d %-10s %-12s %-28s %02d/%02d/%04d   %.2f\n",
        SoThuTu, ThongTinHocVien.MaLop, ThongTinHocVien.MaHocVien,
        ThongTinHocVien.HoTen,
        ThongTinHocVien.NgaySinh.Ngay, ThongTinHocVien.NgaySinh.Thang, ThongTinHocVien.NgaySinh.Nam,
        ThongTinHocVien.DiemTrungBinhTichLuy);
}

// In toan bo danh sach hoc vien dang bang co tieu de cot
void InBangHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien) {
    if (SoLuongHocVien == 0) { printf("Danh sach hoc vien dang rong.\n"); return; }
    printf("%-5s %-10s %-12s %-28s %-12s %s\n", "STT", "Ma lop", "Ma HV", "Ho ten", "Ngay sinh", "Diem");
    printf("-------------------------------------------------------------------------------\n");
    for (int ViTri = 0; ViTri < SoLuongHocVien; ViTri++)
        InMotHocVien(DanhSachHocVien[ViTri], ViTri + 1);
}

// Xac nhan luu hoc vien: ENTER de luu, ESC de huy
int XacNhanThemHocVien(void) {
    int Phim;
    printf("\nThem moi hoc vien nay?");
    printf("\nNhan ENTER de luu, ESC de huy.");
    while (1) {
        Phim = _getch();
        if (Phim == 13) return 1;
        if (Phim == 27) return 0;
    }
}
