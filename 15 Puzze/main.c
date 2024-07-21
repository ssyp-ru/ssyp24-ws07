#include <SFML/Graphics.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
int value;
sfTexture* texture;
sfSprite* sprite;
} cell_t;

int main()
{
    srand(time(NULL));
    cell_t array [4] [4];
    int a;
    int b;
    int win = 0;
    for (a = 0; a < 4;a++){
        for (b = 0; b < 4;b++){
            array [a][b].value = 4 * a + b;
            char buff[7] = "";
            sprintf(buff, "%d.png", 4 * a + b);
            printf("%s ", buff);
            sfIntRect tmp = {0, 0, 146, 145};
            array [a][b].texture = sfTexture_createFromFile(buff, &tmp);
            printf("%d\n" ,array [a] [b].value);
            array [a][b].sprite = sfSprite_create();
            sfSprite_setTexture(array[a][b].sprite, array[a][b].texture, sfFalse);
        }
        printf("\n");
    }
    int inv;
    do{
        inv = 0;
        for(int e = 0; e < 16; e++){
            cell_t tmp = array [e/4][e%4];
            int f = rand()%16;
            array [e/4][e%4] = array [f/4][f%4];
            array [f/4][f%4] = tmp;
        }
        for (int i = 0; i < 16; i++)
            if (array[i/4][i%4].value)
                for (int j = 0; j < i; j++)
                    if (array[j/4][j%4].value > array[i/4][i%4].value)
                        inv++;
        for (int i = 0; i < 16; i++)
            if (array[i/4][i%4].value == 0)
                inv += 1 + i / 4;
        puts((inv & 1) ? "No solution" : "Solution exists");
    }while(inv & 1);

    char str[] = "Win!";
    sfFont* font = sfFont_createFromFile("pricedown.otf");
    sfText* text = sfText_create();
    sfText_setString(text, str);
    sfText_setCharacterSize(text, 120);
    sfText_setFont(text, font);
    sfText_setStyle(text, sfTextBold);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, (sfVector2f){200, 200});
    sfRenderWindow* window = sfRenderWindow_create((sfVideoMode){146 * 4, 145 * 4, 32}, "Pyatnashki", sfDefaultStyle, NULL);
    while (sfRenderWindow_isOpen(window))
    {

        // Process events
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed){
                if (win){
                    if (event.key.code == sfKeyR){
                        win = 0;
                        do{
                            inv = 0;
                            for(int e = 0; e < 16; e++){
                                cell_t tmp = array [e/4][e%4];
                                int f = rand()%16;
                                array [e/4][e%4] = array [f/4][f%4];
                                array [f/4][f%4] = tmp;
                            }
                            for (int i = 0; i < 16; i++)
                                if (array[i/4][i%4].value)
                            for (int j = 0; j < i; j++)
                                if (array[j/4][j%4].value > array[i/4][i%4].value)
                                    inv++;
                            for (int i = 0; i < 16; i++)
                                if (array[i/4][i%4].value == 0)
                                    inv += 1 + i / 4;
                            puts((inv & 1) ? "No solution" : "Solution exists");
                        }while(inv & 1);
                    }
                }   else    {
                    int x = 0, y = 0;
                    for (int i = 0; i < 4;i++)
                        for (int j = 0; j < 4;j++)
                            if (array[i][j].value == 0){
                                x = i;
                                y = j;
                            }
                    if (event.key.code == sfKeyUp){
                        if (y < 3){
                            cell_t tmp = array [x][y];
                            array [x][y] = array [x][y + 1];
                            array [x][y + 1] = tmp;
                        }
                    }
                    if (event.key.code == sfKeyDown){
                        if (y > 0){
                            cell_t tmp = array [x][y];
                            array [x][y] = array [x][y - 1];
                            array [x][y - 1] = tmp;
                        }
                    }
                    if (event.key.code == sfKeyLeft){
                        if (x < 3){
                            cell_t tmp = array [x][y];
                            array [x][y] = array [x + 1][y];
                            array [x + 1][y] = tmp;
                        }
                    }
                    if (event.key.code == sfKeyRight){
                        if (x > 0){
                            cell_t tmp = array [x][y];
                            array [x][y] = array [x - 1][y];
                            array [x - 1][y] = tmp;
                        }
                    }

                    int count = 0;
                    for (int j = 0; j < 4;j++){
                        for (int h = 0; h < 4;h++){
                            printf("%d|%d ", array [h][j].value, (4 * j + h + 1) % 16);
                            if (array [h][j].value == (4 * j + h + 1) % 16)
                                count++;
                        }
                        printf("\n");
                    }
                    printf("=====%d=====\n", count);
                    if (count == 16)
                        win = 1;
                        //sfRenderWindow_close(window);
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        // Draw the sprite
        for (int c = 0; c < 4;c++)
            for (int d = 0; d < 4;d++){
                sfSprite_setPosition(array[d][c].sprite, (sfVector2f){146.0 * d, 145.0 * c});
                sfRenderWindow_drawSprite(window, array[d][c].sprite, NULL);
                }
        if (win)
            sfRenderWindow_drawText(window, text, NULL);
        // Update the window
        sfRenderWindow_display(window);
    }

    return 0;
}
