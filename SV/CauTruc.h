// ============================================================
// CauTruc.h - Hang so, cau truc du lieu & khai bao nguyen mau ham
// ============================================================

#ifndef CAU_TRUC_H
#define CAU_TRUC_H

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ============================================================
// CAC HANG SO
// ============================================================
#define SoKyTuToiDaMaLop       20
#define SoKyTuToiDaMaHocVien   20
#define SoKyTuToiDaHoTen       100
#define SoLuongHocVienToiDa    200

// Mau sac
#define MAU_MAC_DINH      7
#define MAU_TIEU_DE       14
#define MAU_VIEN           3
#define MAU_DONG_CHON     112
#define MAU_THANH_CONG    10
#define MAU_LOI            4

// ============================================================
// CAU TRUC DU LIEU
// ============================================================
typedef struct {
    int Ngay, Thang, Nam;
} Date;

typedef struct {
    char MaLop[SoKyTuToiDaMaLop];
    char MaHocVien[SoKyTuToiDaMaHocVien];
    char HoTen[SoKyTuToiDaHoTen];
    Date NgaySinh;
    float DiemTrungBinhTichLuy;
} HocVien;

// ============================================================
// TIEN ICH (TienIch.cpp)
// ============================================================
HANDLE LayConsole();
void   DatMauSac(int Mau);
void   DatMauMacDinh();
void   GotoXY(int X, int Y);
void   XoaManHinh();
void   InTieuDe(const char* TieuDe);
void   ChoPhimEscQuayLai();
int    ChonMenu(int DongBatDau, const char* CacLuaChon[], int SoLuong, const char* ThongTinBoSung);

int    NhapDongCoEsc(const char* Nhan, char* BoDem, int KichThuoc);
int    NhapHoTenChuanHoa(const char* Nhan, char* BoDem, int KichThuoc);
int    NhapSoNguyenCoEsc(const char* Nhan, int* GiaTri);
int    NhapNgaySinhHopLe(Date* NgaySinh);
int    NhapMaHocVienHopLe(char* MaHocVien, int KichThuoc, HocVien DanhSach[], int SoLuong);
int    NhapDiemHopLe(float* Diem);
int    XacNhanThemHocVien();
int    LaNamNhuan(int Nam);

void   InNgaySinh(Date NgaySinh);
void   InMotHocVien(HocVien HV, int STT);
void   InBangHocVien(HocVien DanhSach[], int SoLuong);

// ============================================================
// DU LIEU (DuLieu.cpp)
// ============================================================
int    DocDanhSachTuFile(const char* TenTep, HocVien DanhSach[], int ToiDa);
int    GhiDanhSachVaoFile(const char* TenTep, HocVien DanhSach[], int SoLuong);

// ============================================================
// SAP XEP (SapXep.cpp) - 4 thuat toan
// ============================================================
int    SoSanhHocVien(HocVien A, HocVien B, int Khoa);
void   SapXepChon(HocVien DanhSach[], int SoLuong, int Khoa);
void   SapXepChen(HocVien DanhSach[], int SoLuong, int Khoa);
void   SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa);
void   SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa);

// ============================================================
// TIM KIEM (TimKiem.cpp) - 2 thuat toan
// ============================================================
void   TimKiemTuanTu(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua);
void   TimKiemNhiPhan(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua);

// ============================================================
// MENU (Menu.cpp)
// ============================================================
void   XuLyThemHoSo(const char* TenTep);
void   XuLyMenuInDanhSach(const char* TenTep);
void   XuLyMenuSapXep(const char* TenTep);
void   XuLyMenuTimKiem(const char* TenTep);
void   XuLyMenuThongKe(const char* TenTep);

#endif
