#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ============================================================
// CAC HANG SO MAU SAC
// ============================================================
#define MAU_MAC_DINH      7    // Trang tren den
#define MAU_TIEU_DE       14   // Vang tren den
#define MAU_VIEN           3   // Xanh cyan tren den
#define MAU_DONG_CHON     112  // Den tren trang (dao nguoc)
#define MAU_THANH_CONG    10   // Xanh la tren den
#define MAU_LOI            4   // Do tren den

// ============================================================
// CAC HAM TIEN ICH MAU SAC & CON TRO
// ============================================================

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

#define SoKyTuToiDaMaLop 20
#define SoKyTuToiDaMaHocVien 20
#define SoKyTuToiDaHoTen 100
#define SoLuongHocVienToiDa 200

typedef struct {
    int Ngay;
    int Thang;
    int Nam;
} Date;

typedef struct {
    char MaLop[SoKyTuToiDaMaLop];
    char MaHocVien[SoKyTuToiDaMaHocVien];
    char HoTen[SoKyTuToiDaHoTen];
    Date NgaySinh;
    float DiemTrungBinhTichLuy;
} HocVien;

// Xóa màn hình console
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

// Đợi người dùng nhấn ESC để quay lại menu trước
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

    // In thong tin bo sung (neu co)
    if (ThongTinBoSung != NULL) {
        DatMauSac(MAU_TIEU_DE);
        GotoXY(0, DongThongTin);
        printf("  %s\n", ThongTinBoSung);
        DongBatDau++;
    }

    // In toan bo menu lan dau tien
    for (int i = 0; i < SoLuong; i++) {
        GotoXY(0, DongBatDau + i);
        if (i == LienTiep) {
            DatMauSac(MAU_DONG_CHON);
        } else {
            DatMauMacDinh();
        }
        printf("  %-48s", CacLuaChon[i]);
    }

    // Vong lap xu ly phim
    while (1) {
        int Phim = _getch();

        if (Phim == 224) {                         // Phim mo rong (mui ten)
            Phim = _getch();
            Cu = LienTiep;
            if (Phim == 72) {                      // Mui ten LEN
                LienTiep = (LienTiep - 1 + SoLuong) % SoLuong;
            } else if (Phim == 80) {               // Mui ten XUONG
                LienTiep = (LienTiep + 1) % SoLuong;
            }
            if (LienTiep != Cu) {
                // Bo highlight dong cu
                GotoXY(0, DongBatDau + Cu);
                DatMauMacDinh();
                printf("  %-48s", CacLuaChon[Cu]);
                // Highlight dong moi
                GotoXY(0, DongBatDau + LienTiep);
                DatMauSac(MAU_DONG_CHON);
                printf("  %-48s", CacLuaChon[LienTiep]);
            }
        } else if (Phim == 13) {                   // ENTER
            DatMauMacDinh();
            printf("\n");
            return LienTiep;
        } else if (Phim == 27) {                   // ESC
            DatMauMacDinh();
            return -1;
        } else if (Phim >= '1' && Phim <= '9') {  // Phim so
            int ChiSo = Phim - '1';
            if (ChiSo < SoLuong) {
                DatMauMacDinh();
                printf("\n");
                return ChiSo;
            }
        }
    }
}

// Sao chép chuỗi an toàn (dùng strncpy_s)
void SaoChepChuoi(char* ChuoiDich, size_t KichThuocChuoiDich, const char* ChuoiNguon) {
    strncpy_s(ChuoiDich, KichThuocChuoiDich, ChuoiNguon, _TRUNCATE);
}

// Nhập chuỗi ký tự, hỗ trợ Backspace và ESC để hủy bỏ
int NhapDongCoEsc(const char* Nhan, char* BoDem, int KichThuoc) {
    int DoDai = 0;

    BoDem[0] = '\0';
    printf("%s", Nhan);

    while (1) {
        int Phim = _getch();

        if (Phim == 27) {
            BoDem[0] = '\0';
            printf("\n");
            return 0;
        }

        if (Phim == 13) {
            BoDem[DoDai] = '\0';
            printf("\n");
            return 1;
        }

        if (Phim == 8) {
            if (DoDai > 0) {
                DoDai--;
                printf("\b \b");
            }
            continue;
        }

        if (isprint((unsigned char)Phim) && DoDai < KichThuoc - 1) {
            BoDem[DoDai++] = (char)Phim;
            printf("%c", Phim);
        }
    }
}

