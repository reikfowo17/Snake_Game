#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <string>

using namespace std;

// 1. KHAI BÁO

int WIDTH;
int HEIGHT;

void gotoxy(int column, int line);
void Nocursortype();
void VeTuong();
void GetTerminalSize();
void ThayDoiKichThuocManHinh();
void SetColor(int color);
void HienThiDiem(int diem, int level);
void ManHinhBatDau();
bool ManHinhKetThuc(int diem);

struct Point {
    int x, y;
};

class CONRAN {
public:
    struct Point A[2000];
    int DoDai;
    bool chet;

    CONRAN();
    void Ve(Point Qua);
    void XoaDuoi();
    bool DiChuyen(int Huong, Point& Qua, int& Diem, int& Level);
    void GiuTrongKhung();
    bool KiemTraTuCan();
};

// 2. HÀM MAIN

int main() {
    GetTerminalSize();
    Nocursortype();

    while (true) {
        system("cls");
        ManHinhBatDau();

        system("cls");
        VeTuong();

        srand((unsigned)time(0));
        Point Qua;
        Qua.x = rand() % (WIDTH - 2) + 1;
        Qua.y = rand() % (HEIGHT - 2) + 1;

        CONRAN r;
        int Huong = 0;
        int Diem = 0;
        int Level = 1;
        int tocDo = 130;

        r.Ve(Qua);

        int prevW = WIDTH;
        int prevH = HEIGHT;

        while (true) {
            GetTerminalSize();
            if (WIDTH != prevW || HEIGHT != prevH) {
                prevW = WIDTH;
                prevH = HEIGHT;
                ThayDoiKichThuocManHinh();
                GetTerminalSize();
                system("cls");
                VeTuong();
                r.GiuTrongKhung();
                HienThiDiem(Diem, Level);
            }

            bool hasKey = false;
            char key = 0;
            while (_kbhit()) {
                key = _getch();
                hasKey = true;
            }

            if (hasKey) {
                if      ((key == 'a' || key == 'A') && Huong != 0) Huong = 2;
                else if ((key == 'w' || key == 'W') && Huong != 1) Huong = 3;
                else if ((key == 'd' || key == 'D') && Huong != 2) Huong = 0;
                else if ((key == 's' || key == 'S') && Huong != 3) Huong = 1;
                else if (key == 27) goto thoat; // ESC để thoát
            }

            bool anMoi = r.DiChuyen(Huong, Qua, Diem, Level);

            if (r.chet) break;

            if (anMoi) {
                // Tăng tốc độ theo level (tối thiểu 50ms)
                tocDo = max(50, 130 - (Level - 1) * 15);
                HienThiDiem(Diem, Level);
            }

            r.Ve(Qua);
            cout << flush;
            Sleep(tocDo);
        }

        // Game Over
        if (!ManHinhKetThuc(Diem)) break;
    }

    thoat:
    system("cls");
    SetColor(7);
    return 0;
}

// 3. ĐỊNH NGHĨA 

CONRAN::CONRAN() {
    DoDai = 3;
    chet = false;
    A[0].x = 12; A[0].y = 10;
    A[1].x = 11; A[1].y = 10;
    A[2].x = 10; A[2].y = 10;
}

void CONRAN::Ve(Point Qua) {
    // Vẽ đầu rắn (màu vàng sáng)
    SetColor(14);
    gotoxy(A[0].x, A[0].y);
    cout << "O";

    // Vẽ thân rắn (màu xanh lá)
    SetColor(10);
    for (int i = 1; i < DoDai; i++) {
        gotoxy(A[i].x, A[i].y);
        cout << "o";
    }

    // Vẽ mồi (màu đỏ sáng)
    SetColor(12);
    gotoxy(Qua.x, Qua.y);
    cout << "*";

    SetColor(7);
}

void CONRAN::XoaDuoi() {
    gotoxy(A[DoDai - 1].x, A[DoDai - 1].y);
    cout << " ";
}

