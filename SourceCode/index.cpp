#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <cctype> //tolower() ham chuyen mot ki tu thanh chu thuong
#include <conio.h> //getch
#include <windows.h> //Sleep
#include <vector>

#define CLEARSCR system("cls")
#define PAUSE _getch()
#define SLEEP Sleep(500)

//check input <kiem tra dau vao co dung la mot so nguyen hay mot so thuc hay khong>
template <typename T>
T CheckNumber(T &a){
	while(true){
		if(std::cin.fail()){ // kiem tra dau vao bao loi hay khong
			std::cin.clear(); // xoa co thong bao loi
			std::cin.ignore(256,'\n'); // xoa toi da 256 ki tu cho den khi gap xuong dong '\n'
			std::cout << "[!]Khong hop le!" <<std::endl;
			std::cout << "Nhap lai: "; std::cin >> a;
		}
		if(!std::cin.fail()) break; // nguoc lai neu dau vao khong co loi thi thoat ham
	}
}
//check string <kiem tra 2 chuoi giong nhau khong phan biet hoa thuong>
bool CheckEquals(const std::string &a, const std::string &b){
    unsigned int size = a.size(); // lay ra do dai chuoi a
    if (b.size() != size) return false; // kiem tra do dai 2 chuoi neu khac nhau thi tra ve false
    for (int i = 0; i < size; i++){
        if (tolower(a[i]) != tolower(b[i])) return false; // duyet tung ki tu trong chuoi dua ve dang chu thuong roi so sanh, chi can mot ki tu khac thi tra ve false
    }   
return true;
}

//current time format
time_t now = time(NULL);
tm *t = localtime(&now);
int currentYear = 1900 + t->tm_year;

struct NgaySinh{
    int ngay, thang, nam;
};

struct MonHoc{
    std::string tenMH;
    int soTC;
    float diemMH;
};

class SinhVien{
protected:
    char maSV[15];
    std::string hoTen;
    NgaySinh ngaySinh;
    std::string queQuan;
    unsigned int namNhapHoc;
    std::string chuyenNganh;
public:
    SinhVien(){
        std::strcpy(this->maSV, "");
        this->hoTen = "";
        this->ngaySinh.ngay = this->ngaySinh.thang = this->ngaySinh.nam = 0;
        this->queQuan = "";
        this->namNhapHoc = 0;
        this->chuyenNganh = "";
    }
    ~SinhVien(){}

    // ham nhap-xuat thong tin 1 sinh vien
    virtual void NhapTT();
    virtual void XuatTT();

    #pragma region FunctionGet
    char *GetMSSV(){
        return maSV;
    }
    std::string GetTen(){
        return hoTen;
    }
    int GetNgaySinh(){
        return ngaySinh.ngay;
    }
    int GetThangSinh(){
        return ngaySinh.thang;
    }
    int GetNamSinh(){
        return ngaySinh.nam;
    }
    std::string GetQueQuan(){
        return queQuan;
    }
    unsigned int GetNamNH(){
        return namNhapHoc;
    }
    std::string GetChuyenNganh(){
        return chuyenNganh;
    }
    #pragma endregion

    #pragma region FunctionSet
    void SetMSSV(char *_maSV){
        std::strcpy(maSV, _maSV);
    }
    void SetSV(char *_maSV, std::string _hoTen, int ngay, int thang, int nam, std::string _queQuan, unsigned int _namNhapHoc, std::string _chuyenNganh){
        std::strcpy(maSV, _maSV);
        hoTen = _hoTen;
        ngaySinh.ngay = ngay;
        ngaySinh.thang = thang;
        ngaySinh.nam = nam;
        queQuan = _queQuan;
        namNhapHoc = _namNhapHoc;
        chuyenNganh = _chuyenNganh;
    }
    #pragma endregion
};

class TinhTrang:public SinhVien{
private:
    std::vector<MonHoc> dsMonHoc;
    unsigned int tongSoTC; // tong so tin chi cua nganh hoc
    unsigned int soTinDaDK; // so tin chi da dang ki
    unsigned int soTinHocLai; // so tin chi hoc lai
    unsigned int congNo; // cong no con lai cua sinh vien
    unsigned int soTinDat; // so tin chi da dat
public:
    TinhTrang():SinhVien(){
        this->tongSoTC = this->soTinDaDK = this->soTinHocLai = congNo = 0;
    }
    // ham check ten mon hoc giong nhau
    bool CheckTenMH(const std::string &_tenMH);