// Nhập họ tên và tự động chuẩn hóa: viết hoa chữ cái đầu mỗi từ, còn lại viết thường
int NhapHoTenChuanHoa(const char* Nhan, char* BoDem, int KichThuoc) {
    int DoDai = 0;

    BoDem[0] = '\0';
    printf("%s", Nhan);

    while (1) {
        int Phim = _getch();

        if (Phim == 27) {
            BoDem[0] = '\0';
            printf("\n");
            return 0;
        }

        if (Phim == 13) {
            if (DoDai > 0 && BoDem[DoDai - 1] != ' ') {
                BoDem[DoDai] = '\0';
                printf("\n");
                return 1;
            }
            continue;
        }

        if (Phim == 8) {
            if (DoDai > 0) {
                DoDai--;
                BoDem[DoDai] = '\0';
                printf("\b \b");
            }
            continue;
        }

        if (Phim == ' ') {
            if (DoDai > 0 && BoDem[DoDai - 1] != ' ' && DoDai < KichThuoc - 1) {
                BoDem[DoDai++] = ' ';
                printf(" ");
            }
            continue;
        }

        if (isalpha((unsigned char)Phim) && DoDai < KichThuoc - 1) {

            bool CanVietHoa = false;
            if (DoDai == 0 || BoDem[DoDai - 1] == ' ') CanVietHoa = true;
            char KyTu;
            if (CanVietHoa == false) KyTu = (char)tolower(Phim);
            if (CanVietHoa == true) KyTu = (char)toupper(Phim);
            BoDem[DoDai++] = KyTu;
            printf("%c", KyTu);
        }
    }
}

// Kiểm tra năm nhuận: trả về 1 nếu năm nhuận, 0 nếu không
int LaNamNhuan(int Nam) {
    if (Nam % 400 == 0) {
        return 1;
    }
    if (Nam % 100 == 0) {
        return 0;
    }
    return Nam % 4 == 0;
}

// Kiểm tra ngày sinh hợp lệ (ngày/tháng/năm đúng và năm < 2008)
int KiemTraNgaySinhHopLe(Date NgaySinh) {
    int SoNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (LaNamNhuan(NgaySinh.Nam)) {
        SoNgayTrongThang[1] = 29;
    }

    if (NgaySinh.Thang > 0 && NgaySinh.Thang <= 12)
    {
        if (NgaySinh.Ngay > 0 && NgaySinh.Ngay <= SoNgayTrongThang[NgaySinh.Thang - 1])
        {
            if (NgaySinh.Nam < 2008)
            {
                return 1;
            }
        }
    }
    return 0;
}

// In ngày sinh theo định dạng dd/mm/yyyy
void InNgaySinh(Date NgaySinh) {
    printf("%02d/%02d/%04d", NgaySinh.Ngay, NgaySinh.Thang, NgaySinh.Nam);
}

// Chuyển chuỗi sang số nguyên, trả về 0 nếu thất bại
int ChuyenChuoiThanhSoNguyen(const char* Chuoi, int* GiaTri) {
    char KyTuThua;

    if (sscanf_s(Chuoi, "%d%c", GiaTri, &KyTuThua, 1) != 1) {
        return 0;
    }

    return 1;
}

// Nhập số nguyên, lặp đến khi nhập đúng hoặc bấm ESC
int NhapSoNguyenCoEsc(const char* Nhan, int* GiaTri) {
    char Chuoi[20];

    while (1) {
        if (!NhapDongCoEsc(Nhan, Chuoi, sizeof(Chuoi))) {
            return 0;
        }

        if (ChuyenChuoiThanhSoNguyen(Chuoi, GiaTri)) {
            return 1;
        }

        printf("Gia tri phai la so nguyen. Vui long nhap lai.\n");
    }
}

