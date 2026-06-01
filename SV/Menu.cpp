// ============================================================
// Menu.cpp - Cac ham xu ly menu: M1 Them, M2 In, M3 Sap xep, M4 Tim kiem, M5 Thong ke
// ============================================================

#include "CauTruc.h"

// M1: Xu ly them moi ho so hoc vien (nhap -> xac nhan -> luu file)
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

// M2: Xu ly menu in danh sach (toan bo / theo lop)
void XuLyMenuInDanhSach(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        const char* MenuIn[] = {
            "1. In toan bo danh sach",
            "2. In theo lop"
        };

        InTieuDe("M2. IN DANH SACH");
        int Chon = ChonMenu(6, MenuIn, 2, NULL);
        if (Chon <= 0) return;

        if (Chon == 1) {
            InTieuDe("M2. IN TOAN BO DANH SACH");
            InBangHocVien(DanhSachHocVien, SoLuongHocVien);
            ChoPhimEscQuayLai();
        }
        if (Chon == 2) {
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
    }
}

// M3: Xu ly menu sap xep (chon thuat toan -> chon khoa -> sap xep -> hoi luu)
void XuLyMenuSapXep(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        if (SoLuongHocVien == 0) {
            InTieuDe("M3. SAP XEP");
            printf("Danh sach hoc vien dang rong, khong co gi de sap xep.\n");
            ChoPhimEscQuayLai();
            return;
        }

        // Menu cap 1: chon thuat toan
        const char* MenuThuatToan[] = { "1. Sap xep chon", "2. Sap xep chen", "3. Quicksort", "4. Mergesort" };
        InTieuDe("M3. SAP XEP");
        printf("  So hoc vien hien co trong file: %d\n", SoLuongHocVien);
        int ChonTT = ChonMenu(7, MenuThuatToan, 4, NULL);
        if (ChonTT <= 0) return;

        // Menu cap 2: chon khoa
        const char* TenTT[] = { "Sap xep chon", "Sap xep chen", "Quicksort", "Mergesort" };
        const char* TenKhoaArr[] = { "Ma hoc vien", "Ho va ten", "Ngay sinh", "Diem TBTL" };
        const char* MenuKhoa[] = { "1. Ma hoc vien", "2. Ho va ten", "3. Ngay sinh", "4. Diem trung binh tich luy" };
        int ViTriTT = ChonTT - 1;
        InTieuDe("M3. SAP XEP - CHON KHOA");
        printf("  Thuat toan da chon: %s\n", TenTT[ViTriTT]);
        int ChonKhoa = ChonMenu(7, MenuKhoa, 4, NULL);
        if (ChonKhoa <= 0) continue;

        // Thuc hien sap xep
        int ViTriKhoa = ChonKhoa - 1;
        int KhoaKey = KHOA_MA_HOC_VIEN + ViTriKhoa;
        InTieuDe("M3. SAP XEP - KET QUA");
        printf("Thuat toan: %s\n", TenTT[ViTriTT]);
        printf("Khoa sap xep: %s\n", TenKhoaArr[ViTriKhoa]);
        printf("So hoc vien: %d\n\n", SoLuongHocVien);

        switch (ChonTT) {
        case 1: SapXepChon(DanhSachHocVien, SoLuongHocVien, KhoaKey); break;
        case 2: SapXepChen(DanhSachHocVien, SoLuongHocVien, KhoaKey); break;
        case 3: SapXepNhanh(DanhSachHocVien, 0, SoLuongHocVien - 1, KhoaKey); break;
        case 4: SapXepTron(DanhSachHocVien, 0, SoLuongHocVien - 1, KhoaKey); break;
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

static int NhapNgayCanTim(int* Ngay) {
    while (1) {
        if (!NhapSoNguyenCoEsc("Nhap ngay (1-31): ", Ngay)) return 0;
        if (*Ngay >= 1 && *Ngay <= 31) return 1;
        printf("Ngay phai nam trong khoang 1 den 31. Vui long nhap lai.\n");
    }
}

static int NhapThangCanTim(int* Thang) {
    while (1) {
        if (!NhapSoNguyenCoEsc("Nhap thang (1-12): ", Thang)) return 0;
        if (*Thang >= 1 && *Thang <= 12) return 1;
        printf("Thang phai nam trong khoang 1 den 12. Vui long nhap lai.\n");
    }
}

static int NhapNamCanTim(int* Nam) {
    while (1) {
        if (!NhapSoNguyenCoEsc("Nhap nam: ", Nam)) return 0;
        if (*Nam >= 1900 && *Nam <= 2026) return 1;
        printf("Nam phai nam trong khoang 1900 den 2026. Vui long nhap lai.\n");
    }
}

static int NhapNgaySinhDayDuCanTim(Date* NgaySinh) {
    while (1) {
        printf("Nhap ngay sinh can tim:\n");
        if (!NhapNgayCanTim(&NgaySinh->Ngay)) return 0;
        if (!NhapThangCanTim(&NgaySinh->Thang)) return 0;
        if (!NhapNamCanTim(&NgaySinh->Nam)) return 0;

        if (KiemTraNgayThangNamHopLe(*NgaySinh)) return 1;
        printf("Ngay/thang/nam khong ton tai tren lich. Vui long nhap lai.\n");
    }
}

static void XuLyTimKiemTheoNgaySinh(HocVien DanhSachHocVien[], int SoLuongHocVien,
                                    int ChonTK, const char* TenThuatToan) {
    const char* MenuNgaySinh[] = {
        "1. Tim dung ngay/thang/nam",
        "2. Tim theo ngay trong thang",
        "3. Tim theo thang sinh",
        "4. Tim theo nam sinh",
        "5. Tim theo ngay va thang"
    };

    HocVien KetQua[SoLuongHocVienToiDa];
    int SoKetQua = 0;
    int ChonNgaySinh;

    InTieuDe("M4. TIM KIEM THEO NGAY SINH");
    printf("  Cac muc 2-5 loc theo tung phan cua ngay sinh.\n");
    ChonNgaySinh = ChonMenu(8, MenuNgaySinh, 5, NULL);
    if (ChonNgaySinh <= 0) return;

    InTieuDe("M4. TIM KIEM THEO NGAY SINH");

    if (ChonNgaySinh == 1) {
        Date NgaySinhCanTim;
        if (!NhapNgaySinhDayDuCanTim(&NgaySinhCanTim)) return;

        if (ChonTK == 1)
            TimKiemTuanTuTheoNgaySinh(DanhSachHocVien, SoLuongHocVien, NgaySinhCanTim, KetQua, &SoKetQua);
        else
            TimKiemNhiPhanTheoNgaySinh(DanhSachHocVien, SoLuongHocVien, NgaySinhCanTim, KetQua, &SoKetQua);

        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: %s\n", TenThuatToan);
        printf("Kieu tim   : Dung ngay/thang/nam\n");
        printf("Gia tri    : ");
        InNgaySinh(NgaySinhCanTim);
        printf("\n");
    } else if (ChonNgaySinh == 2) {
        int Ngay;
        if (!NhapNgayCanTim(&Ngay)) return;
        TimKiemTheoNgayTrongThang(DanhSachHocVien, SoLuongHocVien, Ngay, KetQua, &SoKetQua);

        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: Tim kiem tuan tu\n");
        printf("Kieu tim   : Theo ngay trong thang\n");
        printf("Gia tri    : ngay %d\n", Ngay);
    } else if (ChonNgaySinh == 3) {
        int Thang;
        if (!NhapThangCanTim(&Thang)) return;
        TimKiemTheoThangSinh(DanhSachHocVien, SoLuongHocVien, Thang, KetQua, &SoKetQua);

        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: Tim kiem tuan tu\n");
        printf("Kieu tim   : Theo thang sinh\n");
        printf("Gia tri    : thang %d\n", Thang);
    } else if (ChonNgaySinh == 4) {
        int Nam;
        if (!NhapNamCanTim(&Nam)) return;
        TimKiemTheoNamSinh(DanhSachHocVien, SoLuongHocVien, Nam, KetQua, &SoKetQua);

        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: Tim kiem tuan tu\n");
        printf("Kieu tim   : Theo nam sinh\n");
        printf("Gia tri    : nam %d\n", Nam);
    } else {
        int Ngay;
        int Thang;
        if (!NhapNgayCanTim(&Ngay)) return;
        if (!NhapThangCanTim(&Thang)) return;
        TimKiemTheoNgayVaThang(DanhSachHocVien, SoLuongHocVien, Ngay, Thang, KetQua, &SoKetQua);

        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: Tim kiem tuan tu\n");
        printf("Kieu tim   : Theo ngay va thang\n");
        printf("Gia tri    : ngay %d, thang %d\n", Ngay, Thang);
    }

    printf("Ket qua    : tim thay %d hoc vien\n\n", SoKetQua);
    if (SoKetQua > 0)
        InBangHocVien(KetQua, SoKetQua);
    else
        printf("Khong tim thay hoc vien nao khop.\n");
    ChoPhimEscQuayLai();
}

// M4: Xu ly menu tim kiem (chon thuat toan -> chon khoa -> nhap gia tri tim)
void XuLyMenuTimKiem(const char* TenTep) {
    while (1) {
        HocVien DanhSachHocVien[SoLuongHocVienToiDa];
        int SoLuongHocVien = DocDanhSachTuFile(TenTep, DanhSachHocVien, SoLuongHocVienToiDa);

        // Menu cap 1: chon thuat toan
        const char* MenuTK[] = { "1. Tim kiem tuan tu", "2. Tim kiem nhi phan" };
        InTieuDe("M4. TIM KIEM");
        printf("  So hoc vien hien co trong file: %d\n", SoLuongHocVien);
        int ChonTK = ChonMenu(7, MenuTK, 2, NULL);
        if (ChonTK <= 0) return;

        // Menu cap 2: chon khoa
        const char* MenuKhoaTK[] = { "1. Ma lop", "2. Ma hoc vien", "3. Ho va ten", "4. Ngay sinh", "5. Diem trung binh tich luy" };
        const char* TenThuatToan[] = { "Tim kiem tuan tu", "Tim kiem nhi phan" };
        int ViTriTK = ChonTK - 1;
        InTieuDe("M4. TIM KIEM - CHON KHOA");
        printf("  Thuat toan da chon: %s\n", TenThuatToan[ViTriTK]);
        int ChonKhoaTK = ChonMenu(7, MenuKhoaTK, 5, NULL);
        if (ChonKhoaTK <= 0) continue;

        // Nhap gia tri tim kiem
        char GiaTri[SoKyTuToiDaHoTen];
        int ViTriKhoaTK = ChonKhoaTK - 1;
        int KhoaTimKiem = KHOA_MA_LOP + ViTriKhoaTK;

        if (KhoaTimKiem == KHOA_NGAY_SINH) {
            XuLyTimKiemTheoNgaySinh(DanhSachHocVien, SoLuongHocVien, ChonTK, TenThuatToan[ViTriTK]);
            continue;
        }

        InTieuDe("M4. TIM KIEM - NHAP GIA TRI");
        printf("Nhan ESC de huy.\n\n");
        if (!NhapDongCoEsc("Gia tri can tim: ", GiaTri, sizeof(GiaTri))) continue;

        // Thuc hien tim kiem
        HocVien KetQua[SoLuongHocVienToiDa];
        int SoKetQua = 0;
        if (ChonTK == 1) TimKiemTuanTu(DanhSachHocVien, SoLuongHocVien, GiaTri, KhoaTimKiem, KetQua, &SoKetQua);
        else TimKiemNhiPhan(DanhSachHocVien, SoLuongHocVien, GiaTri, KhoaTimKiem, KetQua, &SoKetQua);

        // Hien thi ket qua
        const char* TenKhoa[] = { "Ma lop", "Ma hoc vien", "Ho va ten", "Ngay sinh", "Diem TBTL" };
        InTieuDe("M4. TIM KIEM - KET QUA");
        printf("Thuat toan: %s\n", TenThuatToan[ViTriTK]);
        printf("Khoa       : %s\n", TenKhoa[ViTriKhoaTK]);
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

        const char* MenuTK[] = { "1. So luong sinh vien theo lop", "2. Ty le xep loai hoc tap theo lop" };
        InTieuDe("M5. THONG KE");
        printf("  So hoc vien hien co trong file: %d\n", SoLuongHocVien);
        int Chon = ChonMenu(7, MenuTK, 2, NULL);
        if (Chon <= 0) return;

        InTieuDe("M5. THONG KE");
        if (Chon == 1)
            ThongKeSoLuongTheoLop(DanhSachHocVien, SoLuongHocVien);
        else
            ThongKeXepLoaiTheoLop(DanhSachHocVien, SoLuongHocVien);
        ChoPhimEscQuayLai();
    }
}
