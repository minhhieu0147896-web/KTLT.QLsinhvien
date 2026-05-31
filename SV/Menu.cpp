// ============================================================
// Menu.cpp - Cac ham xu ly menu: M1 Them, M2 In, M3 Sap xep, M4 Tim kiem, M5 Thong ke
// ============================================================

#include "CauTruc.h"

// M1: Xu ly them moi ho so hoc vien (nhap → xac nhan → luu file)
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

    if (!NhapDongCoEsc("Ma lop                : ", HocVienTam.MaLop, sizeof(HocVienTam.MaLop))) return;
    if (!NhapMaHocVienHopLe(HocVienTam.MaHocVien, sizeof(HocVienTam.MaHocVien), DanhSachHocVien, SoLuongHocVien)) return;
    if (!NhapHoTenChuanHoa("Ho va ten             : ", HocVienTam.HoTen, sizeof(HocVienTam.HoTen))) return;
    if (!NhapNgaySinhHopLe(&HocVienTam.NgaySinh)) return;
    if (!NhapDiemHopLe(&HocVienTam.DiemTrungBinhTichLuy)) return;

    printf("\nThong tin vua nhap:\n");
    printf("Ma lop      : %s\n", HocVienTam.MaLop);
    printf("Ma hoc vien : %s\n", HocVienTam.MaHocVien);
    printf("Ho va ten   : %s\n", HocVienTam.HoTen);
    printf("Ngay sinh   : "); InNgaySinh(HocVienTam.NgaySinh); printf("\n");
    printf("Diem TBTL   : %.2f\n", HocVienTam.DiemTrungBinhTichLuy);

    if (!XacNhanThemHocVien()) return;

    DanhSachHocVien[SoLuongHocVien] = HocVienTam;
    SoLuongHocVien++;

    if (GhiDanhSachVaoFile(TenTep, DanhSachHocVien, SoLuongHocVien))
        printf("\nDa them hoc vien va luu vao file nhi phan %s.\n", TenTep);
    else
        printf("\nKhong ghi duoc file nhi phan.\n");

    ChoPhimEscQuayLai();
}

// M2: Xu ly menu in danh sach (toan bo / theo lop / theo ket qua sap xep)
void XuLyMenuInDanhSach(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

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
            int SoLuongTimThay = 0;

            InTieuDe("M2. IN DANH SACH THEO LOP");
            if (!NhapDongCoEsc("Nhap ma lop: ", MaLopCanIn, sizeof(MaLopCanIn))) continue;

            printf("%-5s %-10s %-12s %-28s %-12s %s\n", "STT", "Ma lop", "Ma HV", "Ho ten", "Ngay sinh", "Diem");
            printf("-------------------------------------------------------------------------------\n");
            for (int i = 0; i < SoLuongHocVien; i++)
                if (strcmp(DanhSachHocVien[i].MaLop, MaLopCanIn) == 0) {
                    SoLuongTimThay++;
                    InMotHocVien(DanhSachHocVien[i], SoLuongTimThay);
                }
            if (SoLuongTimThay == 0) printf("Khong co hoc vien nao thuoc lop %s.\n", MaLopCanIn);
            ChoPhimEscQuayLai();
        }
        if (Chon == 2) {
            InTieuDe("M2. IN THEO KET QUA SAP XEP/TIM KIEM");
            printf("Chuc nang nay se hoan thien o cac tuan sau.\n");
            ChoPhimEscQuayLai();
        }
    }
}

