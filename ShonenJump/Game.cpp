#define _CRT_SECURE_NO_WARNINGS
#include "common.h" 
#pragma comment(lib, "MSIMG32.LIB")

ExMessage msg;

float x = WIDTH / 2;
float y = GROUND_Y;
float vy = 0;
int jumpsLeft = MAX_JUMPS;
int isOnGround = 0;

// 冲刺
int isDashing = 0;
int dashFrames = 0;
int dashDirection = 0;
int dashCooldown = 0;

// 武器模式
int weapon = 0;

// 平台
Platform platforms[MAX_PLATFORMS_ARR];
int platformCount = 0;

// 敌人
Enemy enemies[MAX_ENEMIES];
int enemyCount = 0;

// 子弹
Bullet bullets[MAX_BULLETS];
int bulletCount = 0;

// 相机
float cameraY = 0;
float playerScreenY = HEIGHT / 2;

// 死亡判定
int gameOver = 0;
float highestYReached = 0;
float fallDistance = 0;

// 分数
int currentScore = 0;
int highScore = 0;
float scoreMultiplier = 0.01;
float scoreHeightBase = 0;


RECT restartBtn = { WIDTH / 2 - 60, HEIGHT / 2 + 20, WIDTH / 2 + 60, HEIGHT / 2 + 60 };
RECT menuBtn = { WIDTH / 2 - 60, HEIGHT / 2 + 80, WIDTH / 2 + 60, HEIGHT / 2 + 120 };

IMAGE bg_img;
IMAGE player_img;
IMAGE platform_normal_img;
IMAGE platform_moving_img;
IMAGE platform_broken_img;
IMAGE platform_broken_effect_img;
IMAGE enemy_img;
IMAGE story_img;



void StoryMode() {

}

void EndlessMode() {
	initGame();

	while (1) {
		BeginBatchDraw();

		updateWithInput();
		updateWithoutInput();
		show();

		EndBatchDraw();
		Sleep(16);
	}
}

void initGame() {

	loadimage(&bg_img, "F:\\GameMaterial\\Bg.jpg");
	loadimage(&player_img, "F:\\GameMaterial\\Player.png");
	loadimage(&platform_normal_img, "F:\\GameMaterial\\Normal3.png");
	loadimage(&platform_moving_img, "F:\\GameMaterial\\Moving3.png");
	loadimage(&platform_broken_img, "F:\\GameMaterial\\Breaking3.png");
	loadimage(&enemy_img, "F:\\GameMaterial\\Enemy.png");

	// 初始化随机数
	srand((unsigned int)time(NULL));

	// 重置主角位置
	x = WIDTH / 2;
	y = GROUND_Y - 40;
	vy = 0;
	jumpsLeft = MAX_JUMPS;
	isDashing = 0;
	dashCooldown = 0;
	weapon = 0;

	// 重置状态
	gameOver = 0;
	currentScore = 0;
	scoreHeightBase = GROUND_Y;
	highestYReached = y;
	fallDistance = 0;

	// 初始化相机
	cameraY = 0;
	playerScreenY = HEIGHT / 2;

	// 重置平台
	platformCount = 0;
	enemyCount = 0;
	bulletCount = 0;

	// 生成初始平台
	generatePlatforms();
}

