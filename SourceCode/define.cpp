#include "index.cpp"

#define Chon "\n[!] Moi nhap lua chon: "
#define conLai "\n[!] Khong co chuc nang nay. Thu lai!"

#pragma region ClassSinhVien
// dinh nghia ham thanh phan cua class SinhVien
void TitleSinhVien(){
    std::cout <<char(179)<<std::setw(5)<<std::left<< "STT"
        <<"\t"<<std::setw(15)<<std::left<< "MSSV"
        <<"\t"<<std::setw(30)<<std::left<< "Ho Ten"
        <<"\t"<<std::setw(10)<<std::left<< "Ngay Sinh"
        <<"\t"<<std::setw(30)<<std::left<< "Que Quan"
        <<"\t"<<std::setw(12)<<std::left<< "Nam Nhap Hoc"
        <<"\t"<<std::setw(15)<<std::left<< "Chuyen Nganh";
}

void SinhVien::NhapTT(){
    fflush(stdin);
    std::cout << "Nhap ho ten cua sinh vien: "; std::getline(std::cin, hoTen);
    std::cout << "Nhap ngay thang nam sinh cua sinh vien: " <<std::endl;
    
    //Kiem tra ngay-thang-nam sinh cua sinh vien co hop le hay khong
    do{
        std::cout << "- Ngay: "; std::cin >> ngaySinh.ngay;
            if (ngaySinh.ngay <= 0 || ngaySinh.ngay > 31) std::cout << "[!]Ngay sinh khong hop le." <<std::endl;
            else{
                do{
                    std::cout << "- Thang: "; std::cin >> ngaySinh.thang;
                    if(ngaySinh.thang <= 0 || ngaySinh.thang > 12) std::cout << "[!]Thang sinh khong hop le." <<std::endl;
                    else if(ngaySinh.thang == 2 && (ngaySinh.ngay == 30 || ngaySinh.ngay == 31)) std::cout << "[!]Thang 2 khong co "<< ngaySinh.ngay <<" ngay." <<std::endl;
                } while ((ngaySinh.thang <= 0 || ngaySinh.thang > 12) || (ngaySinh.thang == 2 && (ngaySinh.ngay == 30 || ngaySinh.ngay == 31)));
                CheckNumber(ngaySinh.thang); 
            }
        } while (ngaySinh.ngay <= 0 || ngaySinh.ngay > 31);
        CheckNumber(ngaySinh.ngay);
    do{
        std::cout << "- Nam: "; std::cin >> ngaySinh.nam;
        CheckNumber(ngaySinh.nam);
        if (ngaySinh.nam <= 0 || currentYear - ngaySinh.nam >= 90 || currentYear - ngaySinh.nam <= 0) std::cout << "[!] Nhap lai." <<std::endl;
    } while (ngaySinh.nam <= 0 || currentYear - ngaySinh.nam >= 90 || currentYear - ngaySinh.nam <= 0);
    
    fflush(stdin);
    std::cout << "Nhap que quan cua sinh vien: "; std::getline(std::cin, queQuan);
    do{
        std::cout << "Nhap nam nhap hoc cua sinh vien: "; std::cin >> namNhapHoc;
        CheckNumber(namNhapHoc);
        if (namNhapHoc <= 1900) std::cout << "[!] Nhap lai." <<std::endl;
    } while (namNhapHoc <= 1900);
    fflush(stdin);
    std::cout << "Nhap chuyen nganh cua sinh vien: "; std::getline(std::cin, chuyenNganh);
}

void SinhVien::XuatTT(){
    std::cout <<"\t"<<std::setw(15)<<std::left<< maSV
        <<"\t"<<std::setw(30)<<std::left<< hoTen
        <<"\t"<< ngaySinh.ngay <<"/"<< ngaySinh.thang <<"/"<< ngaySinh.nam
        <<"\t"<<std::setw(30)<<std::left<< queQuan
        <<"\t"<<std::setw(12)<<std::left<< namNhapHoc
        <<"\t"<<std::setw(15)<<std::left<< chuyenNganh;
}
#pragma endregion

#pragma region ClassTinhTrang
// dinh nghia cac ham thanh phan cua class TinhTrang
void TitleTinhTrang(){
    std::cout << char(218);
    for (int i = 0; i < 207; i++){
        std::cout << char(196);
    }
    std::cout << char(191) <<std::endl;
    TitleSinhVien();
    std::cout <<"\t"<<std::setw(12)<<std::left<< "Tong Tin Chi"
        <<"\t"<<std::setw(18)<<std::left<< "So Tin Chi Dang Ky"
        <<"\t"<<std::setw(18)<<std::left<< "So Tin Chi Hoc Lai"
        <<"\t"<<std::setw(8)<<std::left<< "Cong No" <<char(179)<<std::endl;
    std::cout << char(195);
    for (int i = 0; i < 207; i++){
        std::cout << char(196);
    }
    std::cout << char(180)<<std::endl;
}

void TitleMonHoc(){
    std::cout << char(218);
    for (int i = 0; i < 55; i++){
        std::cout << char(196);
    }
    std::cout << char(191) <<std::endl;
    std::cout <<char(179)<<std::setw(30)<<std::left<< "Ten Mon Hoc"
        <<"\t"<<std::setw(10)<<std::left<< "So Tin Chi"
        <<"\t"<<std::setw(8)<<std::left<< "Diem TB" <<char(179)<<std::endl;
    std::cout << char(195);
    for (int i = 0; i < 55; i++){
        std::cout << char(196);
    }
    std::cout << char(180)<<std::endl;
}

bool TinhTrang::CheckTenMH(const std::string &_tenMH){
    for (int i = 0; i < dsMonHoc.size(); i++){
        if (CheckEquals(dsMonHoc[i].tenMH, _tenMH) == true) return true;
    }
return false;
}

