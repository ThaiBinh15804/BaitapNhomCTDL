#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

//Định nghĩa Kiểu dữ liệu dùng trong chương trình
struct Date   //Kiểu dữ liệu cho ngày gồm 3 thành phần ngày, tháng, năm
{
    int ngay;
    int thang; 
    int nam;
};

struct Khachhang   //Đối tượng Khách hàng cần quản lí 5 thuộc tính
{
    char maKH[100];   //Mã Khách hàng
    char tenKH[100];  //Tên Khách hàng
    int tuoi;         //Tuổi Khách hàng
    char gioiTinh[10];//Giới tính Khách hàng
    char Sdt[15];     //SDT của Khách hàng
};

struct Hanghoa  //Đối tượng hàng hoá quản lí 3 thuộc tính
{
    char tenSP[50];     //Tên sản phẩm
    int soLuong;        //Số lượng hàng hoá còn trong kho
    double giaBan;      //Giá bán mỗi sản phẩm
};

struct ChitietHoadon    //Đối tượng chi tiết hoá đơn quản lí 3 thuộc tính 1 đối tượng con
{
    char maHoadon[50];      //Mã Hoá đơn (Mục đích của mã hoá đơn là xác định CTHD thuộc HD nào)
    Hanghoa sanpham;        //CTHD quản lí hàng hoá mà nó chứa đựng 
    //(VD: CTHD của hàng hoá NuocNgot thì nó sẽ quản lí các thuộc tính mà hàng hoá nước ngọt có)
    int soluong_mua;        //Số lượng Khách hàng mua
    double tien;      //tien = soluong_mua * giaBan(1sp)
};
 
//Định nghĩa cấu trúc của CTHD_Node trước để tạo 2 node Head, Tail trỏ đến phần tử đầu và cuối danh sách CTHD cua HD
struct CTHD_Node
{
    ChitietHoadon data;
    CTHD_Node *next;
};

struct Hoadon   //Đối tượng hoá đơn quản lí 3 thuộc tính và 3 đối tượng con
{
    char maHoadon[50];      //Mã hoá đơn
    Khachhang khachhang;    //Quản lí các thuộc tính của đối tượng khách hàng đã mua các sản phẩm của HD
    Date ngay_nhap;         //Quản lí ngày, tháng, năm khách mua hàng
    //Quản lí danh sách chi tiết hoá đơn của hoán đơn
    CTHD_Node *CTHDHead;    //Trỏ đến phân tử đầu danh sách chi tiết hoá đơn của hoá đơn
    CTHD_Node *CTHDTail;    //Trỏ đến phân tử cuối danh sách chi tiết hoá đơn của hoá đơn
    int soLuongCTHD;        // Số lượng chi tiết hóa đơn của hoá đơn
    double tongTien;        //tongTien = CTHD(1) + CTHD(2) + ... + CTHD(N)
};


//Định nghĩa cấu trúc Node của các đối tượng khi thao tác bằng danh sách liên kết đơn
struct KH_Node
{
    Khachhang data;
    KH_Node *next;
};

struct HH_Node
{
    Hanghoa data;
    HH_Node *next;
};

struct HD_Node
{
    Hoadon data;
    HD_Node *next;
};

struct CTHD_List
{
    CTHD_Node *head;
    CTHD_Node *tail;
};

struct KH_List
{
    KH_Node *head;
    KH_Node *tail;
};

struct HH_List
{
    HH_Node *head;
    HH_Node *tail;
};

struct HD_List
{
    HD_Node *head;
    HD_Node *tail;
};

//Hàm khởi tạo cho từng Node, danh sách của các đối tượng
void init_KH(KH_List &ds)
{
    ds.head = NULL;
    ds.tail = NULL;
}

void init_HH(HH_List &ds)
{
    ds.head = NULL;
    ds.tail = NULL;
}

void init_CTHD(CTHD_List &ds)
{
    ds.head = NULL;
    ds.tail = NULL;
}

void init_HD(HD_List &ds)
{
    ds.head = NULL;
    ds.tail = NULL;
}

KH_Node *create_KH_Node(Khachhang dulieu)
{
    KH_Node *p = new KH_Node;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat!");
        return NULL;
    }

    p->data = dulieu;
    p->next = NULL;

    return p;
}

HH_Node *create_HH_Node(Hanghoa dulieu)
{
    HH_Node *p = new HH_Node;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat!");
        return NULL;
    }

    p->data = dulieu;
    p->next = NULL;

    return p;
}

HD_Node *create_HD_Node(Hoadon dulieu)
{
    HD_Node *p = new HD_Node;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat!");
        return NULL;
    }

    p->data = dulieu;
    p->data.CTHDHead = NULL;
    p->data.CTHDTail = NULL;
    p->next = NULL;

    return p;
}

CTHD_Node *create_CTHD_Node(ChitietHoadon dulieu)
{
    CTHD_Node *p = new CTHD_Node;
    if (p == NULL)
    {
        printf("\nKhong du bo nho cap phat!");
        return NULL;
    }

    p->data = dulieu;
    p->next = NULL;

    return p;
}

