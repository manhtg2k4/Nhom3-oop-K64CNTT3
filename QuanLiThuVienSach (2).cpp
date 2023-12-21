#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Dinh nghia lop Sach
class Sach {
public:
    static int sttCounter; // Bien tinh de dem so thu tu cua sach
    int stt;
    string tenSach;
    string tacGia;
    int namXuatBan;

	// Ham khoi tao mac dinh, tu dong tang so thu tu
    Sach() {
        stt = ++sttCounter;
    }
	
	// Ham khoi tao co tham so
    Sach(string tenSach, string tacGia, int namXuatBan) : tenSach(tenSach), tacGia(tacGia), namXuatBan(namXuatBan) {
        stt = ++sttCounter;
    }

	// Ham hien thi thong tin cua sach
    void HienThiThongTin() const {
        cout << "\033[1;33m| \033[0m" << 
        setw(3) << right << stt 
        << "\033[1;33m | \033[0m" << setw(28) << left << tenSach 
        << "\033[1;33m | \033[0m" << setw(17) << left << tacGia
        << "\033[1;33m | \033[0m" << setw(6) << namXuatBan 
        << "\033[1;33m |\033[0m" << endl;
    }
};

// Khoi tao bien tinh sttCounter
int Sach::sttCounter = -1;

// Lop QuanLiThuVien ke thua tu lop Sach
class QuanLyThuVien : public Sach {
private:
    vector<Sach> danhSachSach; // Tao danh sach cac doi tuong sach 

public:
	// Ham them sach vao danh sach
    void ThemSach(const Sach& sach) {
        danhSachSach.push_back(sach);
    }

	// Ham nhap thong tin sach tu nguoi dung 
    void NhapThongTinSach() {
        string tenSach, tacGia;
        int namXuatBan;

        cout << "Nhap ten sach: ";
        getline(cin, tenSach);

        cout << "Nhap ten tac gia: ";
        getline(cin, tacGia);

        cout << "Nhap nam xuat ban: ";
        cin >> namXuatBan; cin.ignore();

        ThemSach(Sach(tenSach, tacGia, namXuatBan));
        cout << "Da them sach: " << tenSach << endl;
    }
	
	// Ham hien thi danh sach sach 
    void HienThiDanhSach() const {
        cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;
        cout << "\033[1;33m| STT |           Ten Sach           |      Tac Gia      | Nam XB |\033[0m" << endl;
        cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;

        for (const auto& sach : danhSachSach) {
            sach.HienThiThongTin();
        }
        cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;
    }

	// Cac ham sap xep sach theo TenSach, TacGia, NamXuatBan
    void SapXepTheoTenSach() {
        sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
            return a.tenSach < b.tenSach;
        });
    }

    void SapXepTheoTacGia() {
        sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
            return a.tacGia < b.tacGia;
        });
    }

    void SapXepTheoNamXuatBan() {
        sort(danhSachSach.begin(), danhSachSach.end(), [](const Sach& a, const Sach& b) {
            return a.namXuatBan < b.namXuatBan;
        });
    }
    
    // Ham xoa sach theo ten sach
    void XoaSach(const string& tenSach) {
    	// Tim sach co ten sach trung khop voi tham so dau vao
        auto it = remove_if(danhSachSach.begin(), danhSachSach.end(),
                            [tenSach](const Sach& sach) { return sach.tenSach == tenSach; });
        // Kiem tra xem co sach can xoa khong
        if (it != danhSachSach.end()) {
        	// Xoa sach tu vi tri it den cuoi danh sach 
            danhSachSach.erase(it, danhSachSach.end());
			
			// Cap nhat lai so thu tu cua sach sau khi xoa
            for (int i = 0; i < danhSachSach.size(); ++i) {
                danhSachSach[i].stt = i + 1;
            }
            // Thong bao da xoa sach thanh cong
            cout << "Da xoa sach co ten: " << tenSach << endl;
        } else {
        	// Thong bao khong co sach can xoa
            cout << "Khong tim thay sach co ten: " << tenSach << endl;
        }
    }

	// Ham sua thong tin cua sach theo ten sach
    void SuaSach(const string& tenSach) {
    	// Tim sach co ten sach trung khop voi tham so dau vao
        auto it = find_if(danhSachSach.begin(), danhSachSach.end(),
                          [tenSach](const Sach& sach) { return sach.tenSach == tenSach; });
		// Kiem tra xem co can sua khong
        if (it != danhSachSach.end()) {
            cout << "Nhap thong tin moi cho sach :" << endl;
			// Nhap thong tin cua sach moi tu nguoi dung
            string tacGiaMoi;
            int namXuatBanMoi;

            cout << "Nhap ten tac gia: ";
            getline(cin, tacGiaMoi);

            cout << "Nhap nam xuat ban: ";
            cin >> namXuatBanMoi;

			// Cap nhat thong tin sach
            it->tacGia = tacGiaMoi;
            it->namXuatBan = namXuatBanMoi;
			
			// Hien thi thong tin sach sau khi sua 
            cout << "Da cap nhat thong tin cho sach co ten: " << tenSach << endl;
        } else {
        	// Thong bao khong tim thay sach can sua
            cout << "Khong tim thay sach co ten: " << tenSach << endl;
        }
    }

	// Ham tim kiem sach theo ten sach
    void TimKiemTheotenSach(const string& tenSach) const {
    	// Tim sach co ten sach trung khop voi tham so dau vao
        auto it = find_if(danhSachSach.begin(), danhSachSach.end(),
                          [tenSach](const Sach& sach) { return sach.tenSach == tenSach; });
		// Kiem tra xem sach co can tim kiem khong
        if (it != danhSachSach.end()) {
        	// Hien thi thong tin sach co ten sach trung khop
            cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;
            cout << "\033[1;33m| STT |           Ten Sach           |      Tac Gia      | Nam XB |\033[0m" << endl;
            cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;
            it->HienThiThongTin();
            cout << "\033[1;33m+-----+------------------------------+-------------------+--------+\033[0m" << endl;
        } else {
        	// Thong bao khong tim thay sach co so thu tu trung khop
            cout << "Khong tim thay sach co ten " << tenSach << endl;
        }
    }
};

