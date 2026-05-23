#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void XoaManHinh(void) {
    system("cls");
}

void InTieuDe(const char* TieuDe) {
    XoaManHinh();
    printf("========================================\n");
    printf(" CHUONG TRINH QUAN LY HOC VIEN - TUAN 2\n");
    printf("========================================\n");
    printf("%s\n", TieuDe);
    printf("----------------------------------------\n");
    printf("Nhan phim so de chon. Nhan ESC de quay lai.\n");
    printf("----------------------------------------\n");
}

void ChoPhimEscQuayLai(void) {
    int Phim;

    printf("\nNhan ESC de quay lai...");
    do {
        Phim = _getch();
    } while (Phim != 27);
}

void SaoChepChuoi(char* ChuoiDich, size_t KichThuocChuoiDich, const char* ChuoiNguon) {
    strncpy_s(ChuoiDich, KichThuocChuoiDich, ChuoiNguon, _TRUNCATE);
}

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

int LaNamNhuan(int Nam) {
    if (Nam % 400 == 0) {
        return 1;
    }
    if (Nam % 100 == 0) {
        return 0;
    }
    return Nam % 4 == 0;
}

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

void InNgaySinh(Date NgaySinh) {
    printf("%02d/%02d/%04d", NgaySinh.Ngay, NgaySinh.Thang, NgaySinh.Nam);
}

int ChuyenChuoiThanhSoNguyen(const char* Chuoi, int* GiaTri) {
    char KyTuThua;

    if (sscanf_s(Chuoi, "%d%c", GiaTri, &KyTuThua, 1) != 1) {
        return 0;
    }

    return 1;
}

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

int KiemTraTrungMaHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien, const char* MaHocVien) {
    int ViTri;

    for (ViTri = 0; ViTri < SoLuongHocVien; ViTri++) {
        if (strcmp(DanhSachHocVien[ViTri].MaHocVien, MaHocVien) == 0) {
            return 1;
        }
    }

    return 0;
}

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

int KiemTraDiemHopLe(const char* ChuoiDiem, float* Diem) {
    char KyTuThua;

    if (sscanf_s(ChuoiDiem, "%f%c", Diem, &KyTuThua, 1) != 1) {
        return 0;
    }

    return *Diem >= 0.0f && *Diem <= 4.0f;
}

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

void XuLyMenuInDanhSach(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        int Phim;

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        InTieuDe("M2. IN DANH SACH");
        printf("1. In toan bo danh sach\n");
        printf("2. In theo lop\n");
        printf("3. In theo ket qua sap xep/tim kiem\n");

        Phim = _getch();
        if (Phim == 27) {
            return;
        }

        if (Phim == '1') {
            InTieuDe("M2. IN TOAN BO DANH SACH");
            InBangHocVien(DanhSachHocVien, SoLuongHocVien);
            ChoPhimEscQuayLai();
        }

        if (Phim == '2') {
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

        if (Phim == '3') {
            InTieuDe("M2. IN THEO KET QUA SAP XEP/TIM KIEM");
            printf("Chuc nang nay se hoan thien o cac tuan sau.\n");
            ChoPhimEscQuayLai();
        }
    }
}

// ============================================================
// TUAN 3: CAC HAM SO SANH & SAP XEP
// ============================================================

int SoSanhTheoMaHocVien(HocVien A, HocVien B) {
    return strcmp(A.MaHocVien, B.MaHocVien) < 0;
}

int SoSanhTheoHoTen(HocVien A, HocVien B) {
    return strcmp(A.HoTen, B.HoTen) < 0;
}

int SoSanhTheoNgaySinh(HocVien A, HocVien B) {
    if (A.NgaySinh.Nam != B.NgaySinh.Nam)
        return A.NgaySinh.Nam < B.NgaySinh.Nam;
    if (A.NgaySinh.Thang != B.NgaySinh.Thang)
        return A.NgaySinh.Thang < B.NgaySinh.Thang;
    return A.NgaySinh.Ngay < B.NgaySinh.Ngay;
}