//Hàm ghi, đọc File của các đối tượng
void ghiFIle_Khachhang(KH_List ds)
{
    FILE *f = fopen("Khachhang.txt", "w");
    if (f == NULL)
    {
        printf("\nKhong mo duoc file");
        _getch();
        return;
    }

    for (KH_Node *k = ds.head; k != NULL; k = k->next)  //Dùng vòng lặp để đọc toàn bộ danh sách hiện tại
    {
        //In thông tin của Khách hàng từ danh sách vào File
        fprintf(f, "%-20s %-20s %-10d %-10s %-20s\n",k->data.maKH, k->data.tenKH, k->data.tuoi, 
                                            k->data.gioiTinh, k->data.Sdt);    
    }

    fclose(f);
}

void docFile_Khachhang(KH_List &ds, int *slg_KH)
{
    FILE *f = fopen("Khachhang.txt", "r");
    if (f == NULL)
    {
        printf("\nKhong the mo file");
        _getch();
        return;
    }

    int ktra;                   //Biến dùng kiểm tra xem đã đọc đủ và đúng dữ liệu từ File chưa
    Khachhang dulieu;           //Lưu trữ tạm thời dữ liệu đọc từ File
    KH_Node *tmp = ds.head;     //Biến tmp để duyệt toàn bộ danh sách có sẵn 
    
    while ((ktra = fscanf(f, "%20s %20s %10d %10s %20s",dulieu.maKH, dulieu.tenKH, 
                &dulieu.tuoi, dulieu.gioiTinh, dulieu.Sdt)) == 5)    //Đọc dữ liệ từ File vào biến tạm thời
    {
        KH_Node *p = create_KH_Node(dulieu);
        int find = 0;   
        //Kiểm tra xem có tính trạng trùng dữ liệu khi đọc tử File ra danh sách không
        while (tmp != NULL)
        {
            if (strcmp(tmp->data.Sdt, p->data.Sdt) == 0)
            {
                find = 1;
                free(p);
                break;
            }
            tmp = tmp->next;
        }

        //Đưa con trỏ về đầu để kiểm tra và thêm vào cuối danh sách
        tmp = ds.head;
        if (find != 1)
        {
            if (ds.head == NULL)
            {
                ds.head = ds.tail = p;
            }
            else
            {
                ds.tail->next = p;
                ds.tail = p;
            }
            (*slg_KH)++;
        }
    }
    fclose(f);
}

void ghiFIle_Hanghoa(HH_List ds)
{
    FILE *f = fopen("Hanghoa.txt", "w");
    if (f == NULL)
    {
        printf("\nKhong mo duoc file");
        _getch();
        return;
    }

    for (HH_Node *k = ds.head; k != NULL; k = k->next)
    {
        fprintf(f, "%-20s %-10d %-20.0lf\n", k->data.tenSP, k->data.soLuong, k->data.giaBan);    
    }

    fclose(f);
}

void docFile_Hanghoa(HH_List &ds, int *slg_HH)
{
    FILE *f = fopen("Hanghoa.txt", "r");
    if (f == NULL)
    {
        printf("\nKhong the mo file");
        _getch();
        return;
    }

    int ktra;
    Hanghoa dulieu;
    HH_Node *tmp = ds.head;
    
    while ((ktra = fscanf(f, "%20s %10d %20lf", dulieu.tenSP, &dulieu.soLuong, &dulieu.giaBan)) == 3)
    {
        HH_Node *p = create_HH_Node(dulieu);
        int find = 0;
        while (tmp != NULL)
        {
            if (strcmp(tmp->data.tenSP, p->data.tenSP) == 0)
            {
                find = 1;
                free(p);
                break;
            }
            tmp = tmp->next;
        }

        tmp = ds.head;
        if (find != 1)
        {
            if (ds.head == NULL)
            {
                ds.head = ds.tail = p;
            }
            else
            {
                ds.tail->next = p;
                ds.tail = p;
            }
            (*slg_HH)++;
        }
    }
    fclose(f);
}


void ghiFIle_ChitietHoadon(CTHD_List ds)
{
    FILE *f = fopen("ChitietHoadon.txt", "w");
    if (f == NULL)
    {
        printf("\nKhong mo duoc file");
        _getch();
        return;
    }

    for (CTHD_Node *k = ds.head; k != NULL; k = k->next)
    {
        fprintf(f, "%-20s %-20s %-10d %-20.0lf\n", k->data.maHoadon, 
                k->data.sanpham.tenSP, k->data.soluong_mua, k->data.tien);    
    }

    fclose(f);
}

void docFile_ChitietHoadon(CTHD_List &ds, int *slg_CTHD)
{
    FILE *f = fopen("ChitietHoadon.txt", "r");
    if (f == NULL)
    {
        printf("\nKhong the mo file");
        _getch();
        return;
    }

    int ktra;
    ChitietHoadon dulieu;
    CTHD_Node *tmp = ds.head;
    
    while ((ktra = fscanf(f, "%20s %20s %10d %20lf", dulieu.maHoadon, 
                        dulieu.sanpham.tenSP, &dulieu.soluong_mua, &dulieu.tien)) == 4)
    {
        CTHD_Node *p = create_CTHD_Node(dulieu);
        int find = 0;
        while (tmp != NULL)
        {
            if (strcmp(tmp->data.maHoadon, p->data.maHoadon) == 0 
                        && strcmp(tmp->data.sanpham.tenSP, p->data.sanpham.tenSP) == 0)
            {
                find = 1;
                free(p);
                break;
            }
            tmp = tmp->next;
        }

        tmp = ds.head;
        if (find != 1)
        {
            if (ds.head == NULL)
            {
                ds.head = ds.tail = p;
            }
            else
            {
                ds.tail->next = p;
                ds.tail = p;
            }
            (*slg_CTHD)++;
        }
    }
    fclose(f);
}


