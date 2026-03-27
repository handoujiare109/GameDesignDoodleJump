#define _CRT_SECURE_NO_WARNINGS
#include "common.h" 

ExMessage msg;

int weapon = 0;
int x = 400;
int y = 500;
int vy = 0;
int isOnGround = 1;// 是否在地面
int jumpsLeft = 2;// 剩余跳跃机会
int isDashing = 0;          // 是否正在冲刺中
int dashFrames = 0;         // 冲刺剩余帧数
int dashCooldown = 0;       // 冲刺冷却剩余帧数
int dashDirection = 0;      // 冲刺方向（-1: 左, 1: 右）
const int DASH_DISTANCE = 80;   // 冲刺移动距离（像素）
const int DASH_SPEED = 16;      // 冲刺速度（每帧移动距离，需要与帧率配合）
const int DASH_COOLDOWN_FRAMES = 120;  // 冷却帧数（60帧 = 2秒）
const int GRAVITY = 1;// 重力
const int JUMP_POWER = -15;// 初速度

void StoryMode() {

}

void EndlessMode() {
	// 初始准备数据 //
	
	// 素材加载 //

	while (1) {
		BeginBatchDraw();

		            
		show();

		//updateWithInput();
		//updateWithoutInput();

		EndBatchDraw();
		Sleep(16);
	}

}

void show() {
	//******之后修改！！******//
	IMAGE bg_img;
	loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
	//******之后修改！！******//
}

void Act() {
	while (peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR)) {
		
		// 键盘 //
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case '1':
				weapon = 0;
				break;
			case '2':
				weapon = 1;
				break;
			case '3':
				weapon = 2;
			case 'A':      // 按 A 向左移动
				if (!isDashing) {
					x -= 10;
				}
				break;
			case 'D':      // 按 D 向右移动
				if (!isDashing) {
					x += 10;
				}
				break;
			case VK_SPACE:
				if (jumpsLeft > 0 && jumpsLeft <= 2) {  // 最多跳2次
					vy = JUMP_POWER;
					jumpsLeft--;
					isOnGround = 0;
				}
				break;
			case VK_SHIFT:  // 左 Shift 键
				// 冲刺条件：冷却已到、没有在冲刺中、按着 A 或 D
				if (dashCooldown <= 0 && !isDashing) {
					// 检测当前是否按着 A 或 D
					bool pressingA = (GetAsyncKeyState('A') & 0x8000);
					bool pressingD = (GetAsyncKeyState('D') & 0x8000);

					if (pressingA || pressingD) {
						// 开始冲刺
						isDashing = 1;
						dashFrames = DASH_DISTANCE / DASH_SPEED;  // 计算冲刺需要的帧数

						// 确定冲刺方向
						if (pressingA) {
							dashDirection = -1;  // 向左冲刺
						}
						else if (pressingD) {
							dashDirection = 1;   // 向右冲刺
						}

						// 进入冷却
						dashCooldown = DASH_COOLDOWN_FRAMES;
					}
				}
				break;
			}
		}
		// 冲刺相关 //
		if (isDashing) {
			// 执行冲刺移动
			x += dashDirection * DASH_SPEED;
			dashFrames--;

			// 冲刺结束
			if (dashFrames <= 0) {
				isDashing = 0;
			}
		}

		// 跳跃相关 //
		vy += GRAVITY;
		y += vy;

		if (y >= 500) {
			y = 500;
			vy = 0;
			isOnGround = 1;
			jumpsLeft = 2;    // 落地后重置跳跃次数
		}
		else {
			isOnGround = 0;
		}
		
		// 左键 //
		if (msg.message == WM_LBUTTONDOWN) {
			if (weapon == 0) {
				// 发射子弹 //
			}
			else if (weapon == 2) {
				// 大子弹 //
			}

		}
	}
}