void TinhTrang::NhapTT(){
    unsigned int tongTinDK = 0;
    SinhVien::NhapTT();
    soTinDaDK = soTinDat = soTinHocLai = 0;
    MonHoc a;
    std::string chon;
    
    do{
        std::cout << "Nhap tong so tin chi doi voi nganh hoc: "; std::cin >> tongSoTC;
        if (tongSoTC <= 0) std::cout << "[!] Nhap lai." <<std::endl;
    } while (tongSoTC <= 0);

    do{
        std::cout << "Nhap cong no con lai cua sinh vien: "; std::cin >> congNo;
        if (congNo < 0) std::cout << "[!] Nhap lai." <<std::endl;
    } while (congNo < 0);
    
    std::cout << "Nhap danh sach mon hoc cua sinh vien:" <<std::endl; 
    do{
        fflush(stdin);
        do{
            std::cout << "Nhap ten mon hoc: "; std::getline(std::cin, a.tenMH);
            if (CheckTenMH(a.tenMH) == true) std::cout << "\n[!] Mon hoc da ton tai." <<std::endl;
        } while(CheckTenMH(a.tenMH) == true);
        
        do{
            std::cout << "Nhap so tin chi cua mon hoc: "; std::cin >> a.soTC;
            CheckNumber(a.soTC);
            if (a.soTC <= 0) std::cout << "\n[!] Nhap lai." <<std::endl;
        } while(a.soTC <= 0);
        tongTinDK += a.soTC;
        
        do{
            std::cout << "Nhap diem mon hoc: "; std::cin >> a.diemMH;
            CheckNumber(a.diemMH);
            if (a.diemMH < 0) std::cout << "\n[!] Nhap lai." <<std::endl;
        } while(a.diemMH < 0);

        do{
            fflush(stdin);
            std::cout << "Ban co muon nhap them mon hoc cho sinh vien (y/n)?"; std::getline(std::cin ,chon);
            if (CheckEquals(chon, "y") != true && CheckEquals(chon, "n") != true) std::cout << "[!] Nhap lai!" <<std::endl;
        } while(CheckEquals(chon, "y") != true && CheckEquals(chon, "n") != true);
        dsMonHoc.push_back(a);
    } while(CheckEquals(chon, "y") == true);
    
    while(tongTinDK > tongSoTC){
        std::cout << "\n[!] Loi...Tong so tin chi cac mon dang ki dang vuot qua so tin chi cua nganh hoc." <<std::endl;
        std::cout << "Ban can kiem tra va sua lai danh sach mon hoc." <<std::endl;

        std::cout << "\n\n\tDANH SACH MON HOC CUA SINH VIEN MSSV: " << maSV <<std::endl;
        
        TitleMonHoc();
        XuatMH();
        std::cout << char(192);
        for (int i = 0; i < 55; i++){
            std::cout << char(196);
        }
        std::cout << char(217)<<std::endl;
        SuaMonHoc(tongTinDK);
    }

    for (int i = 0; i < dsMonHoc.size(); i++){
        soTinDaDK += dsMonHoc[i].soTC;
    }
    
    for (int i = 0; i < dsMonHoc.size(); i++){
        if (dsMonHoc[i].diemMH <= 5.4) soTinHocLai += dsMonHoc[i].soTC;
    }

    for (int i = 0; i < dsMonHoc.size(); i++){
        if (dsMonHoc[i].diemMH > 5.4) soTinDat += dsMonHoc[i].soTC;
    }
    
}

void TinhTrang::SuaMonHoc(unsigned int &_tongTinDK){
    std::string _tenMH;
    int _soTinMH;
    float _diemMH;
    int viTri;
    bool checkTrue = false;
    do{
        fflush(stdin);
        std::cout << "\nNhap ten mon hoc muon sua: "; std::getline(std::cin, _tenMH);
        for (int i = 0; i < dsMonHoc.size(); i++){
            if (CheckEquals(_tenMH, dsMonHoc[i].tenMH) == true){
                checkTrue = true;
                viTri = i;
            }
        }
        if (checkTrue == false) std::cout << "\n[!] Khong co mon hoc: " << _tenMH << " trong danh sach." <<std::endl;
    } while(checkTrue == false);
    _tongTinDK -= dsMonHoc[viTri].soTC;

    do{
        fflush(stdin);
        std::cout << "Nhap lai ten mon hoc: "; std::getline(std::cin, _tenMH);
        if (_tenMH == dsMonHoc[viTri].tenMH) break;
        else {
            if (CheckTenMH(_tenMH) == true) std::cout << "\n[!] Mon hoc da ton tai." <<std::endl;
        }
    } while(CheckTenMH(_tenMH) == true);

    do{
        std::cout << "Nhap so tin chi cua mon hoc: "; std::cin >> _soTinMH;
        CheckNumber(_soTinMH);
        if (_soTinMH <= 0) std::cout << "\n[!] Nhap lai." <<std::endl;
    } while(_soTinMH <= 0);
    _tongTinDK += _soTinMH;
        
    do{
        std::cout << "Nhap diem mon hoc: "; std::cin >> _diemMH;
        CheckNumber(_diemMH);
        if (_diemMH < 0) std::cout << "\n[!] Nhap lai." <<std::endl;
    } while(_diemMH < 0);

    dsMonHoc[viTri].tenMH = _tenMH;
    dsMonHoc[viTri].soTC = _soTinMH;
    dsMonHoc[viTri].diemMH = _diemMH;
}

void TinhTrang::XuatTT(){
    SinhVien::XuatTT();
    std::cout <<"\t"<<std::setw(12)<<std::left<< tongSoTC
        <<"\t"<<std::setw(18)<<std::left<< soTinDaDK
        <<"\t"<<std::setw(18)<<std::left<< soTinHocLai
        <<"\t"<<std::setw(8)<<std::left<< congNo <<char(179)<<std::endl;
}

void TinhTrang::XuatMH(){
    for (int i = 0; i < dsMonHoc.size(); i++){
        std::cout <<char(179)<<std::setw(30)<<std::left<< dsMonHoc[i].tenMH
            <<"\t"<<std::setw(10)<<std::left<< dsMonHoc[i].soTC
            <<"\t"<<std::setw(8)<<std::left<< dsMonHoc[i].diemMH <<char(179)<<std::endl;
    }
    
}
#pragma endregion