void ghiFIle_Hoadon(HD_List ds)
{
    FILE *f = fopen("Hoadon.txt", "w");
    if (f == NULL)
    {
        printf("\nKhong mo duoc file");
        _getch();
        return;
    }

    for (HD_Node *k = ds.head; k != NULL; k = k->next)
    {
        fprintf(f, "%-20s %-20s %-20s %02d/%02d/%-10d %-10d %-20.0lf\n", k->data.maHoadon, 
                    k->data.khachhang.maKH, k->data.khachhang.tenKH, 
                    k->data.ngay_nhap.ngay, k->data.ngay_nhap.thang, 
                    k->data.ngay_nhap.nam, k->data.soLuongCTHD, k->data.tongTien);    
    }

    fclose(f);
}

void docFile_Hoadon(HD_List &HD_list, CTHD_List CTHD_list, int *slg_HD, int *slg_CTHD)
{
    FILE *f = fopen("Hoadon.txt", "r");
    if (f == NULL)
    {
        printf("\nKhong the mo file");
        _getch();
        return;
    }

    int ktra;
    Hoadon dulieu;
    HD_Node *tmp_HD = HD_list.head;

    while ((ktra = fscanf(f, "%20s %20s %20s %02d/%02d/%10d %10d %20lf", 
                            dulieu.maHoadon, dulieu.khachhang.maKH, dulieu.khachhang.tenKH, 
                            &dulieu.ngay_nhap.ngay, &dulieu.ngay_nhap.thang, &dulieu.ngay_nhap.nam, 
                            &dulieu.soLuongCTHD, &dulieu.tongTien)) == 8)
    {
        HD_Node *p = create_HD_Node(dulieu);
        int find = 0;
        while (tmp_HD != NULL)
        {
            if (strcmp(tmp_HD->data.maHoadon, p->data.maHoadon) == 0)
            {
                find = 1;
                free(p);
                break;
            }
            tmp_HD = tmp_HD->next;
        }
        tmp_HD = HD_list.head;

        //Đọc dữ liệu từ File ChitietHoadon để lưu vào danh sách CTHD của hoá đơn tương ứng
        CTHD_Node *k = CTHD_list.head;
        while(k != NULL)
        {
            if (strcmp(p->data.maHoadon, k->data.maHoadon) == 0)
            {
                CTHD_Node *luutru = create_CTHD_Node(k->data);
                if (p->data.CTHDHead == NULL)
                {
                    p->data.CTHDHead = luutru;
                    p->data.CTHDTail = luutru;
                }
                else
                {
                    p->data.CTHDTail->next = luutru;
                    p->data.CTHDTail = luutru;
                }
            }
            k = k->next;
        }

        if (find != 1)  //Kiểm tra nếu mã hoá đơn không trùng thì thêm vào cuối ds hoá đơn
        {
            if (HD_list.head == NULL)
            {
                HD_list.head = HD_list.tail = p;
            }
            else
            {
                HD_list.tail->next = p;
                HD_list.tail = p;
            }
            (*slg_HD)++;
        }
        
    }
    fclose(f);
}

//Hàm nhập, xuất thông tin của các đối tượng
void nhapthongtin_khachhang(Khachhang &kh)
{
    fflush(stdin);
    printf("\nNhap ma khach hang: ", kh.maKH); 
    scanf("%s",kh.maKH);
    printf("\nNhap tuoi: ",kh.tuoi); 
    scanf("%d",&kh.tuoi);
    printf("\nNhap gioi tinh: ", kh.gioiTinh); 
    scanf("%s",kh.gioiTinh);
    printf("\nNhap so dien thoai: ", kh.Sdt); 
    scanf("%s",kh.Sdt);
}
void xuatthongtin_khachhang(Khachhang kh)
{
    printf("\nMa khach hang: %s",kh.maKH);
    printf("\nTen khach hang: %s",kh.tenKH);
    printf("\nTuoi: %d",kh.tuoi);
    printf("\nGioi tinh: %s",kh.gioiTinh);
    printf("\nSo dien thoai: %s",kh.Sdt);
}

void nhapthongtin_hanghoa(Hanghoa &hh)
{
    fflush(stdin);
    printf("\nNhap ten san pham: "); 
    scanf("%s",hh.tenSP);
    printf("\nNhap so luong: "); 
    scanf("%d",&hh.soLuong);
    printf("\nNhap gia ban: "); 
    scanf("%lf", &hh.giaBan);
}
void xuatthongtin_hanghoa(Hanghoa hh)
{
    printf("\nTen san pham: %s", hh.tenSP);
    printf("\nSo luong sp: %d", hh.soLuong);
    printf("\nGia ban: %lf", hh.giaBan);
}

