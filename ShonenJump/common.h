#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <mmsystem.h>
#include <time.h>
#pragma comment(lib, "winmm.lib") 

// 常量
#define HEIGHT 900
#define WIDTH 1600
#define NAME_LEN 20
#define PASS_LEN 20
#define GROUND_Y (HEIGHT - 50)
#define FAIL_FALL_DISTANCE 800

// 主角参数
#define GRAVITY 0.6f
#define JUMP_POWER -13.0f
#define MAX_JUMPS 2
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

// 冲刺参数
#define DASH_DISTANCE 80
#define DASH_SPEED 20
#define DASH_COOLDOWN_FRAMES 60

// 平台参数
#define PLATFORM_NORMAL 0    // 普通平台
#define PLATFORM_MOVING 1    // 移动平台
#define PLATFORM_BROKEN 2    // 断裂平台
#define MOVING_SPEED 4       // 移动速度
#define MOVING_RANGE 80      // 移动范围
#define BROKEN_FRAMES 30     // 断裂延迟帧数
#define PLATFORM_WIDTH 60
#define PLATFORM_HEIGHT 12
#define PLATFORM_GAP 55
#define MAX_PLATFORMS 20
#define SCROLL_SPEED 2.0f

// 敌人
#define ENEMY_SIZE 20

// 最大子弹数
#define MAX_BULLETS 50
#define MAX_ENEMIES 50
#define MAX_PLATFORMS_ARR 50

// 结构体
typedef struct {
    int id;
    char username[NAME_LEN];
    char password[PASS_LEN];
    int score;
    int is_logged;
} User;

typedef struct  {
    float x;  // 脚的x（中心）
    float y;  // 脚的y（底部）
    float vx;
    float vy;
    int width;
    int height;
} Character;

// 平台
typedef struct {
    int x, y;
    int type;           // 平台类型：0普通 1移动 2断裂
    int isMoving;       // 是否正在移动（移动平台用）
    int moveDir;        // 移动方向 1右 -1左
    int moveRange;      // 移动范围
    int startX;         // 起始X坐标
    int isBroken;       // 是否已断裂（断裂平台用）
    int brokenTimer;    // 断裂计时器
} Platform;

typedef struct {
    int x, y;
    int width, height;
    int active;
} Enemy;

typedef struct{
    float x, y;
    float dx, dy;   // ⭐方向
    int width, height;
    int active;
    int type;
} Bullet;

// 全局变量声明
extern User current_user;
extern const char* file_path;
//int scoreCurrent;
//int scoreHigher;
//int coin;


// 函数声明
bool login();
void regist();
void gameMain();
void saveUser(User u);
int findUser(char* username);
void setSmoothFont(int height, const char* fontName);
void GameIn();
void Info();
void Shop();
void Exit();
void StoryMode();
void EndlessMode();
void initGame();
void generatePlatforms();
void addPlatform(int yPos);
void updateWithoutInput();
void updateWithInput();
void show();
void handleCollisions();
void spawnEnemy(int x, int y);
void updateEnemies();
void shootBullet(int type);
void updateBullets();
void fadeFromBgTransition(IMAGE* bg_img1, int duration_ms);
void fadeFromWhiteTransition(IMAGE* bg_img1, int duration_ms);
void PlayMusic(const char* filename);
void StopMusic();
void PlaySFX(const char* filename);
void loadHighScore();
void saveHighScore();
void updateScore();
inline void putimage_alpha(int x, int y, IMAGE* img);

#endif