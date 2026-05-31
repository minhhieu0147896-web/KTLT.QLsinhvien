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
#define MAU_MAC_DINH      7    // Trang tren den
#define MAU_TIEU_DE       14   // Vang tren den
#define MAU_VIEN           3   // Xanh cyan tren den
#define MAU_DONG_CHON     112  // Den tren trang (dao nguoc)
#define MAU_THANH_CONG    10   // Xanh la tren den
#define MAU_LOI            4   // Do tren den

// ============================================================
// CAU TRUC DU LIEU
// ============================================================
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

// ============================================================
// KHAI BAO NGUYEN MAU HAM - TIEN ICH (TienIch.cpp)
// ============================================================
HANDLE LayConsole();
void   DatMauSac(int Mau);
void   DatMauMacDinh();
void   GotoXY(int X, int Y);
void   InDongKhung(const char* NoiDung, int MauChu);
void   InDuongKeNgang(char KyTuGocTrai, char KyTuNoi, char KyTuGocPhai);
void   XoaManHinh();
void   InTieuDe(const char* TieuDe);
void   ChoPhimEscQuayLai();
int    ChonMenu(int DongBatDau, const char* CacLuaChon[], int SoLuong, const char* ThongTinBoSung);
void   SaoChepChuoi(char* ChuoiDich, size_t KichThuocChuoiDich, const char* ChuoiNguon);

// Nhap lieu & kiem tra
int    NhapDongCoEsc(const char* Nhan, char* BoDem, int KichThuoc);
int    NhapHoTenChuanHoa(const char* Nhan, char* BoDem, int KichThuoc);
int    LaNamNhuan(int Nam);
int    KiemTraNgaySinhHopLe(Date NgaySinh);
void   InNgaySinh(Date NgaySinh);
int    ChuyenChuoiThanhSoNguyen(const char* Chuoi, int* GiaTri);
int    NhapSoNguyenCoEsc(const char* Nhan, int* GiaTri);
int    NhapNgaySinhHopLe(Date* NgaySinh);
int    KiemTraMaHocVienHopLe(const char* MaHocVien);
int    KiemTraTrungMaHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien, const char* MaHocVien);
int    NhapMaHocVienHopLe(char* MaHocVien, int KichThuoc, HocVien DanhSachHocVien[], int SoLuongHocVien);
int    KiemTraDiemHopLe(const char* ChuoiDiem, float* Diem);
int    NhapDiemHopLe(float* Diem);
int    XacNhanThemHocVien();

// In an
void   InMotHocVien(HocVien ThongTinHocVien, int SoThuTu);
void   InBangHocVien(HocVien DanhSachHocVien[], int SoLuongHocVien);

// ============================================================
// KHAI BAO NGUYEN MAU HAM - DU LIEU (DuLieu.cpp)
// ============================================================
int    DocDanhSachTuFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongToiDa);
int    GhiDanhSachVaoFile(const char* TenTep, HocVien DanhSachHocVien[], int SoLuongHocVien);

// ============================================================
// KHAI BAO NGUYEN MAU HAM - SAP XEP (SapXep.cpp)
// ============================================================
int    SoSanhTheoMaHocVien(HocVien A, HocVien B);
int    SoSanhTheoHoTen(HocVien A, HocVien B);
int    SoSanhTheoNgaySinh(HocVien A, HocVien B);
int    SoSanhTheoDiemTrungBinhTichLuy(HocVien A, HocVien B);
int    SoSanhHocVien(HocVien A, HocVien B, int Khoa);
void   HoanDoiHocVien(HocVien* A, HocVien* B);
void   SapXepChon(HocVien DanhSach[], int SoLuong, int Khoa);
void   SapXepChen(HocVien DanhSach[], int SoLuong, int Khoa);
int    PhanHoach(HocVien DanhSach[], int Trai, int Phai, int Khoa);
void   SapXepNhanh(HocVien DanhSach[], int Trai, int Phai, int Khoa);
void   Tron(HocVien DanhSach[], int Trai, int Giua, int Phai, int Khoa);
void   SapXepTron(HocVien DanhSach[], int Trai, int Phai, int Khoa);
const char* LayTenThuatToan(int ThuatToan);
const char* LayTenKhoa(int Khoa);

// ============================================================
// KHAI BAO NGUYEN MAU HAM - TIM KIEM (TimKiem.cpp)
// ============================================================
int    SoSanhTimKiem(HocVien HV, const char* GiaTri, int Khoa);
void   TimKiemTuanTu(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua);
void   TimKiemNhiPhan(HocVien DanhSach[], int SoLuong, const char* GiaTri, int Khoa, HocVien KetQua[], int* SoKetQua);

// ============================================================
// KHAI BAO NGUYEN MAU HAM - MENU (Menu.cpp)
// ============================================================
void   XuLyThemHoSo(const char* TenTep);
void   XuLyMenuInDanhSach(const char* TenTep);
void   XuLyMenuSapXep(const char* TenTep);
void   XuLyMenuTimKiem(const char* TenTep);
void   XuLyMenuThongKe(const char* TenTep);

#endif // CAU_TRUC_H
