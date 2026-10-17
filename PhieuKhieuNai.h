#ifndef PHIEU_KHIEU_NAI_H
#define PHIEU_KHIEU_NAI_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "Entity.h"
#include "Repository.h"

using namespace std;

class PhieuKhieuNai : public Entity {
private:
    string maKhachHang;
    string maPhieuGui;
    string noiDung;
    string ngayKhieuNai;
    string trangThai;
    int danhGia;
    string nhanXet;

public:
    PhieuKhieuNai()
        : Entity(""),
          maKhachHang(""),
          maPhieuGui(""),
          noiDung(""),
          ngayKhieuNai(""),
          trangThai("Cho xu ly"),
          danhGia(0),
          nhanXet("") {}

    void nhap() override {
        cout << "Nhap ma phieu khieu nai: ";
        getline(cin, maID);

        cout << "Nhap ma khach hang: ";
        getline(cin, maKhachHang);

        cout << "Nhap ma phieu gui: ";
        getline(cin, maPhieuGui);

        cout << "Nhap noi dung khieu nai: ";
        getline(cin, noiDung);

        cout << "Nhap ngay khieu nai (dd/mm/yyyy): ";
        getline(cin, ngayKhieuNai);

        trangThai = "Cho xu ly";
        danhGia = 0;
        nhanXet = "";
    }

    void xuat() const override {
        cout << "Ma phieu khieu nai: " << maID << '\n';
        cout << "Ma khach hang: " << maKhachHang << '\n';
        cout << "Ma phieu gui: " << maPhieuGui << '\n';
        cout << "Noi dung khieu nai: " << noiDung << '\n';
        cout << "Ngay khieu nai: " << ngayKhieuNai << '\n';
        cout << "Trang thai: " << trangThai << '\n';

        if (danhGia == 0)
            cout << "Danh gia khach hang: Chua danh gia\n";
        else
            cout << "Danh gia khach hang: "
                 << danhGia << "/5 sao\n";

        cout << "Nhan xet cua khach hang: "
             << (nhanXet.empty() ? "Chua co" : nhanXet)
             << '\n';

        cout << "----------------------------------------\n";
    }

    void setTrangThai(const string& trangThaiMoi) {
        trangThai = trangThaiMoi;
    }

    void setDanhGia(int diem, const string& nhanXetMoi) {
        if (diem < 1 || diem > 5)
            throw invalid_argument("Danh gia phai tu 1 den 5 sao!");

        danhGia = diem;
        nhanXet = nhanXetMoi;
    }

    string toFileRecord() const override {
        stringstream ss;
        ss << maID << '|'
           << maKhachHang << '|'
           << maPhieuGui << '|'
           << noiDung << '|'
           << ngayKhieuNai << '|'
           << trangThai << '|'
           << danhGia << '|'
           << nhanXet;

        return ss.str();
    }

    void fromFileRecord(const string& record) override {
        stringstream ss(record);
        string fields[8];

        for (int i = 0; i < 8; i++) {
            if (!getline(ss, fields[i], '|'))
                throw invalid_argument("Du lieu phieu khieu nai khong hop le!");
        }

        maID = fields[0];
        maKhachHang = fields[1];
        maPhieuGui = fields[2];
        noiDung = fields[3];
        ngayKhieuNai = fields[4];
        trangThai = fields[5];
        danhGia = stoi(fields[6]);
        nhanXet = fields[7];
    }
};

class PhieuKhieuNaiMenu {
private:
    Repository<PhieuKhieuNai>& repo;

public:
    PhieuKhieuNaiMenu(Repository<PhieuKhieuNai>& r)
        : repo(r) {}

    void themPhieu() {
        PhieuKhieuNai p;
        p.nhap();

        try {
            repo.add(p);
            cout << "Them phieu khieu nai thanh cong!\n";
        }
        catch (const exception& e) {
            cout << "Loi: " << e.what() << '\n';
        }

        system("pause");
    }

