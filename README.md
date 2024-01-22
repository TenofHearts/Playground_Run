此程序用于南京大学技术科学实验班期末项目.

运行代码:cd "d:\Programing\cpl\Playground_Run\" ; if ($?) { gcc -Iinclude src/main.c src/game.c src/obstacle.c src/start_menu.c src/death_menu.c src/stop_menu.c src/utils/print_text.c src/utils/init_game.c src/utils/character_motion.c src/utils/score.c src/utils/time.c -o main -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_image -lmingw32 -lSDL2_ttf } ; if ($?) { .\main }

src(source)存放源文件,include存放头文件,res(resourse)存放素材

游戏规则：
按A或方向左键是向上变道；按D或方向右键是向下变道；按W或方向上键跳跃；按S或方向下键滑铲。R可重开，空格可暂停，ESC可退出。
吃金币可以得20分，吃盾可获得5秒无敌
速度会随着分数增加而变快。