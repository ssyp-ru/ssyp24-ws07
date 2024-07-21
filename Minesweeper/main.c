#include <SFML/Graphics.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.h>
#include <stdbool.h>

typedef struct{
    sfTexture* texture;
    sfSprite* sprite;
}graph_t;

typedef struct{
    uint8_t num;
    uint8_t view;
}cell_t;

void open_field(cell_t* ptr, uint8_t x, uint8_t y){
    cell_t (*field)[10] = (cell_t (*)[10])ptr;
    field[x][y].view = 1;
    if (field[x][y].num != 0)
        return;
    else    {
        if((x + 1) <= 9 && field[x + 1][y].view == 0)
            open_field(ptr, x + 1, y);
        if((x + 1) <= 9 && (y + 1) <= 9 && field[x + 1][y + 1].view == 0)
            open_field(ptr, x + 1, y + 1);
        if((y + 1) <= 9 && field[x][y + 1].view == 0)
            open_field(ptr, x, y + 1);
        if((x - 1) >= 0 && (y + 1) <= 9 && field[x - 1][y + 1].view == 0)
            open_field(ptr, x - 1, y + 1);
        if((x - 1) >= 0 && field[x - 1][y].view == 0)
            open_field(ptr, x - 1, y);
        if((x - 1) >= 0 && (y - 1) >= 0 && field[x - 1][y - 1].view == 0)
            open_field(ptr, x - 1, y - 1);
        if((y - 1) >= 0 && field[x][y - 1].view == 0)
            open_field(ptr, x, y - 1);
        if((x + 1) <= 9 && (y - 1) >= 0 && field[x +1][y - 1].view == 0)
            open_field(ptr, x + 1, y - 1);
    }
}

void init_field(cell_t* ptr){
    cell_t (*array)[10] = (cell_t (*)[10])ptr;
    for (uint8_t i = 0; i < 10; i++){
        for (uint8_t j = 0; j < 10; j++){
            array[i][j].num = 0;
            array[i][j].view = 0;
            }
        }

    for (int i = 0; i < 10; i++){
        int j = rand() % 10;
        int k = rand() % 10;
        if (array[j][k].num != 9)
            array[j][k].num = 9;
        else
            i--;
    }

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(array[i][j].num != 9){
                uint8_t bomb = 0;
                if((i + 1) <= 9 && array[i + 1][j].num == 9)
                    bomb++;
                if((i + 1) <= 9 && (j + 1) <= 9 && array[i + 1][j + 1].num == 9)
                    bomb++;
                if((j + 1) <= 9 && array[i][j + 1].num == 9)
                    bomb++;
                if((i - 1) >= 0 && (j + 1) <= 9 && array[i - 1][j + 1].num == 9)
                    bomb++;
                if((i - 1) >= 0 && array[i - 1][j].num == 9)
                    bomb++;
                if((i - 1) >= 0 && (j - 1) >= 0 && array[i - 1][j - 1].num == 9)
                    bomb++;
                if((j - 1) >= 0 && array[i][j - 1].num == 9)
                    bomb++;
                if((i + 1) <= 9 && (j - 1) >= 0 && array[i +1][j - 1].num == 9)
                    bomb++;
                array[i][j].num = bomb;
            }
}

int get_closed(cell_t* ptr){
    cell_t (*array)[10] = (cell_t (*)[10])ptr;
    int count = 0;
    for (uint8_t i = 0; i < 10; i++)
        for (uint8_t j = 0; j < 10; j++)
            if (array[i][j].view == 0 || array[i][j].view == 2)
                count++;
    return count;
}