void show() {
	int i;

	cleardevice();

	// 绘制背景
	putimage(0, 0, &bg_img);

	// 绘制平台
	for (i = 0; i < platformCount; i++) {
		int screenY = platforms[i].y + cameraY;
		if (screenY > -PLATFORM_HEIGHT && screenY < HEIGHT) {
			IMAGE* pImg = NULL;


			if (platforms[i].isBroken) {
				pImg = &platform_broken_img;
			}
			else {
				switch (platforms[i].type) {
				case PLATFORM_NORMAL:
					pImg = &platform_normal_img;
					break;
				case PLATFORM_MOVING:
					pImg = &platform_moving_img;
					break;
				case PLATFORM_BROKEN:
					pImg = &platform_broken_img;
					break;
				default:
					pImg = &platform_normal_img;
					break;
				}
			}

			if (pImg != NULL) {
				putimage_alpha(platforms[i].x, screenY, pImg);
			}

			// 断裂平台提示
			if (platforms[i].isBroken && platforms[i].brokenTimer > 0) {
				setfillcolor(RGB(255, 100, 100));
				setfillstyle(BS_SOLID);

				solidrectangle(platforms[i].x + 20, screenY + 5,
					platforms[i].x + 40, screenY + 10);
			}
		}
	}

	// 绘制敌人
	for (i = 0; i < enemyCount; i++) {
		int screenY = enemies[i].y + cameraY;
		putimage_alpha(enemies[i].x, screenY, &enemy_img);
	}

	// 绘制子弹
	for (i = 0; i < bulletCount; i++) {
		setfillcolor(bullets[i].type == 2 ? RGB(255, 0, 0) : RGB(255, 255, 0));
		solidrectangle(bullets[i].x, bullets[i].y + cameraY,
			bullets[i].x + bullets[i].width, bullets[i].y + bullets[i].height + cameraY);
	}

	// 绘制主角
	putimage_alpha((int)x, (int)(y + cameraY), &player_img);

	// 显示信息
	setbkcolor(WHITE);
	setcolor(BLACK);
	TCHAR text[128];
	wsprintf(text, _T("Weapon: %d  DashCD:%d  Platforms: %d  Score: %d"), weapon, dashCooldown, platformCount,currentScore);
	outtextxy(10, 10, text);

	
	// ****显示分数****//



	//****************//
}

void updateWithInput() {
	ExMessage msg;

	while (peekmessage(&msg, EX_MOUSE | EX_KEY | EX_CHAR)) {
		// 死亡
		if (gameOver) {
			if (msg.message == WM_LBUTTONDOWN) {
				GameIn();
			}
		}
		// 键盘
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
				break;
			case 'A':
				if (!isDashing) x -= 8;
				break;
			case 'D':
				if (!isDashing) x += 8;
				break;
			case VK_SPACE:
				if (jumpsLeft > 0 && jumpsLeft <= MAX_JUMPS) {
					vy = JUMP_POWER;
					jumpsLeft--;
					isOnGround = 0;
				}
				break;
			case VK_SHIFT:
				if (dashCooldown <= 0 && !isDashing) {
					int pressingA = (GetAsyncKeyState('A') & 0x8000);
					int pressingD = (GetAsyncKeyState('D') & 0x8000);
					if (pressingA || pressingD) {
						isDashing = 1;
						dashFrames = DASH_DISTANCE / DASH_SPEED;
						dashDirection = pressingA ? -1 : 1;
						dashCooldown = DASH_COOLDOWN_FRAMES;
					}
				}
				break;
			}
		}
		// 鼠标左键
		if (msg.message == WM_LBUTTONDOWN) {
			if (weapon == 0) {
				shootBullet(0);
			}
			else if (weapon == 2) {
				shootBullet(2);
			}
		}
	}

	// 持续移动
	if (GetAsyncKeyState('A') & 0x8000 && !isDashing) {
		x -= 8;
	}
	if (GetAsyncKeyState('D') & 0x8000 && !isDashing) {
		x += 8;
	}

	// 边界限制
	if (x < 0) x = 0;
	if (x > WIDTH - 40) x = WIDTH - 40;

	// 冲刺冷却
	if (isDashing) {
		x += dashDirection * DASH_SPEED;
		dashFrames--;
		if (dashFrames <= 0) {
			isDashing = 0;
		}
	}
	if (dashCooldown > 0) dashCooldown--;

	// 重力物理
	vy += GRAVITY;
	y += vy;

	// 平台碰撞检测
	handleCollisions();

	// 游戏结束静止
	if (gameOver) return;

	// 掉落到地面以下重置位置
	if (y > GROUND_Y + 100) {
		y = GROUND_Y;
		vy = 0;
		jumpsLeft = MAX_JUMPS;
		isOnGround = 1;
		x = WIDTH / 2;
		cameraY = 0;
	}

	// 子弹更新
	updateBullets();

	// 敌人更新
	updateEnemies();
}

