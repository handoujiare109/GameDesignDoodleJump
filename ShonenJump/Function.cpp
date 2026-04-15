#define _CRT_SECURE_NO_WARNINGS
#include "common.h" 

// 主菜单
void gameMain() {

    RECT start_rect = { 600, 420, 1000, 500 };
    RECT info_rect = { 600, 520, 1000, 600 };
    RECT shop_rect = { 600, 620, 1000, 700 };
    RECT exit_rect = { 600, 720, 1000, 800 };

    IMAGE bg_img1;
    IMAGE bg_img;

    int hover_button = 0;

    ExMessage msg;
    int corner_radius = 15;
    char ch;

    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
    loadimage(&bg_img1, "F:\\GameMaterial\\Bg_1.png");

    BeginBatchDraw();

    while (1) {
        putimage(0, 0, &bg_img1);
        while (peekmessage(&msg, EX_MOUSE)) {
            // 高亮 //
            if (msg.x >= start_rect.left && msg.x <= start_rect.right &&
                msg.y >= start_rect.top && msg.y <= start_rect.bottom) {
                hover_button = 1;
            }
            else if (msg.x >= info_rect.left && msg.x <= info_rect.right &&
                msg.y >= info_rect.top && msg.y <= info_rect.bottom) {
                hover_button = 2;
            }
            else if (msg.x >= shop_rect.left && msg.x <= shop_rect.right &&
                msg.y >= shop_rect.top && msg.y <= shop_rect.bottom) {
                hover_button = 3;
            }
            else if (msg.x >= exit_rect.left && msg.x <= exit_rect.right &&
                msg.y >= exit_rect.top && msg.y <= exit_rect.bottom) {
                hover_button = 4;
            }
            else {
                hover_button = 0;
            }
           
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= start_rect.left && msg.x <= start_rect.right &&
                    msg.y >= start_rect.top && msg.y <= start_rect.bottom) {
                    GameIn();
                }
                else if (msg.x >= info_rect.left && msg.x <= info_rect.right &&
                    msg.y >= info_rect.top && msg.y <= info_rect.bottom) {
                    Info();
                }
                else if (msg.x >= shop_rect.left && msg.x <= shop_rect.right &&
                    msg.y >= shop_rect.top && msg.y <= shop_rect.bottom) {
                    Shop();
                }
                else if (msg.x >= exit_rect.left && msg.x <= exit_rect.right &&
                    msg.y >= exit_rect.top && msg.y <= exit_rect.bottom) {
                    Exit();
                }
            }
            
        }

        setfillcolor(0x3D3A39);
        // 开始按钮
        if (hover_button == 1) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(start_rect.left, start_rect.top,
            start_rect.right, start_rect.bottom, corner_radius, corner_radius);

        // 信息按钮
        if (hover_button == 2) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(info_rect.left, info_rect.top,
            info_rect.right, info_rect.bottom, corner_radius, corner_radius);

        // 商店按钮
        if (hover_button == 3) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(shop_rect.left, shop_rect.top,
            shop_rect.right, shop_rect.bottom, corner_radius, corner_radius);

        // 退出按钮
        if (hover_button == 4) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(exit_rect.left, exit_rect.top,
            exit_rect.right, exit_rect.bottom, corner_radius, corner_radius);

        // 按钮文字
        setbkmode(TRANSPARENT);
        settextcolor(0xB3DBF9);
        setSmoothFont(30, "汉仪文黑 85W");
        // 开始
        int text_width = textwidth("开始游戏");
        int text_x = start_rect.left + (start_rect.right - start_rect.left - text_width) / 2;
        int text_y = start_rect.top + (start_rect.bottom - start_rect.top - textheight("开始游戏")) / 2;
        outtextxy(text_x, text_y, "开始游戏");
        // 信息 
        text_width = textwidth("玩家信息");
        text_x = info_rect.left + (info_rect.right - info_rect.left - text_width) / 2;
        text_y = info_rect.top + (info_rect.bottom - info_rect.top - textheight("玩家信息")) / 2;
        outtextxy(text_x, text_y, "玩家信息");
        // 商店
        text_width = textwidth("商城");
        text_x = shop_rect.left + (shop_rect.right - shop_rect.left - text_width) / 2;
        text_y = shop_rect.top + (shop_rect.bottom - shop_rect.top - textheight("商城")) / 2;
        outtextxy(text_x, text_y, "商城");
        //退出
        text_width = textwidth("退出游戏");
        text_x = exit_rect.left + (exit_rect.right - exit_rect.left - text_width) / 2;
        text_y = exit_rect.top + (exit_rect.bottom - exit_rect.top - textheight("退出游戏")) / 2;
        outtextxy(text_x, text_y, "退出游戏");


        FlushBatchDraw();
        Sleep(5);
    }
    EndBatchDraw();
}

