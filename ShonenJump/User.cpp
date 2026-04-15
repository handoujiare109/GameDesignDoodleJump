#define _CRT_SECURE_NO_WARNINGS
#include "common.h" 

// 登录
bool login() {
    
    BeginBatchDraw();

    // 定义用户名和密码的字符数组
    char username[NAME_LEN] = "";
    char password[PASS_LEN] = "";
    int username_len = 0;
    int password_len = 0;

    // 0未输入，1用户名，2密码
    int input_state = 0;
    // 0正常，1不存在，2错误
    int login_error = 0;

    RECT login_box = { 450, 250, 1150, 750 };
    RECT username_rect = { 600, 350, 1000, 400 };
    RECT password_rect = { 600, 450, 1000, 500 };
    RECT login_rect = { 600, 550, 1000, 620 };
    RECT register_rect = { 700, 650, 900, 700 };

    ExMessage msg;
    int corner_radius = 15;
    char ch;

    IMAGE bg_img;
    IMAGE bg_img1;
    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
    loadimage(&bg_img1, "F:\\GameMaterial\\Bg_1.png");

    while (1) {
        while (peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= username_rect.left && msg.x <= username_rect.right &&
                    msg.y >= username_rect.top && msg.y <= username_rect.bottom) {
                    input_state = 1;
                }
                // 点击密码文本框
                else if (msg.x >= password_rect.left && msg.x <= password_rect.right &&
                    msg.y >= password_rect.top && msg.y <= password_rect.bottom) {
                    input_state = 2;
                }
                // 点击登录按钮
                else if (msg.x >= login_rect.left && msg.x <= login_rect.right &&
                    msg.y >= login_rect.top && msg.y <= login_rect.bottom) {

                    // 登录验证
                    if (strlen(username) > 0 && strlen(password) > 0) {
                        FILE* fp = fopen(file_path, "rb");
                        if (fp != NULL) {
                            User u;
                            while (fread(&u, sizeof(User), 1, fp) == 1) {
                                if (strcmp(u.username, username) == 0 &&
                                    strcmp(u.password, password) == 0) {
                                    fclose(fp);
                                    return true;
                                }
                            }
                            fclose(fp);
                        }
                        login_error = 1;
                    }
                }
                else if (msg.x >= register_rect.left && msg.x <= register_rect.right &&
                    msg.y >= register_rect.top && msg.y <= register_rect.bottom) {
                    regist();
                }

                else {
                    input_state = 0;
                }
            }
            else if (msg.message == WM_CHAR && input_state != 0) {
                ch = msg.ch;

                // 退格
                if (ch == '\b') {
                    if (input_state == 1 && username_len > 0) {
                        username[--username_len] = '\0';
                    }
                    else if (input_state == 2 && password_len > 0) {
                        password[--password_len] = '\0';
                    }
                }
                // 回车
                else if (ch == '\r') {
                    input_state = 0;
                }
                // 普通字符
                else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
                    (ch >= '0' && ch <= '9')) {
                    if (input_state == 1 && username_len < NAME_LEN - 1) {
                        username[username_len++] = ch;
                        username[username_len] = '\0';
                    }
                    else if (input_state == 2 && password_len < PASS_LEN - 1) {
                        password[password_len++] = ch;
                        password[password_len] = '\0';
                    }
                }
            }
        }

        putimage(0, 0, &bg_img);

        // 绘制登录框
        setfillcolor(0x80FFFFFF);
        setlinecolor(RGB(200, 200, 200));
        setlinestyle(PS_SOLID, 2);
        fillroundrect(login_box.left, login_box.top,
            login_box.right, login_box.bottom, 30, 30);

        // 提示
        setbkmode(TRANSPARENT);
        settextcolor(0x3D3A39);
        setSmoothFont(30, "汉仪文黑 85W");
        outtextxy(500, 300, "用户名:");
        outtextxy(500, 400, "密码:");

        // 文本框
        setlinecolor(RGB(200, 200, 200));
        setfillcolor(WHITE);
        fillrectangle(username_rect.left, username_rect.top,
            username_rect.right, username_rect.bottom);
        fillrectangle(password_rect.left, password_rect.top,
            password_rect.right, password_rect.bottom);

        // 高亮
        if (input_state == 1) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
            rectangle(username_rect.left, username_rect.top,
                username_rect.right, username_rect.bottom);
        }
        else if (input_state == 2) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
            rectangle(password_rect.left, password_rect.top,
                password_rect.right, password_rect.bottom);
        }

        // 显示用户名和密码
        setbkmode(TRANSPARENT);
        settextcolor(LIGHTGRAY);
        setSmoothFont(25, "汉仪文黑 85W");
        if (username_len > 0) {
            outtextxy(username_rect.left + 10, username_rect.top + 12, username);
        }
        setbkmode(TRANSPARENT);
        char password_display[PASS_LEN] = "";

        for (int i = 0; i < password_len; i++) {
            password_display[i] = '*';
        }

        password_display[password_len] = '\0';
        if (password_len > 0) {
            outtextxy(password_rect.left + 10, password_rect.top + 12, password_display);
        }

        // 绘制登录按钮
        setfillcolor(0x3D3A39);
        setlinecolor(0x3D3A39);
        setlinestyle(PS_SOLID, 1);
        fillroundrect(login_rect.left, login_rect.top,
            login_rect.right, login_rect.bottom,
            corner_radius, corner_radius);

        // 登录文字
        setbkmode(TRANSPARENT);
        settextcolor(0xB3DBF9);
        setSmoothFont(35, "汉仪文黑 85W");
        int login_text_width = textwidth("登录");
        int login_text_x = login_rect.left + (login_rect.right - login_rect.left - login_text_width) / 2;
        int login_text_y = login_rect.top + (login_rect.bottom - login_rect.top - textheight("登录")) / 2;
        outtextxy(login_text_x, login_text_y, "登录");

        // 注册入口
        setbkmode(TRANSPARENT);
        settextcolor(0xB3DBF9);
        setSmoothFont(25, "汉仪文黑 85W");
        outtextxy(720, 660, "没有账号？点此注册");

        // 错误提示
        if (login_error == 1) {
            settextcolor(RED);
            outtextxy(650, 520, "用户名或密码错误！");
        }

        // 显示光标
        if (input_state != 0) {
            int cursor_x, cursor_y;
            setSmoothFont(25, "汉仪文黑 85W");

            if (input_state == 1) {
                cursor_x = username_rect.left + 10 + textwidth(username);
                cursor_y = username_rect.top + 12;
            }
            else {
                cursor_x = password_rect.left + 10 + textwidth("*") * password_len;
                cursor_y = password_rect.top + 12;
            }
            static int cursor_blink = 0;
            cursor_blink = (cursor_blink + 1) % 90;
            if (cursor_blink < 45) {
                setlinecolor(0x3D3A39);
                line(cursor_x, cursor_y, cursor_x, cursor_y + 25);
            }
        }

        FlushBatchDraw();

        Sleep(5);
    }
    EndBatchDraw();
    return false;
}