// M3: Xu ly menu sap xep (chon thuat toan → chon khoa → sap xep → hoi luu)
void XuLyMenuSapXep(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);
        char ThongTin[100];

        if (SoLuongHocVien == 0) {
            InTieuDe("M3. SAP XEP");
            printf("Danh sach hoc vien dang rong, khong co gi de sap xep.\n");
            ChoPhimEscQuayLai();
            return;
        }

        // Menu cap 1: chon thuat toan
        const char* MenuThuatToan[] = { "1. Sap xep chon", "2. Sap xep chen", "3. Quicksort", "4. Mergesort" };
        sprintf_s(ThongTin, sizeof(ThongTin), "So hoc vien hien co trong file: %d", SoLuongHocVien);
        InTieuDe("M3. SAP XEP");
        int ChonTT = ChonMenu(7, MenuThuatToan, 4, ThongTin);
        if (ChonTT == -1) return;

        // Menu cap 2: chon khoa
        const char* MenuKhoa[] = { "1. Ma hoc vien", "2. Ho va ten", "3. Ngay sinh", "4. Diem trung binh tich luy" };
        char KhoaDaChon = '1' + ChonTT;
        sprintf_s(ThongTin, sizeof(ThongTin), "Thuat toan da chon: %s", LayTenThuatToan(KhoaDaChon));
        InTieuDe("M3. SAP XEP - CHON KHOA");
        int ChonKhoa = ChonMenu(7, MenuKhoa, 4, ThongTin);
        if (ChonKhoa == -1) continue;

        // Thuc hien sap xep
        char KhoaKey = '1' + ChonKhoa;
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
                if (GhiDanhSachVaoFile(TenTep, DanhSachHocVien, SoLuongHocVien))
                    printf("\nDa luu danh sach da sap xep vao file %s.\n", TenTep);
                else printf("\nLoi: Khong ghi duoc file.\n");
                break;
            }
            if (Phim == 27) { printf("\nKhong luu thay doi.\n"); break; }
        }
        ChoPhimEscQuayLai();
    }
}

// M4: Xu ly menu tim kiem (chon thuat toan → chon khoa → nhap gia tri tim)
void XuLyMenuTimKiem(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);
        char ThongTin[100];

        // Menu cap 1: chon thuat toan
        const char* MenuTK[] = { "1. Tim kiem tuan tu", "2. Tim kiem nhi phan" };
        sprintf_s(ThongTin, sizeof(ThongTin), "So hoc vien hien co trong file: %d", SoLuongHocVien);
        InTieuDe("M4. TIM KIEM");
        int ChonTK = ChonMenu(7, MenuTK, 2, ThongTin);
        if (ChonTK == -1) return;

        // Menu cap 2: chon khoa
        const char* MenuKhoaTK[] = { "1. Ma lop", "2. Ma hoc vien", "3. Ho va ten", "4. Ngay sinh", "5. Diem trung binh tich luy" };
        char KyTuTK = '1' + ChonTK;
        sprintf_s(ThongTin, sizeof(ThongTin), "Thuat toan da chon: %c", KyTuTK);
        InTieuDe("M4. TIM KIEM - CHON KHOA");
        int ChonKhoaTK = ChonMenu(7, MenuKhoaTK, 5, ThongTin);
        if (ChonKhoaTK == -1) continue;

        // Nhap gia tri tim kiem
        char GiaTri[SoKyTuToiDaHoTen];
        char KhoaKyTu = '1' + ChonKhoaTK;
        InTieuDe("M4. TIM KIEM - NHAP GIA TRI");
        printf("Nhan ESC de huy.\n\n");
        if (!NhapDongCoEsc("Gia tri can tim: ", GiaTri, sizeof(GiaTri))) continue;

        // Thuc hien tim kiem
        HocVien KetQua[SoLuongHocVienToiDa];
        int SoKetQua = 0;
        if (ChonTK == 0) TimKiemTuanTu(DanhSachHocVien, SoLuongHocVien, GiaTri, KhoaKyTu, KetQua, &SoKetQua);
        else TimKiemNhiPhan(DanhSachHocVien, SoLuongHocVien, GiaTri, KhoaKyTu, KetQua, &SoKetQua);

        // Hien thi ket qua
        const char* TenThuatToan[] = { "Tim kiem tuan tu", "Tim kiem nhi phan" };
        const char* TenKhoa[] = { "Ma lop", "Ma hoc vien", "Ho va ten", "Ngay sinh", "Diem TBTL" };
        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: %s\n", TenThuatToan[ChonTK]);
        printf("Khoa       : %s\n", TenKhoa[ChonKhoaTK]);
        printf("Gia tri    : %s\n", GiaTri);
        printf("Ket qua    : tim thay %d hoc vien\n\n", SoKetQua);
        if (SoKetQua > 0) InBangHocVien(KetQua, SoKetQua);
        else printf("Khong tim thay hoc vien nao khop.\n");
        ChoPhimEscQuayLai();
    }
}

// M5: Xu ly menu thong ke (so luong theo lop / ty le xep loai)
void XuLyMenuThongKe(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);
        char ThongTin[100];

        const char* MenuTK[] = { "1. So luong sinh vien theo lop", "2. Ty le xep loai hoc tap theo lop" };
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