// Nhập ngày sinh và kiểm tra hợp lệ (gồm kiểm tra rời rạc + kiểm tra tổng thể)
int NhapNgaySinhHopLe(Date* NgaySinh) {
    while (1) {
        printf("Nhap ngay sinh: \n");

        if (!NhapSoNguyenCoEsc("Ngay : ", &NgaySinh->Ngay)) {
            return 0;
        }
        if (NgaySinh->Ngay < 1 || NgaySinh->Ngay > 31) {
            printf("Ngay phai tu 1 den 31. Vui long nhap lai ngay sinh.\n");
            continue;
        }

        if (!NhapSoNguyenCoEsc("Thang: ", &NgaySinh->Thang)) {
            return 0;
        }
        if (NgaySinh->Thang < 1 || NgaySinh->Thang > 12) {
            printf("Thang phai tu 1 den 12. Vui long nhap lai ngay sinh.\n");
            continue;
        }

        if (!NhapSoNguyenCoEsc("Nam  : ", &NgaySinh->Nam)) {
            return 0;
        }
        if (NgaySinh->Nam < 1900 || NgaySinh->Nam > 2026) {
            printf("Nam phai tu 1900 den 2026. Vui long nhap lai ngay sinh.\n");
            continue;
        }

        if (KiemTraNgaySinhHopLe(*NgaySinh)) {
            return 1;
        }

        printf("Ngay thang khong hop le. Vui long nhap lai ngay sinh.\n");
    }
}

// Kiểm tra mã HV có đúng định dạng: 2024xxx (7 ký tự, xxx từ 001-999)
int KiemTraMaHocVienHopLe(const char* MaHocVien) {
    int SoThuTu;

    if (strlen(MaHocVien) != 7) {
        return 0;
    }

    if (strncmp(MaHocVien, "2024", 4) != 0) {
        return 0;
    }

    if (!isdigit((unsigned char)MaHocVien[4]) ||
        !isdigit((unsigned char)MaHocVien[5]) ||
        !isdigit((unsigned char)MaHocVien[6])) {
        return 0;
    }

    SoThuTu = atoi(MaHocVien + 4);
    return SoThuTu >= 1 && SoThuTu <= 999;
}

// Kiểm tra mã HV có bị trùng trong danh sách hay không
int KiemTraTrungMaHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien, const char* MaHocVien) {
    int ViTri;

    for (ViTri = 0; ViTri < SoLuongHocVien; ViTri++) {
        if (strcmp(DanhSachHocVien[ViTri].MaHocVien, MaHocVien) == 0) {
            return 1;
        }
    }

    return 0;
}

// Nhập mã HV, kiểm tra hợp lệ + không trùng, cho phép ESC hủy
int NhapMaHocVienHopLe(char* MaHocVien, int KichThuoc, HocVien DanhSachHocVien[], int SoLuongHocVien) {
    while (1) {
        if (!NhapDongCoEsc("Ma hoc vien (2024001-2024999): ", MaHocVien, KichThuoc)) {
            return 0;
        }

        if (!KiemTraMaHocVienHopLe(MaHocVien)) {
            printf("Ma hoc vien phai co dang 2024***, trong do *** tu 001 den 999.\n");
            continue;
        }

        if (KiemTraTrungMaHocVien(DanhSachHocVien, SoLuongHocVien, MaHocVien)) {
            printf("Ma hoc vien da ton tai. Vui long nhap ma khac.\n");
            continue;
        }

        return 1;
    }
}

// Kiểm tra chuỗi điểm có hợp lệ không (số thực trong khoảng 0.0 - 4.0)
int KiemTraDiemHopLe(const char* ChuoiDiem, float* Diem) {
    char KyTuThua;

    if (sscanf_s(ChuoiDiem, "%f%c", Diem, &KyTuThua, 1) != 1) {
        return 0;
    }

    return *Diem >= 0.0f && *Diem <= 4.0f;
}

// Nhập điểm TBTL, lặp đến khi nhập đúng (0.0 - 4.0) hoặc ESC
int NhapDiemHopLe(float* Diem) {
    char ChuoiDiem[20];

    while (1) {
        if (!NhapDongCoEsc("Diem TBTL (0.0 - 4.0): ", ChuoiDiem, sizeof(ChuoiDiem))) {
            return 0;
        }

        if (KiemTraDiemHopLe(ChuoiDiem, Diem)) {
            return 1;
        }

        printf("Diem khong hop le. Vui long nhap lai.\n");
    }
}

// In 1 dòng thông tin học viên theo định dạng bảng
void InMotHocVien(HocVien ThongTinHocVien, int SoThuTu) {
    printf("%-5d %-10s %-12s %-28s %02d/%02d/%04d   %.2f\n",
        SoThuTu,
        ThongTinHocVien.MaLop,
        ThongTinHocVien.MaHocVien,
        ThongTinHocVien.HoTen,
        ThongTinHocVien.NgaySinh.Ngay,
        ThongTinHocVien.NgaySinh.Thang,
        ThongTinHocVien.NgaySinh.Nam,
        ThongTinHocVien.DiemTrungBinhTichLuy);
}

