#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

// 常量
#define NAME_LEN 20
#define PASS_LEN 20

// 结构体
struct User {
    int id;
    char username[NAME_LEN];
    char password[PASS_LEN];
    int score;
    int is_logged;
};

struct Character {
    float x;  // 脚的x（中心）
    float y;  // 脚的y（底部）
    float vx;
    float vy;
    int width;
    int height;
};

struct Platform {
    int x, y;
};

// 全局变量声明
extern User current_user;
extern const char* file_path;

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
void play();
void show();
void Movement();
void updateWithInput();
void updateWithoutInput();
void fadeFromBgTransition(IMAGE* bg_img1, int duration_ms);
void fadeFromWhiteTransition(IMAGE* bg_img1, int duration_ms);

#endif