int SoSanhTheoDiemTrungBinhTichLuy(HocVien A, HocVien B) {
    return A.DiemTrungBinhTichLuy < B.DiemTrungBinhTichLuy;
}

int SoSanhHocVien(HocVien A, HocVien B, int Khoa) {
    switch (Khoa) {
    case '1': return SoSanhTheoMaHocVien(A, B);
    case '2': return SoSanhTheoHoTen(A, B);
    case '3': return SoSanhTheoNgaySinh(A, B);
    case '4': return SoSanhTheoDiemTrungBinhTichLuy(A, B);
    }
    return 0;
}

void HoanDoiHocVien(HocVien* A, HocVien* B) {
    HocVien Tam = *A;
    *A = *B;
    *B = Tam;
}

// Thuat toan 1: Sap xep chon (Selection Sort)
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

// Thuat toan 2: Sap xep chen (Insertion Sort)
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

// Thuat toan 3: Quicksort
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

void SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int ViTriChot = PhanHoach(DanhSach, Trai, Phai, Khoa);
        SapXepNhanh(DanhSach, Trai, ViTriChot - 1, Khoa);
        SapXepNhanh(DanhSach, ViTriChot + 1, Phai, Khoa);
    }
}

// Thuat toan 4: Mergesort
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

void SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa) {
    if (Trai < Phai) {
        int Giua = Trai + (Phai - Trai) / 2;
        SapXepTron(DanhSach, Trai, Giua, Khoa);
        SapXepTron(DanhSach, Giua + 1, Phai, Khoa);
        Tron(DanhSach, Trai, Giua, Phai, Khoa);
    }
}

const char* LayTenThuatToan(int ThuatToan) {
    switch (ThuatToan) {
    case '1': return "Sap xep chon (Selection Sort)";
    case '2': return "Sap xep chen (Insertion Sort)";
    case '3': return "Quicksort";
    case '4': return "Mergesort";
    }
    return "";
}

const char* LayTenKhoa(int Khoa) {
    switch (Khoa) {
    case '1': return "Ma hoc vien";
    case '2': return "Ho va ten";
    case '3': return "Ngay sinh";
    case '4': return "Diem trung binh tich luy";
    }
    return "";
}