// In toàn bộ danh sách học viên dạng bảng có tiêu đề cột
void InBangHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien) {
    int ViTri;

    if (SoLuongHocVien == 0) {
        printf("Danh sach hoc vien dang rong.\n");
        return;
    }

    printf("%-5s %-10s %-12s %-28s %-12s %s\n", "STT", "Ma lop", "Ma HV", "Ho ten", "Ngay sinh", "Diem");
    printf("-------------------------------------------------------------------------------\n");
    for (ViTri = 0; ViTri < SoLuongHocVien; ViTri++) {
        InMotHocVien(DanhSachHocVien[ViTri], ViTri + 1);
    }
}

// Đọc danh sách học viên từ file nhị phân, trả về số lượng đọc được
int DocDanhSachTuFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongToiDa) {
    FILE* Tep;
    int SoLuongDocDuoc;

    if (fopen_s(&Tep, TenTep, "rb") != 0) {
        fopen_s(&Tep, TenTep, "wb");
        if (Tep != NULL) {
            fclose(Tep);
        }
        return 0;
    }

    SoLuongDocDuoc = (int)fread(DanhSachHocVien, sizeof(HocVien), SoLuongToiDa, Tep);

    fclose(Tep);

    return SoLuongDocDuoc;
}

// Ghi danh sách học viên vào file nhị phân, trả về 1 nếu thành công
int GhiDanhSachVaoFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongHocVien) {
    FILE* Tep;
    int SoLuongGhiDuoc;

    if (fopen_s(&Tep, TenTep, "wb") != 0) {
        return 0;
    }

    SoLuongGhiDuoc = (int)fwrite(DanhSachHocVien, sizeof(HocVien), SoLuongHocVien, Tep);

    fclose(Tep);

    return SoLuongGhiDuoc == SoLuongHocVien;
}

// Xác nhận lưu học viên: ENTER để lưu, ESC để hủy
int XacNhanThemHocVien(void) {
    int Phim;

    printf("\nThem moi hoc vien nay?");
    printf("\nNhan ENTER de luu, ESC de huy.");

    while (1) {
        Phim = _getch();
        if (Phim == 13) {
            return 1;
        }
        if (Phim == 27) {
            return 0;
        }
    }
}

// M1: Xử lý thêm mới hồ sơ học viên (nhập → xác nhận → lưu file)
void XuLyThemHoSo(const char* TenTep) {
    HocVien DanhSachHocVien[SoLuongHocVienToiDa];
    HocVien HocVienTam = { "", "", "", { 0, 0, 0 }, 0 };
    int SoLuongHocVien;

    SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

    if (SoLuongHocVien >= SoLuongHocVienToiDa) {
        InTieuDe("M1. THEM MOI HO SO");
        printf("Danh sach da day, khong the them hoc vien moi.\n");
        ChoPhimEscQuayLai();
        return;
    }

    InTieuDe("M1. THEM MOI HO SO");
    printf("Nhap thong tin hoc vien.\n");
    printf("Nhan ESC tai bat ky truong nao de huy va quay lai.\n\n");

    if (!NhapDongCoEsc("Ma lop                : ", HocVienTam.MaLop, sizeof(HocVienTam.MaLop))) {
        return;
    }

    if (!NhapMaHocVienHopLe(HocVienTam.MaHocVien, sizeof(HocVienTam.MaHocVien), DanhSachHocVien, SoLuongHocVien)) {
        return;
    }

    if (!NhapHoTenChuanHoa("Ho va ten             : ", HocVienTam.HoTen, sizeof(HocVienTam.HoTen))) {
        return;
    }

    if (!NhapNgaySinhHopLe(&HocVienTam.NgaySinh)) {
        return;
    }

    if (!NhapDiemHopLe(&HocVienTam.DiemTrungBinhTichLuy)) {
        return;
    }

    printf("\nThong tin vua nhap:\n");
    printf("Ma lop      : %s\n", HocVienTam.MaLop);
    printf("Ma hoc vien : %s\n", HocVienTam.MaHocVien);
    printf("Ho va ten   : %s\n", HocVienTam.HoTen);
    printf("Ngay sinh   : ");
    InNgaySinh(HocVienTam.NgaySinh);
    printf("\n");
    printf("Diem TBTL   : %.2f\n", HocVienTam.DiemTrungBinhTichLuy);

    if (!XacNhanThemHocVien()) {
        return;
    }

    DanhSachHocVien[SoLuongHocVien] = HocVienTam;
    SoLuongHocVien++;

    if (GhiDanhSachVaoFile(TenTep, DanhSachHocVien, SoLuongHocVien)) {
        printf("\nDa them hoc vien va luu vao file nhi phan %s.\n", TenTep);
    }
    else {
        printf("\nKhong ghi duoc file nhi phan.\n");
    }

    ChoPhimEscQuayLai();
}

