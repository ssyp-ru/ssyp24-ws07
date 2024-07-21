#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <time.h>
#include <SFML/Audio.h>

typedef struct{
    sfTexture* texture;
    sfSprite* sprite;
    float y;
    float vy;
}bird_t;

void itoa(int32_t num, char* buff) {
    int u = abs(num);
    int y = abs(num);
    int len = 0;
    for(len = 0; u > 0; len++, u /= 10);
    if (num < 0) {
        len++;
    }
    buff[len] = '\0';
    if(num < 0) {
        buff[0] = '-';
        for(int i = len; i > 1; i--) {
            buff[i - 1] = y % 10 + '0';
            y /= 10;
        }
    }
    if(num == 0 || num > 0) {
        for(int i = len; i > 0; i--) {
            buff[i - 1] = num % 10 + '0';
            num /= 10;
        }
    }
}

int main()
{
    srand(time(NULL));

    char scht[11];
    int flag = 10;

    sfMusic* load;
    load = sfMusic_createFromFile("music.ogg");

    sfMusic* load1;
    load1 = sfMusic_createFromFile("music1.ogg");

    sfFont *font;
    font = sfFont_createFromFile("PFAgoraSlabPro Bold.ttf");

    sfText* text;
    text = sfText_create();
    sfText_setString(text, "0");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 40);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, (sfVector2f){900, 60});

    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){1000, 640, 32}, "Project", sfDefaultStyle, NULL);
    sfIntRect tmp = {0,0, 1000, 500};
    sfTexture* texture = sfTexture_createFromFile("1234.jpg", &tmp);
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfFalse);

    sfIntRect tmp1 = {0,0, 1000, 140};
    sfTexture* texture1 = sfTexture_createFromFile("99.jpeg", &tmp1);
    sfSprite* sprite1 = sfSprite_create();
    sfSprite_setTexture(sprite1, texture1, sfFalse);

    sfIntRect tmp111 = {0,0, 1000, 140};
    sfTexture* texture111 = sfTexture_createFromFile("12378.png", &tmp111);
    sfSprite* sprite111 = sfSprite_create();
    sfSprite_setTexture(sprite111, texture111, sfFalse);
    sfSprite_setPosition(sprite111, (sfVector2f){450.0, 800.0});

    sfIntRect tmp112 = {0,0, 100, 33};
    sfTexture* texture112 = sfTexture_createFromFile("32.png", &tmp112);
    sfSprite* sprite112 = sfSprite_create();
    sfSprite_setTexture(sprite112, texture112, sfFalse);
    sfSprite_setPosition(sprite112, (sfVector2f){20.0, 20.0});

    sfIntRect tmp2 = {0,0, 1000, 140};
    sfTexture* texture2 = sfTexture_createFromFile("99.jpeg", &tmp2);
    sfSprite* sprite2 = sfSprite_create();
    sfSprite_setTexture(sprite2, texture2, sfFalse);

    sfIntRect tmp3 = {0,0, 1000, 140};
    sfTexture* texture3 = sfTexture_createFromFile("99.jpeg", &tmp3);
    sfSprite* sprite3 = sfSprite_create();
    sfSprite_setTexture(sprite3, texture3, sfFalse);

    sfIntRect tmp4 = {0,0, 1000, 140};
    sfTexture* texture4 = sfTexture_createFromFile("99.jpeg", &tmp4);
    sfSprite* sprite4 = sfSprite_create();
    sfSprite_setTexture(sprite4, texture4, sfFalse);

    sfIntRect tmp5 = {0,0, 80, 80};
    sfTexture* texture5 = sfTexture_createFromFile("899.png", &tmp5);
    sfSprite* sprite5 = sfSprite_create();
    sfSprite_setTexture(sprite5, texture5, sfFalse);

    sfSprite_setPosition(sprite5, (sfVector2f){500.0, 450.0});

    //STOLBIKI

    float kp;
    kp = (float)(150 + rand() % 151) / 100;
    sfIntRect tmp6 = {0,0, 1000, 1000};
    sfTexture* texture6 = sfTexture_createFromFile("66.png", &tmp6);
    sfSprite* sprite6 = sfSprite_create();
    sfSprite_setTexture(sprite6, texture6, sfFalse);
    sfSprite_setPosition(sprite6, (sfVector2f){700.0, 500 - 105 * kp});
    sfSprite_setScale(sprite6, (sfVector2f){1.0, kp});


    float kp1;
    kp1 = (float)(150 + rand() % 151) / 100;
    sfIntRect tmp7 = {0,0, 1000, 1000};
    sfTexture* texture7 = sfTexture_createFromFile("66.png", &tmp7);
    sfSprite* sprite7 = sfSprite_create();
    sfSprite_setTexture(sprite7, texture7, sfFalse);
    sfSprite_setScale(sprite7, (sfVector2f){1.0, kp1});
    sfSprite_setPosition(sprite7, (sfVector2f){950.0, 500 - 105 * kp1});

    float kp2;
    kp2 = (float)(150 + rand() % 151) / 100;
    sfIntRect tmp8 = {0,0, 1000, 1000};
    sfTexture* texture8 = sfTexture_createFromFile("66.png", &tmp8);
    sfSprite* sprite8 = sfSprite_create();
    sfSprite_setTexture(sprite8, texture8, sfFalse);
    sfSprite_setScale(sprite8, (sfVector2f){1.0, kp2});
    sfSprite_setPosition(sprite8, (sfVector2f){1200.0, 500 - 105 * kp2});

    float kp3;
    kp3 = (float)(150 + rand() % 151) / 100;
    sfIntRect tmp9 = {0,0, 1000, 1000};
    sfTexture* texture9 = sfTexture_createFromFile("66.png", &tmp9);
    sfSprite* sprite9 = sfSprite_create();
    sfSprite_setTexture(sprite9, texture9, sfFalse);
    sfSprite_setScale(sprite9, (sfVector2f){1.0, kp3});
    sfSprite_setPosition(sprite9, (sfVector2f){1450.0, 500 - 105 * kp3});

    float kp4;
    kp4 = (float)(150 + rand() % 151) / 100;
    sfIntRect tmp10 = {0,0, 1000, 1000};
    sfTexture* texture10 = sfTexture_createFromFile("66.png", &tmp10);
    sfSprite* sprite10 = sfSprite_create();
    sfSprite_setTexture(sprite10, texture10, sfFalse);
    sfSprite_setScale(sprite10, (sfVector2f){1.0, kp4});
    sfSprite_setPosition(sprite10, (sfVector2f){1700.0, 500 - 105 * kp4});



    int tet = 445;
    int h = 0;
    int nebesnaya_kara = 0;
    int sch = 0;
    sfClock* clock = sfClock_create();
    float dt = 0;
    sfRenderWindow_setFramerateLimit(window, 60);

    sfMusic_setLoop(load, sfTrue);
    sfMusic_play(load);


    while (sfRenderWindow_isOpen(window))
    {
        sfClock_restart(clock);
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {

            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if(event.type == sfEvtKeyPressed) {
                if(event.key.code == sfKeyUp && sfSprite_getPosition(sprite5).y > 0 && h == 0) {
                    sfSprite_move(sprite5, (sfVector2f){0, -125});
                }
                if(event.key.code == sfKeyEnter) {
                    sfRenderWindow_close(window);
                }

            }
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(255, 255, 255));
        sfSprite_setPosition(sprite, (sfVector2f){0.0, 0.0});
        sfRenderWindow_drawSprite(window, sprite, NULL);


        sfSprite_setPosition(sprite1, (sfVector2f){0.0, 500.0});
        sfRenderWindow_drawSprite(window, sprite1, NULL);

        sfSprite_setPosition(sprite2, (sfVector2f){259.0, 500.0});
        sfRenderWindow_drawSprite(window, sprite2, NULL);

        sfSprite_setPosition(sprite3, (sfVector2f){518.0, 500.0});
        sfRenderWindow_drawSprite(window, sprite3, NULL);

        sfSprite_setPosition(sprite4, (sfVector2f){777.0, 500.0});
        sfRenderWindow_drawSprite(window, sprite4, NULL);

        sfRenderWindow_drawSprite(window, sprite111, NULL);

        if (h == 1 || h == 2 || h == 3) {
            if (sfSprite_getPosition(sprite111).y > 515.0) {
                sfSprite_move(sprite111, (sfVector2f){0, -6});
            }
            sfMusic_stop(load);
        }


        sfRenderWindow_drawSprite(window, sprite6, NULL);

        sfRenderWindow_drawSprite(window, sprite7, NULL);

        sfRenderWindow_drawSprite(window, sprite8, NULL);

        sfRenderWindow_drawSprite(window, sprite9, NULL);

        sfRenderWindow_drawSprite(window, sprite10, NULL);

        sfRenderWindow_drawSprite(window, sprite5, NULL);

        sfRenderWindow_drawSprite(window, sprite112, NULL);

        sfRenderWindow_drawText(window, text, NULL);


        if (sfSprite_getPosition(sprite5).y < 450.0 && (h == 0 || h == 2 || h == 3 || nebesnaya_kara == 1)) {
                sfSprite_move(sprite5, (sfVector2f){0, 6});
                tet += 1;
        }

        if (sfSprite_getPosition(sprite112).x >= -1) {
            sfSprite_move(sprite112, (sfVector2f){-0.1, 0 /* dt*/});
        }

        if (sfSprite_getPosition(sprite112).x <= 0) {
            sfSprite_setPosition(sprite112, (sfVector2f){20, 20});
        }

        //STOLBIKI_HEIGHT

        sfVector2f r4 = sfSprite_getPosition(sprite10);
        float x4 = r4.x;
        float y4 = r4.y;
        if (h == 0)
            sfSprite_move(sprite6, (sfVector2f){-3, 0});
        sfVector2f r = sfSprite_getPosition(sprite6);
        float x = r.x;
        float y = r.y;
        if (x < -64) {
            kp = (float)(150 + rand() % 151) / 100;
            sfSprite_setPosition(sprite6, (sfVector2f){x4 + 250, 500 - 105 * kp});
            sfSprite_setScale(sprite6, (sfVector2f){1.0, kp});
            x = x4 + 250;
        }

        if (h == 0)
            sfSprite_move(sprite7, (sfVector2f){-3, 0});
        sfVector2f r1 = sfSprite_getPosition(sprite7);
        float x1 = r1.x;
        float y1 = r1.y;
        if (x1 < -64) {
            kp1 = (float)(150 + rand() % 151) / 100;
            sfSprite_setPosition(sprite7, (sfVector2f){x + 250, 500 - 105 * kp1});
            sfSprite_setScale(sprite7, (sfVector2f){1.0, kp1});
            x1 = x + 250;
        }

        if (h == 0)
            sfSprite_move(sprite8, (sfVector2f){-3, 0});
        sfVector2f r2 = sfSprite_getPosition(sprite8);
        float x2 = r2.x;
        float y2 = r2.y;
        if (x2 < -64) {
            kp2 = (float)(150 + rand() % 151) / 100;
            sfSprite_setPosition(sprite8, (sfVector2f){x1 + 250, 500 - 105 * kp2});
            sfSprite_setScale(sprite8, (sfVector2f){1.0, kp2});
            x2 = x1 + 250;
        }

        if (h == 0)
            sfSprite_move(sprite9, (sfVector2f){-3, 0});
        sfVector2f r3 = sfSprite_getPosition(sprite9);
        float x3 = r3.x;
        float y3 = r3.y;
        if (x3 < -64) {
            kp3 = (float)(150 + rand() % 151) / 100;
            sfSprite_setPosition(sprite9, (sfVector2f){x2 + 250, 500 - 105 * kp3});
            sfSprite_setScale(sprite9, (sfVector2f){1.0, kp3});
            x3 = x2 + 250;
        }

        if (h == 0)
            sfSprite_move(sprite10, (sfVector2f){-3, 0});
        sfVector2f r5 = sfSprite_getPosition(sprite10);
        float x5 = r5.x;
        float y5 = r5.y;
        if (x5 < -64) {
            kp4 = (float)(150 + rand() % 151) / 100;
            sfSprite_setPosition(sprite10, (sfVector2f){x3 + 250, 500 - 105 * kp4});
            sfSprite_setScale(sprite10, (sfVector2f){1.0, kp4});
            x5 = x3 + 250;
        }
        sfTime time = sfClock_getElapsedTime(clock);

        dt = (float)sfTime_asMicroseconds(time) / 80;

        sfVector2f rpt = sfSprite_getPosition(sprite5);
        float xpt = rpt.x;
        float ypt = rpt.y;


        //PROVERKA_LINE
        if (x >= 551){
            if ((x <= 555 && x >= 551) && (ypt + 52 > 501 - 105 * kp && ypt <= 500) && h != 1) {
                h = 2;
                sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                sfSprite_setPosition(sprite5, (sfVector2f){x - 52, ypt});
                }
        }   else{
            //BIRDINUP
            if ((x < 500+51 && x > 500 - 47) && (ypt + 52 >= 500 - 105 * kp && (ypt + 52 <= 507 - 105 * kp)) && (h != 2)) {
                    h = 1;
                    sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                    sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                    sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                    sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                    sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                    sfSprite_setPosition(sprite5, (sfVector2f){xpt, y - 53});
                    }
        }

        if (x1 >= 551){
            if ((x1 <= 555 && x1 >= 551) && (ypt + 52 > 501 - 105 * kp1 && ypt <= 500) && h != 1) {
                h = 2;
                sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                sfSprite_setPosition(sprite5, (sfVector2f){x1 - 52, ypt});
                }
        }   else{
            //BIRDINUP
            if ((x1 < 500+51 && x1 > 500 - 47) && (ypt + 52 >= 500 - 105 * kp1 && (ypt + 52 <= 507 - 105 * kp1)) && (h != 2)) {
                    h = 1;
                    sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                    sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                    sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                    sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                    sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                    sfSprite_setPosition(sprite5, (sfVector2f){xpt, y1 - 53});
                    }
        }

        if (x2 >= 551){
            if ((x2 <= 555 && x2 >= 551) && (ypt + 52 > 501 - 105 * kp2 && ypt <= 500) && h != 1) {
                h = 2;
                sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                sfSprite_setPosition(sprite5, (sfVector2f){x2 - 52, ypt});
                }
        }   else{
            //BIRDINUP
            if ((x2 < 500+51 && x2 > 500 - 47) && (ypt + 52 >= 500 - 105 * kp2 && (ypt + 52 <= 507 - 105 * kp2)) && (h != 2)) {
                    h = 1;
                    sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                    sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                    sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                    sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                    sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                    sfSprite_setPosition(sprite5, (sfVector2f){xpt, y2 - 53});
                    }
        }

        if (x3 >= 551){
            if ((x3 <= 555 && x3 >= 551) && (ypt + 52 > 501 - 105 * kp3 && ypt <= 500) && h != 1) {
                h = 2;
                sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                sfSprite_setPosition(sprite5, (sfVector2f){x3 - 52, ypt});
                }
        }   else{
                if ((x3 < 500+51 && x3 > 500 - 47) && (ypt + 52 >= 500 - 105 * kp3 && (ypt + 52 <= 507 - 105 * kp3)) && (h != 2)) {
                    h = 1;
                    sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                    sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                    sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                    sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                    sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                    sfSprite_setPosition(sprite5, (sfVector2f){xpt, y3 - 53});
                    }
        }

        if (x5 >= 551){
            if ((x5 <= 555 && x5 >= 551) && (ypt + 52 > 501 - 105 * kp4 && ypt <= 500) && h != 1) {
                h = 2;
                sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                sfSprite_setPosition(sprite5, (sfVector2f){x5 - 52, ypt});
                }
        }   else{
                if ((x5 < 500+51 && x5 > 500 - 47) && (ypt + 52 >= 500 - 105 * kp4 && (ypt + 52 <= 507 - 105 * kp4)) && (h != 2)) {
                    h = 1;
                    sfSprite_setPosition(sprite6, (sfVector2f){x, y});
                    sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
                    sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
                    sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
                    sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
                    sfSprite_setPosition(sprite5, (sfVector2f){xpt, y5 - 53});
                }
        }


        //SCHETCHIK_COUNT
        if (x >= 433 && x <=435) {
            sch += 1;
        }

        if (x1 >= 433 && x1 <=435) {
            sch += 1;
        }

        if (x2 >= 433 && x2 <=435) {
            sch += 1;
        }

        if (x3 >= 433 && x3 <=435) {
            sch += 1;
        }

        if (x5 >= 433 && x5 <=435) {
            sch += 1;
        }

        //NEBO(UP_LINE)
        float test_y = sfSprite_getPosition(sprite5).y;

        if (test_y < -14) {
            sfSprite_setPosition(sprite5, (sfVector2f){xpt, 0});
            nebesnaya_kara = 1;
        }
        if (test_y < -15) {
            h = 3;
            sfSprite_setPosition(sprite6, (sfVector2f){x, y});
            sfSprite_setPosition(sprite7, (sfVector2f){x1, y1});
            sfSprite_setPosition(sprite8, (sfVector2f){x2, y2});
            sfSprite_setPosition(sprite9, (sfVector2f){x3, y3});
            sfSprite_setPosition(sprite10, (sfVector2f){x5, y5});
        }

        //SCHETCHIK_PRINT

        itoa(sch, scht);
        sfText_setColor(text, sfBlue);
        if (sch % 2 == 0)
            sfText_setColor(text, sfGreen);
        sfText_setString(text, scht);
        sfRenderWindow_display(window);
    }
    return 0;
}
