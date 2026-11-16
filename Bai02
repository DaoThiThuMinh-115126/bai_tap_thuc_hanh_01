#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cctype>

using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int thoi_gian_do);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    int lay_gio_vao() const;
    int lay_tg_do() const;
    double lay_phi_do() const;

    void dat_ma_xe(int ma);
    void dat_loai_xe(string loai);
    void dat_gio_vao(int gio);
    void dat_tg_do(int thoi_gian_do);

    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() {
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
    phi_do = 0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int thoi_gian_do) {
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    tg_do = thoi_gian_do;
    phi_do = tinh_phi();
}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }
double phuong_tien::lay_phi_do() const { return phi_do; }

void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
void phuong_tien::dat_loai_xe(string loai) {
    loai_xe = loai;
    phi_do = tinh_phi();
}
void phuong_tien::dat_gio_vao(int gio) {
    gio_vao = gio;
    phi_do = tinh_phi();
}
void phuong_tien::dat_tg_do(int thoi_gian_do) {
    tg_do = thoi_gian_do;
    phi_do = tinh_phi();
}

double phuong_tien::tinh_phi() const {
    double gia = 2.0;

    if (loai_xe == "Car") {
        gia = 6.0;
    } else if (loai_xe == "Motorcycle") {
        gia = 4.0;
    } else if (loai_xe == "Bicycle") {
        gia = 2.0;
    }

    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);

    double tong = 0;

    for (int gio = 0; gio < tg_do; gio++) {
        if (gio < 2) {
            if (cao_diem) {
                tong += gia * 1.30;
            } else {
                tong += gia * 0.95;
            }
        } else {
            tong += gia * 0.90;
        }
    }

    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc_bai;
    static const int MAX_XE = 3;
    phuong_tien ds_xe[MAX_XE];
    int so_xe_hien_tai;

    int lay_suc_chua() const;

public:
    bai_xe();
    bai_xe(int ma, char kich_thuoc);

    int lay_ma_bai() const;
    char lay_kich_thuoc() const;
    int lay_so_xe() const;
    phuong_tien lay_xe(int vi_tri) const;

    bool da_day() const;
    bool them_xe(const phuong_tien& xe);
    bool xoa_xe(int ma_xe);
    int tim_vi_tri_xe(int ma_xe) const;
    void hien_thi_bai() const;
};

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc_bai = 'S';
    so_xe_hien_tai = 0;
}

bai_xe::bai_xe(int ma, char kich_thuoc) {
    ma_bai = ma;
    kich_thuoc_bai = kich_thuoc;
    so_xe_hien_tai = 0;
}

int bai_xe::lay_suc_chua() const {
    if (kich_thuoc_bai == 'S') return 1;
    if (kich_thuoc_bai == 'M') return 2;
    return 3;
}

int bai_xe::lay_ma_bai() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc_bai; }
int bai_xe::lay_so_xe() const {
    return so_xe_hien_tai;
}

phuong_tien bai_xe::lay_xe(int vi_tri) const {
    if (vi_tri >= 0 && vi_tri < so_xe_hien_tai) {
        return ds_xe[vi_tri];
    }
    return phuong_tien();
}

bool bai_xe::da_day() const {
    return so_xe_hien_tai >= lay_suc_chua();
}

bool bai_xe::them_xe(const phuong_tien& xe) {
    if (da_day() || so_xe_hien_tai >= MAX_XE) {
        return false;
    }

    ds_xe[so_xe_hien_tai] = xe;
    so_xe_hien_tai++;
    return true;
}

int bai_xe::tim_vi_tri_xe(int ma_xe) const {
    for (int i = 0; i < so_xe_hien_tai; i++) {
        if (ds_xe[i].lay_ma_xe() == ma_xe) {
            return i;
        }
    }
    return -1;
}

bool bai_xe::xoa_xe(int ma_xe) {
    int vi_tri = tim_vi_tri_xe(ma_xe);

    if (vi_tri == -1) {
        return false;
    }

    // Don cac phan tu phia sau sang trai
    for (int i = vi_tri; i < so_xe_hien_tai - 1; i++) {
        ds_xe[i] = ds_xe[i + 1];
    }

    so_xe_hien_tai--;
    return true;
}

void bai_xe::hien_thi_bai() const {
    cout << "\nParking Lot " << ma_bai
         << " [" << kich_thuoc_bai << "] "
         << so_xe_hien_tai << "/" << lay_suc_chua()
         << " vehicles\n";

    if (so_xe_hien_tai == 0) {
        cout << "  The parking lot is empty.\n";
    }

    for (int i = 0; i < so_xe_hien_tai; i++) {
        ds_xe[i].hien_thi();
    }
}

int nhap_so_nguyen(string thong_bao) {
    int gia_tri;

    while (true) {
        cout << thong_bao;
        cin >> gia_tri;

        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return gia_tri;
        }
    }
}

string nhap_chuoi(string thong_bao) {
    string gia_tri;
    cout << thong_bao;
    cin >> gia_tri;
    return gia_tri;
}