// M2: Xử lý menu in danh sách (toàn bộ / theo lớp / theo kết quả sắp xếp)
void XuLyMenuInDanhSach(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        const char* MenuIn[] = {
            "1. In toan bo danh sach",
            "2. In theo lop",
            "3. In theo ket qua sap xep/tim kiem"
        };

        InTieuDe("M2. IN DANH SACH");
        int Chon = ChonMenu(6, MenuIn, 3, NULL);
        if (Chon == -1) return;

        if (Chon == 0) {
            InTieuDe("M2. IN TOAN BO DANH SACH");
            InBangHocVien(DanhSachHocVien, SoLuongHocVien);
            ChoPhimEscQuayLai();
        }

        if (Chon == 1) {
            char MaLopCanIn[SoKyTuToiDaMaLop];
            int ViTri;
            int SoLuongTimThay = 0;

            InTieuDe("M2. IN DANH SACH THEO LOP");
            if (!NhapDongCoEsc("Nhap ma lop: ", MaLopCanIn, sizeof(MaLopCanIn))) {
                continue;
            }

            printf("%-5s %-10s %-12s %-28s %-12s %s\n", "STT", "Ma lop", "Ma HV", "Ho ten", "Ngay sinh", "Diem");
            printf("-------------------------------------------------------------------------------\n");
            for (ViTri = 0; ViTri < SoLuongHocVien; ViTri++) {
                if (strcmp(DanhSachHocVien[ViTri].MaLop, MaLopCanIn) == 0) {
                    SoLuongTimThay++;
                    InMotHocVien(DanhSachHocVien[ViTri], SoLuongTimThay);
                }
            }

            if (SoLuongTimThay == 0) {
                printf("Khong co hoc vien nao thuoc lop %s.\n", MaLopCanIn);
            }
            ChoPhimEscQuayLai();
        }

        if (Chon == 2) {
            InTieuDe("M2. IN THEO KET QUA SAP XEP/TIM KIEM");
            printf("Chuc nang nay se hoan thien o cac tuan sau.\n");
            ChoPhimEscQuayLai();
        }
    }
}

// ============================================================
// TUAN 3: CAC HAM SO SANH & SAP XEP
// ============================================================

// So sánh 2 học viên theo mã học viên (tăng dần)
int SoSanhTheoMaHocVien(HocVien A, HocVien B) {
    return strcmp(A.MaHocVien, B.MaHocVien) < 0;
}

// So sánh 2 học viên theo họ tên (tăng dần theo bảng chữ cái)
int SoSanhTheoHoTen(HocVien A, HocVien B) {
    return strcmp(A.HoTen, B.HoTen) < 0;
}

// So sánh 2 học viên theo ngày sinh (tăng dần: cũ hơn → trẻ hơn)
int SoSanhTheoNgaySinh(HocVien A, HocVien B) {
    if (A.NgaySinh.Nam != B.NgaySinh.Nam)
        return A.NgaySinh.Nam < B.NgaySinh.Nam;
    if (A.NgaySinh.Thang != B.NgaySinh.Thang)
        return A.NgaySinh.Thang < B.NgaySinh.Thang;
    return A.NgaySinh.Ngay < B.NgaySinh.Ngay;
}

// So sánh 2 học viên theo điểm trung bình tích lũy (tăng dần)
int SoSanhTheoDiemTrungBinhTichLuy(HocVien A, HocVien B) {
    return A.DiemTrungBinhTichLuy < B.DiemTrungBinhTichLuy;
}

// So sánh 2 học viên theo khóa được chọn (1=mã, 2=tên, 3=ngày sinh, 4=điểm)
int SoSanhHocVien(HocVien A, HocVien B, int Khoa) {
    switch (Khoa) {
    case '1': return SoSanhTheoMaHocVien(A, B);
    case '2': return SoSanhTheoHoTen(A, B);
    case '3': return SoSanhTheoNgaySinh(A, B);
    case '4': return SoSanhTheoDiemTrungBinhTichLuy(A, B);
    }
    return 0;
}

