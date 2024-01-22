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
最开始初始化，开始界面到游戏界面的动画通过移动SDL_RenderCopy()的srcrect来完成。游戏过程中分为处理输入输出和显示画面两部分：处理输入部分我并未将其封装为一个函数，这是因为我想要在不同的页面中使输入对应的操作不同，因此封装成函数没什么意义；显示图像部分我通过分别控制背景，任务，障碍，分数几个部分来实现。另外，我进行了暂停菜单和死亡菜单的设计。
特别的，我在main()中将game()放在一个死循环中，这样我只需要将game()函数返回，即可实现重新开始。我将障碍物按生成的顺序组成一个链表，对这个链表我实现了删去头、删去中间、延长尾和删去链表的操作，确保了内存不泄露。除此之外，我将多个功能按模块封装，程序可维护性较强。我设计了较多的动画，且帧率达到了50帧。这些是我自认为中程序的优点。