// 注册
void regist() {

    BeginBatchDraw();

    char username[NAME_LEN] = "";
    char password[PASS_LEN] = "";
    char confirm[PASS_LEN] = "";

    int username_len = 0;
    int password_len = 0;
    int confirm_len = 0;

    int input_state = 0;
    int reg_error = 0;

    RECT regist_box = { 450, 250, 1150, 750 };
    RECT username_rect = { 600,330,1000,380 };
    RECT password_rect = { 600,430,1000,480 };
    RECT confirm_rect = { 600,530,1000,580 };
    RECT regist_rect = { 600,620,1000,690 };

    IMAGE bg_img;
    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");

    ExMessage msg;
    char ch;

    while (1) {

        while (peekmessage(&msg, EX_MOUSE | EX_CHAR)) {

            if (msg.message == WM_LBUTTONDOWN) {

                if (msg.x >= username_rect.left && msg.x <= username_rect.right &&
                    msg.y >= username_rect.top && msg.y <= username_rect.bottom) {
                    input_state = 1;
                }

                else if (msg.x >= password_rect.left && msg.x <= password_rect.right &&
                    msg.y >= password_rect.top && msg.y <= password_rect.bottom) {
                    input_state = 2;
                }

                else if (msg.x >= confirm_rect.left && msg.x <= confirm_rect.right &&
                    msg.y >= confirm_rect.top && msg.y <= confirm_rect.bottom) {
                    input_state = 3;
                }

                else if (msg.x >= regist_rect.left && msg.x <= regist_rect.right &&
                    msg.y >= regist_rect.top && msg.y <= regist_rect.bottom) {

                    if (strlen(username) == 0 || strlen(password) == 0) {
                        reg_error = 1;
                    }
                    else if (strcmp(password, confirm) != 0) {
                        reg_error = 2;
                    }
                    else if (findUser(username) != -1) {
                        reg_error = 3;
                    }
                    else {

                        User u;

                        u.id = rand();
                        strcpy(u.username, username);
                        strcpy(u.password, password);
                        u.score = 0;
                        u.is_logged = 0;

                        saveUser(u);

                        return;
                    }
                }
                else {
                    input_state = 0;
                }
            }

            else if (msg.message == WM_RBUTTONDOWN) {
                return;
            }

            else if (msg.message == WM_CHAR && input_state != 0) {

                ch = msg.ch;

                if (ch == '\b') {

                    if (input_state == 1 && username_len > 0)
                        username[--username_len] = '\0';

                    else if (input_state == 2 && password_len > 0)
                        password[--password_len] = '\0';

                    else if (input_state == 3 && confirm_len > 0)
                        confirm[--confirm_len] = '\0';
                }

                else if ((ch >= 'a' && ch <= 'z') ||
                    (ch >= 'A' && ch <= 'Z') ||
                    (ch >= '0' && ch <= '9')) {

                    if (input_state == 1 && username_len < NAME_LEN - 1) {
                        username[username_len++] = ch;
                        username[username_len] = '\0';
                    }

                    else if (input_state == 2 && password_len < PASS_LEN - 1) {
                        password[password_len++] = ch;
                        password[password_len] = '\0';
                    }

                    else if (input_state == 3 && confirm_len < PASS_LEN - 1) {
                        confirm[confirm_len++] = ch;
                        confirm[confirm_len] = '\0';
                    }
                }
            }
        }

        // 背景
        putimage(0, 0, &bg_img);

        // 文本框
        setfillcolor(0x80FFFFFF);
        setlinecolor(RGB(200, 200, 200));
        setlinestyle(PS_SOLID, 2);
        fillroundrect(regist_box.left, regist_box.top,regist_box.right, regist_box.bottom, 30, 30);

        setbkmode(TRANSPARENT);
        settextcolor(0x3D3A39);
        setSmoothFont(30, "汉仪文黑 85W");

        outtextxy(500, 305, "用户名:");
        outtextxy(500, 405, "密码:");
        outtextxy(500, 505, "确认:");

        setfillcolor(WHITE);

        fillrectangle(username_rect.left, username_rect.top,
            username_rect.right, username_rect.bottom);

        fillrectangle(password_rect.left, password_rect.top,
            password_rect.right, password_rect.bottom);

        fillrectangle(confirm_rect.left, confirm_rect.top,
            confirm_rect.right, confirm_rect.bottom);

        if (input_state == 1) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
            rectangle(username_rect.left, username_rect.top,
                username_rect.right, username_rect.bottom);
        }
        else if (input_state == 2) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
            rectangle(password_rect.left, password_rect.top,
                password_rect.right, password_rect.bottom);
        }
        else if (input_state == 3) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
            rectangle(confirm_rect.left, confirm_rect.top,
                confirm_rect.right, confirm_rect.bottom);
        }
        outtextxy(username_rect.left + 10, username_rect.top + 10, username);

        char pwd_display[PASS_LEN] = "";
        for (int i = 0; i < password_len; i++)
            pwd_display[i] = '*';
        pwd_display[password_len] = '\0';

        outtextxy(password_rect.left + 10, password_rect.top + 10, pwd_display);

        char confirm_display[PASS_LEN] = "";
        for (int i = 0; i < confirm_len; i++)
            confirm_display[i] = '*';
        confirm_display[confirm_len] = '\0';

        outtextxy(confirm_rect.left + 10, confirm_rect.top + 10, confirm_display);

        setlinecolor(0x3D3A39);
        setfillcolor(0x3D3A39);
        fillroundrect(regist_rect.left, regist_rect.top,
            regist_rect.right, regist_rect.bottom, 15, 15);

        settextcolor(0xB3DBF9);
        setSmoothFont(25, "汉仪文黑 85W");

        setbkmode(TRANSPARENT);
        settextcolor(0xB3DBF9);
        setSmoothFont(35, "汉仪文黑 85W");
        int regist_rect_width = textwidth("注册");
        int regist_rect_x = regist_rect.left + (regist_rect.right - regist_rect.left - regist_rect_width) / 2;
        int regist_rect_y = regist_rect.top + (regist_rect.bottom - regist_rect.top - textheight("注册")) / 2;
        outtextxy(regist_rect_x, regist_rect_y, "注册");

        if (reg_error == 1) {
            settextcolor(RED);
            outtextxy(650, 610, "用户名或密码不能为空");
        }
        else if (reg_error == 2) {
            settextcolor(RED);
            outtextxy(650, 610, "两次密码不一致");
        }
        else if (reg_error == 3) {
            settextcolor(RED);
            outtextxy(650, 610, "用户名已存在");
        }

        FlushBatchDraw();
        Sleep(10);
    }
    EndBatchDraw();
}

