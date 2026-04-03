# Snake Game (C++)

Một phiên bản trò chơi Rắn Săn Mồi (Snake Game) đơn giản được viết bằng C++, chạy trực tiếp trên Console (Terminal).

## Tính năng

- Giao diện trò chơi hiển thị bằng ký tự trên màn hình Console.
- Hình dáng rắn hiển thị bằng các ký tự `X`.
- Cho phép người chơi điều khiển rắn di chuyển.

## Phím điều khiển

Sử dụng các phím sau để điều khiển rắn:
- `w`: Đi lên
- `x`: Đi xuống
- `a`: Sang trái
- `d`: Sang phải

## Hướng dẫn chạy

### Yêu cầu hệ thống
- Hệ điều hành **Windows** (vì mã nguồn sử dụng thư viện `<windows.h>` và `<conio.h>`).
- Trình biên dịch C++ (GCC/MinGW hoặc Visual Studio C++).

### Các bước thực hiện
1. **Clone** repository về máy:
   ```bash
   git clone https://github.com/reikfowo17/Snake_Game.git
   ```
2. Mở thư mục dự án:
   ```bash
   cd Snake_Game
   ```
3. Biên dịch mã nguồn (ví dụ sử dụng `g++`):
   ```bash
   g++ Snake.cpp -o SnakeGame.exe
   ```
4. Chạy file thực thi:
   ```bash
   ./SnakeGame.exe
   ```

## Mã nguồn
- File `Snake.cpp` chứa toàn bộ logic chương trình.