#pragma region ClassSinhVienDTN
// dinh nghia cac ham thanh phan cua class sinh vien da tot nghiep
void TitleSVDTN(){
    std::cout << char(218);
    for (int i = 0; i < 158; i++){
        std::cout << char(196);
    }
    std::cout << char(191) <<std::endl;
    TitleSinhVien();
    std::cout <<"\t"<<std::setw(14)<<std::left<< "Nam Tot Nghiep"
        <<"\t"<<std::setw(7)<<std::left<< "Diem TB" <<char(179)<<std::endl;
    std::cout << char(195);
    for (int i = 0; i < 158; i++){
        std::cout << char(196);
    }
    std::cout << char(180)<<std::endl;
}

void SVDaTotNghiep::NhapTT(){
    SinhVien::NhapTT();
    do{
        std::cout << "Nhap nam tot nghiep cua sinh vien: "; std::cin >> namTotNghiep;
        CheckNumber(namTotNghiep);
        if (currentYear - namTotNghiep >= 10 || currentYear - namTotNghiep < 0) std::cout << "[!] Nhap lai." <<std::endl;
    } while (currentYear - namTotNghiep >= 10 || currentYear - namTotNghiep < 0);
    do{
        std::cout << "Nhap diem TB cua sinh vien: "; std::cin >> diemTB;
        CheckNumber(diemTB);
        if (diemTB < 0) std::cout << "[!] Nhap lai." <<std::endl;
    } while (diemTB < 0);
}

void SVDaTotNghiep::XuatTT(){
    SinhVien::XuatTT();
    std::cout <<"\t"<<std::setw(14)<<std::left<< namTotNghiep
        <<"\t"<<std::setw(7)<<std::left<< diemTB <<char(179)<<std::endl;
}
#pragma endregion

// dinh nghia cac ham thanh phan cua class QuanLySV
#pragma region ThaoTacFile-Nhap-Xuat
/*MSSV khong the trung nhau giua cac sinh vien nen ham sau se kiem tra duyet ca 2 mang sinh vien gom
sinh vien dang theo hoc va ca sinh vien da tot nghiep de kiem tra neu MSSV da ton tai thi tra ve 'true'
con khong thi tra ve 'false'*/
bool QuanLySinhVien::CheckMSSV(const char *_maSV){
    if (dsSinhVien.size() == 0 && dsSinhVienTotNghiep.size() == 0) return false; // Neu 2 mang 1 chieu cac sinh vien trong thi tra ve 'false'
    for (int i = 0; i < dsSinhVien.size(); i++){
        if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) return true;
    }
    for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
        if (std::strcmp(dsSinhVienTotNghiep[i].GetMSSV(), _maSV) == 0) return true;
    }
return false;
}

void QuanLySinhVien::ChuyenDoi(TinhTrang &a, SVDaTotNghiep &b){
    float tongDiemTB = 0;
    for (int i = 0; i < a.GetSLMonHoc(); i++){
        tongDiemTB += a.GetDiemMonHoc(i);
    }
    float diemTB;
    diemTB = tongDiemTB / a.GetSLMonHoc();
    
    b.SetSVDTN(a.GetMSSV(), a.GetTen(), a.GetNgaySinh(), a.GetThangSinh(), a.GetNamSinh(), a.GetQueQuan(), 
    a.GetNamNH(), a.GetChuyenNganh(), currentYear, diemTB);
}

void QuanLySinhVien::NhapDS(){
    TinhTrang a;
    SVDaTotNghiep b;
    char _maSV[15];
    int chon;
    do{
        CLEARSCR;
        std::cout << "---------------------MENU NHAP THONG TIN SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Nhap thong tin sinh vien van theo hoc." <<std::endl;
        std::cout << "\t2. Nhap thong tin sinh vien da ra truong." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            CLEARSCR;
            std::cout << "\nNhap thong sinh vien dang theo hoc" <<std::endl;
            
            // Nhap MSSV rieng de co the kiem tra MSSV nay co trung voi MSSV cua sinh vien khac trong danh sach co san hay khong
            do {
                fflush(stdin);
                std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
            } while(CheckMSSV(_maSV) == true);
            a.NhapTT(); // Nhap giu lieu cua 1 sinh vien dang theo hoc vao doi tuong a
            a.SetMSSV(_maSV); // truyen MSSV da kiem tra ben tren vao doi tuong a

            if (a.GetSoTCDat() == a.GetTongTC()){
                std::string chon1;
                do{
                    fflush(stdin);
                    std::cout << "Sinh vien da hoc du so tin chi cua chuyen nganh. Ban co muon chuyen sinh vien nay qua danh sach sinh vien da tot nghiep khong (y/n)?"; std::getline(std::cin ,chon1);
                    if (CheckEquals(chon1, "y") != true && CheckEquals(chon1, "n") != true) std::cout << "[!] Nhap lai!" <<std::endl;
                } while(CheckEquals(chon1, "y") != true && CheckEquals(chon1, "n") != true);
                if (CheckEquals(chon1, "y") == true){
                    ChuyenDoi(a, b);
                    dsSinhVienTotNghiep.push_back(b);
                }
                else dsSinhVien.push_back(a);
            }
            else dsSinhVien.push_back(a); // Day doi tuong a vao vector mang mot chieu cac sinh vien dang theo hoc
            SLEEP;
            std::cout << "[!] Nhap xong..." <<std::endl;
            PAUSE;
            break;
        case 2:
            CLEARSCR;
            std::cout << "\nNhap thong sinh vien da tot nghiep" <<std::endl;
            // tuong tu dong 188
            do {
                fflush(stdin);
                std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
            } while(CheckMSSV(_maSV) == true);
            b.NhapTT(); // Nhap du lieu cho mot sinh vien da tot nghiep vao doi tuong b
            b.SetMSSV(_maSV); // truyen MSSV da kiem tra ben tren vao doi tuong b
            dsSinhVienTotNghiep.push_back(b); // Day doi tuong b vao vector mang mot chieu cac sinh vien da tot nghiep
            SLEEP;
            std::cout << "[!] Nhap xong..." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << conLai <<std::endl;
            break;
        }
        CLEARSCR;
    } while (chon != 0);
}

