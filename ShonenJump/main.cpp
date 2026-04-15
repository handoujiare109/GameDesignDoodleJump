#define _CRT_SECURE_NO_WARNINGS
#include "common.h" 

const char* file_path = "C:\\Users\\hamo8\\Desktop\\logers.txt";

int main() {

    IMAGE bg_img1;
    IMAGE bg_img;

    loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
    loadimage(&bg_img1, "F:\\GameMaterial\\Bg_1.png");

    initgraph(1600,900);
    
    // 进入登录界面
    if (login()) {
        PlayMusic("bgm.mp3");
        fadeFromBgTransition(&bg_img, 1800);
        fadeFromWhiteTransition(&bg_img1, 1800);
        gameMain();
        
        
    }
    return 0;
}