//Hàm tính tiền cho mỗi chi tiết hoá đơn tương ứng
void tinhTien_CTHD(ChitietHoadon *cthd, HH_List HH_list) 
{
    // Duyệt danh sách hàng hóa để tìm sản phẩm tương ứng với chi tiết hóa đơn
    HH_Node *node = HH_list.head;
    double tien = 0.00;
    while (node != NULL) {
        if (strcmp(node->data.tenSP, cthd->sanpham.tenSP) == 0) 
        {
            // Tìm được sản phẩm tương ứng, tính tiền cho chi tiết hóa đơn
            tien = node->data.giaBan *cthd->soluong_mua; 
            break;
        }
        node = node->next;
    }

    cthd->tien = tien;
}

void nhapthongtin_chitiethoadon(ChitietHoadon &cthd, HH_List HH_list)
{
    fflush(stdin);
    printf("\nNhap ten san pham: ");
    scanf("%s", cthd.sanpham.tenSP);
    printf("\nNhap so luong mua: "); 
    scanf("%d",&cthd.soluong_mua);

}

void xuatthongtin_chitiethoadon(ChitietHoadon cthd)
{
    printf("\nMa hoa don: %s",cthd.maHoadon);
    printf("\nTen san pham: %s", cthd.sanpham.tenSP);
    printf("\nSo luong mua: %d",cthd.soluong_mua);
    printf("\nSo tien: %0.0lf", cthd.tien);
}

void nhapthongtin_hoadon(Hoadon &hd)
{
    fflush(stdin);
    // printf("\nNhap ma hoa don: "); 
    // scanf("%s",hd.maHoadon);
    printf("\nNhap ten khach hang: ");
    scanf("%s", hd.khachhang.tenKH);
    printf("\nNhap ngay tao hoa don: "); 
    scanf("%d/%d/%d",&hd.ngay_nhap.ngay,&hd.ngay_nhap.thang,&hd.ngay_nhap.nam);
    printf("\nNhap so luong CTHD: ");
    scanf("%d",&hd.soLuongCTHD);
}
void xuatthongtin_hoadon(Hoadon hd)
{
    printf("\nMa hoa don: %s",hd.maHoadon);
    printf("\nMa khach hang: %s", hd.khachhang.maKH);
    printf("\nTen khach hang: %s", hd.khachhang.tenKH);
    printf("\nNgay nhap tao hoa don: %d/%d/%d",hd.ngay_nhap.ngay,hd.ngay_nhap.thang,hd.ngay_nhap.nam);
    printf("\nSo luong CTHD: %d", hd.soLuongCTHD);
    printf("\nTong tien: %0.0lf", hd.tongTien);
}

//Hàm thêm các đối tượng mới vào cuối danh sách
void them_vao_cuoi_Khachhang(KH_List &l, KH_Node *p)
{
    if (l.head == NULL)
    {
        l.head = l.tail = p;
    }
    else
    {
        l.tail->next = p;
        l.tail = p;
    }
}

void them_vao_cuoi_hanghoa(HH_List &l, HH_Node *p)
{
    if (l.head == NULL)
    {
        l.head = l.tail = p;
    }
    else
    {
        l.tail->next = p;
        l.tail = p;
    }
}

void them_vao_cuoi_chitiethoadon(CTHD_List &l, CTHD_Node *p)
{
    if (l.head == NULL)
    {
        l.head = l.tail = p;
    }
    else
    {
        l.tail->next = p;
        l.tail = p;
    }
}

void them_vao_cuoi_hoadon(HD_List &l, HD_Node *p)
{
    if (l.head == NULL)
    {
        l.head = l.tail = p;
    }
    else
    {
        l.tail->next = p;
        l.tail = p;
    }
}

//Hàm kiểm tra xem hàng hoá mới nhập có tồn tại trong danh sách chưa
int ktra_HH(HH_List HH_list, Hanghoa hh)
{
    HH_Node *tmp = HH_list.head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.tenSP, hh.tenSP) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

//Hàm tăng số lượng của hàng hoá khi nhập thêm sản phẩm đã tồn tại trước đây
void tang_slgHH(HH_List &HH_list, Hanghoa hh, int slgTang)
{
    HH_Node *k = HH_list.head;
    while (k != NULL)
    {
        if (strcmp(k->data.tenSP, hh.tenSP) == 0)
        {
            k->data.soLuong = k->data.soLuong + slgTang;
        }
        k = k->next;
    }
}

//Hàm thêm hàng hoá vào danh sách hàng hoá (thêm vào kho)
void them_HH(HH_List &HH_list, int *slg_HH)
{
    printf("\nNhap so hang hoa ban muon them: ");
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++)
    {
        Hanghoa hh;
        printf("\n------ Nhap vao thong tin hang hoa thu %d ------", i);
        nhapthongtin_hanghoa(hh);

        if (ktra_HH(HH_list, hh) == 1)      //Nếu sản phẩm đã tồn tại thì tăng thêm số lượng trong kho
        {
            printf("\nSan pham %s da ton tai trong kho!", hh.tenSP);
            int m;
            printf("\nVui long nhap vao so luong them moi cua san pham: ");
            scanf("%d", &m);
            tang_slgHH(HH_list, hh, m);
            (*slg_HH) = (*slg_HH) + m;
        }
        else
        {
            HH_Node *tmp = create_HH_Node(hh);
            them_vao_cuoi_hanghoa(HH_list, tmp);
            (*slg_HH)++;
        }
    }
}