    void hienThiDanhSach() {
        vector<PhieuKhieuNai> ds = repo.getAll();

        if (ds.empty()) {
            cout << "Chua co phieu khieu nai nao!\n";
        } else {
            for (const auto& p : ds)
                p.xuat();
        }

        system("pause");
    }

    void timKiem() {
        string id;

        cout << "Nhap ma phieu can tim: ";
        getline(cin, id);

        PhieuKhieuNai* p = repo.findById(id);

        if (p != nullptr)
            p->xuat();
        else
            cout << "Khong tim thay phieu khieu nai!\n";

        system("pause");
    }

    void capNhatTrangThai() {
        string id;

        cout << "Nhap ma phieu can cap nhat: ";
        getline(cin, id);

        PhieuKhieuNai* p = repo.findById(id);

        if (p == nullptr) {
            cout << "Khong tim thay phieu!\n";
            system("pause");
            return;
        }

        cout << "1. Cho xu ly\n";
        cout << "2. Dang xu ly\n";
        cout << "3. Da giai quyet\n";
        cout << "4. Tu choi khieu nai\n";
        cout << "Chon trang thai moi: ";

        int chon;
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le!\n";
            system("pause");
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (chon) {
        case 1: p->setTrangThai("Cho xu ly"); break;
        case 2: p->setTrangThai("Dang xu ly"); break;
        case 3: p->setTrangThai("Da giai quyet"); break;
        case 4: p->setTrangThai("Tu choi khieu nai"); break;
        default:
            cout << "Lua chon khong hop le!\n";
            system("pause");
            return;
        }

        repo.ghiFile();
        cout << "Cap nhat trang thai thanh cong!\n";
        system("pause");
    }

    void capNhatDanhGia() {
        string id;

        cout << "Nhap ma phieu can danh gia: ";
        getline(cin, id);

        PhieuKhieuNai* p = repo.findById(id);

        if (p == nullptr) {
            cout << "Khong tim thay phieu!\n";
            system("pause");
            return;
        }

        int diem;
        cout << "Nhap diem danh gia (1-5 sao): ";

        if (!(cin >> diem)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Diem danh gia khong hop le!\n";
            system("pause");
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (diem < 1 || diem > 5) {
            cout << "Diem danh gia phai tu 1 den 5!\n";
            system("pause");
            return;
        }

        string nhanXet;
        cout << "Nhap nhan xet cua khach hang: ";
        getline(cin, nhanXet);

        p->setDanhGia(diem, nhanXet);
        repo.ghiFile();

        cout << "Cap nhat danh gia thanh cong!\n";
        system("pause");
    }

    void xoaPhieu() {
        string id;

        cout << "Nhap ma phieu can xoa: ";
        getline(cin, id);

        if (repo.removeById(id))
            cout << "Xoa phieu thanh cong!\n";
        else
            cout << "Khong tim thay phieu!\n";

        system("pause");
    }

    void menu() {
        int chon;

        do {
            system("cls");
            cout << "======= QUAN LY PHIEU KHIEU NAI =======\n";
            cout << "1. Them phieu khieu nai\n";
            cout << "2. Hien thi danh sach phieu\n";
            cout << "3. Tim kiem phieu\n";
            cout << "4. Cap nhat trang thai xu ly\n";
            cout << "5. Cap nhat danh gia khach hang\n";
            cout << "6. Xoa phieu khieu nai\n";
            cout << "0. Quay lai menu chinh\n";
            cout << "======================================\n";
            cout << "Nhap lua chon: ";

            if (!(cin >> chon)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                chon = -1;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch (chon) {
            case 1: themPhieu(); break;
            case 2: hienThiDanhSach(); break;
            case 3: timKiem(); break;
            case 4: capNhatTrangThai(); break;
            case 5: capNhatDanhGia(); break;
            case 6: xoaPhieu(); break;
            case 0: break;
            default:
                cout << "Lua chon khong hop le!\n";
                system("pause");
            }
        } while (chon != 0);
    }
};

#endif