int main()
{
    srand(time(NULL));
    uint8_t b = 0;
    char str[] = "Play!";
    char str1[] = "Retry?";
    char str2[] = "WIN!";
    cell_t array[10][10];
    init_field(array);
    graph_t graph[12];
    for (uint8_t i = 0; i < 12; i++){
        char buff[7] = "";
        sprintf(buff, "%d.jpg", i);
        sfIntRect tmp = {0, 0, 32, 32};
        graph[i].texture = sfTexture_createFromFile(buff, &tmp);
        if (!graph[i].texture)
            return EXIT_FAILURE;
        graph[i].sprite = sfSprite_create();
        sfSprite_setTexture(graph[i].sprite, graph[i].texture, sfFalse);
    }
    sfIntRect rect = {0, 0, 1600,887 };
    sfTexture* menu = sfTexture_createFromFile("MAIN.jpg", &rect);
    sfSprite* menu_sprite = sfSprite_create();
    sfSprite_setScale(menu_sprite, (sfVector2f){0.37, 0.37});
    sfSprite_setTexture(menu_sprite, menu, sfFalse);
    sfSprite_setPosition(menu_sprite, (sfVector2f){-16, 0});
    sfFont* font = sfFont_createFromFile("Doom2016Left.ttf");
    sfText* text = sfText_create();
    sfText_setString(text, str);
    sfText_setCharacterSize(text, 96);
    sfText_setFont(text,font);
    sfText_setStyle(text, sfTextRegular);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, (sfVector2f){16,96});
    sfText* text1 = sfText_create();
    sfText_setString(text1, str1);
    sfText_setCharacterSize(text1, 96);
    sfText_setFont(text1,font);
    sfText_setStyle(text1, sfTextRegular);
    sfText_setColor(text1, sfBlack);
    sfText_setPosition(text1, (sfVector2f){64,96});
    sfText* text2 = sfText_create();
    sfText_setString(text2, str2);
    sfText_setCharacterSize(text2, 96);
    sfText_setFont(text2,font);
    sfText_setStyle(text2, sfTextRegular);
    sfText_setColor(text2, sfBlack);
    sfText_setPosition(text2, (sfVector2f){96,96});

    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){320, 320, 32}, "MINESWEEPER", sfDefaultStyle, NULL);
    sfMusic* Music = sfMusic_createFromFile("music.ogg");
    sfMusic_setVolume(Music, 25);
    if(!Music){
        return 1;
    }
    sfMusic_setLoop(Music, sfTrue);
    sfMusic_play(Music);
    uint8_t state = 1;
    while (sfRenderWindow_isOpen(window))
    {

        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtMouseButtonPressed && state == 0){
                if (event.mouseButton.button == sfMouseLeft){
                    uint8_t x = event.mouseButton.x / 32;
                    uint8_t y = event.mouseButton.y / 32;
                    if (array[x][y].view != 2){
                        array[x][y].view = 1;
                        if(array[x][y].num == 9){
                            state = 2;
                        } else {
                            open_field(array, x, y);
                            if (get_closed(array) == 10)
                                state = 3;
                        }
                    }
                }
                if(event.mouseButton.button == sfMouseRight && state == 0){
                    uint8_t x = event.mouseButton.x / 32;
                    uint8_t y = event.mouseButton.y / 32;
                    if (array[x][y].view == 0)
                        array[x][y].view = 2;
                    else if(array[x][y].view == 2)
                        array[x][y].view = 0;
                }
            }

            if (event.type == sfEvtKeyPressed){
                if (event.key.code == sfKeyEnter && state == 1)
                    state = 0;
                if (event.key.code == sfKeyEnter && state == 2){
                    init_field(array);
                    state = 0;
                }
                if (event.key.code == sfKeyEnter && state == 3){
                    init_field(array);
                    state = 0;
                }
            }
        }
        sfRenderWindow_clear(window, sfCyan);
        if (state == 1){
            {
                    sfRenderWindow_drawSprite(window,menu_sprite,  NULL);
                    sfRenderWindow_drawText(window, text, NULL);
            }
        }   else    {
            for (uint8_t i = 0; i < 10; i++){
                for (uint8_t j = 0; j < 10; j++){
                    if (array[i][j].view == 1){
                        sfSprite_setPosition(graph[array[i][j].num].sprite, (sfVector2f){32.0 * i, 32.0 * j});
                        sfRenderWindow_drawSprite(window, graph[array[i][j].num].sprite, NULL);
                    }   else if (array[i][j].view == 2){
                        sfSprite_setPosition(graph[11].sprite, (sfVector2f){32.0 * i, 32.0 * j});
                        sfRenderWindow_drawSprite(window, graph[11].sprite, NULL);
                    }   else    {
                        sfSprite_setPosition(graph[10].sprite, (sfVector2f){32.0 * i, 32.0 * j});
                        sfRenderWindow_drawSprite(window, graph[10].sprite, NULL);
                    }
                }
                if (state == 2)
                    sfRenderWindow_drawText(window, text1, NULL);
                if (state == 3)
                    sfRenderWindow_drawText(window, text2, NULL);
            }
        }
        sfRenderWindow_display(window);
    }
    sfMusic_destroy(Music);
    return EXIT_SUCCESS;
}