//Hàm kiểm tra Khách hàng đã có tên trong hệ thống chưa
int ktra_KH(KH_List KH_list, Khachhang kh)
{
    KH_Node *tmp = KH_list.head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.tenKH, kh.tenKH) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

int ktra_CTHD(HH_List HH_list, ChitietHoadon cthd)
{
    if (HH_list.head == NULL)
        return 0;
    HH_Node *tmp = HH_list.head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.tenSP, cthd.sanpham.tenSP) == 0)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

void them_KH(KH_List &KH_list, int *slg_KH, Khachhang &kh)
{
    printf("\nKhach hang %s lan dau mua tai cua hang.", kh.tenKH);
    printf("\nVui long nhap thong tin khach hang: \n");
    nhapthongtin_khachhang(kh);
    KH_Node *KH_tmp = create_KH_Node(kh);
    them_vao_cuoi_Khachhang(KH_list, KH_tmp);
    (*slg_KH)++;
}

//Hàm tính tổng tiền của hoá đơn (tổng tiền các CTHD)
void tongTien_HD(HD_Node *hd)
{
    CTHD_Node *tmp = hd->data.CTHDHead;
    double tong = 0;
    
    while (tmp != NULL)
    {
        tong = tong + tmp->data.tien;
        tmp = tmp->next;
    }

    hd->data.tongTien = tong;
}

//Hàm giảm số lượng HH trong kho khi có khách hàng mua
int giam_slgHH(ChitietHoadon CTHD, HH_List &HH_list)
{
    HH_Node *k = HH_list.head;
    while (k != NULL)
    {
        if (strcmp(CTHD.sanpham.tenSP, k->data.tenSP) == 0)
        {
            if (CTHD.soluong_mua > k->data.soLuong)
            {
                printf("\nSo luong ban mua lon hon so luong hang trong kho.");
                printf("\nHien tai hang hoa co the mua toi da la: %d", k->data.soLuong);
                printf("\nHay nhap lai... ");
                return 1;
            }
            else
            {
                k->data.soLuong = k->data.soLuong - CTHD.soluong_mua;
                return 0;
            }
        }
        k = k->next;
    }
}

// Hàm ktra_HD   
int ktra_HD(HD_List HD_list, char *maHoadon)
{
    HD_Node *tmp = HD_list.head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.maHoadon, maHoadon) == 0)
        return 1;
        tmp = tmp->next;
    }
    
    return 0;
}

//Tạo mã hoá đơn tự động không bị trùng với hoá đơn đã có trong file
void tao_maHD(HD_List HD_list, char *maHD)
{
    int i = 1;
    char tmp[10];
    sprintf(tmp, "%d", i);
    strcpy(maHD, "HD");
    strcat(maHD, tmp);
    while (ktra_HD(HD_list, maHD) == 1)
    {
        i++;
        sprintf(tmp, "%d", i);
        strcpy(maHD, "HD");
        strcat(maHD, tmp);
    }
}


//Hàm thêm hoá đơn mới khi có khách hàng mua
void them_HD(HD_List &HD_list, CTHD_List &CTHD_list, HH_List HH_list, KH_List &KH_list, 
                                                int *slg_KH, int *slg_HD, int *slg_CTHD)
{
    Hoadon HD;
    nhapthongtin_hoadon(HD);
    tao_maHD(HD_list, HD.maHoadon);

    if (ktra_HD(HD_list, HD.maHoadon) == 1)
    {
        printf("\nMa hoa don %s da ton tai!", HD.maHoadon);
        printf("\nVui long nhap lai...");
        _getch();
        return;
    }
    
    if (ktra_KH(KH_list, HD.khachhang) == 0)
    {   
        Khachhang tmp = HD.khachhang;
        them_KH(KH_list, slg_KH, tmp);
        strcpy(HD.khachhang.maKH, tmp.maKH);
    }
    else
    {
        KH_Node *tmp_KH = KH_list.head;
        while (tmp_KH != NULL)
        {
            if (strcmp(HD.khachhang.tenKH, tmp_KH->data.tenKH) == 0)
                strcpy(HD.khachhang.maKH, tmp_KH->data.maKH);
            tmp_KH = tmp_KH->next;
        }
    }

    HD_Node *tmp_HD = create_HD_Node(HD);
    int i = 1;
    while (i <= tmp_HD->data.soLuongCTHD)
    {
        ChitietHoadon CTHD;
        do
        {
            printf("\n------ Nhap vao san pham mua thu %d ------", i);
            nhapthongtin_chitiethoadon(CTHD, HH_list);  //Ds hàng hoá để tính tiền của hàng hoá
            strcpy(CTHD.maHoadon, HD.maHoadon);
        }
        while (giam_slgHH(CTHD, HH_list) == 1);

        int ktra = ktra_CTHD(HH_list, CTHD);
        if  (ktra == 1)  //Kiểm tra sp vừa nhập có tồn tại trong danh sách hàng hoá không
        { //Nếu có
            tinhTien_CTHD(&CTHD, HH_list);
            CTHD_Node *tmp_CTHD = create_CTHD_Node(CTHD);
            if (tmp_HD->data.CTHDHead == NULL)
                tmp_HD->data.CTHDHead = tmp_HD->data.CTHDTail = tmp_CTHD;
            else
            {
                tmp_HD->data.CTHDTail->next = tmp_CTHD;
                tmp_HD->data.CTHDTail = tmp_CTHD;
            }

            CTHD_Node *CTHD_tmp = create_CTHD_Node(CTHD);   //tạo chi tiết hoá đơn để thêm vào ds CTHD gốc (tổng rất nhiều chi tiết hoá đơn)
            them_vao_cuoi_chitiethoadon(CTHD_list, CTHD_tmp);

            (*slg_CTHD)++;
            i++; 
        }
        else
        {  //Nếu không
            printf("\nSan pham %s khong ton tai trong ds hang hoa", CTHD.sanpham.tenSP);
            printf("\nVui long nhap lai!");
        }   
    }

    tongTien_HD(tmp_HD);
    them_vao_cuoi_hoadon(HD_list, tmp_HD);
    (*slg_HD)++;
}