// 保存用户
void saveUser(User u) {
    FILE* fp = fopen(file_path, "ab");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }

    fwrite(&u, sizeof(User), 1, fp);
    fclose(fp);
}

// 查找用户
int findUser(char* username) {
    User u;
    FILE* fp = fopen(file_path, "rb");

    if (fp == NULL) {
        return -1;
    }

    while (fread(&u, sizeof(User), 1, fp) == 1) {
        if (strcmp(u.username, username) == 0) {
            fclose(fp);
            return u.id;
        }
    }

    fclose(fp);
    return -1;
}

// 启动渐变
void fadeFromBgTransition(IMAGE* img, int duration_ms) {
    int steps = 60;
    int step_time = duration_ms / steps;
    int width = getwidth();
    int height = getheight();

    BeginBatchDraw();

    putimage(0, 0, img);
    FlushBatchDraw();
    Sleep(200);

    for (int i = 0; i <= steps; i++) {
        int white_level = 0 + (255 * i / steps);

        cleardevice();
        putimage(0, 0, img);
        setfillcolor(RGB(white_level, white_level, white_level));
        solidrectangle(0, 0, width, height);

        FlushBatchDraw();
        Sleep(step_time);
    }

    FlushBatchDraw();

    EndBatchDraw();
}
void fadeFromWhiteTransition(IMAGE* img, int duration_ms) {
    int steps = 60;
    int step_time = duration_ms / steps;
    int width = getwidth();
    int height = getheight();

    BeginBatchDraw();


    // 逐渐降低白色亮度
    for (int i = 0; i <= steps; i++) {
        int white_level = 255 - (255 * i / steps);  // 从255到0

        cleardevice();
        putimage(0, 0, img);
        setfillcolor(RGB(white_level, white_level, white_level));
        solidrectangle(0, 0, width, height);

        FlushBatchDraw();
        Sleep(step_time);
    }

    cleardevice();
    putimage(0, 0, img);
    FlushBatchDraw();

    EndBatchDraw();
}