// kiem tra file co dang rong hay khong
bool QuanLySinhVien::CheckEmpty(const char *tenFile){
    int length;
    std::ifstream fileOut;
	fileOut.open(tenFile, std::ios_base::binary); // mo file o che do nhi phan
    fileOut.seekg(0, std::ios::end); // xac dinh vi tri n byte bat dau tu cuoi cua fileOut
    length = fileOut.tellg(); // Xem con tro file o dau, byte tinh theo moi byte 1 ky tu va luu vao bien length
    // kiem tra neu length == 0 thi tuc la file dang trong va tra ve 'true' con lai tra ve 'false'
    if (length == 0){
        return true;
    }
    else{
        return false;
    }
}

// dinh nghia phan doc file sinh vien dang theo hoc
void QuanLySinhVien::DocFileSV(){
    if (CheckEmpty("SinhVienDangHoc.txt") == false){ // kiem tra file chua thong tin sinh vien dang hoc co trong hay khong
        checkSV = 1;
        std::ifstream fileOut;
	    fileOut.open("SinhVienDangHoc.txt", std::ios_base::in); // mo file voi thao tac doc du lieu sinh vien dang theo hoc
        while (!fileOut.eof()){
            TinhTrang a;
            char _maSV[15];
            std::string _hoTen;
            int ngay, thang, nam;
            std::string _queQuan;
            unsigned int _namNhapHoc;
            std::string _chuyenNganh;
            unsigned int _tongSoTC, _soTinDaDK, _soTinHocLai, _congNo;
            fileOut.getline(_maSV, 15, ',');
            fileOut.ignore(1);
            std::getline(fileOut, _hoTen, ',');
            fileOut.ignore(1);
            fileOut >> ngay;
            fileOut.ignore(1);
            fileOut >> thang;
            fileOut.ignore(1);
            fileOut >> nam;
            fileOut.ignore(2);
            std::getline(fileOut, _queQuan, ',');
            fileOut.ignore(1);
            fileOut >> _namNhapHoc;
            fileOut.ignore(2);
            std::getline(fileOut, _chuyenNganh, ',');
            fileOut.ignore(1);
            fileOut >> _tongSoTC;
            fileOut.ignore(1);
            fileOut >> _soTinDaDK;
            fileOut.ignore(1);
            fileOut >> _soTinHocLai;
            fileOut.ignore(1);
            fileOut >> _congNo;
            fileOut.ignore(1);
            a.SetSVDangHoc(_maSV, _hoTen, ngay, thang, nam, _queQuan, _namNhapHoc, _chuyenNganh, _tongSoTC, _soTinDaDK, _soTinHocLai, _congNo);
            if (std::strcmp(a.GetMSSV(), "")) dsSinhVien.push_back(a);
        }
        fileOut.close();
    }
}

void QuanLySinhVien::XuatDS_SV(){
    std::string chon;
    std::cout << "\n\n\t\t\t\t\t\t\t\t\tDANH SACH SINH VIEN DANG THEO HOC DA LUU\n" <<std::endl;
    TitleTinhTrang();
    for (int i = 0; i < dsSinhVien.size(); i++){
        std::cout <<char(179)<< i+1;
        dsSinhVien[i].XuatTT();
    }
    std::cout << char(192);
    for (int i = 0; i < 207; i++){
        std::cout << char(196);
    }
    std::cout << char(217)<<std::endl;
    do{
        do{
            fflush(stdin);
            std::cout << "Ban co muon xem thong tin mon hoc cua sinh vien (y/n)?"; std::getline(std::cin ,chon);
            if (CheckEquals(chon, "y") != true && CheckEquals(chon, "n") != true) std::cout << "[!] Nhap lai!" <<std::endl;
        } while(CheckEquals(chon, "y") != true && CheckEquals(chon, "n") != true);
        if (CheckEquals(chon, "y") == true){
            CLEARSCR;
            char _maSV[15];
            bool checkMSSV = false;
            do{
                fflush(stdin);
                std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                for (int i = 0; i < dsSinhVien.size(); i++){
                    if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) checkMSSV = true;
                }
                if (checkMSSV == false) std::cout << "[!] Trong danh sach chua co sinh vien co MSSV la " << _maSV <<std::endl;
            } while(checkMSSV == false);
            
            std::cout << "\n\n\tDANH SACH MON HOC CUA SINH VIEN MSSV: " << _maSV <<std::endl;
            TitleMonHoc();
            for (int i = 0; i < dsSinhVien.size(); i++){
                if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0){
                    dsSinhVien[i].XuatMH();
                }
            }
                
            std::cout << char(192);
            for (int i = 0; i < 55; i++){
                std::cout << char(196);
            }
            std::cout << char(217)<<std::endl;
        }
        else if (CheckEquals(chon, "n") == true) std::cout << "\n[!] Nhan phim bat ki." <<std::endl;
    } while(CheckEquals(chon, "y") == true);

}

//dinh nghia phan doc file sinh vien da tot nghiep
void QuanLySinhVien::DocFileSVDTN(){
    if (CheckEmpty("SinhVienDaTotNghiep.txt") == false){ // kiem tra file sinh vien da tot nghiep co trong hay khong
        checkSVDTN = 2;
        std::ifstream fileOut;
	    fileOut.open("SinhVienDaTotNghiep.txt", std::ios_base::in); // mo file voi thao tac doc du lieu sinh vien da tot nghiep
        while (!fileOut.eof()){
            SVDaTotNghiep a;
            char _maSV[15];
            std::string _hoTen;
            int ngay, thang, nam;
            std::string _queQuan;
            unsigned int _namNhapHoc;
            std::string _chuyenNganh;
            unsigned int _namTotNghiep;
            float _diemTB;
            fileOut.getline(_maSV, 15, ',');
            fileOut.ignore(1);
            std::getline(fileOut, _hoTen, ',');
            fileOut.ignore(1);
            fileOut >> ngay;
            fileOut.ignore(1);
            fileOut >> thang;
            fileOut.ignore(1);
            fileOut >> nam;
            fileOut.ignore(2);
            std::getline(fileOut, _queQuan, ',');
            fileOut.ignore(1);
            fileOut >> _namNhapHoc;
            fileOut.ignore(2);
            std::getline(fileOut, _chuyenNganh, ',');
            fileOut.ignore(1);
            fileOut >> _namTotNghiep;
            fileOut.ignore(1);
            fileOut >> _diemTB;
            fileOut.ignore(1);
            a.SetSVDTN(_maSV, _hoTen, ngay, thang, nam, _queQuan, _namNhapHoc, _chuyenNganh, _namTotNghiep, _diemTB);
            if (std::strcmp(a.GetMSSV(), "")) dsSinhVienTotNghiep.push_back(a);
        }
        fileOut.close();
    }
}

