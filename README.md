此程序用于南京大学技术科学实验班期末项目

平台：Windows11

C语言环境：mingw 13.2.0

编译选项：1，CMakeLists
2，gcc指令：cd "d:\Programing\cpl\Playground_Run\" ; if ($?) { gcc -Iinclude src/main.c src/game.c src/obstacle.c src/start_menu.c src/death_menu.c src/stop_menu.c src/utils/print_text.c src/utils/init_game.c src/utils/character_motion.c src/utils/score.c src/utils/time.c src/utils/motion.c -o main -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_image -lmingw32 -lSDL2_ttf } ; if ($?) { .\main }

第三方库：SDL2

游戏规则：
按A或方向左键是向上变道；按D或方向右键是向下变道；按W或方向上键跳跃；按S或方向下键滑铲。R可重开，空格可暂停，ESC可退出
吃金币可以得20分，吃盾可获得5秒无敌
速度会随着分数增加而变快（100，250，500，1000）

程序思路：
最开始初始化，开始界面到游戏界面的动画通过移动SDL_RenderCopy()的srcrect来完成。游戏过程中分为处理输入输出和显示画面两部分：处理输入部分我并未将其封装为一个函数，这是因为我想要在不同的页面中使输入对应的操作不同，因此封装成函数没什么意义；显示图像部分我通过