void in_Hoadon(HD_List HD_list)
{
    HD_Node *tmp = HD_list.head;
    int i = 0;
    while (tmp != NULL)
    {
        printf("\n\t--- HD %d ---", ++i);
        xuatthongtin_hoadon(tmp->data);
        // int i = 0;
        // for (CTHD_Node *h = tmp->data.CTHDHead; h != NULL; h = h->next)
        // {
        //     printf("\n  **** CTHD %d ****", ++i);
        //     xuatthongtin_chitiethoadon(h->data);
        // }
        tmp = tmp->next;
    }
    _getch();
}

//Hàm sắp xếp danh sách hoá đơn giảm theo tổng tiền
void SX_HD_tongTien_giam(HD_List &HD_list)
{
    for (HD_Node *i = HD_list.head; i != NULL; i = i->next)
    {
        for (HD_Node *j = i->next; j != NULL; j = j->next)
        {
            if (i->data.tongTien < j->data.tongTien)
            {
                Hoadon tmp = i->data;
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
}

//Hàm sắp xếp danh sách hoá đơn tăng theo mã Khách hàng
void SX_HD_maKH_tang(HD_List &HD_list)
{
    for (HD_Node *i = HD_list.head; i != NULL; i = i->next)
    {
        for (HD_Node *j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->data.khachhang.maKH, j->data.khachhang.maKH) > 0)
            {
                Hoadon tmp = i->data;
                i->data = j->data;
                j->data = tmp;
            }
        }
    }
}


//In ra hoá đơn có tổng tiền max
void HD_tongTien_max(HD_List HD_list)
{
    HD_Node *max = HD_list.head;
    HD_Node *k = HD_list.head->next;
    while (k != NULL)
    {
        if (k->data.tongTien > max->data.tongTien)
            max = k;
        k = k->next;
    }

    k = HD_list.head;
    printf("\nCac hoa don co tong tien lon nhat la:  ");
    printf("\n--------------------------------------");
    while (k != NULL)
    {
        if (k->data.tongTien == max->data.tongTien)
        {
            printf("\n");
            xuatthongtin_hoadon(k->data);
        }
        k = k->next;
    }
}

//Hàm trả về thông tin hoá đơn có mã Hoá đơn tương ứng
HD_Node *timKiem_HD_maHD(HD_List HD_list, char maHD[])
{
    HD_Node *tmp = HD_list.head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.maHoadon, maHD) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}


//Hàm in ra các hoá đơn có mã Khách hàng tương ứng
void lietKe_HD_maKH(HD_List HD_list, char maKH[])
{
    HD_Node *tmp = HD_list.head;
    printf("\nCac hoa don co ma khach hang: %s", maKH);
    printf("\n----------------------------------");
    int i = 0;
    while (tmp != NULL)
    {
        if (strcmp(tmp->data.khachhang.maKH, maKH) == 0)
        {
            printf("\n >>>>> HD %d <<<<<", ++i);
            xuatthongtin_hoadon(tmp->data);
        }
        tmp = tmp->next;
    }   
}

//Hàm thống kê doanh thu theo ngày
void thongKe_doanhThu_ngay(HD_List HD_List, int ngay, int thang, int nam)
{
    HD_Node *tmp = HD_List.head;
    double tong = 0;
    int i = 0;
    while (tmp != NULL)
    {
        if (tmp->data.ngay_nhap.ngay == ngay && 
            tmp->data.ngay_nhap.thang == thang &&
            tmp->data.ngay_nhap.nam == nam)
        {
            printf("\n >>>>> HD %d <<<<<", ++i);
            xuatthongtin_hoadon(tmp->data);
            tong = tong + tmp->data.tongTien;
        }
        tmp = tmp->next;
    }
    printf("\n============================\n");
    printf("\nTong doanh thu cua ngay %d/%d/%d la: %0.0lf", ngay, thang, nam, tong);
}