void QuanLySinhVien::XuatDS_SVDTN(){
    std::cout << "\n\n\t\t\t\t\t\t\t\t\tDANH SACH SINH VIEN DA TOT NGHIEP DA LUU\n" <<std::endl;
    TitleSVDTN();
    for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
        std::cout <<char(179)<< i+1;
        dsSinhVienTotNghiep[i].XuatTT();
    }
    std::cout << char(192);
    for (int i = 0; i < 158; i++){
        std::cout << char(196);
    }
    std::cout << char(217)<<std::endl;
}
// dinh nghia phan thao tac file MonHoc
void QuanLySinhVien::DocFileMH(){
    if (CheckEmpty("MonHoc.txt") == false){ // kiem tra file chua thong tin mon hoc co trong hay khong
        char _maSV[15];
        std::ifstream fileOut;
	    fileOut.open("MonHoc.txt", std::ios_base::in); // mo file voi thao tac doc du lieu cac mon hoc cua sinh vien dang theo hoc
        while (!fileOut.eof()){
            fileOut.getline(_maSV, 15, ',');
            fileOut.ignore(1);
            int n, viTri;
            for (int i = 0; i < dsSinhVien.size(); i++){
                if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) viTri = i;
            }
            fileOut >> n;
            fileOut.ignore(2);
            for (int i = 0; i < n; i++){
                MonHoc a;
                std::getline(fileOut, a.tenMH, ',');
                fileOut.ignore(1);
                fileOut >> a.soTC;
                fileOut.ignore(1);
                fileOut >> a.diemMH;
                fileOut.ignore(2);
                dsSinhVien[viTri].SetMH(a);
            }
            fileOut.ignore(1);
        }
        fileOut.close();
    }
}

void QuanLySinhVien::XuatDS(){
    int chon;
    do {
        CLEARSCR;
        std::cout << "---------------------MENU HIEN THI THONG TIN SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Hien thi danh sach sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Hien thi danh sach sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            if (checkSV == 1) XuatDS_SV();
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        case 2:
            if (checkSVDTN == 2) XuatDS_SVDTN();
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    } while (chon != 0);
}

// dinh nghia phan ghi file sinh vien dang theo hoc
void QuanLySinhVien::GhiFileSV(){
    std::ofstream fileIn;
    fileIn.open("SinhVienDangHoc.txt", std::ios::out); // mo file sinh vien voi thao tac ghi du lieu vao file .txt
    for (int i = 0; i < dsSinhVien.size(); i++){
        fileIn << dsSinhVien[i].GetMSSV() << ", ";
        fileIn << dsSinhVien[i].GetTen() << ", ";
        fileIn << dsSinhVien[i].GetNgaySinh() <<"/"<< dsSinhVien[i].GetThangSinh() <<"/"<< dsSinhVien[i].GetNamSinh() << ", ";
        fileIn << dsSinhVien[i].GetQueQuan() << ", ";
        fileIn << dsSinhVien[i].GetNamNH() << ", ";
        fileIn << dsSinhVien[i].GetChuyenNganh() << ", ";
        fileIn << dsSinhVien[i].GetTongTC() << ", ";
        fileIn << dsSinhVien[i].GetSoTCDK() << ", ";
        fileIn << dsSinhVien[i].GetSoTCHL() << ", ";
        fileIn << dsSinhVien[i].GetCongNo() <<std::endl;
    }
    fileIn.close();
}

// dinh nghia phan ghi file sinh vien da tot nghiep
void QuanLySinhVien::GhiFileSVDTN(){
    std::ofstream fileIn;
    fileIn.open("SinhVienDaTotNghiep.txt", std::ios::out);  // mo file sinh vien da tot nghiep voi thao tac ghi du lieu vao file .txt
    for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
        fileIn << dsSinhVienTotNghiep[i].GetMSSV() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetTen() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetNgaySinh() <<"/"<< dsSinhVienTotNghiep[i].GetThangSinh() <<"/"<< dsSinhVienTotNghiep[i].GetNamSinh() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetQueQuan() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetNamNH() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetChuyenNganh() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetNamTN() << ", ";
        fileIn << dsSinhVienTotNghiep[i].GetDiemTB() <<std::endl;
    }
    fileIn.close();
}

// dinh nghia phan ghi file mon hoc
void QuanLySinhVien::GhiFileMH(){
    int length = dsSinhVien.size();
    std::ofstream fileIn;
    fileIn.open("MonHoc.txt", std::ios::out);  // mo file mon hoc voi thao tac ghi du lieu vao file .txt
    for (int i = 0; i < length - 1; i++){
        fileIn << dsSinhVien[i].GetMSSV() << ", ";
        fileIn << dsSinhVien[i].GetSLMonHoc() << ", ";
        for (int j = 0; j < dsSinhVien[i].GetSLMonHoc(); j++){
            fileIn << dsSinhVien[i].GetTenMH(j) << ", ";
            fileIn << dsSinhVien[i].GetSoTCMonHoc(j) << ", ";
            fileIn << dsSinhVien[i].GetDiemMonHoc(j) << ", ";
        }
        fileIn <<std::endl;
    }
    fileIn << dsSinhVien[length - 1].GetMSSV() << ", ";
    fileIn << dsSinhVien[length - 1].GetSLMonHoc() << ", ";
    for (int j = 0; j < dsSinhVien[length - 1].GetSLMonHoc(); j++){
        fileIn << dsSinhVien[length - 1].GetTenMH(j) << ", ";
        fileIn << dsSinhVien[length - 1].GetSoTCMonHoc(j) << ", ";
        fileIn << dsSinhVien[length - 1].GetDiemMonHoc(j) << ",";
    }
    fileIn.close();
}
#pragma endregion

