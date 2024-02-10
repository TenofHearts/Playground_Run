# 此程序用于南京大学技术科学实验班期末项目, 作者叶晋

**平台:** Windows11

**C语言环境:** mingw 13.2.0

**编译选项:** 1, CMakeLists
2, gcc指令: 

``` gcc
cd "d:\Programing\cpl\Playground_Run\" ; if ($?) { gcc -Iinclude src/main.c src/game.c src/obstacle.c src/start_menu.c src/death_menu.c src/stop_menu.c src/utils/print_text.c src/utils/init_game.c src/utils/character_motion.c src/utils/score.c src/utils/time.c src/utils/motion.c src/utils/audio.c -o main -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_image -lmingw32 -lSDL2_ttf -lSDL2_mixer } ; if ($?) { .\main }
```

**第三方库:** SDL2

**游戏规则:**
按A或方向左键是向上变道; 按D或方向右键是向下变道; 按W或方向上键跳跃; 按S或方向下键滑铲. R可重开, 空格可暂停, ESC可退出
吃金币可以得20分, 吃盾可获得**1次**无敌(普通模式下15秒会减少一个盾), 吃浓雾陷阱会有7秒浓雾遮住屏幕, 且扣10分
磁铁可以允许你吸引附近的金币; 足球可以撞开前方的障碍物
速度会随着分数增加而变快(100, 250, 500, 1000)
另外, 按B可开启和关闭宝宝模式(速度增加和上限均减少)
按M可以开启或关闭静音
现已加入双人模式, 在双人模式中分数为两人中最高者, 且目前在双人模式中无磁铁. 双人模式中Player 1使用"WASD"控制, Player 2使用"上下左右"控制

**程序思路:** 
*最开始初始化, 开始界面到游戏界面的动画通过移动SDL_RenderCopy()的srcrect来完成. 游戏过程中分为处理输入输出和显示画面两部分: 处理输入部分我并未将其封装为一个函数, 这是因为我想要在不同的页面中使输入对应的操作不同, 因此封装成函数没什么意义; 显示图像部分我通过分别控制背景, 任务, 障碍, 分数几个部分来实现. 另外, 我进行了暂停菜单和死亡菜单的设计*
**特别的,** *我在main()中将game()放在一个死循环中, 这样我只需要将game()函数返回, 即可实现重新开始. 我将障碍物按生成的顺序组成一个链表, 对这个链表我实现了删去头, 删去中间, 延长尾和删去链表的操作, 确保了内存不泄露. 除此之外, 我将多个功能按模块封装, 程序可维护性较强. 我设计了较多的动画, 且帧率达到了50帧. 我添加了独特的障碍: 浓雾陷阱和无敌盾. 我调整了道具出现的平衡性问题. 我多用宏, 增加了程序的可读性和可维护性. 我为程序增加了BGM. 这些是我自认为中程序的优点*

**另外,** *playground_run.exe可以在未搭建环境的windows电脑上直接运行 (需要动态链接库文件与·``playground_run.exe``在同一目录下) ~~(好像说过有加分)~~