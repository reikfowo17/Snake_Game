#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// 1. KHAI BÁO

int WIDTH; 
int HEIGHT;
void gotoxy(int column, int line);
void Nocursortype();
void VeTuong();
void GetTerminalSize();
void ThayDoiKichThuocManHinh();

struct Point {
  int x, y;
};

class CONRAN {
public:
  struct Point A[100];
  int DoDai;
  
  CONRAN();                  
  void Ve();                 
  void XoaDuoi();            
  void DiChuyen(int Huong);  
  void GiuTrongKhung();      
};

// 2. HÀM MAIN

int main() {
  GetTerminalSize();
  Nocursortype(); 
  system("cls"); 
  VeTuong();
  CONRAN r;
  int Huong = 0;
  r.Ve(); 
  int prevW = WIDTH;
  int prevH = HEIGHT;

  while (1) {
    GetTerminalSize();
    if (WIDTH != prevW || HEIGHT != prevH) {
      prevW = WIDTH;
      prevH = HEIGHT;
      ThayDoiKichThuocManHinh();
      GetTerminalSize();
      system("cls");
      VeTuong();
      r.GiuTrongKhung();
    }

    bool hasKey = false;
    char key = 0;
    
    while (_kbhit()) {
      key = _getch(); 
      hasKey = true;
    }

    if (hasKey) {
      if ((key == 'a' || key == 'A') && Huong != 0) Huong = 2;
      else if ((key == 'w' || key == 'W') && Huong != 1) Huong = 3;
      else if ((key == 'd' || key == 'D') && Huong != 2) Huong = 0;
      else if ((key == 's' || key == 'S') && Huong != 3) Huong = 1;
    }

    r.DiChuyen(Huong);
    r.Ve();
    
    cout << flush;
    Sleep(120); 
  }

  return 0;
}

// 3. ĐỊNH NGHĨA HÀM

CONRAN::CONRAN() {
  DoDai = 3;
  A[0].x = 12; A[0].y = 10;
  A[1].x = 11; A[1].y = 10;
  A[2].x = 10; A[2].y = 10;
}

void CONRAN::Ve() {
  for (int i = 0; i < DoDai; i++) {
    gotoxy(A[i].x, A[i].y);
    cout << "X";
  }
}

void CONRAN::XoaDuoi() {
  gotoxy(A[DoDai - 1].x, A[DoDai - 1].y);
  cout << " "; 
}

void CONRAN::DiChuyen(int Huong) {
  XoaDuoi(); 
  
  for (int i = DoDai - 1; i > 0; i--)
    A[i] = A[i - 1];
    
  if (Huong == 0) A[0].x = A[0].x + 1; 
  if (Huong == 1) A[0].y = A[0].y + 1; 
  if (Huong == 2) A[0].x = A[0].x - 1; 
  if (Huong == 3) A[0].y = A[0].y - 1; 

  if (A[0].x >= WIDTH) {
      A[0].x = 1; 
  } else if (A[0].x <= 0) {
      A[0].x = WIDTH - 1; 
  }

  if (A[0].y >= HEIGHT) {
      A[0].y = 1; 
  } else if (A[0].y <= 0) {
      A[0].y = HEIGHT - 1; 
  }
}

void CONRAN::GiuTrongKhung() {
  for (int i = 0; i < DoDai; i++) {
    if (A[i].x < 1)
      A[i].x = 1;
    else if (A[i].x >= WIDTH)
      A[i].x = WIDTH - 1;
    if (A[i].y < 1)
      A[i].y = 1;
    else if (A[i].y >= HEIGHT)
      A[i].y = HEIGHT - 1;
  }
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
    WIDTH = csbi.srWindow.Right - csbi.srWindow.Left;
    HEIGHT = csbi.srWindow.Bottom - csbi.srWindow.Top;
}

void ThayDoiKichThuocManHinh() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    SMALL_RECT window = csbi.srWindow;
    COORD newSize;
    newSize.X = window.Right - window.Left + 1;
    newSize.Y = window.Bottom - window.Top + 1;

    // Chi thay doi buffer neu can
    if (csbi.dwSize.X < newSize.X || csbi.dwSize.Y < newSize.Y) {
        SetConsoleScreenBufferSize(hConsole, newSize);
    }

    // Dat lai kich thuoc cua so (truong hop full screen / maximize)
    SMALL_RECT newWindow = {0, 0, (SHORT)(newSize.X - 1), (SHORT)(newSize.Y - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &newWindow);
}

void VeTuong() {
    // Vẽ viền trên và viền dưới
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(i, 0); 
        cout << "+"; // Thay doi ky tu o day
        
        gotoxy(i, HEIGHT); 
        cout << "+"; // Thay doi ky tu o day
    }

    // Vẽ viền trái và viền phải
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); 
        cout << "+"; // Thay doi ky tu o day
        
        gotoxy(WIDTH, i); 
        cout << "+"; // Thay doi ky tu o day
    }
}