//Hàm thống kê doanh thu theo tháng
void thongKe_doanhThu_thang(HD_List HD_List, int thang, int nam)
{
    HD_Node *tmp = HD_List.head;
    double tong = 0;
    int i = 0;
    while (tmp != NULL)
    {
        if (tmp->data.ngay_nhap.thang == thang &&
            tmp->data.ngay_nhap.nam == nam)
        {
            printf("\n >>>>> HD %d <<<<<", ++i);
            xuatthongtin_hoadon(tmp->data);
            tong = tong + tmp->data.tongTien;
        }
        tmp = tmp->next;
    }
    printf("\n============================\n");
    printf("\nTong doanh thu cua thang %d/%d la: %0.0lf", thang, nam, tong);
}

//Hàm thống kê doanh thu theo năm
void thongKe_doanhThu_nam(HD_List HD_List, int nam)
{
    HD_Node *tmp = HD_List.head;
    double tong = 0;
    int i = 0;
    while (tmp != NULL)
    {
        if (tmp->data.ngay_nhap.nam == nam)
        {
            printf("\n >>>>> HD %d <<<<<", ++i);
            xuatthongtin_hoadon(tmp->data);
            tong = tong + tmp->data.tongTien;
        }
        tmp = tmp->next;
    }
    printf("\n============================\n");
    printf("\nTong doanh thu cua nam %d la: %0.0lf", nam, tong);
}

//Hàm thống kê doanh thu theo quý
void thongKe_doanhThu_quy(HD_List HD_List, int quy, int nam)
{
    HD_Node *tmp = HD_List.head;
    double tong = 0;
    int i = 0;
    while (tmp != NULL)
    {
        if (tmp->data.ngay_nhap.nam == nam)
        {
            if (quy == 1)
            {
                if (tmp->data.ngay_nhap.thang >= 1 && tmp->data.ngay_nhap.thang <= 3)
                {
                    printf("\n >>>>> HD %d <<<<<", ++i);
                    xuatthongtin_hoadon(tmp->data);
                    tong = tong + tmp->data.tongTien;
                }
            }

            if (quy == 2)
            {
                if (tmp->data.ngay_nhap.thang >= 4 && tmp->data.ngay_nhap.thang <= 6)
                {
                    printf("\n >>>>> HD %d <<<<<", ++i);
                    xuatthongtin_hoadon(tmp->data);
                    tong = tong + tmp->data.tongTien;
                }
            }

            if (quy == 3)
            {
                if (tmp->data.ngay_nhap.thang >= 7 && tmp->data.ngay_nhap.thang <= 9)
                {
                    printf("\n >>>>> HD %d <<<<<", ++i);
                    xuatthongtin_hoadon(tmp->data);
                    tong = tong + tmp->data.tongTien;
                }
            }

            if (quy == 4)
            {
                if (tmp->data.ngay_nhap.thang >= 10 && tmp->data.ngay_nhap.thang <= 12)
                {
                    printf("\n >>>>> HD %d <<<<<", ++i);
                    xuatthongtin_hoadon(tmp->data);
                    tong = tong + tmp->data.tongTien;
                }
            }
        }
        tmp = tmp->next;
    }
    printf("\n============================\n");
    printf("\nTong doanh thu cua nam %d la: %0.0lf", nam, tong);
}

//Hàm thống kê doanh thu theo ngày, tháng, năm
void thongKe_doanhThu_ngay_thang_nam(HD_List HD_list)
{
    printf("\nBan muon thong ke doanh thu theo: ");
    printf("\n\t1. Ngay");
    printf("\n\t2. Thang");
    printf("\n\t3. Nam");
    printf("\n\t4. Quy");

    int lc;
    printf("\nVui long nhap lua chon: ");
    scanf("%d", &lc);

    switch (lc)
    {
    case 1:
        {
            Date ngay;
            printf("\nNhap vao ngay ban muon thong ke (ngay/thang/nam): ");
            scanf("%d/%d/%d", &ngay.ngay, &ngay.thang, &ngay.nam);
            printf("\nCac hoa don cua ngay: %d/%d/%d", ngay.ngay, ngay.thang, ngay.nam);
            printf("\n--------------------------------");
            thongKe_doanhThu_ngay(HD_list, ngay.ngay, ngay.thang, ngay.nam);
            break;
        }
        break;
    case 2:
        {
            int thang, nam;
            printf("\nNhap vao thang ban muon thong ke (thang/nam): ");
            scanf("%d/%d", &thang, &nam);
            printf("\nCac hoa don cua thang: %d/%d", thang, nam);
            printf("\n--------------------------------");
            thongKe_doanhThu_thang(HD_list, thang, nam);
            break;
        }
        break;
    case 3:
        {
            int nam;
            printf("\nNhap vao nam ban muon thong ke: ");
            scanf("%d", &nam);
            printf("\nCac hoa don cua nam: %d", nam);
            printf("\n--------------------------------");
            thongKe_doanhThu_nam(HD_list, nam);
            break;
        }
        break;
    case 4:
        {
            int nam, quy;
            printf("\nNhap vao quy ban muon thong ke (quy/nam): ");
            scanf("%d/%d", &quy, &nam);
            printf("\nCac hoa don cua quy: %d", nam);
            printf("\n--------------------------------");
            thongKe_doanhThu_quy(HD_list, quy, nam);
            break;
        }
        break;
    }
}