void handleCollisions() {
	int i;
	isOnGround = 0;

	// 计算主角边界
	float playerLeft = x;
	float playerRight = x + PLAYER_WIDTH;
	float playerBottom = y + PLAYER_HEIGHT;
	float playerCenterX = x + PLAYER_WIDTH / 2;

	// 横向宽容度
	const float leftTolerance = 0.0f;
	const float rightTolerance = 40.0f;

	// 检测平台碰撞
	for (i = 0; i < platformCount; i++) {
		// 跳过已断裂平台
		if (platforms[i].isBroken) continue;

		// 计算平台的边界
		float platformLeft = platforms[i].x;
		float platformRight = platforms[i].x + PLATFORM_WIDTH;
		float platformTop = platforms[i].y;

		// 检查横向
		int horizontalOverlap = (playerRight > platformLeft - leftTolerance &&
			playerLeft < platformRight + rightTolerance);

		// 检查纵向
		int verticalCollision = (vy > 0 &&
			playerBottom > platformTop &&
			playerBottom - vy <= platformTop + 15);

		if (verticalCollision && horizontalOverlap) {
			// 断裂平台处理
			if (platforms[i].type == PLATFORM_BROKEN) {
				y = platformTop - PLAYER_HEIGHT;
				vy = 0;
				isOnGround = 1;
				jumpsLeft = MAX_JUMPS;

				// 断裂
				platforms[i].isBroken = 1;
				platforms[i].brokenTimer = BROKEN_FRAMES;
				break;
			}
			// 普通和移动平台处理
			else if (platforms[i].type == PLATFORM_NORMAL || platforms[i].type == PLATFORM_MOVING) {
				y = platformTop - PLAYER_HEIGHT;
				vy = 0;
				isOnGround = 1;
				jumpsLeft = MAX_JUMPS;
				break;
			}
		}
	}

	// 地面碰撞
	if (y + PLAYER_HEIGHT > GROUND_Y) {
		y = GROUND_Y - PLAYER_HEIGHT;
		vy = 0;
		isOnGround = 1;
		jumpsLeft = MAX_JUMPS;
	}
}

void updateWithoutInput() {
	int i;

	// 游戏结束判定
	if (gameOver) return;

	// 游戏失败判定
	if (y < highestYReached || highestYReached == 0) {
		highestYReached = y;
	}

	// 游戏失败判定
	fallDistance = y - highestYReached;

	// 如果掉落超过阈值，游戏失败
	if (fallDistance > FAIL_FALL_DISTANCE) {
		StopMusic();
		PlaySFX("inHuman.mp3");
		gameOver = 1;
		return;
	}

	// 分数刷新
	updateScore();

	// 相机跟随
	float targetCameraY = playerScreenY - y;
	cameraY = targetCameraY;
	if (cameraY < 0) cameraY = 0;



	// 更新移动平台和断裂平台
	for (i = 0; i < platformCount; i++) {
		// 移动平台
		if (platforms[i].type == PLATFORM_MOVING && !platforms[i].isBroken) {
			platforms[i].x += platforms[i].moveDir * MOVING_SPEED;

			// 边界反弹
			if (platforms[i].x > platforms[i].startX + MOVING_RANGE) {
				platforms[i].x = platforms[i].startX + MOVING_RANGE;
				platforms[i].moveDir = -1;
			}
			else if (platforms[i].x < platforms[i].startX - MOVING_RANGE) {
				platforms[i].x = platforms[i].startX - MOVING_RANGE;
				platforms[i].moveDir = 1;
			}
		}

		// 断裂平台倒计时
		if (platforms[i].isBroken) {
			platforms[i].brokenTimer--;
			if (platforms[i].brokenTimer <= 0) {
				for (int j = i; j < platformCount - 1; j++) {
					platforms[j] = platforms[j + 1];
				}
				platformCount--;
				i--;
				continue;
			}
		}
	}

	// 删除超出屏幕下方的平台
	i = 0;
	while (i < platformCount) {
		int screenY = platforms[i].y + cameraY;
		if (screenY > HEIGHT + 200) {
			for (int j = i; j < platformCount - 1; j++) {
				platforms[j] = platforms[j + 1];
			}
			platformCount--;
		}
		else {
			i++;
		}
	}

	if (platformCount < MAX_PLATFORMS_ARR - 2) {
		// 找到当前最高的平台
		int highestY = 9999;
		for (int j = 0; j < platformCount; j++) {
			if (platforms[j].y < highestY) {
				highestY = platforms[j].y;
			}
		}

		int highestScreenY = highestY + cameraY;

		while (highestScreenY > -200 && platformCount < MAX_PLATFORMS_ARR) {
			int newY = highestY - PLATFORM_GAP;

			// 添加平台
			addPlatform(newY);

			// 随机生成敌人
			if (rand() % 3 == 0) {
				int randX = rand() % (WIDTH - PLATFORM_WIDTH - 40) + 20;
				spawnEnemy(randX, newY - ENEMY_SIZE);
			}

			// 更新最高平台信息
			highestY = newY;
			highestScreenY = highestY + cameraY;
		}
	}

	// 跟随平台
	if (isOnGround) {
		for (int i = 0; i < platformCount; i++) {
			if (platforms[i].type == PLATFORM_MOVING && !platforms[i].isBroken) {
				
				// 跟随判断
				float playerLeft = x;
				float playerRight = x + PLAYER_WIDTH;
				float platformLeft = platforms[i].x;
				float platformRight = platforms[i].x + PLATFORM_WIDTH;

				int horizontalOverlap = (playerRight > platformLeft - 0.0f &&
					playerLeft < platformRight + 40.0f);

				// 检查垂直
				float playerBottom = y + PLAYER_HEIGHT;
				float platformTop = platforms[i].y;
				int verticalContact = (fabs(playerBottom - platformTop) < 5.0f);

				if (horizontalOverlap && verticalContact) {
					x += platforms[i].moveDir * MOVING_SPEED;

					// 边界限制
					if (x < 0) x = 0;
					if (x > WIDTH - PLAYER_WIDTH) x = WIDTH - PLAYER_WIDTH;
					break;
				}
			}
		}
	}
	// 移除超出屏幕的敌人
	i = 0;
	while (i < enemyCount) {
		int screenY = enemies[i].y + cameraY;
		if (screenY + ENEMY_SIZE < 0 || screenY > HEIGHT + 100) {
			for (int j = i; j < enemyCount - 1; j++) {
				enemies[j] = enemies[j + 1];
			}
			enemyCount--;
		}
		else {
			i++;
		}
	}
}