void XuLyMenuSapXep(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        int ThuatToan;

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        if (SoLuongHocVien == 0) {
            InTieuDe("M3. SAP XEP");
            printf("Danh sach hoc vien dang rong, khong co gi de sap xep.\n");
            ChoPhimEscQuayLai();
            return;
        }

        InTieuDe("M3. SAP XEP");
        printf("So hoc vien hien co trong file: %d\n\n", SoLuongHocVien);
        printf("Chon thuat toan:\n");
        printf("1. Sap xep chon\n");
        printf("2. Sap xep chen\n");
        printf("3. Quicksort\n");
        printf("4. Mergesort\n");

        ThuatToan = _getch();
        if (ThuatToan == 27) {
            return;
        }

        if (ThuatToan >= '1' && ThuatToan <= '4') {
            int Khoa;

            InTieuDe("M3. SAP XEP - CHON KHOA");
            printf("Thuat toan da chon: %s\n\n", LayTenThuatToan(ThuatToan));
            printf("1. Ma hoc vien\n");
            printf("2. Ho va ten\n");
            printf("3. Ngay sinh\n");
            printf("4. Diem trung binh tich luy\n");

            Khoa = _getch();
            if (Khoa == 27) {
                continue;
            }

            if (Khoa >= '1' && Khoa <= '4') {
                InTieuDe("M3. SAP XEP - KET QUA");
                printf("Thuat toan: %s\n", LayTenThuatToan(ThuatToan));
                printf("Khoa sap xep: %s\n", LayTenKhoa(Khoa));
                printf("So hoc vien: %d\n\n", SoLuongHocVien);

                switch (ThuatToan) {
                case '1':
                    SapXepChon(DanhSachHocVien, SoLuongHocVien, Khoa);
                    break;
                case '2':
                    SapXepChen(DanhSachHocVien, SoLuongHocVien, Khoa);
                    break;
                case '3':
                    SapXepNhanh(DanhSachHocVien, 0, SoLuongHocVien - 1, Khoa);
                    break;
                case '4':
                    SapXepTron(DanhSachHocVien, 0, SoLuongHocVien - 1, Khoa);
                    break;
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
                        }
                        else {
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
    }
}

void XuLyMenuTimKiem(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        int ThuatToan;

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        InTieuDe("M4. TIM KIEM");
        printf("So hoc vien hien co trong file: %d\n\n", SoLuongHocVien);
        printf("Chon thuat toan tim kiem:\n");
        printf("1. Tim kiem tuan tu\n");
        printf("2. Tim kiem nhi phan\n");

        ThuatToan = _getch();
        if (ThuatToan == 27) {
            return;
        }

        if (ThuatToan >= '1' && ThuatToan <= '2') {
            int Khoa;

            InTieuDe("M4. TIM KIEM - CHON KHOA");
            printf("Thuat toan da chon: %c\n\n", ThuatToan);
            printf("1. Ma lop\n");
            printf("2. Ma hoc vien\n");
            printf("3. Ho va ten\n");
            printf("4. Ngay sinh\n");
            printf("5. Diem trung binh tich luy\n");

            Khoa = _getch();
            if (Khoa == 27) {
                continue;
            }

            if (Khoa >= '1' && Khoa <= '5') {
                char GiaTri[SoKyTuToiDaHoTen];

                InTieuDe("M4. TIM KIEM - NHAP GIA TRI");
                printf("Nhan ESC de huy.\n\n");

                if (!NhapDongCoEsc("Gia tri can tim: ", GiaTri, sizeof(GiaTri))) {
                    continue;
                }

                InTieuDe("M4. TIM KIEM");
                printf("Da chon thuat toan %c, khoa %c, gia tri \"%s\".\n", ThuatToan, Khoa, GiaTri);
                printf("So hoc vien hien co trong file: %d\n", SoLuongHocVien);
                printf("Chuc nang tim kiem se hoan thien o tuan 4.\n");
                ChoPhimEscQuayLai();
            }
        }
    }
}

void XuLyMenuThongKe(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien;
        int Phim;

        SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        InTieuDe("M5. THONG KE");
        printf("So hoc vien hien co trong file: %d\n\n", SoLuongHocVien);
        printf("1. So luong sinh vien theo lop\n");
        printf("2. Ty le xep loai hoc tap theo lop\n");

        Phim = _getch();
        if (Phim == 27) {
            return;
        }

        if (Phim >= '1' && Phim <= '2') {
            InTieuDe("M5. THONG KE");
            printf("Ban da chon muc %c.\n", Phim);
            printf("So hoc vien hien co trong file: %d\n", SoLuongHocVien);
            printf("Chuc nang thong ke se hoan thien o tuan 5.\n");
            ChoPhimEscQuayLai();
        }
    }
}

int main(void) {
    int DangChay = 1;
    const char* TenTepNhiPhan = "HocVien.dat";

    while (DangChay) {
        int Phim;

        InTieuDe("MENU CHINH");
        printf("1. Them moi ho so (M1)\n");
        printf("2. In danh sach (M2)\n");
        printf("3. Sap xep (M3)\n");
        printf("4. Tim kiem (M4)\n");
        printf("5. Thong ke (M5)\n");
        printf("6. Thoat (M6)\n");

        Phim = _getch();
        switch (Phim) {
        case '1':
            XuLyThemHoSo(TenTepNhiPhan);
            break;
        case '2':
            XuLyMenuInDanhSach(TenTepNhiPhan);
            break;
        case '3':
            XuLyMenuSapXep(TenTepNhiPhan);
            break;
        case '4':
            XuLyMenuTimKiem(TenTepNhiPhan);
            break;
        case '5':
            XuLyMenuThongKe(TenTepNhiPhan);
            break;
        case '6':
            DangChay = 0;
            break;
        case 27:
            DangChay = 0;
            break;
        default:
            break;
        }
    }

    XoaManHinh();
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
