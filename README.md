# brain_app
 
CeGCC �̐ݒ� (WSL�g��)
�� �Q�l: https://brain.fandom.com/ja/wiki/CeGCC

CeGCC�C���X�g�[��
�@sudo bash -c 'echo "deb [trusted=yes] https://max.kellermann.name/debian cegcc_buster-default main" > /etc/apt/sources.list.d/gcc-arm-mingw32ce.list'
�@sudo apt update
�@sudo apt install gcc-arm-mingw32ce

�R���p�C��
�@arm-mingw32ce-g++ -Wall -Wextra -O3 -std=gnu++2a -march=armv5tej -mcpu=arm926ej-s -static -s -lcommctrl -lcommdlg -lmmtimer -o AppMain.exe (�R���p�C������t�@�C��).cpp
