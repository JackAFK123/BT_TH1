#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MatHang {
public:
    static int autoIncrementID;
    int maHang;
    string tenHang;
    string nhomHang;
    double giaBan;
    int soLuong;

    MatHang() : maHang(autoIncrementID++), tenHang(""), nhomHang(""), giaBan(0.0), soLuong(0) {}

    MatHang(const string& ten, const string& nhom, double gia, int soluong)
        : maHang(autoIncrementID++), tenHang(ten), nhomHang(nhom), giaBan(gia), soLuong(soluong) {}

    string getNhomHang() const {
        return nhomHang;
    }
};

int MatHang::autoIncrementID = 1000;

class NhanVien {
public:
    static int autoIncrementID;
    int maNV;
    string hoTen;
    vector<MatHang> danhSachBanHang;

    NhanVien() : maNV(autoIncrementID++), hoTen("") {}

    NhanVien(const string& ten) : maNV(autoIncrementID++), hoTen(ten) {}//Todo: bo sung dia chi, sdt, ngay sinh 

    void themMatHang(const MatHang& matHang) {
        // Todo: Ktra xem mat hang da duoc ban hay chua 
        auto it = find_if(danhSachBanHang.begin(), danhSachBanHang.end(),
                          [&](const MatHang& mh) { return mh.maHang == matHang.maHang; });

        if (it == danhSachBanHang.end() && danhSachBanHang.size() < 5) {
            danhSachBanHang.push_back(matHang);
        } else {
            cout << "Nhan vien " << hoTen << " da ban mat hang nay hoac da ban qua 5 mat hang." << endl;
        }
    }
};

int NhanVien::autoIncrementID = 1000;

class BangDanhSachBanHang {
private:
    struct Node {
        NhanVien nhanVien;
        MatHang matHang;
        Node* next;

        Node(const NhanVien& nv, const MatHang& mh) : nhanVien(nv), matHang(mh), next(NULL) {}
    };

    Node* head;

public:
    BangDanhSachBanHang() : head(NULL) {}

    void themBanHang(const NhanVien& nv, const MatHang& mh) {
        Node* newNode = new Node(nv, mh);
        newNode->next = head;
        head = newNode;
    }

    void hienThiBangDanhSach() {
        Node* current = head;
        while (current) {
            cout << "Ma NV: " << current->nhanVien.maNV << endl;
            cout << "Ho và ten NV: " << current->nhanVien.hoTen << endl;
            cout << "Ma Hang: " << current->matHang.maHang << endl;
            cout << "Ten Hang: " << current->matHang.tenHang << endl;
            cout << "Nhom Hang: " << current->matHang.nhomHang << endl;
            cout << "Gia Ban: " << current->matHang.giaBan << endl;
            cout << "So Luong: " << current->matHang.soLuong << endl;
            cout << "--------------------------------------------" << endl;
            current = current->next;
        }
    }

    void sapXepTheoTenNhanVien() {
        vector<Node*> nodes;
        Node* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        sort(nodes.begin(), nodes.end(), [](const Node* a, const Node* b) {
            return a->nhanVien.hoTen < b->nhanVien.hoTen;
        });

        head = NULL;
        for (Node* node : nodes) {
            node->next = head;
            head = node;
        }
    }

    void sapXepTheoNhomMatHang() {
        vector<Node*> nodes;
        Node* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        sort(nodes.begin(), nodes.end(), [](const Node* a, const Node* b) {
            return a->matHang.getNhomHang() < b->matHang.getNhomHang();
        });

        head = NULL;
        for (Node* node : nodes) {
            node->next = head;
            head = node;
        }
    }

    void lapBangKeDoanhThu() {
        Node* current = head;
        while (current) {
            double doanhThu = current->matHang.giaBan * current->matHang.soLuong;
            cout << "Nhan vien " << current->nhanVien.hoTen << " - Doanh thu: " << doanhThu << endl;
            current = current->next;
        }
    }
};