#pragma region ChucNangTimKiem
// dinh nghia cac ham thanh phan cua chuc nang tim kiem thong tin sinh vien
void QuanLySinhVien::TimKiemTheoMSSV(const char *_maSV){
    int chon;
    bool check = false; 
    do{
        CLEARSCR;
        std::cout << "\t1. Tim kiem theo MSSV dang theo hoc." <<std::endl;
        std::cout << "\t2. Tim kiem theo MSSV da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            for (int i = 0; i < dsSinhVien.size(); i++){
                if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) check = true;
            }
            if (check == true){
                std::cout << "\n\n\t\t\t\t\t\t\t\t\tSINH VIEN DANG THEO HOC CO MSSV: " << _maSV <<std::endl;
                TitleTinhTrang();
                for (int i = 0; i < dsSinhVien.size(); i++){
                    if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0){
                        std::cout <<char(179)<< i+1;
                        dsSinhVien[i].XuatTT();
                    }
                }
                std::cout << char(192);
                for (int i = 0; i < 207; i++){
                    std::cout << char(196);
                }
                std::cout << char(217)<<std::endl;
                check = false;
            }
            else std::cout << "\n[!] Khong co sinh vien co MSSV: " << _maSV << " trong danh sach." <<std::endl;
            PAUSE;
            break;
        case 2:
            for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                if (std::strcmp(dsSinhVienTotNghiep[i].GetMSSV(), _maSV) == 0) check = true;
            }
            if (check == true){
                std::cout << "\n\n\t\t\t\t\t\t\t\t\tSINH VIEN DA TOT NGHIEP CO MSSV: " << _maSV <<std::endl;
                TitleSVDTN();
                for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                    if (std::strcmp(dsSinhVienTotNghiep[i].GetMSSV(), _maSV) == 0){
                        std::cout <<char(179)<< i+1;
                        dsSinhVienTotNghiep[i].XuatTT();
                    }
                }
                std::cout << char(192);
                for (int i = 0; i < 158; i++){
                    std::cout << char(196);
                }
                std::cout << char(217)<<std::endl;
                check = false;
            }
            else std::cout << "\n[!] Khong co sinh vien da tot nghiep co MSSV: " << _maSV << " trong danh sach." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    } while(chon != 0);
}

void QuanLySinhVien::TimKiemTheoTen(const std::string _hoTen){
    int chon;
    bool check = false;
    do{
        CLEARSCR;
        std::cout << "\t1. Tim kiem theo ho ten sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Tim kiem theo theo ho ten sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            for (int i = 0; i < dsSinhVien.size(); i++){
                if (CheckEquals(dsSinhVien[i].GetTen(), _hoTen) == true) check = true;
            }
            if (check == true){
                std::cout << "\n\n\t\t\t\t\t\t\t\t\tSINH VIEN DANG THEO HOC CO TEN: " << _hoTen <<std::endl;
                TitleTinhTrang();
                for (int i = 0; i < dsSinhVien.size(); i++){
                    if (CheckEquals(dsSinhVien[i].GetTen(), _hoTen) == true){
                        std::cout <<char(179)<< i+1;
                        dsSinhVien[i].XuatTT();
                    }
                }
                std::cout << char(192);
                for (int i = 0; i < 207; i++){
                    std::cout << char(196);
                }
                std::cout << char(217)<<std::endl;
                check = false;
            }
            else std::cout << "\n[!] Khong co sinh vien co ten: " << _hoTen << " trong danh sach sinh vien." <<std::endl;
            PAUSE;
            break;
        case 2:
            for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                if (CheckEquals(dsSinhVienTotNghiep[i].GetTen(), _hoTen) == true) check = true;
            }
            if (check == true){
                std::cout << "\n\n\t\t\t\t\t\t\t\t\tSINH VIEN DA TOT NGHIEP CO TEN: " << _hoTen <<std::endl;
                TitleSVDTN();
                for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                    if (CheckEquals(dsSinhVienTotNghiep[i].GetTen(), _hoTen) == true){
                        std::cout <<char(179)<< i+1;
                        dsSinhVienTotNghiep[i].XuatTT();
                    }
                }
                std::cout << char(192);
                for (int i = 0; i < 158; i++){
                    std::cout << char(196);
                }
                std::cout << char(217)<<std::endl;
                check = false;
            }
            else std::cout << "\n[!] Khong co sinh vien co ten: " << _hoTen << " trong danh sach sinh vien da tot nghiep." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    } while(chon != 0);
}

void QuanLySinhVien::TimKiem(){
    int chon, chon1;
    char _maSV[15];
    std::string _hoTen;
    do{
        CLEARSCR;
        std::cout << "---------------------MENU TIM KIEM THONG TIN SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Tim kiem theo ma so sinh vien." <<std::endl;
        std::cout << "\t2. Tim kiem theo ten sinh vien." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            fflush(stdin);
            std::cout << "Nhap ma so sinh vien muon tim kiem: "; std::cin.getline(_maSV, 15);
            TimKiemTheoMSSV(_maSV);
            break;
        case 2:
            fflush(stdin);
            std::cout << "Nhap ho ten sinh vien muon tim kiem: "; std::getline(std::cin, _hoTen);
            TimKiemTheoTen(_hoTen);
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    } while (chon != 0);
}
#pragma endregion

