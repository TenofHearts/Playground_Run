此程序用于南京大学技术科学实验班期末项目.

运行代码:cd "d:\Programing\cpl\Playground_Run\" ; if ($?) { gcc -Iinclude src/main.c src/game.c src/start_menu.c src/utils/print_text.c src/utils/character_motion.c src/utils/score.c -o main -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_image -lmingw32 -lSDL2_ttf } ; if ($?) { .\main }

src(source)存放源文件,include存放头文件,res(resourse)存放素材