// 启动
void GameIn() {

    PlayMusic("bgm_start1.mp3");

    RECT storyMode_rect= { 600, 520, 1000, 600 };
    RECT endlessMode_rect = { 600, 620, 1000, 700 };

    ExMessage msg;
    IMAGE bg_img;
    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");

    int button = 0;
    int corner_radius = 15;



    BeginBatchDraw();

    while (1) {

        putimage(0, 0, &bg_img);

        while (peekmessage(&msg, EX_MOUSE)) {
            // 高亮 //
            if (msg.x >= storyMode_rect.left && msg.x <= storyMode_rect.right &&
                msg.y >= storyMode_rect.top && msg.y <= storyMode_rect.bottom) {
                button = 1;
            }
            else if (msg.x >= endlessMode_rect.left && msg.x <= endlessMode_rect.right &&
                msg.y >= endlessMode_rect.top && msg.y <= endlessMode_rect.bottom) {
                button = 2;
            }
            if (msg.message == WM_LBUTTONDOWN) {
                if (msg.x >= storyMode_rect.left && msg.x <= storyMode_rect.right &&
                    msg.y >= storyMode_rect.top && msg.y <= storyMode_rect.bottom) {
                    StoryMode();
                }
                else if (msg.x >= endlessMode_rect.left && msg.x <= endlessMode_rect.right &&
                    msg.y >= endlessMode_rect.top && msg.y <= endlessMode_rect.bottom) {
                    EndlessMode();
                }
            }
            else if (msg.message == WM_RBUTTONDOWN) {
                PlayMusic("bgm.mp3");
                gameMain();
            }
        }
        setfillcolor(0x3D3A39);
        // 开始按钮
        if (button == 1) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(storyMode_rect.left, storyMode_rect.top,
            storyMode_rect.right, storyMode_rect.bottom, corner_radius, corner_radius);

        // 信息按钮
        if (button == 2) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(endlessMode_rect.left , endlessMode_rect.top,
            endlessMode_rect.right, endlessMode_rect.bottom, corner_radius, corner_radius);

        setfillcolor(0x3D3A39);

        if (button == 1) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(storyMode_rect.left, storyMode_rect.top,
            storyMode_rect.right, storyMode_rect.bottom, corner_radius, corner_radius);

        if (button == 2) {
            setlinecolor(0xB3DBF9);
            setlinestyle(PS_SOLID, 3);
        }
        else {
            setlinecolor(0x3D3A39);
            setlinestyle(PS_SOLID, 3);
        }
        fillroundrect(endlessMode_rect.left, endlessMode_rect.top,
            endlessMode_rect.right, endlessMode_rect.bottom, corner_radius, corner_radius);

        // 绘制按钮
        setbkmode(TRANSPARENT);
        settextcolor(0xB3DBF9);
        settextstyle(30, 0, _T("汉仪文黑 85W"));

        // 剧情模式
        int text_width = textwidth("故事模式");
        int text_x = storyMode_rect.left + (storyMode_rect.right - storyMode_rect.left - text_width) / 2;
        int text_y = storyMode_rect.top + (storyMode_rect.bottom - storyMode_rect.top - textheight("故事模式")) / 2;
        outtextxy(text_x, text_y, "故事模式");

        // 无尽模式
        text_width = textwidth("无尽模式");
        text_x = endlessMode_rect.left + (endlessMode_rect.right - endlessMode_rect.left - text_width) / 2;
        text_y = endlessMode_rect.top + (endlessMode_rect.bottom - endlessMode_rect.top - textheight("无尽模式")) / 2;
        outtextxy(text_x, text_y, "无尽模式");

        FlushBatchDraw();
        Sleep(5);
    }

    EndBatchDraw();

}

// 信息
void Info() {

    BeginBatchDraw();

    ExMessage msg;
    int corner_radius = 15;

    IMAGE bg_img;
    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");

    // 用户名，货币，装备，最高纪录，存档 //

}

// 商店
void Shop() {

    BeginBatchDraw();

    ExMessage msg;
    int corner_radius = 15;

    IMAGE bg_img;
    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
}

// 退出
void Exit() {
    closegraph();
}

// 去锯齿
void setSmoothFont(int height, const char* fontName) {
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = height;
    f.lfWidth = 0;
    f.lfQuality = ANTIALIASED_QUALITY;
    strcpy_s(f.lfFaceName, fontName);
    settextstyle(&f);                      
}

// 播放音乐
void PlayMusic(const char* filename) {

    StopMusic ();
    // 获取当前工作目录并打印
    char cwd[256];
    GetCurrentDirectory(256, cwd);
    printf("当前工作目录: %s\n", cwd);
    printf("尝试播放: %s\n", filename);

    // 检查文件是否存在
    FILE* test = fopen(filename, "rb");
    if (test == NULL) {
        printf("错误：找不到音乐文件 %s\n", filename);
        return;
    }
    fclose(test);

    // 打开音乐文件
    char openCmd[512];
    sprintf(openCmd, "open \"%s\" alias current_music", filename);

    int result = mciSendString(openCmd, NULL, 0, NULL);
    if (result == 0) {
        // 播放音乐（循环播放）
        int playResult = mciSendString("play current_music repeat", NULL, 0, NULL);
        if (playResult == 0) {
            printf("成功播放: %s\n", filename);
        }
        else {
            printf("播放失败，错误码: %d\n", playResult);
        }
    }
    else {
        printf("打开文件失败，错误码: %d\n", result);
    }
}

// 停止音乐
void StopMusic(void) {
    mciSendString("close current_music", NULL, 0, NULL);
}

// 一次性音效
void PlaySFX(const char* filename) {
    static int sfx_counter = 0;

    char alias[64];
    sprintf(alias, "sfx_%d", sfx_counter++);

    char openCmd[512];
    sprintf(openCmd, "open \"%s\" alias %s", filename, alias);

    int result = mciSendString(openCmd, NULL, 0, NULL);
    if (result == 0) {
        char playCmd[512];
        sprintf(playCmd, "play %s", alias);
        mciSendString(playCmd, NULL, 0, NULL);
    }
    else {
        printf("SFX failed to open: %d\n", result);
    }
}