// Hoán đổi vị trí 2 học viên trong mảng
void HoanDoiHocVien(HocVien* A, HocVien* B) {
    HocVien Tam = *A;
    *A = *B;
    *B = Tam;
}

// Thuật toán sắp xếp chọn: mỗi vòng tìm min trong đoạn chưa sắp xếp rồi đưa về đầu
void SapXepChon(HocVien DanhSach[], int SoLuong, int Khoa) {
    int i, j, ViTriNhoNhat;

    for (i = 0; i < SoLuong - 1; i++) {
        ViTriNhoNhat = i;
        for (j = i + 1; j < SoLuong; j++) {
            if (SoSanhHocVien(DanhSach[j], DanhSach[ViTriNhoNhat], Khoa)) {
                ViTriNhoNhat = j;
            }
        }
        if (ViTriNhoNhat != i) {
            HoanDoiHocVien(&DanhSach[i], &DanhSach[ViTriNhoNhat]);
        }
    }
}

// Thuật toán sắp xếp chèn: rút từng phần tử rồi chèn vào đúng vị trí trong phần đã sắp
void SapXepChen(HocVien DanhSach[], int SoLuong, int Khoa) {
    int i, j;
    HocVien KhoaTam;

    for (i = 1; i < SoLuong; i++) {
        KhoaTam = DanhSach[i];
        j = i - 1;
        while (j >= 0 && SoSanhHocVien(KhoaTam, DanhSach[j], Khoa)) {
            DanhSach[j + 1] = DanhSach[j];
            j--;
        }
        DanhSach[j + 1] = KhoaTam;
    }
}

// Phân hoạch Lomuto cho Quicksort: đưa phần tử nhỏ hơn chốt sang trái, lớn hơn sang phải
int PhanHoach(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    HocVien Chot = DanhSach[Phai];
    int i = Trai - 1;
    int j;

    for (j = Trai; j < Phai; j++) {
        if (SoSanhHocVien(DanhSach[j], Chot, Khoa)) {
            i++;
            HoanDoiHocVien(&DanhSach[i], &DanhSach[j]);
        }
    }
    HoanDoiHocVien(&DanhSach[i + 1], &DanhSach[Phai]);
    return i + 1;
}

// Thuật toán Quicksort: chọn chốt → phân hoạch → đệ quy 2 nửa trái & phải
void SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int ViTriChot = PhanHoach(DanhSach, Trai, Phai, Khoa);
        SapXepNhanh(DanhSach, Trai, ViTriChot - 1, Khoa);
        SapXepNhanh(DanhSach, ViTriChot + 1, Phai, Khoa);
    }
}

// Trộn 2 mảng con đã sắp xếp thành 1 mảng có thứ tự
void Tron(HocVien DanhSach[], int Trai, int Giua, int Phai, int Khoa) {
    int i, j, k;
    int KichThuocTrai = Giua - Trai + 1;
    int KichThuocPhai = Phai - Giua;

    HocVien* MangTrai = (HocVien*)malloc(KichThuocTrai * sizeof(HocVien));
    HocVien* MangPhai = (HocVien*)malloc(KichThuocPhai * sizeof(HocVien));

    if (MangTrai == NULL || MangPhai == NULL) {
        if (MangTrai) free(MangTrai);
        if (MangPhai) free(MangPhai);
        return;
    }

    for (i = 0; i < KichThuocTrai; i++)
        MangTrai[i] = DanhSach[Trai + i];
    for (j = 0; j < KichThuocPhai; j++)
        MangPhai[j] = DanhSach[Giua + 1 + j];

    i = 0; j = 0; k = Trai;
    while (i < KichThuocTrai && j < KichThuocPhai) {
        if (SoSanhHocVien(MangTrai[i], MangPhai[j], Khoa)) {
            DanhSach[k] = MangTrai[i];
            i++;
        }
        else {
            DanhSach[k] = MangPhai[j];
            j++;
        }
        k++;
    }

    while (i < KichThuocTrai) {
        DanhSach[k] = MangTrai[i];
        i++; k++;
    }

    while (j < KichThuocPhai) {
        DanhSach[k] = MangPhai[j];
        j++; k++;
    }

    free(MangTrai);
    free(MangPhai);
}