void spawnEnemy(int x, int y) {
	if (enemyCount >= MAX_ENEMIES) return;

	enemies[enemyCount].x = x;
	enemies[enemyCount].y = y;
	enemies[enemyCount].width = ENEMY_SIZE;
	enemies[enemyCount].height = ENEMY_SIZE;
	enemies[enemyCount].active = 1;
	enemyCount++;
}

void updateEnemies() {
	int i;
	for (i = 0; i < enemyCount; i++) {
		if (abs((int)x - enemies[i].x) < 35 && abs((int)y - enemies[i].y) < 35) {
			y = GROUND_Y;
			vy = 0;
			jumpsLeft = MAX_JUMPS;
			cameraY = 0;
			x = WIDTH / 2;
		}
	}
}

void shootBullet(int type) {
	if (bulletCount >= MAX_BULLETS) return;

	Bullet* b = &bullets[bulletCount];

	b->x = x + PLAYER_WIDTH/ 2 - b->width / 2 + 35;
	b->y = y + 15;

	b->width = (type == 2) ? 16 : 10;
	b->height = 8;

	b->dx = 0;
	b->dy = -1;

	b->active = 1;
	b->type = type;

	bulletCount++;
}

void updateBullets() {
	int i = 0;
	float speed = 15.0f;

	while (i < bulletCount) {
		Bullet* b = &bullets[i];

		// 移动
		b->x += b->dx * speed;
		b->y += b->dy * speed;

		// 计算子弹屏幕坐标
		float screenX = b->x;
		float screenY = b->y + cameraY;  // 相机偏移

		// 超出屏幕删除（屏幕坐标判断）
		if (screenX < -50 || screenX > WIDTH + 50 ||
			screenY < -50 || screenY > HEIGHT + 50) {

			for (int j = i; j < bulletCount - 1; j++) {
				bullets[j] = bullets[j + 1];
			}
			bulletCount--;
			continue;
		}

		// 碰撞检测
		int hit = 0;
		for (int j = 0; j < enemyCount; j++) {
			if (b->active && enemies[j].active &&
				b->x < enemies[j].x + enemies[j].width &&
				b->x + b->width > enemies[j].x &&
				b->y < enemies[j].y + enemies[j].height &&
				b->y + b->height > enemies[j].y) {

				enemies[j].active = 0;
				hit = 1;
				break;
			}
		}

		// 命中删除子弹
		if (hit) {
			for (int j = i; j < bulletCount - 1; j++) {
				bullets[j] = bullets[j + 1];
			}
			bulletCount--;
		}
		else {
			i++;
		}
	}

	// 清理敌人
	int i2 = 0;
	while (i2 < enemyCount) {
		if (!enemies[i2].active) {
			for (int j = i2; j < enemyCount - 1; j++) {
				enemies[j] = enemies[j + 1];
			}
			enemyCount--;
		}
		else {
			i2++;
		}
	}
}

