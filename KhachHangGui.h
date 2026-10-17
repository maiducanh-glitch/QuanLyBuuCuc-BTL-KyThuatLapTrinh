
#ifndef KHACH_HANG_GUI_H
#define KHACH_HANG_GUI_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <stdexcept>
#include "Entity.h"
#include "Repository.h"

using namespace std;

class KhachHangGui : public Entity {
private:
    string hoTen;
    string ngaySinh;
    string soDienThoai;
    string email;
    string diaChi;

public:
    KhachHangGui()
        : Entity(""),
          hoTen(""),
          ngaySinh(""),
          soDienThoai(""),
          email(""),
          diaChi("") {}

    void nhap() override {
        cout << "Nhap ma khach hang: ";
        getline(cin, maID);

        cout << "Nhap ho ten: ";
        getline(cin, hoTen);

        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ngaySinh);

        cout << "Nhap so dien thoai: ";
        getline(cin, soDienThoai);

        cout << "Nhap email: ";
        getline(cin, email);

        cout << "Nhap dia chi: ";
        getline(cin, diaChi);
    }

    void xuat() const override {
        cout << "Ma khach hang: " << maID << '\n';
        cout << "Ho ten: " << hoTen << '\n';
        cout << "Ngay sinh: " << ngaySinh << '\n';
        cout << "So dien thoai: " << soDienThoai << '\n';
        cout << "Email: " << email << '\n';
        cout << "Dia chi: " << diaChi << '\n';
        cout << "----------------------------------------\n";
    }

    string toFileRecord() const override {
        stringstream ss;
        ss << maID << '|'
           << hoTen << '|'
           << ngaySinh << '|'
           << soDienThoai << '|'
           << email << '|'
           << diaChi;

        return ss.str();
    }

    void fromFileRecord(const string& record) override {
        stringstream ss(record);
        string fields[6];

        for (int i = 0; i < 6; i++) {
            if (!getline(ss, fields[i], '|')) {
                throw invalid_argument(
                    "Du lieu khach hang khong hop le!"
                );
            }
        }

        maID = fields[0];
        hoTen = fields[1];
        ngaySinh = fields[2];
        soDienThoai = fields[3];
        email = fields[4];
        diaChi = fields[5];
    }

    void capNhatThongTin() {
        cout << "Nhap ho ten moi: ";
        getline(cin, hoTen);

        cout << "Nhap ngay sinh moi: ";
        getline(cin, ngaySinh);

        cout << "Nhap so dien thoai moi: ";
        getline(cin, soDienThoai);

        cout << "Nhap email moi: ";
        getline(cin, email);

        cout << "Nhap dia chi moi: ";
        getline(cin, diaChi);
    }
};

class KhachHangGuiMenu {
private:
    Repository<KhachHangGui>& repo;

public:
    KhachHangGuiMenu(Repository<KhachHangGui>& r)
        : repo(r) {}

    void themKhachHang() {
        KhachHangGui kh;
        kh.nhap();

        try {
            repo.add(kh);
            cout << "Them khach hang thanh cong!\n";
        }
        catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }

        system("pause");
    }

    void hienThiDanhSach() {
        vector<KhachHangGui> ds = repo.getAll();

        if (ds.empty()) {
            cout << "Danh sach khach hang dang trong!\n";
        } else {
            for (const auto& kh : ds) {
                kh.xuat();
            }
        }

        system("pause");
    }

    void timKiemKhachHang() {
        string id;

        cout << "Nhap ma khach hang can tim: ";
        getline(cin, id);

        KhachHangGui* kh = repo.findById(id);

        if (kh != nullptr) {
            kh->xuat();
        } else {
            cout << "Khong tim thay khach hang!\n";
        }

        system("pause");
    }

    void capNhatKhachHang() {
        string id;

        cout << "Nhap ma khach hang can cap nhat: ";
        getline(cin, id);

        KhachHangGui* kh = repo.findById(id);

        if (kh == nullptr) {
            cout << "Khong tim thay khach hang!\n";
            system("pause");
            return;
        }

        KhachHangGui khMoi;
        khMoi.setMaID(id);
        khMoi.capNhatThongTin();

        if (repo.update(id, khMoi)) {
            cout << "Cap nhat thong tin thanh cong!\n";
        } else {
            cout << "Cap nhat that bai!\n";
        }

        system("pause");
    }

    void xoaKhachHang() {
        string id;

        cout << "Nhap ma khach hang can xoa: ";
        getline(cin, id);

        if (repo.removeById(id)) {
            cout << "Xoa khach hang thanh cong!\n";
        } else {
            cout << "Khong tim thay khach hang!\n";
        }

        system("pause");
    }

    void menu() {
        int chon;

        do {
            system("cls");

            cout << "======= QUAN LY KHACH HANG GUI =======\n";
            cout << "1. Them khach hang\n";
            cout << "2. Hien thi danh sach khach hang\n";
            cout << "3. Tim kiem khach hang\n";
            cout << "4. Cap nhat thong tin khach hang\n";
            cout << "5. Xoa khach hang\n";
            cout << "0. Quay lai menu chinh\n";
            cout << "======================================\n";
            cout << "Nhap lua chon: ";

            if (!(cin >> chon)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                chon = -1;
            } else {
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
            }

            switch (chon) {
            case 1:
                themKhachHang();
                break;
            case 2:
                hienThiDanhSach();
                break;
            case 3:
                timKiemKhachHang();
                break;
            case 4:
                capNhatKhachHang();
                break;
            case 5:
                xoaKhachHang();
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                system("pause");
            }
        } while (chon != 0);
    }
};

#endif
