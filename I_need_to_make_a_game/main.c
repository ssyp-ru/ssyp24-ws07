#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

uint8_t point_in_a_rect(int x, int y, int rx, int ry, int w, int h){
    if(x >= rx && x <= rx + w && y >= ry && y <= ry + h) return 1;
    else return 0;
}

uint8_t collision(int r1x, int r1y, int h1, int w1, int r2x, int r2y, int h2, int w2){
    if(point_in_a_rect(r1x, r1y, r2x, r2y, w2, h2)) return 1;
    if(point_in_a_rect(r1x + w1, r1y, r2x, r2y, w2, h2)) return 1;
    if(point_in_a_rect(r1x, r1y + h1, r2x, r2y, w2, h2)) return 1;
    if(point_in_a_rect(r1x + w1, r1y + h1, r2x, r2y, w2, h2)) return 1;
    return 0;
}

int main()
{
	//Initialize random numbers generator
    srand(time(NULL));

    //Project uses following assets:
    sfMusic* xp_load;

    sfFont* font;
    sfText* text;
    sfText* text1;

    sfTexture* cat;
    sfSprite* pusheen;

    sfTexture* idea_t;
    sfSprite* idea;
    sfTexture* comp;
    sfSprite* pc;
    sfTexture* monitor;
    sfSprite* mon;
    sfTexture* icon;
    sfSprite* icons;

    sfTexture* wall;
    sfSprite* wallS;
    sfTexture* wall_win;
    sfSprite* wallWinS;
    sfTexture* wallD;
    sfSprite* wallDS;
    sfTexture* disp;
    sfSprite* display;
    sfTexture* flor;
    sfSprite* florS;

    sfTexture* clc;
    sfSprite* clock;
    sfTexture* restt;
    sfSprite* rest;
    sfTexture* furn;
    sfSprite* furniture;

    sfTexture* end;
    sfSprite* ending;
    sfTexture* cook;
    sfSprite* cooking;
    sfTexture* bugt;
    sfSprite* bug;

    sfRenderWindow* window;


    sfIntRect src_64_192 = {0, 0, 64, 192};
    sfIntRect src_16_16 = {0, 0, 16, 16};
    sfIntRect src_32_32 = {0, 0, 32, 32};
    sfIntRect src_80_60 = {0, 0, 80, 60};
    sfIntRect src_64_16 = {0, 0, 64, 16};
    sfIntRect src_64_32 = {0, 0, 64, 32};
    sfIntRect src_320_60 = {0, 0, 320, 60};

	// LOADING ASSETS FROM CORESPOINING FOLDER:
    {
        // === MUSIC ===
        {
            xp_load = sfMusic_createFromFile("hello.ogg");
            if(!xp_load){
                printf("FAILED TO LOAD MUSIC: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
        }

        // === FONT ===
        {
            font = sfFont_createFromFile("HomeVideo-BLG6G.ttf");
            if(!font){
                printf("FAILED TO LOAD FONT: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
        }

        // === TWO TEXTS ===
        {
            text = sfText_create();
            text1 = sfText_create();

            sfText_setString(text, "UNDEFINED");
            sfText_setString(text1, "UNDEFINED");

            sfText_setCharacterSize(text, 32);
            sfText_setCharacterSize(text1, 16);

            sfText_setFont(text, font);
            sfText_setFont(text1, font);

            sfText_setFillColor(text, sfBlack);
            sfText_setFillColor(text1, sfBlack);

            sfText_setPosition(text, (sfVector2f) {50, 25});
        }

        // === WINDOW ===
        {
            sfVideoMode mode = {800, 600, 32};
            window = sfRenderWindow_create(mode, "I need to make a game. Quick.", sfClose, NULL);
            sfRenderWindow_setFramerateLimit(window, 30);
        }

        // === PUSHEEN ===
        {
            cat = sfTexture_createFromFile("pusheen_spritesheet.png", &src_64_192);
            if(!cat){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            pusheen = sfSprite_create();
            sfSprite_setTexture(pusheen, cat, sfFalse);
            sfSprite_setPosition(pusheen, (sfVector2f){300, 300});
        }

        // === IDEA, COMPUTER, MONITORS, ICONS ===
        {
            idea_t = sfTexture_createFromFile("idea.png", &src_16_16);
            comp = sfTexture_createFromFile("computer.png", &src_32_32);
            monitor = sfTexture_createFromFile("monitor.png", &src_80_60);
            icon = sfTexture_createFromFile("icons_spritesheet.png", &src_64_16);

            if(!idea_t){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!cat){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!monitor){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!icon){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }

            idea = sfSprite_create();
            pc = sfSprite_create();
            mon = sfSprite_create();
            icons = sfSprite_create();

            sfSprite_setTexture(idea, idea_t, sfFalse);
            sfSprite_setTexture(pc, comp, sfFalse);
            sfSprite_setTexture(mon, monitor, sfFalse);
            sfSprite_setTexture(icons, icon, sfFalse);
        }

        // === BACKGROUND ===
        {
            wall = sfTexture_createFromFile("wall.png", &src_32_32);
            wall_win = sfTexture_createFromFile("wall_window.png", &src_32_32);
            wallD = sfTexture_createFromFile("wall_door.png", &src_32_32);
            disp = sfTexture_createFromFile("bottom_bar.png", &src_32_32);
            flor = sfTexture_createFromFile("modern_floor.png", &src_32_32);

            wallS = sfSprite_create();
            wallWinS = sfSprite_create();
            wallDS = sfSprite_create();
            display = sfSprite_create();
            florS = sfSprite_create();

            if(!wall){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!flor){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!wall_win){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!wallD){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!disp){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }

            sfSprite_setTexture(wallS, wall, sfFalse);
            sfSprite_setTexture(wallWinS, wall_win, sfFalse);
            sfSprite_setTexture(wallDS, wallD, sfFalse);
            sfSprite_setTexture(display, disp, sfFalse);
            sfSprite_setTexture(florS, flor, sfFalse);
        }


        // === CLOCK, FURNITURE, BED
        {
            clc = sfTexture_createFromFile("clock.png", &src_64_16);
            restt = sfTexture_createFromFile("rest.png", &src_80_60);
            furn = sfTexture_createFromFile("furniture.png", &src_64_32);
            bugt = sfTexture_createFromFile("bug.png", &src_16_16);

            if(!clc){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!bugt){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!restt){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!furn){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }

            clock = sfSprite_create();
            rest = sfSprite_create();
            bug = sfSprite_create();
            furniture = sfSprite_create();

            sfSprite_setTexture(clock, clc, sfFalse);
            sfSprite_setTexture(rest, restt, sfFalse);
            sfSprite_setTexture(furniture, furn, sfFalse);
            sfSprite_setTexture(bug, bugt, sfFalse);
        }

        // === ENDINGS, COOKING ==
        {
            end = sfTexture_createFromFile("endings_spritesheet.png", &src_320_60);
            cook = sfTexture_createFromFile("cooking.png", &src_80_60);

            if(!end){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }
            if(!cook){
                printf("FAILED TO LOAD TEXTURE: CRITICAL ERROR");
                return EXIT_FAILURE;
            }

            ending = sfSprite_create();
            cooking = sfSprite_create();

            sfSprite_setTexture(ending, end, sfFalse);
            sfSprite_setTexture(cooking, cook, sfFalse);
    }
    }

    int animation_phase = 0;
    int timer = 0;
    int last_movement = 0;
    int game_phase = 0;
    int project_phase = 0;
    int time_left = 2;
    int mins = 0;
    int hunger = 0;
    int tiredness = 88;
    int bugs = 0;

    /* === Game Phase Decypher:
    0 - tutorual (move)
    1 - turorial (computer)
    2 - tutorial (interractions)
    3 - normal game
    4 - choosing time to rest */
    sfIntRect rect = {0, 32, 32, 32};

    while (sfRenderWindow_isOpen(window)) {
        sfVector2f pos = sfSprite_getPosition(pusheen);
        sfRenderWindow_clear(window, sfWhite);
        for(int16_t i = 0; i < 800; i += 128){
            for(int16_t j = 0; j < 600; j += 128){
                sfRenderWindow_drawSprite(window, florS, NULL);
                sfSprite_setPosition(florS, (sfVector2f){i, j});
                sfSprite_setScale(florS, (sfVector2f){4, 4});
            }
        }
        for(int16_t i = 0; i < 800; i += 128){
            sfRenderWindow_drawSprite(window, wallS, NULL);
            sfSprite_setPosition(wallS, (sfVector2f){i, 0});
            sfSprite_setScale(wallS, (sfVector2f){4, 4});
        }
        for(int16_t i = 0; i < 800; i += 128){
            sfRenderWindow_drawSprite(window, display, NULL);
            sfSprite_setPosition(display, (sfVector2f){i, 472});
            sfSprite_setScale(display, (sfVector2f){4, 4});
        }
        sfRenderWindow_drawSprite(window, wallWinS, NULL);
        sfSprite_setPosition(wallWinS, (sfVector2f){383, 0});
        sfSprite_setScale(wallWinS, (sfVector2f){4, 4});
        sfRenderWindow_drawSprite(window, wallWinS, NULL);
        sfSprite_setPosition(wallWinS, (sfVector2f){639, 0});
        sfSprite_setScale(wallWinS, (sfVector2f){4, 4});
        sfRenderWindow_drawSprite(window, wallDS, NULL);
        sfSprite_setPosition(wallDS, (sfVector2f){127, 0});
        sfSprite_setScale(wallDS, (sfVector2f){4, 4});
        sfRenderWindow_drawSprite(window, pc, NULL);
        sfSprite_setPosition(pc, (sfVector2f){511, 255});
        sfSprite_setScale(pc, (sfVector2f){4, 4});
        sfRenderWindow_drawSprite(window, furniture, NULL);
        sfIntRect w = {0, 0, 32, 32};
        sfSprite_setTextureRect(furniture, w);
        sfSprite_setScale(furniture, (sfVector2f){4, 4});
        sfSprite_setPosition(furniture, (sfVector2f){0, 127});
        sfRenderWindow_drawSprite(window, furniture, NULL);
        w = {32, 0, 32, 32};
        sfSprite_setTextureRect(furniture, w);
        sfSprite_setScale(furniture, {4, 4});
        sfSprite_setPosition(furniture, (sfVector2f){0, 256});

        if(game_phase == 0) sfText_setString(text, "Try WASD to move");
        else if(game_phase == 1) sfText_setString(text, "Take a look in your E-mail");
        else if(game_phase == 2) sfText_setString(text, "Press 'E' to itrerract with objects");

        if(game_phase == 1 && collision(pos.x, pos.y, 64, 128, 511, 256, 128, 128)) game_phase = 2;

        sfEvent event;
        uint8_t flag_global = 0;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtKeyPressed){
                if(event.key.code == sfKeyA && !collision(pos.x, pos.y, 64, 128, 0, 0, 600, 5)){
                    last_movement = timer;
                    rect.top = 64;
                    pos.x -= 3.5;
                    if(game_phase == 0) game_phase = 1;
                }
                if(event.key.code == sfKeyD && !collision(pos.x, pos.y, 64, 100, 800, 0, 600, 5)){
                    last_movement = timer;
                    rect.top = 96;
                    pos.x += 3.5;
                    if(game_phase == 0) game_phase = 1;
                }
                if(event.key.code == sfKeyW && !collision(pos.x, pos.y, 64, 128, 0, 0, 100, 800)){
                    last_movement = timer;
                    rect.top = 128;
                    pos.y -= 3.5;
                    if(game_phase == 0) game_phase = 1;
                }
                if(event.key.code == sfKeyS  && !collision(pos.x, pos.y, 64, 128, 0, 472, 5, 800)){
                    last_movement = timer;
                    rect.top = 0;
                    pos.y += 3.5;
                    if(game_phase == 0) game_phase = 1;
                }
                if(event.key.code == sfKeyE  && collision(pos.x, pos.y, 64, 128, 511, 256, 128, 128)){
                    //computer interraction
                    /*=== computer phases ===
                    0 - computer not initialized
                    1 - computer home screen
                    2 - computer mail
                    3 - computer quit
                    4 - VS start
                    5 - VS minigame
                    6 - VS result
                    7 - bug fixing minigame
                    8 - bug fix result*/
                    uint8_t minigame_count = 0;
                    uint8_t computer_state = 0;
                    uint8_t minigame_target = 0;
                    sfVector2f ideas [5] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
                    sfVector2f pon = {200, 450};
                    if(game_phase == 2) game_phase = 3;
                    while(computer_state != 3){
                        sfRenderWindow_clear(window, sfWhite);
                        sfRenderWindow_drawSprite(window, mon, NULL);
                        sfSprite_setPosition(mon, (sfVector2f){0, 0});
                        sfSprite_setScale(mon, (sfVector2f){10, 10});
                        if(computer_state == 0 && sfMusic_getStatus(xp_load) != sfPlaying){
                            sfMusic_play(xp_load);
                        }
                        if(computer_state == 0 && sfMusic_getStatus(xp_load) == sfPlaying){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){150, 300});
                            sfText_setString(text, "Welcome, Pushin!");
                        }
                        if(computer_state == 2){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfText_setString(text, "From: notify@gamejam.com\nTo:pusheen@gmail.com");
                            sfRenderWindow_drawText(window, text1, NULL);
                            sfText_setPosition(text1, (sfVector2f){80, 264});
                            sfText_setString(text1, "Hello, mr. Pusheen.\nWe are glad to tell you that the 2085\ngamejam has officialy started.\n\nWe have noticed that even though you registered\nfor this event you didn't join the recent live\nstream.\nThis game jam's theme is 'A game inside a game'.\nYou will be able to submit your work until:\njune 13, 12:00 UTC\n\nBest wishes,\nMeta Gamejam team");
                            sfRenderWindow_drawSprite(window, icons, NULL);
                            sfIntRect e = {48, 0, 16, 16};
                            sfSprite_setTextureRect(icons, e);
                            sfSprite_setPosition(icons, (sfVector2f){400, 430});
                            sfSprite_setScale(icons, (sfVector2f){5, 5});
                        }
                        if(computer_state == 1){
                            sfRenderWindow_drawSprite(window, icons, NULL);
                            sfSprite_setTextureRect(icons, src_64_16);
                            sfSprite_setPosition(icons, (sfVector2f){150, 256});
                            sfSprite_setScale(icons, (sfVector2f){5, 5});
                        }
                        if(computer_state == 5){
                            if(minigame_count == 0) computer_state = 6;
                            if(minigame_count > 0){
                                if(rand() > 8 && rand() > 8 && rand() > 7 && rand() > 8 && rand() > 8 && rand() > 7){
                                    uint8_t flag = 9;
                                    for(int i = 0; i < 5; i++){
                                        if(ideas[i].x == 0 && ideas[i].y == 0) {
                                            flag = i;
                                        }
                                    }
                                    if(flag != 9){
                                        ideas[flag].x = ((rand() * rand() * 960) % 295) + 80;
                                        ideas[flag].y = ((rand() * rand() * 420) % 170) + 350;
                                        if(ideas[flag].x < 0) ideas[flag].x = (ideas[flag].x * -1) + 160;
                                        if(ideas[flag].y < 0) ideas[flag].y = (ideas[flag].y * -1) + 800;
                                        if(ideas[flag].x < 120) ideas[flag].x += 120;
                                        if(ideas[flag].y > 450)ideas[flag].y = 400;
                                    }
                                }
                                for(int i = 0; i < 5; i++){
                                    if(ideas[i].x != 0 && ideas[i].y != 0){
                                        sfRenderWindow_drawSprite(window, idea, NULL);
                                        sfSprite_setPosition(idea, ideas[i]);
                                        sfSprite_setScale(idea, (sfVector2f){5, 5});
                                    }
                                }
                                sfRenderWindow_drawText(window, text, NULL);
                                sfText_setPosition(text, (sfVector2f){80, 200});
                                sfText_setString(text, "Click on the light bulbs");
                            }
                        }
                        if(computer_state == 9){
                            sfRenderWindow_drawSprite(window, idea, NULL);
                            sfSprite_setPosition(idea, (sfVector2f){pon.x, pon.y});
                            sfSprite_setScale(idea, (sfVector2f){5, 5});
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfText_setString(text, "Catch all the bugs!");
                            int flag = 9;
                            for(int i = 0; i < 5; i++){
                                if(ideas[i].x == 0 && ideas[i].y == 0){
                                    flag = i;
                                }
                            }
                            int r = rand() % 100;
                            if(flag != 9 && r > 95){
                                ideas[flag].x = ((rand() * rand() * 960) % 295) + 80;
                                if(ideas[flag].x < 0) ideas[flag].x = (random() % 450) + 80;
                                if(ideas[flag].x < 120) ideas[flag].x += 120;
                                ideas[flag].y = 200;
                            }
                            for(int i = 0; i < 5; i++){
                                if(ideas[i].y != 0){
                                    ideas[i].y += 2;
                                    if(ideas[i].y > 360){
                                        if((ideas[i].x > pon.x && ideas[i].x < pon.x + 80) || (ideas[i].x + 80 > pon.x && ideas[i].x + 80 < 80 + pon.x)){
                                            bugs -= 1;
                                            ideas[i].x = 0;
                                            ideas[i].y = 0;
                                        }
                                    }
                                    sfRenderWindow_drawSprite(window, bug, NULL);
                                    sfSprite_setPosition(bug, ideas[i]);
                                    sfSprite_setScale(bug, (sfVector2f){5, 5});
                                    if(ideas[i].y > 460){
                                        ideas[i].x = 0;
                                        ideas[i].y = 0;
                                    }
                                }
                            }
                            minigame_count -= 1;
                            if(minigame_count < 1) computer_state = 10;
                        }
                        if(computer_state == 10){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfText_setString(text, "Bug fixing session done");
                            sfRenderWindow_drawText(window, text1, NULL);
                            sfText_setPosition(text1, (sfVector2f){80, 264});
                            char buffer[] = "Project completeness:   % ->   %\nTiredness:   % ->   %\nHunger:   % ->   %\nTime left:    hours ->    hours\nBugs:    \nENTER to exit";
                            buffer[22] = project_phase / 10 + 48;
                            buffer[23] = (project_phase % 10) + 48;
                            project_phase += minigame_target * 3;
                            if(project_phase > 99) project_phase = 99;
                            buffer[29] = project_phase / 10 + 48;
                            buffer[30] = (project_phase % 10) + 48;
                            buffer[44] = tiredness / 10 + 48;
                            buffer[45] = (tiredness % 10) + 48;
                            tiredness = tiredness + minigame_target * 6 + tiredness / 20;
                            buffer[51] = tiredness / 10 + 48;
                            buffer[52] = (tiredness % 10) + 48;
                            buffer[63] = hunger / 10 + 48;
                            buffer[64] = (hunger % 10) + 48;
                            hunger += minigame_target * 4;
                            buffer[70] = hunger / 10 + 48;
                            buffer[71] = (hunger % 10) + 48;
                            buffer[85] = time_left / 10 + 48;
                            buffer[86] = (time_left % 10) + 48;
                            time_left -= minigame_target;
                            buffer[97] = time_left / 10 + 48;
                            buffer[98] = (time_left % 10) + 48;
                            buffer[112] = bugs / 10 + 48;
                            buffer[113] = (bugs % 10) + 48;
                            sfText_setString(text1, buffer);
                            computer_state = 7;
                        }
                        if(computer_state == 4){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfText_setString(text, "Visual Studio Code");
                            sfRenderWindow_drawText(window, text1, NULL);
                            sfText_setPosition(text1, (sfVector2f){80, 264});

                            if(tiredness > 80 || hunger > 80 || time_left < 1) {
                                char buffer[] = "Your project is currently   % done\nYou are not in thee right condition to work";
                                buffer[26] = project_phase / 10 + 48;
                                buffer[27] = (project_phase % 10) + 48;
                                sfText_setString(text1, buffer);
                            }
                            else{
                                char buffer[] = "Your project is currently   % done\nChoose how much do you want to work for:   ";
                                buffer[26] = project_phase / 10 + 48;
                                buffer[27] = (project_phase % 10) + 48;
                                sfText_setString(text1, buffer);
                            }
                            if(tiredness < 50 && hunger < 50 && time_left > 3){
                                sfRenderWindow_drawSprite(window, clock, NULL);
                                sfSprite_setPosition(clock, (sfVector2f){150, 325});
                                sfIntRect u = {0, 0, 64, 16};
                                sfSprite_setTextureRect(clock, u);
                                sfSprite_setScale(clock, (sfVector2f){5, 5});
                            }
                            else if(tiredness < 60 && hunger < 60 && time_left > 2){
                                sfRenderWindow_drawSprite(window, clock, NULL);
                                sfIntRect u = {0, 0, 48, 16};
                                sfSprite_setTextureRect(clock, u);
                                sfSprite_setPosition(clock, (sfVector2f){150, 325});
                                sfSprite_setScale(clock, (sfVector2f){5, 5});
                            }
                            else if(tiredness < 70 && hunger < 70 && time_left > 1){
                                sfRenderWindow_drawSprite(window, clock, NULL);
                                sfIntRect u = {0, 0, 32, 16};
                                sfSprite_setTextureRect(clock, u);
                                sfSprite_setPosition(clock, (sfVector2f){150, 325});
                                sfSprite_setScale(clock, (sfVector2f){5, 5});
                            }
                            else if(tiredness < 80 && hunger < 80 && time_left > 0){
                                sfRenderWindow_drawSprite(window, clock, NULL);
                                sfIntRect u = {0, 0, 16, 16};
                                sfSprite_setTextureRect(clock, u);
                                sfSprite_setPosition(clock, (sfVector2f){150, 325});
                                sfSprite_setScale(clock, (sfVector2f){5, 5});
                            }
                            sfRenderWindow_drawSprite(window, icons, NULL);
                            sfIntRect e = {48, 0, 16, 16};
                            sfSprite_setTextureRect(icons, e);
                            sfSprite_setPosition(icons, (sfVector2f){400, 430});
                            sfSprite_setScale(icons, (sfVector2f){5, 5});

                        }
                        if(computer_state == 0 && sfMusic_getStatus(xp_load) != sfPlaying){
                            sfMusic_stop(xp_load);
                            computer_state = 1;
                        }
                        if(computer_state == 7){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfRenderWindow_drawText(window, text1, NULL);
                            sfText_setPosition(text1, (sfVector2f){80, 264});
                        }
                        if(computer_state == 6){
                            sfRenderWindow_drawText(window, text, NULL);
                            sfText_setPosition(text, (sfVector2f){80, 200});
                            sfText_setString(text, "Coding session complete");
                            sfRenderWindow_drawText(window, text1, NULL);
                            sfText_setPosition(text1, (sfVector2f){80, 264});
                            char buffer[] = "Project completeness:   % ->   %\nTiredness:   % ->   %\nHunger:   % ->   %\nTime left:    hours ->    hours\nBugs:   \nENTER to exit";
                            buffer[22] = project_phase / 10 + 48;
                            buffer[23] = (project_phase % 10) + 48;
                            project_phase += minigame_target * 3;
                            if(project_phase > 99) project_phase = 99;
                            buffer[29] = project_phase / 10 + 48;
                            buffer[30] = (project_phase % 10) + 48;
                            buffer[44] = tiredness / 10 + 48;
                            buffer[45] = (tiredness % 10) + 48;
                            tiredness = tiredness + minigame_target * 6 + tiredness / 20;
                            buffer[51] = tiredness / 10 + 48;
                            buffer[52] = (tiredness % 10) + 48;
                            buffer[63] = hunger / 10 + 48;
                            buffer[64] = (hunger % 10) + 48;
                            hunger += minigame_target * 4;
                            buffer[70] = hunger / 10 + 48;
                            buffer[71] = (hunger % 10) + 48;
                            buffer[85] = time_left / 10 + 48;
                            buffer[86] = (time_left % 10) + 48;
                            time_left -= minigame_target;
                            buffer[97] = time_left / 10 + 48;
                            buffer[98] = (time_left % 10) + 48;
                            bugs += 1;
                            buffer[112] = bugs / 10 + 48;
                            buffer[113] = (bugs % 10) + 48;
                            sfText_setString(text1, buffer);
                            computer_state = 7;
                        }
                        sfEvent ev_local;
                        while(sfRenderWindow_pollEvent(window, &ev_local)){
                            if(ev_local.type == sfEvtClosed) {
                                flag_global = 1;
                                computer_state = 3;
                                sfMusic_stop(xp_load);
                                break;
                            }
                            if(ev_local.type == sfEvtMouseButtonPressed && computer_state){
                                printf("Pos: %d %d\n", ev_local.mouseButton.x, ev_local.mouseButton.y);
                                if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 395, 262, 70, 70) && computer_state == 1) {
                                    computer_state = 3;
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 315, 262, 70, 70) && computer_state == 1) {
                                    computer_state = 4;
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 156, 278, 70, 45) && computer_state == 1) {
                                    computer_state = 2;
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 400, 430, 80, 80) && (computer_state == 2 || computer_state == 4)) {
                                    computer_state = 1;
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 150, 325, 80, 80) && computer_state == 4 && tiredness < 80 && time_left > 0 && hunger < 80) {
                                    for(int i = 0; i < 5; i++){
                                        ideas[i].x = 0;
                                        ideas[i].y = 0;
                                    }
                                    if(project_phase < 99){
                                        computer_state = 5;
                                        minigame_count = 7;
                                        minigame_target = 1;
                                    }
                                    else{
                                        computer_state = 9;
                                        minigame_count = 150;
                                        minigame_target = 1;
                                    }
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 230, 325, 80, 80) && computer_state == 4 && tiredness < 70 && time_left > 1 && hunger < 70) {
                                    for(int i = 0; i < 5; i++){
                                        ideas[i].x = 0;
                                        ideas[i].y = 0;
                                    }
                                    if(project_phase < 99){
                                        computer_state = 5;
                                        minigame_count = 10;
                                        minigame_target = 2;
                                    }
                                    else{
                                        computer_state = 9;
                                        minigame_count = 300;
                                        minigame_target = 2;
                                    }
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 310, 325, 80, 80) && computer_state == 4 && tiredness < 60 && time_left > 2 && hunger < 60) {
                                    for(int i = 0; i < 5; i++){
                                        ideas[i].x = 0;
                                        ideas[i].y = 0;
                                    }
                                    if(project_phase < 99){
                                        computer_state = 5;
                                        minigame_count = 16;
                                        minigame_target = 3;
                                    }
                                    else{
                                        computer_state = 9;
                                        minigame_count = 450;
                                        minigame_target = 3;
                                    }
                                }
                                else if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, 390, 325, 80, 80) && computer_state == 4 && tiredness < 50 && time_left > 3 && hunger < 50) {
                                    for(int i = 0; i < 5; i++){
                                        ideas[i].x = 0;
                                        ideas[i].y = 0;
                                    }
                                    if(project_phase < 99){
                                        computer_state = 5;
                                        minigame_count = 15;
                                        minigame_target = 4;
                                    }
                                    else{
                                        computer_state = 9;
                                        minigame_count = 600;
                                        minigame_target = 4;
                                    }
                                }
                                if(computer_state == 5){
                                    uint8_t cc = 0;
                                    for(int i = 0; i < 5; i++){
                                        if(point_in_a_rect(ev_local.mouseButton.x, ev_local.mouseButton.y, ideas[i].x, ideas[i].y, 80, 80)){
                                            minigame_count -= 1;
                                            ideas[i].x = 0;
                                            ideas[i].y = 0;
                                            cc = 1;
                                            if(minigame_count == 0) computer_state = 6;
                                        }
                                    }
                                    if(!cc) bugs += 1;
                                }
                            }
                            if(ev_local.type == sfEvtKeyPressed){
                                if(ev_local.key.code == sfKeyEnter){
                                    computer_state = 1;
                                }
                                if(ev_local.key.code == sfKeyA){
                                    if(pon.x > 80) pon.x -= 5;
                                }
                                if(ev_local.key.code == sfKeyD){
                                    if(pon.x < 500) pon.x += 5;
                                }
                            }
                        }
                        sfRenderWindow_display(window);
                    }
                }
                if(event.key.code == sfKeyE  && collision(pos.x, pos.y, 64, 128, 0, 127, 88, 112)){
                    uint8_t in_rest_menu  = 1;
                    uint8_t sleep_target = 0;
                    sfText_setString(text, "");
                    while(in_rest_menu){
                        sfRenderWindow_clear(window, sfWhite);
                        sfRenderWindow_drawSprite(window, rest, NULL);
                        sfSprite_setPosition(rest, (sfVector2f){0, 0});
                        sfSprite_setScale(rest, (sfVector2f){10, 10});
                        if(in_rest_menu == 1){
                            sfRenderWindow_drawSprite(window, icons, NULL);
                            sfIntRect e = {48, 0, 16, 16};
                            sfSprite_setTextureRect(icons, e);
                            sfSprite_setPosition(icons, (sfVector2f){700, 500});
                            sfSprite_setScale(icons, (sfVector2f){5, 5});
                        }
                        if(in_rest_menu == 2){
                            char buf[] = "Tiredness:   % ->   %\nhunger:   % ->   %\ntime left:    hours ->    hours\nENTER to continue";
                            buf[11] = tiredness / 10 + 48;
                            buf[12] = (tiredness % 10) + 48;
                            tiredness -= sleep_target * 6;
                            if(tiredness < 0) tiredness = 0;
                            buf[18] = tiredness / 10 + 48;
                            buf[19] = (tiredness % 10) + 48;
                            buf[30] = hunger / 10 + 48;
                            buf[31] = (hunger % 10) + 48;
                            hunger += sleep_target * 4;
                            buf[37] = hunger / 10 + 48;
                            buf[38] = (hunger % 10) + 48;
                            buf[52] = time_left / 10 + 48;
                            buf[53] = (time_left % 10) + 48;
                            time_left -= sleep_target;
                            buf[64] = time_left / 10 + 48;
                            buf[65] = (time_left % 10) + 48;
                            in_rest_menu = 3;
                            sfText_setString(text, buf);
                        }
                        sfRenderWindow_drawText(window, text, NULL);
                        sfText_setPosition(text, (sfVector2f){100, 50});

                        sfEvent evt;
                        while(sfRenderWindow_pollEvent(window, &evt)){
                            if(evt.type == sfEvtClosed){
                                sfRenderWindow_close(window);
                            }
                            if(evt.type == sfEvtMouseButtonPressed){
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  150, 200, 80, 80) && in_rest_menu == 1){
                                    if(hunger < 70){
                                        if(time_left > 2){
                                            sleep_target = 3;
                                            in_rest_menu = 2;
                                        }
                                        else{
                                            sfText_setString(text, "Not enough time");
                                        }
                                    }
                                    else{
                                        sfText_setString(text, "Too hungry");
                                    }
                                }
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  260, 200, 80, 80)  && in_rest_menu == 1){
                                    if(hunger < 60){
                                        if(time_left > 4){
                                            sleep_target = 5;
                                            in_rest_menu = 2;
                                        }
                                        else{
                                            sfText_setString(text, "Not enough time");
                                        }
                                    }
                                    else{
                                        sfText_setString(text, "Too hungry");
                                    }
                                }
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  370, 200, 80, 80) && in_rest_menu == 1){
                                    if(hunger < 50){
                                        if(time_left > 6){
                                            sleep_target = 7;
                                            in_rest_menu = 2;
                                        }
                                        else{
                                            sfText_setString(text, "Not enough time");
                                        }
                                    }
                                    else{
                                        sfText_setString(text, "Too hungry");
                                    }
                                }
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  480, 200, 80, 80) && in_rest_menu == 1){
                                    if(hunger < 40){
                                        if(time_left > 7){
                                            sleep_target = 8;
                                            in_rest_menu = 2;
                                        }
                                        else{
                                            sfText_setString(text, "Not enough time");
                                        }
                                    }
                                    else{
                                        sfText_setString(text, "Too hungry");
                                    }
                                }
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  590, 200, 80, 80) && in_rest_menu == 1){
                                    if(hunger < 50){
                                        if(time_left > 8){
                                            sleep_target = 9;
                                            in_rest_menu = 2;
                                        }
                                        else{
                                            sfText_setString(text, "Not enough time");
                                        }
                                    }
                                    else{
                                        sfText_setString(text, "Too hungry");
                                    }
                                }
                                if(point_in_a_rect(evt.mouseButton.x, evt.mouseButton.y,  700, 500, 80, 80) && in_rest_menu == 1){
                                    in_rest_menu = 0;
                                }
                            }
                            if(evt.type == sfEvtKeyPressed){
                                    in_rest_menu = 0;
                            }
                        }

                        sfRenderWindow_display(window);
                    }
                }
                if(event.key.code == sfKeyE  && collision(pos.x, pos.y, 64, 128, 0, 290, 88, 112)){
                    sfRectangleShape* recta;
                    recta = sfRectangleShape_create();
                    sfRectangleShape_setSize(recta, (sfVector2f){10, 50});
                    sfRectangleShape_setFillColor(recta, sfWhite);
                    float score  = 1;
                    int8_t minigame_duratuin = 5;
                    sfText_setString(text, "");
                    sfVector2f rpos = {200, 180};
                    int8_t axel = 1;
                    while(minigame_duratuin != -2){
                        sfRenderWindow_clear(window, sfWhite);
                        sfRenderWindow_drawSprite(window, cooking, NULL);
                        sfSprite_setPosition(cooking, (sfVector2f){0, 0});
                        sfSprite_setScale(cooking, (sfVector2f){10, 10});
                        if(minigame_duratuin == 10){
                            sfText_setString(text, "Press SPACE when the rectangle\nis in the green zone\nPress ENTER to leave");
                        }
                        else if(minigame_duratuin > 0){
                            char pony [] = " 0% done";
                            pony[0] = 10 - (2 * minigame_duratuin) + 48;
                            sfText_setString(text, pony);
                        }
                        sfRenderWindow_drawText(window, text, NULL);
                        sfText_setPosition(text, (sfVector2f){100, 20});

                        sfEvent evt;
                        while(sfRenderWindow_pollEvent(window, &evt)){
                            if(evt.type == sfEvtClosed){
                                sfRenderWindow_close(window);
                            }
                            if(evt.type == sfEvtKeyPressed){
                                if(evt.key.code == sfKeyEnter){
                                    minigame_duratuin = -2;
                                }
                                if(evt.key.code == sfKeySpace){
                                    minigame_duratuin -= 1;
                                    if(rpos.x >  430){
                                        score += (190 - (rpos.x - 430)) / 19;
                                    }
                                    else{
                                        score += (rpos.x - 200) / 23;
                                    }
                                }
                            }
                        }
                        if(minigame_duratuin == 0){
                        char buf[] = "Food prepared\nHunger:   % ->   %\nScore:   \nENTER to leave";
                            buf[22] = hunger / 10 + 48;
                            buf[23] = (hunger % 10) + 48;
                            if(score > 15) hunger -= score - 15;
                            if (hunger < 0) hunger = 0;
                            buf[29] = hunger / 10 + 48;
                            buf[30] = (hunger % 10) + 48;
                            buf[40] = ((score / 10) + 48);
                            buf[41] = ((int)score % 10) + 48;
                            minigame_duratuin = -1;
                            sfText_setString(text, buf);
                        }
                        if(minigame_duratuin > 0){
                            if(axel == 1){
                               rpos.x += 15;
                               if(rpos.x > 610) axel = -1;
                            }
                            if(axel == -1){
                                rpos.x -= 15;
                               if(rpos.x < 210) axel = 1;
                            }
                            sfRenderWindow_drawRectangleShape(window, recta, NULL);
                            sfRectangleShape_setPosition(recta, rpos);
                        }
                        sfRenderWindow_display(window);
                    }
                sfRectangleShape_destroy(recta);
                }
            }
        }
        if(flag_global){
            sfRenderWindow_close(window);
            break;
        }
        sfRenderWindow_drawSprite(window, pusheen, NULL);
        sfSprite_setPosition(pusheen, (sfVector2f){0, 0});
        if(last_movement + 60 < timer && rect.top != 32) rect.top = 32;
        if(last_movement + 600 < timer && rect.top == 32) rect.top = 160;
        if (animation_phase == 1 && rect.top != 160) {
            rect.left = 32;
        }
        else{
            rect.left = 0;
        }
        sfSprite_setTextureRect(pusheen, rect);
        sfSprite_setScale(pusheen, (sfVector2f){4, 4});
        sfSprite_setPosition(pusheen, pos);
        sfRenderWindow_drawText(window, text, NULL);
        sfText_setPosition(text, (sfVector2f){16, 496});
        sfRenderWindow_display(window);
        if(timer % 20 == 0) {
            animation_phase = (animation_phase + 1) % 2;
        }
        timer += 1;
        if(game_phase == 3){
            if(timer % 29 == 0) mins += 1;
            if(timer % 2 == 0 && tiredness > 79 && time_left < 3) mins += 1;
            if(mins > 60){
                time_left -= 1;
                mins = 0;
            }
        }
        if(time_left == 0){
            if(project_phase == 99 && bugs < 9){
                while(sfRenderWindow_isOpen(window)){
                    sfRenderWindow_clear(window, sfWhite);
                    sfRenderWindow_drawSprite(window, ending, NULL);
                    sfSprite_setPosition(ending, (sfVector2f){0, 0});
                    sfSprite_setScale(ending, (sfVector2f){10, 10});
                    sfIntRect yo = {0, 0, 80, 60};
                    sfSprite_setTextureRect(ending, yo);
                    sfEvent evet;
                    sfRenderWindow_drawText(window, text, NULL);
                    sfText_setString(text, "Ending 1/4: perfect ending");
                    sfText_setPosition(text, (sfVector2f){15, 15});
                    sfRenderWindow_drawText(window, text1, NULL);
                    sfText_setCharacterSize(text1, 20);
                    sfText_setString(text1, "Your game was briliant.\nYou won the contest. On top of\nthat, it got pretty popular.\nAfter making a few more updates\nyou earned a lot from it.\n\nThanks for playing.\nI really appreciate that.");
                    sfText_setPosition(text1, (sfVector2f){15, 79});
                    while(sfRenderWindow_pollEvent(window, &evet)){
                        if(evet.type == sfEvtClosed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtKeyPressed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtMouseButtonPressed){
                            sfRenderWindow_close(window);
                        }
                    }
                    sfRenderWindow_display(window);
                }
            }
            if(project_phase > 95 && bugs < 20){
                while(sfRenderWindow_isOpen(window)){
                    sfRenderWindow_clear(window, sfWhite);
                    sfRenderWindow_drawSprite(window, ending, NULL);
                    sfSprite_setPosition(ending, (sfVector2f){0, 0});
                    sfSprite_setScale(ending, (sfVector2f){10, 10});
                    sfIntRect yo = {80, 0, 80, 60};
                    sfSprite_setTextureRect(ending, yo);
                    sfEvent evet;
                    sfRenderWindow_drawText(window, text, NULL);
                    sfText_setString(text, "Ending 2/4: good ending");
                    sfText_setPosition(text, (sfVector2f){15, 15});
                    sfRenderWindow_drawText(window, text1, NULL);
                    sfText_setCharacterSize(text1, 20);
                    sfText_setString(text1, "You implemented all the planed features and won the contest.\nAfter this a big company noticed you.\nYou recived a job offer.\nNow you will finaly get your dream job\n\nThanks for playing.\nI really appreciate that.");
                    sfText_setPosition(text1, (sfVector2f){15, 79});
                    while(sfRenderWindow_pollEvent(window, &evet)){
                        if(evet.type == sfEvtClosed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtKeyPressed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtMouseButtonPressed){
                            sfRenderWindow_close(window);
                        }
                    }
                    sfRenderWindow_display(window);
                }
            }
            if(project_phase < 15){
                while(sfRenderWindow_isOpen(window)){
                    sfRenderWindow_clear(window, sfWhite);
                    sfRenderWindow_drawSprite(window, ending, NULL);
                    sfSprite_setPosition(ending, (sfVector2f){0, 0});
                    sfSprite_setScale(ending, (sfVector2f){10, 10});
                    sfIntRect yo = {240, 0, 80, 60};
                    sfSprite_setTextureRect(ending, yo);
                    sfEvent evet;
                    sfRenderWindow_drawText(window, text, NULL);
                    sfText_setString(text, "Ending 4/4: 'no, thanks' ending");
                    sfText_setColor(text, sfWhite);
                    sfText_setPosition(text, (sfVector2f){15, 15});
                    sfRenderWindow_drawText(window, text1, NULL);
                    sfText_setCharacterSize(text1, 20);
                    sfText_setColor(text1, sfWhite);
                    sfText_setString(text1, "You decided that the contest isn't\nworth your attention\n\nThanks for playing.\nI really appreciate that.");
                    sfText_setPosition(text1, (sfVector2f){15, 79});
                    while(sfRenderWindow_pollEvent(window, &evet)){
                        if(evet.type == sfEvtClosed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtKeyPressed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtMouseButtonPressed){
                            sfRenderWindow_close(window);
                        }
                    }
                    sfRenderWindow_display(window);
                }
            }
            else{
                while(sfRenderWindow_isOpen(window)){
                    sfRenderWindow_clear(window, sfWhite);
                    sfRenderWindow_drawSprite(window, ending, NULL);
                    sfSprite_setPosition(ending, (sfVector2f){0, 0});
                    sfSprite_setScale(ending, (sfVector2f){10, 10});
                    sfIntRect yo = {160, 0, 80, 60};
                    sfSprite_setTextureRect(ending, yo);
                    sfEvent evet;
                    sfRenderWindow_drawText(window, text, NULL);
                    sfText_setString(text, "Ending 3/4: neutral ending");
                    sfText_setPosition(text, (sfVector2f){15, 15});
                    sfRenderWindow_drawText(window, text1, NULL);
                    sfText_setCharacterSize(text1, 20);
                    sfText_setString(text1, "Your project wasn't perfect. However, you\nhad a lot of fun making it.\nWhile working on this project you\nlearned new skills and just had a good time.\n\nThanks for playing.\nI really appreciate that.");
                    sfText_setPosition(text1, (sfVector2f){15, 79});
                    while(sfRenderWindow_pollEvent(window, &evet)){
                        if(evet.type == sfEvtClosed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtKeyPressed){
                            sfRenderWindow_close(window);
                        }
                        if(event.type == sfEvtMouseButtonPressed){
                            sfRenderWindow_close(window);
                        }
                    }
                    sfRenderWindow_display(window);
                }
            }
        }
        char res[] = "Time left:    hours, hunger:   %,\ntiredness:   %";
        res[11] = time_left / 10 + 48;
        res[12] = (time_left % 10) + 48;
        res[29] = hunger / 10 + 48;
        res[30] = (hunger % 10) + 48;
        res[45] = tiredness / 10 + 48;
        res[46] = (tiredness % 10) + 48;
        sfText_setString(text, res);
    }

    sfMusic_destroy(xp_load);

    sfFont_destroy(font);
    sfText_destroy(text);
    sfText_destroy(text1);

    sfTexture_destroy(cat);
    sfSprite_destroy(pusheen);

    sfTexture_destroy(idea_t);
    sfSprite_destroy(idea);
    sfTexture_destroy(comp);
    sfSprite_destroy(pc);
    sfTexture_destroy(monitor);
    sfSprite_destroy(mon);
    sfTexture_destroy(icon);
    sfSprite_destroy(icons);

    sfTexture_destroy(wall);
    sfSprite_destroy(wallS);
    sfTexture_destroy(wall_win);
    sfSprite_destroy(wallWinS);
    sfTexture_destroy(wallD);
    sfSprite_destroy(wallDS);
    sfTexture_destroy(disp);
    sfSprite_destroy(display);
    sfTexture_destroy(flor);
    sfSprite_destroy(florS);

    sfTexture_destroy(clc);
    sfSprite_destroy(clock);
    sfTexture_destroy(restt);
    sfSprite_destroy(rest);
    sfTexture_destroy(furn);
    sfSprite_destroy(furniture);

    sfTexture_destroy(end);
    sfSprite_destroy(ending);
    sfTexture_destroy(cook);
    sfSprite_destroy(cooking);

    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