void generatePlatforms() {
	platformCount = 0;
	int startY = HEIGHT - 50;
	int i;
	for (i = 0; i < MAX_PLATFORMS; i++) {
		int yPos = startY - i * PLATFORM_GAP;
		if (yPos > 0) {
			addPlatform(yPos);
		}
	}
}

void addPlatform(int yPos) {
	if (platformCount >= MAX_PLATFORMS_ARR) return;

	int type;  // ← 添加这个变量定义

	// 根据高度决定平台类型（越高越容易出现断裂平台）
	int typeRand;
	if (yPos < 200) {  // 高空区域
		typeRand = rand() % 100;
		if (typeRand < 40) type = PLATFORM_NORMAL;      // 40%普通
		else if (typeRand < 70) type = PLATFORM_MOVING; // 30%移动
		else type = PLATFORM_BROKEN;                    // 30%断裂
	}
	else if (yPos < 400) {  // 中空区域
		typeRand = rand() % 100;
		if (typeRand < 60) type = PLATFORM_NORMAL;
		else if (typeRand < 85) type = PLATFORM_MOVING;
		else type = PLATFORM_BROKEN;
	}
	else {  // 低空区域（安全区）
		typeRand = rand() % 100;
		if (typeRand < 85) type = PLATFORM_NORMAL;
		else if (typeRand < 95) type = PLATFORM_MOVING;
		else type = PLATFORM_BROKEN;
	}

	// 设置平台属性
	platforms[platformCount].x = rand() % (WIDTH - PLATFORM_WIDTH - 40) + 20;
	platforms[platformCount].y = yPos;
	platforms[platformCount].type = type;  // ← 关键：设置平台类型
	platforms[platformCount].isMoving = (type == PLATFORM_MOVING) ? 1 : 0;  // 移动平台才移动
	platforms[platformCount].moveDir = (type == PLATFORM_MOVING) ? ((rand() % 2 == 0) ? 1 : -1) : 0;
	platforms[platformCount].moveRange = (type == PLATFORM_MOVING) ? MOVING_RANGE : 0;
	platforms[platformCount].startX = platforms[platformCount].x;
	platforms[platformCount].isBroken = 0;  // 添加断裂标志
	platforms[platformCount].brokenTimer = 0;  // 添加断裂计时器
	platformCount++;
}

void loadHighScore() {
	FILE* file = fopen("highscore.dat", "rb");
	if (file != NULL) {
		fread(&highScore, sizeof(int), 1, file);
		fclose(file);
	}
	else {
		highScore = 0;
	}
}

void saveHighScore() {
	FILE* file = fopen("highscore.dat", "wb");
	if (file != NULL) {
		fwrite(&highScore, sizeof(int), 1, file);
		fclose(file);
	}
}

void updateScore() {
	// 计算高度
	float currentHeight = GROUND_Y - y;
	if (currentHeight < 0) currentHeight = 0;

	// 计算分数
	int newScore = (int)(currentHeight * scoreMultiplier);

	if (newScore > currentScore) {
		currentScore = newScore;

		// 更新最高分
		if (currentScore > highScore) {
			highScore = currentScore;
			saveHighScore();  // 实时保存最高分
		}
	}
}

inline void putimage_alpha(int x, int y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}