#pragma region ChucNangSua
// dinh nghia ham thanh phan cua chuc nang sua thong tin sinh vien
void QuanLySinhVien::SuaTheoViTri(){
    int viTri, chon;
    char _maSV[15];
    bool check = false;
    do{
        CLEARSCR;
        std::cout << "\n---------------------SUA THONG TIN SINH VIEN THEO VI TRI---------------------" <<std::endl;
        std::cout << "\t1. Sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:        
            if (checkSV == 1){
                CLEARSCR;
                XuatDS_SV();
                do{
                    std::cout << "Nhap STT sinh vien muon sua thong tin: "; std::cin >> viTri;
                    CheckNumber(viTri);
                    if (viTri <= 0 || viTri > dsSinhVien.size()) std::cout << "\n[!] Nhap lai STT." <<std::endl;
                }while (viTri <= 0 || viTri > dsSinhVien.size());
                std::cout << "\nNhap lai thong tin sinh vien" <<std::endl;
                do {
                    fflush(stdin);
                    std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                    if (std::strcmp(dsSinhVien[viTri-1].GetMSSV(), _maSV) == 0) check = true;
                    else{
                        if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
                        else check = true;
                    }
                } while(check == false);
                TinhTrang a;
                a.SetMSSV(_maSV);
                a.NhapTT();
                dsSinhVien[viTri-1] = a;
                SLEEP;
                std::cout << "\n[!] Da sua lai thong tin sinh vien." <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        case 2:        
            if (checkSVDTN == 2){
                CLEARSCR;
                XuatDS_SVDTN();
                do{
                    std::cout << "Nhap STT sinh vien muon sua thong tin: "; std::cin >> viTri;
                    CheckNumber(viTri);
                    if (viTri <= 0 || viTri > dsSinhVienTotNghiep.size()) std::cout << "\n[!] Nhap lai STT." <<std::endl;
                }while (viTri <= 0 || viTri > dsSinhVienTotNghiep.size());
                std::cout << "\nNhap lai thong tin sinh vien" <<std::endl;
                do {
                    fflush(stdin);
                    std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                    if (std::strcmp(dsSinhVienTotNghiep[viTri-1].GetMSSV(), _maSV) == 0) check = true;
                    else{
                        if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
                        else check = true;
                    }
                } while(check == false);
                SVDaTotNghiep a;
                a.SetMSSV(_maSV);
                a.NhapTT();
                dsSinhVienTotNghiep[viTri-1] = a;
                SLEEP;
                std::cout << "\n[!] Da sua lai thong tin sinh vien." <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien da tot nghiep bi trong." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << "\n[!] Khong co chuc nang nay." <<std::endl;
            PAUSE;
            break;
        }
    }while(chon != 0);
}

void QuanLySinhVien::SuaTheoMSSV(){
    int chon, viTri;
    char _maSV[15];
    bool check = false;
    do{
        CLEARSCR;
        std::cout << "\n---------------------SUA THONG TIN SINH VIEN THEO MSSV---------------------" <<std::endl;
        std::cout << "\t1. Sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:        
            if (checkSV == 1){
                CLEARSCR;
                XuatDS_SV();
                do{
                    fflush(stdin);
                    std::cout << "Nhap MSSV sinh vien muon sua thong tin: "; std::cin.getline(_maSV, 15);
                    if (CheckMSSV(_maSV) == false) std::cout << "\n[!] Khong co sinh vien co MSSV la " << _maSV <<std::endl;
                }while (CheckMSSV(_maSV) == false);

                for (int i = 0; i < dsSinhVien.size(); i++){
                    if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) viTri = i;
                }

                std::cout << "\nNhap lai thong tin sinh vien" <<std::endl;
                do {
                    fflush(stdin);
                    std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                    if (std::strcmp(dsSinhVien[viTri].GetMSSV(), _maSV) == 0) check = true;
                    else{
                        if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
                        else check = true;
                    }
                } while(check == false);
                TinhTrang a;
                a.SetMSSV(_maSV);
                a.NhapTT();
                dsSinhVien[viTri] = a;
                SLEEP;
                std::cout << "\n[!] Da sua lai thong tin sinh vien." <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        case 2:        
            if (checkSVDTN == 2){
                CLEARSCR;
                XuatDS_SVDTN();
                do{
                    fflush(stdin);
                    std::cout << "Nhap MSSV sinh vien muon sua thong tin: "; std::cin.getline(_maSV, 15);
                    if (CheckMSSV(_maSV) == false) std::cout << "\n[!] Khong co sinh vien co MSSV la " << _maSV <<std::endl;
                }while (CheckMSSV(_maSV) == false);

                for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                    if (std::strcmp(dsSinhVienTotNghiep[i].GetMSSV(), _maSV) == 0) viTri = i;
                }

                std::cout << "\nNhap lai thong tin sinh vien" <<std::endl;
                do {
                    fflush(stdin);
                    std::cout << "Nhap MSSV cua sinh vien: "; std::cin.getline(_maSV, 15);
                    if (std::strcmp(dsSinhVienTotNghiep[viTri].GetMSSV(), _maSV) == 0) check = true;
                    else{
                        if (CheckMSSV(_maSV) == true) std::cout << "[!] MSSV da ton tai." <<std::endl;
                        else check = true;
                    }
                } while(check == false);
                SVDaTotNghiep a;
                a.SetMSSV(_maSV);
                a.NhapTT();
                dsSinhVienTotNghiep[viTri] = a;
                SLEEP;
                std::cout << "\n[!] Da sua lai thong tin sinh vien." <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien da tot nghiep bi trong." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << "\n[!] Khong co chuc nang nay." <<std::endl;
            PAUSE;
            break;
        }
    }while(chon != 0);
}

void QuanLySinhVien::Sua(){
    int chon;
    do{
        CLEARSCR;
        std::cout << "---------------------MENU SUA THONG TIN SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Sua thong tin sinh vien theo vi tri." <<std::endl;
        std::cout << "\t2. Sua thong tin sinh vien theo MSSV." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            SuaTheoViTri();
            break;
        case 2:
            SuaTheoMSSV();
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    }while (chon != 0);
}
#pragma endregion