class SystemInterface {
	private:
	    static const int MAX_BAI = 10;
	    bai_xe ds_bai[MAX_BAI];
	    bool co[MAX_BAI];
	    bool KiemTraMaBaiTonTai(int ma) const;
	    bool KiemTraMaXeTonTai(int ma) const;
	
	public:
	    SystemInterface();
	    void runMenu();
};

SystemInterface::SystemInterface() {
    so_bai_hien_tai = 0;
    srand(static_cast<unsigned int>(time(0)));
}

bool SystemInterface::KiemTraMaBaiTonTai(int ma) const {
    for (int i = 0; i < MAX_BAI; ++i) {
        if (co[i] && ds_bai[i].lay_ma() == ma) return true;
    }
    return false;
}

bool SystemInterface::KiemTraMaXeTonTai(int ma) const {
    for (int i = 0; i < MAX_BAI; ++i) {
        if (co[i] && ds_bai[i].chua(ma)) return true;
    }
    return false;
}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (chon) {
            case 1: {
                int slot = -1;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (!co[i]) { slot = i; break; }
                }
                if (slot == -1) {
                    cout << "Da dat gioi han toi da 3 bai do!\n";
                    break;
                }

                int ma; char kt;
                cout << "Ma bai: "; cin >> ma;
                if (KiemTraMaBaiTonTai(ma)) {
                    cout << "Loi: Ma bai do da ton tai!\n";
                    break;
                }

                cout << "Kich thuoc (S/M/L): "; cin >> kt;
                ds_bai[slot] = bai_xe(ma, kt);
                co[slot] = true;
                cout << "Da tao bai " << ma << " thanh cong!\n";
                break;
            }
            case 2: {
                int ma, gio, tg; string loai;
                cout << "Ma xe: "; cin >> ma;
                if (KiemTraMaXeTonTai(ma)) {
                    cout << "Loi: Ma xe da ton tai trong he thong!\n";
                    break;
                }

                cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
                cout << "Gio vao (0-23): "; cin >> gio;
                cout << "Thoi luong (1-23): "; cin >> tg;

                phuong_tien v(ma, loai, gio, tg);
                bool added = false;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (co[i] && ds_bai[i].them(v)) {
                        cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma() 
                             << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                        added = true;
                        break;
                    }
                }
                if (!added) cout << "Tat ca bai da day hoac chua co bai do!\n";
                break;
            }
            case 3: {
                int ma;
                cout << "Ma bai can xoa: "; cin >> ma;
                bool found = false;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (co[i] && ds_bai[i].lay_ma() == ma) {
                        co[i] = false;
                        ds_bai[i] = bai_xe();
                        cout << "Da xoa bai " << ma << "\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            case 4: {
                int ma;
                cout << "Ma xe can lay ra: "; cin >> ma;
                bool ok = false;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (co[i] && ds_bai[i].xoa(ma)) {
                        cout << "Da lay xe " << ma << " ra khoi bai " << ds_bai[i].lay_ma() << "\n";
                        ok = true;
                        break;
                    }
                }
                if (!ok) cout << "Khong tim thay xe!\n";
                break;
            }
            case 5: {
                bool empty = true;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (co[i]) {
                        ds_bai[i].hien_thi();
                        empty = false;
                    }
                }
                if (empty) cout << "Hien chua co bai do xe nao!\n";
                break;
            }
            case 6: {
                int ma;
                cout << "Ma bai: "; cin >> ma;
                bool found = false;
                for (int i = 0; i < MAX_BAI; ++i) {
                    if (co[i] && ds_bai[i].lay_ma() == ma) {
                        ds_bai[i].hien_thi();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            case 7: {
                string loai;
                cout << "Loai xe: "; cin >> loai;
                bool timThay = false;
                for (int i = 0; i < MAX_BAI; ++i) {
                    int dem = 0; double tong = 0;
                    if (co[i] && ds_bai[i].co_loai(loai, dem, tong)) {
                        ds_bai[i].hien_thi();
                        timThay = true;
                    }
                }
                if (!timThay) cout << "Khong tim thay xe loai " << loai << "\n";
                break;
            }
            case 8: {
                string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
                for (int t = 0; t < 3; ++t) {
                    int tong_dem = 0; 
                    double tong_tien = 0;
                    for (int i = 0; i < MAX_BAI; ++i) {
                        if (co[i]) {
                            int d = 0; double s = 0;
                            ds_bai[i].co_loai(loai_arr[t], d, s);
                            tong_dem += d;
                            tong_tien += s;
                        }
                    }
                    cout << loai_arr[t] << ": ";
                    if (tong_dem == 0) cout << "khong co xe\n";
                    else cout << tong_dem << " xe | TB: $" << fixed << setprecision(2) << (tong_tien / tong_dem) << "\n";
                }
                break;
            }
            case 9:
                return;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    }
}
int main() {
    SystemInterface he_thong;
    he_thong.runMenu();
    return 0;
}