int main()
{
    KH_List KH_list;
    HH_List HH_list;
    CTHD_List CTHD_list;
    HD_List HD_list;
    init_HD(HD_list);
    init_CTHD(CTHD_list);
    init_KH(KH_list);
    init_HH(HH_list);
    int slg_KH;
    int slg_CTHD;
    int slg_HH;
    int slg_HD;

    docFile_Khachhang(KH_list, &slg_KH);
    docFile_Hanghoa(HH_list, &slg_HH);
    docFile_ChitietHoadon(CTHD_list, &slg_CTHD);
    docFile_Hoadon(HD_list, CTHD_list, &slg_HD, &slg_CTHD);

    while ( 1 != 0)
    {
        system("cls");
        printf("---------------- MENU ------------------");
        printf("\n\t1.  Them hang hoa.");
        printf("\n\t2.  Them hoa don va cac chi tiet hoa don tuong ung.");
        printf("\n\t3.  In thong tin tat ca chi tiet hoa don.");
        printf("\n\t4.  In thong tin tat ca khach hang.");
        printf("\n\t5.  In thong tin tat ca hoa don.");
        printf("\n\t6.  In thong tin tat ca hang hoa.");
        printf("\n\t7.  Sap xep hoa don giam dan theo tong tien.");
        printf("\n\t8.  Sap xep hoa don tang dan theo ma khach hang.");
        printf("\n\t9.  Hoa don co tong tien lon nhat.");
        printf("\n\t10. Tim kiem hoa don dua tren ma Hoa don.");
        printf("\n\t11. Liet ke thong tin hoa don dua theo ma khach hang.");
        printf("\n\t12. Thong ke doanh thu theo ngay/thang/quy/nam.");
        printf("\n\t0. Thoat!");
        printf("\n---------------- END ------------------");

        int lc;
        printf("\nNhap vao lua chon: ");
        scanf("%d", &lc);
        switch (lc)
        {
        case 1:
        {
            them_HH(HH_list, &slg_HH);
            ghiFIle_Hanghoa(HH_list);
            break;
        }
        case 2:
        {
            them_HD(HD_list, CTHD_list, HH_list, KH_list, &slg_KH, &slg_HD, &slg_CTHD);
            ghiFIle_Khachhang(KH_list);
            ghiFIle_Hoadon(HD_list);
            ghiFIle_ChitietHoadon(CTHD_list);
            ghiFIle_Hanghoa(HH_list);
            break;
        }
        case 3: 
        {
            int i = 0;
            for (CTHD_Node *k = CTHD_list.head; k != NULL; k = k->next)
            {
                printf("\n\t--- CTHD %d ---", ++i);
                xuatthongtin_chitiethoadon(k->data);
            }
            _getch();
            break;
        }
        case 4: 
        {
            int i = 0;
            for (KH_Node *k = KH_list.head; k != NULL; k = k->next)
            {
                printf("\n\t--- KH %d ---", ++i);
                xuatthongtin_khachhang(k->data);
            }
            _getch();
            break;
        }
        case 5: 
        {
            in_Hoadon(HD_list);
            break;
        }
        case 6: 
        {
            int i = 0;
            for (HH_Node *k = HH_list.head; k != NULL; k = k->next)
            {
                printf("\n\t--- HH %d ---", ++i);
                xuatthongtin_hanghoa(k->data);
            }
            _getch();
            break;
        }
        case 7:
        {
            SX_HD_tongTien_giam(HD_list);
            break;
        }
        case 8: 
        {
            SX_HD_maKH_tang(HD_list);
            break;
        }
        case 9:
        {
            HD_tongTien_max(HD_list);
            _getch();
            break;
        }
        case 10:
        {
            char maHD[50];
            printf("\nNhap vao ma hoa don can tim: ");
            scanf("%s", maHD);
            HD_Node *timkiem = timKiem_HD_maHD(HD_list, maHD);
            if (timkiem == NULL)
            {
                printf("\nKhong tim thay hoa don co ma hoa don %s trong danh sach hoa don", maHD);
            }
            else
            {
                printf("\nThong tin mua hoa don co ma %s", maHD);
                printf("\n-------------------------------");
                xuatthongtin_hoadon(timkiem->data);
                printf("\n");
                int i = 0;
                for (CTHD_Node *h = timkiem->data.CTHDHead; h != NULL; h = h->next)
                {
                    printf("\n >>>>> CTHD %d <<<<<", ++i);
                    xuatthongtin_chitiethoadon(h->data);
                }
            }
            _getch();
            break;
        }
        case 11: 
        {
            printf("\nNhap vao ma khach hang cua hoa don ban muon tim: ");
            char maKH[100];
            scanf("%s", maKH);
            lietKe_HD_maKH(HD_list, maKH);
            _getch();
            break;
        }
        case 12: 
        {
            thongKe_doanhThu_ngay_thang_nam(HD_list);
            _getch();
            break;
        }
        case 0: return 1;
            break;
        }
    }
}