// Hien thi menu chuong trinh
void HienThiMenu() {
    cout << "\033[1;32m+-----------------------------+\033[0m" << endl;
    cout << "\033[1;32m|          \033[1;36m   MENU\033[1;32m            |\033[0m" << endl;
    cout << "\033[1;32m+-----------------------------+\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m1. In danh sach sach        \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m2. Them sach                \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m3. Sua sach                 \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m4. Xoa sach                 \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m5. Tim kiem                 \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m6. Sap xep                  \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m| \033[1;33m0. Thoat                    \033[1;32m|\033[0m" << endl;
    cout << "\033[1;32m+-----------------------------+\033[0m" << endl;
}

int main() {
    QuanLyThuVien quanLy; // Doi tuong quan li thu vien
    int luaChon; // Bien lua chon tu menu
	
	// Vong lap chinh
    do {
    	// Nhap lua chon tu nguoi dung
        HienThiMenu();
        cout << "\033[1;34mNhap lua chon cua ban: \033[0m";
        cin >> luaChon;
        cin.ignore();
		// Xu li lua chon tu nguoi dung
        switch (luaChon) {
        	// Cac case tuong ung voi cac chuc nang trong menu
            case 1: // Hien thi danh sach
                quanLy.HienThiDanhSach();
                break;
            case 2: // Them sach
                int n;
                do{
                    cout <<"\033[1;34mNhap so luong sach can them: \033[0m"; cin>>n; cin.ignore();
                }while(n<=0);
                for(int i=0; i<n; i++){
                    quanLy.NhapThongTinSach();
                }
                break;
            case 3: // Sua sach
                {
                string tenSua;
                cout << "\033[1;34mNhap ten sach can sua: \033[0m";
                getline(cin, tenSua);
                quanLy.SuaSach(tenSua);
                }
                break;
            case 4: // Xoa sach
                {
                string tenXoa;
                cout << "\033[1;34mNhap ten sach can xoa: \033[0m";
                getline(cin, tenXoa);
                quanLy.XoaSach(tenXoa);
                }
                break;
            case 5: // Tim kiem sach
               {
                string TenSachTimKiem;
                cout << "\033[1;34mNhap ten sach can tim: \033[0m";
                getline(cin,TenSachTimKiem);
                quanLy.TimKiemTheotenSach(TenSachTimKiem);
               }
                break;
            case 6: // Sap xep sach theo Ten Sach, Tac Gia, Nam Xuat Ban
                int luaChonSapXep;
                cout << "\033[1;34m1. Sap xep theo ten sach\033[0m" << endl;
                cout << "\033[1;34m2. Sap xep theo tac gia\033[0m" << endl;
                cout << "\033[1;34m3. Sap xep theo nam xuat ban\033[0m" << endl;
                cout << "\033[1;34mNhap lua chon cua ban: \033[0m";
                cin >> luaChonSapXep;
                switch (luaChonSapXep) {
                    case 1:
                        quanLy.SapXepTheoTenSach();
                        break;
                    case 2:
                        quanLy.SapXepTheoTacGia();
                        break;
                    case 3:
                        quanLy.SapXepTheoNamXuatBan();
                        break;
                    default:
                        cout << "\033[1;31mLua chon khong hop le!\033[0m" << endl;
                }
                break;
            case 0:
                cout << "\033[1;31mKet thuc chuong trinh.\033[0m" << endl;
                break;
            default:
                cout << "\033[1;31mLua chon khong hop le!\033[0m" << endl;
        }
    } while (luaChon != 0);

    return 0;
}
