# ShonenJump — 涂鸦跳跃 (Doodle Jump) C++ 实现

基于 **C++20 + EasyX 图形库** 的竖版跳跃游戏，模仿经典手游 Doodle Jump 的核心玩法。

## 功能

- **无尽模式**：角色持续向上跳跃，平台会自动生成
- **核心机制**：二段跳、冲刺（Shift）、射击（鼠标左键）
- **三种平台**：普通平台、移动平台、碎裂平台
- **敌人系统**：随机生成敌人，可用子弹消灭
- **武器切换**：按 `1/2/3` 切换武器类型
- **用户系统**：注册、登录，记录个人最高分
- **分数系统**：基于攀登高度计分，自动保存最高分

## 技术栈

| 类别 | 技术 |
| ---- | ---- |
| 语言 | C++20 |
| 图形库 | [EasyX](https://easyx.cn/) |
| 音频 | MCI (winmm.lib) |
| 构建 | Visual Studio 2022 (v143) |
| 平台 | Windows |

## 项目结构

```text
ShonenJump/
├── common.h              # 公共头文件（常量、结构体、函数声明）
├── main.cpp              # 入口点，资源加载，启动登录流程
├── Game.cpp              # 核心玩法（物理、渲染、碰撞、无尽模式）
├── Function.cpp          # 主菜单 UI、模式选择、音频播放
├── User.cpp              # 用户注册/登录、过渡动画
├── Model.cpp             # WIP：预留的 MVC 架构代码
├── Shop.cpp              # WIP：商店系统占位
├── *.mp3                 # 背景音乐和音效
├── highscore.dat         # 最高分持久化文件
└── ShonenJump.vcxproj    # Visual Studio 项目文件
```

## 构建与运行

### 前置条件

- **Windows** 操作系统
- **Visual Studio 2022**（需要 v143 工具链）
- **[EasyX](https://easyx.cn/)** 图形库（下载安装包并安装到 VS2022）

### 准备游戏资源

在运行前，需要在 `F:\GameMaterial\` 目录下放置以下图片资源：

- `Bg.jpg`、`Bg_1.png` — 背景图片
- `Player.png` — 玩家角色
- `Normal3.png`、`Moving3.png`、`Breaking3.png` — 平台贴图
- `Enemy.png` — 敌人贴图

> **注意**：当前图片路径为硬编码，后续版本将改为相对路径。如需立即修改，请将 [main.cpp](ShonenJump/main.cpp) 和 [Game.cpp](ShonenJump/Game.cpp) 中的 `F:\\GameMaterial\\` 替换为你的素材目录。

音频文件（`bgm.mp3` 等）需要放在程序的工作目录下。

### 编译步骤

1. 用 Visual Studio 2022 打开 `GameDesign.slnx`
2. 确保 EasyX 已正确安装（VS 可识别 `<graphics.h>`）
3. 选择 `Debug` 或 `Release` 配置
4. 点击「生成」→「生成解决方案」
5. 运行生成的 `.exe`

## 操作说明

| 操作 | 按键 |
| ---- | ---- |
| 左右移动 | `A` / `D` |
| 跳跃 | `空格` |
| 冲刺 | `Shift` |
| 射击 | 鼠标左键 |
| 切换武器 | `1` / `2` / `3` |
| 返回菜单 | 右键（部分界面） |

## 游戏截图

（待补充）

## 已知问题

1. **硬编码路径**：图片素材路径写死为 `F:\GameMaterial\`，需要手动创建或修改源码
2. **空功能**：故事模式、商店、信息页尚未实现
3. **密码明文存储**：用户密码以明文二进制存储，不适合正式使用
4. **编码问题**：源码使用 GBK 编码，非中文 Windows 可能显示乱码
5. **构建限制**：仅支持 VS2022，缺少 CMakeLists.txt，无法在 Linux/macOS 上构建
6. **错误处理不足**：图片/文件加载失败时缺少友好提示


## 许可证

待定

## 致谢

- 灵感来源：Lima Sky 的 Doodle Jump
- 图形库：[EasyX](https://easyx.cn/)