    // ham nhap-xuat tinh trang 1 sinh vien van dang theo hoc
    void NhapTT();
    void XuatTT();
    void XuatMH();

    #pragma region FunctionGet
    unsigned int GetTongTC(){
        return tongSoTC;
    }
    unsigned int GetSoTCDK(){
        return soTinDaDK;
    }
    unsigned int GetSoTCHL(){
        return soTinHocLai;
    }
    unsigned int GetCongNo(){
        return congNo;
    }
    unsigned int GetSoTCDat(){
        return soTinDat;
    }

    int GetSLMonHoc(){
        return dsMonHoc.size();
    }
    std::string GetTenMH(int i){
        return dsMonHoc[i].tenMH;
    }
    int GetSoTCMonHoc(int i){
        return dsMonHoc[i].soTC;
    }
    float GetDiemMonHoc(int i){
        return dsMonHoc[i].diemMH;
    }
    #pragma endregion
    
    #pragma region FunctionSet
    void SuaMonHoc(unsigned int &_tongTinDK);

    void SetSVDangHoc(char *_maSV, std::string _hoTen, int ngay, int thang, int nam,
                    std::string _queQuan, unsigned int _namNhapHoc, std::string _chuyenNganh,
                    unsigned int _tongSoTC, unsigned int _soTinDaDK, unsigned int _soTinHocLai, unsigned int _congNo){
        SinhVien::SetSV(_maSV, _hoTen, ngay, thang, nam, _queQuan, _namNhapHoc, _chuyenNganh);
        tongSoTC = _tongSoTC;
        soTinDaDK = _soTinDaDK;
        soTinHocLai = _soTinHocLai;
        congNo = _congNo;
    }

    void SetMH(MonHoc a){
        dsMonHoc.push_back(a);
    }
    #pragma endregion
};

class SVDaTotNghiep:public SinhVien{
private:
    unsigned int namTotNghiep;
    float diemTB;
public:
    SVDaTotNghiep():SinhVien(){
        this->namTotNghiep = 0;
        this->diemTB = 0;
    }
    // ham nhap-xuat thong tin 1 sinh vien da tot nghiep ra truong
    void NhapTT();
    void XuatTT();

    #pragma region FunctionGet
    unsigned int GetNamTN(){
        return namTotNghiep;
    }
    float GetDiemTB(){
        return diemTB;
    }
    #pragma endregion

    #pragma region FunctionSet
    void SetSVDTN(char *_maSV, std::string _hoTen, int ngay, int thang, int nam,
                    std::string _queQuan, unsigned int _namNhapHoc, std::string _chuyenNganh,
                    unsigned int _namTotNghiep, float _diemTB){
        SinhVien::SetSV(_maSV, _hoTen, ngay, thang, nam, _queQuan, _namNhapHoc, _chuyenNganh);
        namTotNghiep = _namTotNghiep;
        diemTB = _diemTB;
    }
    #pragma endregion
};

class QuanLySinhVien{
private:
    std::vector <TinhTrang> dsSinhVien;
    std::vector <SVDaTotNghiep> dsSinhVienTotNghiep;
public:
    static int checkSV;
    static int checkSVDTN;
    bool CheckMSSV(const char *_maSV);

// thao tac voi file 
    bool CheckEmpty(const char *tenFile);
    void DocFileSV();
    void DocFileSVDTN();
    void GhiFileSV();
    void GhiFileSVDTN();
    void DocFileMH();
    void GhiFileMH();
// ham nhap - xuat
    void ChuyenDoi(TinhTrang &a, SVDaTotNghiep &b);
    void NhapDS();
    void XuatDS_SV();
    void XuatDS_SVDTN();
    void XuatDS();
// ham chuc nang tim kiem
    void TimKiemTheoMSSV(const char *_maSV);
    void TimKiemTheoTen(const std::string _hoTen);
    void TimKiem();
// ham chuc nang sua
    void SuaTheoViTri();
    void SuaTheoMSSV();
    void Sua();
// ham chuc nang xoa
    void XoaTheoViTri();
    void XoaTheoMSSV();
    void Xoa();
};
int QuanLySinhVien::checkSV = 0;
int QuanLySinhVien::checkSVDTN = 0;