#pragma region ChucNangXoa
// dinh nghia ham thanh phan cua chuc nang xoa thong tin sinh vien
void QuanLySinhVien::XoaTheoViTri(){
    int chon, viTri;
    do{
        CLEARSCR;
        std::cout << "\n---------------------XOA SINH VIEN THEO MSSV---------------------" <<std::endl;
        std::cout << "\t1. Sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            if (checkSV == 1){
                CLEARSCR;
                XuatDS_SV();
                do{
                    std::cout << "Nhap STT sinh vien muon xoa thong tin: "; std::cin >> viTri;
                    CheckNumber(viTri);
                    if (viTri <= 0 || viTri > dsSinhVien.size()) std::cout << "\n[!] Nhap lai STT." <<std::endl;
                }while (viTri <= 0 || viTri > dsSinhVien.size());
                for (int i = viTri - 1; i <= dsSinhVien.size() - 1; i++){
                    dsSinhVien[i] = dsSinhVien[i+1];
                }
                dsSinhVien.erase(dsSinhVien.end());
                SLEEP;
                std::cout << "\n[!] Da xoa sinh vien thu " << viTri <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        case 2:
            if (checkSVDTN == 2){
                CLEARSCR;
                XuatDS_SVDTN();
                do{
                    std::cout << "Nhap STT sinh vien muon xoa thong tin: "; std::cin >> viTri;
                    CheckNumber(viTri);
                    if (viTri <= 0 || viTri > dsSinhVienTotNghiep.size()) std::cout << "\n[!] Nhap lai STT." <<std::endl;
                }while (viTri <= 0 || viTri > dsSinhVienTotNghiep.size());
                for (int i = viTri - 1; i <= dsSinhVienTotNghiep.size() - 1; i++){
                    dsSinhVienTotNghiep[i] = dsSinhVienTotNghiep[i+1];
                }
                dsSinhVienTotNghiep.erase(dsSinhVienTotNghiep.end());
                SLEEP;
                std::cout << "\n[!] Da xoa sinh vien thu " << viTri <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien da tot nghiep bi trong." <<std::endl;
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    }while (chon != 0);
}

void QuanLySinhVien::XoaTheoMSSV(){
    int chon, viTri;
    char _maSV[15];
    bool check = false;
    do{
        CLEARSCR;
        std::cout << "\n---------------------XOA SINH VIEN THEO MSSV---------------------" <<std::endl;
        std::cout << "\t1. Sinh vien dang theo hoc." <<std::endl;
        std::cout << "\t2. Sinh vien da tot nghiep." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:        
            if (checkSV == 1){
                CLEARSCR;
                XuatDS_SV();
                do{
                    fflush(stdin);
                    std::cout << "Nhap MSSV sinh vien muon sua thong tin: "; std::cin.getline(_maSV, 15);
                    if (CheckMSSV(_maSV) == false) std::cout << "\n[!] Khong co sinh vien co MSSV la " << _maSV <<std::endl;
                }while (CheckMSSV(_maSV) == false);

                for (int i = 0; i < dsSinhVien.size(); i++){
                    if (std::strcmp(dsSinhVien[i].GetMSSV(), _maSV) == 0) viTri = i;
                }

                for (int i = viTri; i <= dsSinhVien.size() - 1; i++){
                    dsSinhVien[i] = dsSinhVien[i+1];
                }
                dsSinhVien.erase(dsSinhVien.end());
                SLEEP;
                std::cout << "\n[!] Da xoa sinh vien co MSSV: " << _maSV <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien dang hoc bi trong." <<std::endl;
            PAUSE;
            break;
        case 2:        
            if (checkSVDTN == 2){
                CLEARSCR;
                XuatDS_SVDTN();
                do{
                    fflush(stdin);
                    std::cout << "Nhap MSSV sinh vien muon sua thong tin: "; std::cin.getline(_maSV, 15);
                    if (CheckMSSV(_maSV) == false) std::cout << "\n[!] Khong co sinh vien co MSSV la " << _maSV <<std::endl;
                }while (CheckMSSV(_maSV) == false);

                for (int i = 0; i < dsSinhVienTotNghiep.size(); i++){
                    if (std::strcmp(dsSinhVienTotNghiep[i].GetMSSV(), _maSV) == 0) viTri = i;
                }

                for (int i = viTri; i <= dsSinhVienTotNghiep.size() - 1; i++){
                    dsSinhVienTotNghiep[i] = dsSinhVienTotNghiep[i+1];
                }
                dsSinhVienTotNghiep.erase(dsSinhVienTotNghiep.end());
                SLEEP;
                std::cout << "\n[!] Da xoa sinh vien co MSSV: " << _maSV <<std::endl;
            }
            else std::cout << "[!]Danh sach sinh vien da tot nghiep bi trong." <<std::endl;
            PAUSE;
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    }while(chon != 0);
}

void QuanLySinhVien::Xoa(){
    int chon;
    do{
        CLEARSCR;
        std::cout << "---------------------MENU XOA THONG TIN SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Xoa theo vi tri." <<std::endl;
        std::cout << "\t2. Xoa theo MSSV." <<std::endl;
        std::cout << "\t0. Thoat." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            break;
        case 1:
            XoaTheoViTri();
            break;
        case 2:
            XoaTheoMSSV();
            break;
        default:
            std::cout << conLai <<std::endl;
            PAUSE;
            break;
        }
    }while (chon != 0);
}
#pragma endregion


void Menu(QuanLySinhVien QLSV){
    int chon;
    QLSV.DocFileSV();
    QLSV.DocFileSVDTN();
    QLSV.DocFileMH();
    do{
        CLEARSCR;
        std::cout << "---------------------MENU QUAN LY SINH VIEN---------------------" <<std::endl;
        std::cout << "\t1. Hien thi danh sach sinh vien." <<std::endl;
        std::cout << "\t2. Nhap thong tin sinh vien." <<std::endl;
        std::cout << "\t3. Tim kiem sinh vien." <<std::endl;
        std::cout << "\t4. Sua thong tin sinh vien." <<std::endl;
        std::cout << "\t5. Xoa sinh vien trong danh sach." <<std::endl;
        std::cout << "\t0. Thoat chuong trinh." <<std::endl;
        std::cout << Chon; std::cin >> chon;
        CheckNumber(chon);
        switch (chon){
        case 0:
            SLEEP;
            QLSV.GhiFileSV();
            QLSV.GhiFileSVDTN();
            QLSV.GhiFileMH();
            std::cout << "\n[!] Da thoat." <<std::endl;
            break;
        case 1:
            QLSV.XuatDS();
            break;
        case 2:
            QLSV.NhapDS();
            break;
        case 3:
            QLSV.TimKiem();
        case 4:
            QLSV.Sua();
            break;
        case 5:
            QLSV.Xoa();
            break;
        default:
            std::cout << conLai <<std::endl;
            break;
        }
    } while (chon != 0);
}