// Thuật toán Mergesort: chia đôi mảng → đệ quy → trộn 2 nửa đã sắp
void SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        SapXepTron(DanhSach, Trai, Giua, Khoa);
        SapXepTron(DanhSach, Giua + 1, Phai, Khoa);
        Tron(DanhSach, Trai, Giua, Phai, Khoa);
    }
}

// Trả về tên hiển thị của thuật toán sắp xếp theo mã chọn
const char* LayTenThuatToan(int ThuatToan) {
    switch (ThuatToan) {
    case '1': return "Sap xep chon (Selection Sort)";
    case '2': return "Sap xep chen (Insertion Sort)";
    case '3': return "Quicksort";
    case '4': return "Mergesort";
    }
    return "";
}

// Trả về tên hiển thị của khóa sắp xếp theo mã chọn
const char* LayTenKhoa(int Khoa) {
    switch (Khoa) {
    case '1': return "Ma hoc vien";
    case '2': return "Ho va ten";
    case '3': return "Ngay sinh";
    case '4': return "Diem trung binh tich luy";
    }
    return "";
}

// M3: Xử lý menu sắp xếp (chọn thuật toán → chọn khóa → sắp xếp → hỏi lưu)
void XuLyMenuSapXep(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        char ThongTin[100];

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        if (SoLuongHocVien == 0) {
            InTieuDe("M3. SAP XEP");
            printf("Danh sach hoc vien dang rong, khong co gi de sap xep.\n");
            ChoPhimEscQuayLai();
            return;
        }

        // --- Menu cap 1: chon thuat toan ---
        const char* MenuThuatToan[] = {
            "1. Sap xep chon",
            "2. Sap xep chen",
            "3. Quicksort",
            "4. Mergesort"
        };

        sprintf_s(ThongTin, sizeof(ThongTin), "So hoc vien hien co trong file: %d", SoLuongHocVien);

        InTieuDe("M3. SAP XEP");
        int ChonTT = ChonMenu(7, MenuThuatToan, 4, ThongTin);
        if (ChonTT == -1) return;

        // --- Menu cap 2: chon khoa ---
        const char* MenuKhoa[] = {
            "1. Ma hoc vien",
            "2. Ho va ten",
            "3. Ngay sinh",
            "4. Diem trung binh tich luy"
        };

        char KhoaDaChon = '1' + ChonTT;  // Chuyen 0-based → ky tu '1'-'4'
        sprintf_s(ThongTin, sizeof(ThongTin), "Thuat toan da chon: %s", LayTenThuatToan(KhoaDaChon));

        InTieuDe("M3. SAP XEP - CHON KHOA");
        int ChonKhoa = ChonMenu(7, MenuKhoa, 4, ThongTin);
        if (ChonKhoa == -1) continue;

        // --- Thuc hien sap xep ---
        char KhoaKey = '1' + ChonKhoa;   // Chuyen 0-based → ky tu '1'-'4'
        InTieuDe("M3. SAP XEP - KET QUA");
        printf("Thuat toan: %s\n", LayTenThuatToan(KhoaDaChon));
        printf("Khoa sap xep: %s\n", LayTenKhoa(KhoaKey));
        printf("So hoc vien: %d\n\n", SoLuongHocVien);

        switch (KhoaDaChon) {
        case '1': SapXepChon(DanhSachHocVien, SoLuongHocVien, KhoaKey); break;
        case '2': SapXepChen(DanhSachHocVien, SoLuongHocVien, KhoaKey); break;
        case '3': SapXepNhanh(DanhSachHocVien, 0, SoLuongHocVien - 1, KhoaKey); break;
        case '4': SapXepTron(DanhSachHocVien, 0, SoLuongHocVien - 1, KhoaKey); break;
        }

        printf("Da sap xep xong!\n\n");
        InBangHocVien(DanhSachHocVien, SoLuongHocVien);

        printf("\nBan co muon luu ket qua sap xep vao file khong?\n");
        printf("Nhan ENTER de luu, ESC de bo qua.\n");

        while (1) {
            int Phim = _getch();
            if (Phim == 13) {
                if (GhiDanhSachVaoFile(TenTep, DanhSachHocVien, SoLuongHocVien)) {
                    printf("\nDa luu danh sach da sap xep vao file %s.\n", TenTep);
                } else {
                    printf("\nLoi: Khong ghi duoc file.\n");
                }
                break;
            }
            if (Phim == 27) {
                printf("\nKhong luu thay doi.\n");
                break;
            }
        }

        ChoPhimEscQuayLai();
    }
}