bool CONRAN::DiChuyen(int Huong, Point& Qua, int& Diem, int& Level) {
    Point oldTail = A[DoDai - 1];
    XoaDuoi();

    for (int i = DoDai - 1; i > 0; i--)
        A[i] = A[i - 1];

    if (Huong == 0) A[0].x++;
    if (Huong == 1) A[0].y++;
    if (Huong == 2) A[0].x--;
    if (Huong == 3) A[0].y--;

    // Xuyên tường
    if (A[0].x >= WIDTH)  A[0].x = 1;
    else if (A[0].x <= 0) A[0].x = WIDTH - 1;
    if (A[0].y >= HEIGHT) A[0].y = 1;
    else if (A[0].y <= 0) A[0].y = HEIGHT - 1;

    // Kiểm tra tự cắn
    if (KiemTraTuCan()) {
        chet = true;
        return false;
    }

    // Ăn mồi
    if (A[0].x == Qua.x && A[0].y == Qua.y) {
        A[DoDai] = oldTail;
        DoDai++;
        Diem += 10;
        Level = Diem / 50 + 1;
        // Tạo mồi mới không trùng thân rắn
        do {
            Qua.x = rand() % (WIDTH - 2) + 1;
            Qua.y = rand() % (HEIGHT - 2) + 1;
        } while ([&]() {
            for (int i = 0; i < DoDai; i++)
                if (A[i].x == Qua.x && A[i].y == Qua.y) return true;
            return false;
        }());
        return true;
    }
    return false;
}

bool CONRAN::KiemTraTuCan() {
    for (int i = 1; i < DoDai; i++)
        if (A[0].x == A[i].x && A[0].y == A[i].y)
            return true;
    return false;
}

void CONRAN::GiuTrongKhung() {
    for (int i = 0; i < DoDai; i++) {
        if (A[i].x < 1)       A[i].x = 1;
        else if (A[i].x >= WIDTH)  A[i].x = WIDTH - 1;
        if (A[i].y < 1)       A[i].y = 1;
        else if (A[i].y >= HEIGHT) A[i].y = HEIGHT - 1;
    }
}

// 4. HÀM TIỆN ÍCH

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Nocursortype() {
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void GetTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WIDTH  = csbi.srWindow.Right - csbi.srWindow.Left;
    HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top;
}

void ThayDoiKichThuocManHinh() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    COORD newSize;
    newSize.X = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
    newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

    if (csbi.dwSize.X < newSize.X || csbi.dwSize.Y < newSize.Y)
        SetConsoleScreenBufferSize(hConsole, newSize);

    SMALL_RECT newWindow = {0, 0, (SHORT)(newSize.X - 1), (SHORT)(newSize.Y - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &newWindow);
}

void VeTuong() {
    SetColor(11); // Cyan
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(i, 0);      cout << "#";
        gotoxy(i, HEIGHT); cout << "#";
    }
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i);     cout << "#";
        gotoxy(WIDTH, i); cout << "#";
    }
    SetColor(7);
    HienThiDiem(0, 1);
}

void HienThiDiem(int diem, int level) {
    SetColor(14);
    gotoxy(2, 0);
    cout << " DIEM: " << diem << "  LEVEL: " << level << " ";
    SetColor(7);
}

void ManHinhBatDau() {
    GetTerminalSize();
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;

    SetColor(10);
    gotoxy(cx - 10, cy - 3);
    cout << "================================";
    gotoxy(cx - 10, cy - 2);
    cout << "         SNAKE  GAME            ";
    gotoxy(cx - 10, cy - 1);
    cout << "================================";

    SetColor(14);
    gotoxy(cx - 10, cy + 1);
    cout << "  W/A/S/D  : Di chuyen          ";
    gotoxy(cx - 10, cy + 2);
    cout << "  An moi   : +10 diem            ";
    gotoxy(cx - 10, cy + 3);
    cout << "  ESC      : Thoat               ";

    SetColor(11);
    gotoxy(cx - 10, cy + 5);
    cout << "  Nhan phim bat ky de bat dau... ";
    SetColor(7);

    while (!_kbhit()) Sleep(50);
    _getch();
}

bool ManHinhKetThuc(int diem) {
    GetTerminalSize();
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;

    SetColor(12);
    gotoxy(cx - 10, cy - 3);
    cout << "================================";
    gotoxy(cx - 10, cy - 2);
    cout << "          GAME  OVER!           ";
    gotoxy(cx - 10, cy - 1);
    cout << "================================";

    SetColor(14);
    gotoxy(cx - 10, cy + 1);
    cout << "  Diem cua ban: " << diem << "               ";

    SetColor(11);
    gotoxy(cx - 10, cy + 3);
    cout << "  [ENTER] Choi lai               ";
    gotoxy(cx - 10, cy + 4);
    cout << "  [ESC]   Thoat                  ";
    SetColor(7);

    while (true) {
        if (_kbhit()) {
            char k = _getch();
            if (k == 13)  return true;  // ENTER → chơi lại
            if (k == 27)  return false; // ESC   → thoát
        }
        Sleep(50);
    }
}