int main() {
    std::vector<NhanVien> danhSachNhanVien;
    std::vector<MatHang> danhSachMatHang;
    BangDanhSachBanHang bangDanhSach;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Nhap danh sach mat hang moi" << endl;
        cout << "2. In ra danh sach cac mat hang da co" << endl;
        cout << "3. Nhap danh sach nhan vien" << endl;
        cout << "4. In ra danh sach nhan vien da co" << endl;
        cout << "5. Lap Bang danh sach ban hang cho tung nhan vien" << endl;
        cout << "6. In danh sach ban hang" << endl;
        cout << "7. Sap xep danh sach ban hang theo ten nhan vien" << endl;
        cout << "8. Sap xep danh sach ban hang theo nhom mat hang" << endl;
        cout << "9. Lap bang thong ke doanh thu" << endl;
        cout << "0. Exit" << endl;

        int choice;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int numItems;
                cout << "Nhap so luong mat hang: ";
                cin >> numItems;

                for (int i = 0; i < numItems; ++i) {
                    string ten, nhom;
                    double gia;
                    int soLuong;

                    cout << "Nhap thong tin mat hang #" << i + 1 << ":" << endl;
                    cout << "Ten hang: ";
                    cin.ignore();
                    getline(cin, ten);

                    cout << "Nhom hang: ";
                    getline(cin, nhom);

                    cout << "Gia ban: ";
                    
                    cin >> gia;

                    cout << "So luong: ";
                    cin >> soLuong;

                    MatHang matHang(ten, nhom, gia, soLuong);
                    danhSachMatHang.push_back(matHang);
                }

                cout << "Nhap thong tin mat hang thanh cong!" << endl;
                break;
            }
            case 2: {
                cout << "Danh sach mat hang:" << endl;
                for (const MatHang& matHang : danhSachMatHang) {
                    cout << "Ma Hang: " << matHang.maHang << endl;
                    cout << "Ten Hang: " << matHang.tenHang << endl;
                    cout << "Nhom Hang: " << matHang.nhomHang << endl;
                    cout << "Gia Ban: " << matHang.giaBan << endl;
                    cout << "So Luong: " << matHang.soLuong << endl;
                    cout << "--------------------------------------------" << endl;
                }
                break;
            }
            case 3: {
                int numEmployees;
                cout << "Nhap so luong nhan vien: ";
                cin >> numEmployees;

                for (int i = 0; i < numEmployees; ++i) {
                    string tenNhanVien;
                    cout << "Nhap thong tin nhan vien #" << i + 1 << ":" << endl;
                    cout << "Ten nhan vien: ";
                    cin.ignore();
                    getline(cin, tenNhanVien);

                    NhanVien nhanVien(tenNhanVien);
                    danhSachNhanVien.push_back(nhanVien);
                }

                cout << "Nhap thong tin nhan vien thanh cong!" << endl;
                break;
            }
            case 4: {
                cout << "Danh sach nhan vien:" << endl;
                for (const NhanVien& nhanVien : danhSachNhanVien) {
                    cout << "Ma NV: " << nhanVien.maNV << endl;
                    cout << "Ten NV: " << nhanVien.hoTen << endl;
                    cout << "--------------------------------------------" << endl;
                }
                break;
            }
            case 5: {
                
                for (NhanVien& nhanVien : danhSachNhanVien) {
                    cout << "Nhap danh sach mat hang cho nhan vien " << nhanVien.hoTen << ":\n";

                    for (int i = 0; i < 5; ++i) {
                        int maMatHang;
                        cout << "Nhap ma mat hang #" << i + 1 << ": ";
                        cin >> maMatHang;

                        // Tim mat hang trong danh sach mat hang
                        auto it = find_if(danhSachMatHang.begin(), danhSachMatHang.end(),
                                          [&](const MatHang& mh) { return mh.maHang == maMatHang; });

                        if (it != danhSachMatHang.end()) {
                            nhanVien.themMatHang(*it);
                            bangDanhSach.themBanHang(nhanVien, *it);
                        } else {
                            cout << "Mat hang khong ton tai!" << endl;
                            --i;  
                        }
                    }
                }
                cout << "Lap Bang danh sach ban hang thanh cong!" << endl;
                break;
            }
            case 6: {
                cout << "Danh sach ban hang:" << endl;
                bangDanhSach.hienThiBangDanhSach();
                break;
            }
            case 7: {
                bangDanhSach.sapXepTheoTenNhanVien();
                cout << "Danh sách duoc sap xep theo ten nhan vien." << endl;
                break;
            }
            case 8: {
                bangDanhSach.sapXepTheoNhomMatHang();
                cout << "Danh sach duoc sap xep theo nhom mat hang." << endl;
                break;
            }
            case 9: {
                cout << "Bang ke doanh thu:" << endl;
                bangDanhSach.lapBangKeDoanhThu();
                break;
            }
            case 0: {
                cout << "End." << endl;
                return 0;
            }
            default: {
                cout << "Lua chon khong hop le." << endl;
                break;
            }
        }
    }

    return 0;
}