// M4: Xử lý menu tìm kiếm (chọn thuật toán → chọn khóa → nhập giá trị tìm)
void XuLyMenuTimKiem(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        char ThongTin[100];

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        // --- Menu cap 1: chon thuat toan ---
        const char* MenuTK[] = {
            "1. Tim kiem tuan tu",
            "2. Tim kiem nhi phan"
        };

        sprintf_s(ThongTin, sizeof(ThongTin), "So hoc vien hien co trong file: %d", SoLuongHocVien);

        InTieuDe("M4. TIM KIEM");
        int ChonTK = ChonMenu(7, MenuTK, 2, ThongTin);
        if (ChonTK == -1) return;

        // --- Menu cap 2: chon khoa ---
        const char* MenuKhoaTK[] = {
            "1. Ma lop",
            "2. Ma hoc vien",
            "3. Ho va ten",
            "4. Ngay sinh",
            "5. Diem trung binh tich luy"
        };

        char KyTuTK = '1' + ChonTK;
        sprintf_s(ThongTin, sizeof(ThongTin), "Thuat toan da chon: %c", KyTuTK);

        InTieuDe("M4. TIM KIEM - CHON KHOA");
        int ChonKhoaTK = ChonMenu(7, MenuKhoaTK, 5, ThongTin);
        if (ChonKhoaTK == -1) continue;

        // --- Nhap gia tri tim kiem ---
        char GiaTri[SoKyTuToiDaHoTen];
        char KhoaKyTu = '1' + ChonKhoaTK;

        InTieuDe("M4. TIM KIEM - NHAP GIA TRI");
        printf("Nhan ESC de huy.\n\n");

        if (!NhapDongCoEsc("Gia tri can tim: ", GiaTri, sizeof(GiaTri))) {
            continue;
        }

        InTieuDe("M4. TIM KIEM");
        printf("Da chon thuat toan %c, khoa %c, gia tri \"%s\".\n", KyTuTK, KhoaKyTu, GiaTri);
        printf("So hoc vien hien co trong file: %d\n", SoLuongHocVien);
        printf("Chuc nang tim kiem se hoan thien o tuan 4.\n");
        ChoPhimEscQuayLai();
    }
}

// M5: Xử lý menu thống kê (số lượng theo lớp / tỷ lệ xếp loại)
void XuLyMenuThongKe(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        char ThongTin[100];

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        const char* MenuTK[] = {
            "1. So luong sinh vien theo lop",
            "2. Ty le xep loai hoc tap theo lop"
        };

        sprintf_s(ThongTin, sizeof(ThongTin), "So hoc vien hien co trong file: %d", SoLuongHocVien);

        InTieuDe("M5. THONG KE");
        int Chon = ChonMenu(7, MenuTK, 2, ThongTin);
        if (Chon == -1) return;

        InTieuDe("M5. THONG KE");
        printf("Ban da chon muc %d.\n", Chon + 1);
        printf("So hoc vien hien co trong file: %d\n", SoLuongHocVien);
        printf("Chuc nang thong ke se hoan thien o tuan 5.\n");
        ChoPhimEscQuayLai();
    }
}

// Hàm chính: hiển thị menu chính và điều phối các chức năng
int main(void) {
    int DangChay = 1;
    const char* TenTepNhiPhan = "HocVien.dat";

    const char* MenuChinh[] = {
        "1. Them moi ho so (M1)",
        "2. In danh sach (M2)",
        "3. Sap xep (M3)",
        "4. Tim kiem (M4)",
        "5. Thong ke (M5)",
        "6. Thoat (M6)"
    };

    while (DangChay) {
        InTieuDe("MENU CHINH");

        int Chon = ChonMenu(6, MenuChinh, 6, NULL);
        switch (Chon) {
        case 0: XuLyThemHoSo(TenTepNhiPhan); break;
        case 1: XuLyMenuInDanhSach(TenTepNhiPhan); break;
        case 2: XuLyMenuSapXep(TenTepNhiPhan); break;
        case 3: XuLyMenuTimKiem(TenTepNhiPhan); break;
        case 4: XuLyMenuThongKe(TenTepNhiPhan); break;
        case 5: case -1: DangChay = 0; break;
        }
    }

    XoaManHinh();
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
