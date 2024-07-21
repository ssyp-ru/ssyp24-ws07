
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int main() {
    // Размер кадра и скорость анимации
    const int RUN_WIDTH = 92;
    const int RUN_HEIGHT = 94;
    const int STOP_WIDTH = 92;
    const int STOP_HEIGHT = 94;
    const int OBSTACLE_WIDTH = 32; //37 or 42
    const int OBSTACLE_HEIGHT = 60; //70 or 80
    const float ANIMATION_SPEED = 0.1f;
    const int TOTAL_FRAMES = 2;
    const float OBSTACLE_SPEED = 500.0f;
    const int WINDOW_WIDTH = 700;
    const int WINDOW_HEIGHT = 350;
    const float JUMP_SPEED = 500.0f;
    const float GRAVITY = 1150.0f;

    // Создаем окно
    sfRenderWindow* window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    window = sfRenderWindow_create(mode, "Project", sfResize | sfClose, NULL);

    // Проверка успешного создания окна
    if (!window)
        return -1;

    // Загрузка текстуры для фона
    sfTexture* backgroundTexture = sfTexture_createFromFile("fon.png", NULL);
    if (!backgroundTexture) {
        sfRenderWindow_destroy(window);
        return -1;
    }

    // Создание спрайта для фона
    sfSprite* backgroundSprite = sfSprite_create();
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);

    // Загрузка текстуры для персонажа
    sfTexture* characterTexture = sfTexture_createFromFile("run.png", NULL);
    if (!characterTexture) {
        sfSprite_destroy(backgroundSprite);
        sfTexture_destroy(backgroundTexture);
        sfRenderWindow_destroy(window);
        return -1;
    }

    // Создание спрайта для персонажа
    sfSprite* characterSprite = sfSprite_create();
    sfSprite_setTexture(characterSprite, characterTexture, sfTrue);
    sfIntRect rect = {0, 0, RUN_WIDTH, RUN_HEIGHT};
    sfSprite_setTextureRect(characterSprite, rect);
    sfVector2f player_position = {200, 135}; //начальная позиция персонажа
    sfSprite_setPosition(characterSprite, player_position);

    // Загрузка текстуры для стопа
    sfTexture* stopTexture = sfTexture_createFromFile("stop.png", NULL);
    if (!stopTexture) {
        return -1;
    }

    // Загрузка текстуры для препятствий
    sfTexture* obstacleTexture = sfTexture_createFromFile("obstacle.png", NULL);
    if (!obstacleTexture) {
        sfSprite_destroy(characterSprite);
        sfTexture_destroy(characterTexture);
        sfSprite_destroy(backgroundSprite);
        sfTexture_destroy(backgroundTexture);
        sfRenderWindow_destroy(window);
        return -1;
    }

    // Создание спрайта для препятствий
    sfSprite* obstacleSprite = sfSprite_create();
    sfSprite_setTexture(obstacleSprite, obstacleTexture, sfTrue);
    sfVector2f obstacle_position = {WINDOW_WIDTH, 175}; // начальная позиция препятствия
    sfSprite_setPosition(obstacleSprite, obstacle_position);

    // Загрузка шрифта для текста
    sfFont* font = sfFont_createFromFile("text.ttf");
    if (!font) {
        sfSprite_destroy(obstacleSprite);
        sfTexture_destroy(obstacleTexture);
        sfSprite_destroy(characterSprite);
        sfTexture_destroy(characterTexture);
        sfSprite_destroy(backgroundSprite);
        sfTexture_destroy(backgroundTexture);
        sfRenderWindow_destroy(window);
        return -1;
    }

// Создание текста для сообщения о поражении
    sfText* gameOverText = sfText_create();
    sfText_setColor(gameOverText, sfColor_fromRGB(80, 80, 80));
    sfText_setFont(gameOverText, font);
    sfText_setString(gameOverText, "You lost! Press 'R', to restart");
    sfText_setCharacterSize(gameOverText, 15);
    sfFloatRect textRect = sfText_getLocalBounds(gameOverText);
    sfText_setPosition(gameOverText, (sfVector2f){100, 70});

    // Создание текста для счета
    int score = 0;
    sfText* scoreText = sfText_create();
    sfText_setFont(scoreText, font);
    sfText_setCharacterSize(scoreText, 24);
    sfText_setPosition(scoreText, (sfVector2f){0, 0});
    sfText_setColor(scoreText, sfColor_fromRGB(80, 80, 80));

    // Для анимации
    sfClock* clock = sfClock_create();
    float animation_timer = 0;
    int frame = 0;

    // Для генерации случайных позиций препятствий
    srand(time(NULL));

    // Для прыжка
    int isJumping = 0;
    float jumpVelocity = 0;
    int isGameOver = 0;

    //Для случайных интервалов времени
    sfClock* obstacleClock = sfClock_create();
    float obstacleSpawnTimer = 0;
    int nextObstacleSpawnTime = 1 + rand()%(3 - 1 + 1); // Случайное время от 1 до 3 секунд
    sfFloatRect player_bounds;
    sfFloatRect obstacle_bounds;
    // Основной игровой цикл
    while (sfRenderWindow_isOpen(window)) {
            // Рисуем фон
            sfRenderWindow_drawSprite(window, backgroundSprite, NULL);

            /*// Рисуем персонажа
            sfRenderWindow_drawSprite(window, characterSprite, NULL);

            // Рисуем препятствие
            sfRenderWindow_drawSprite(window, obstacleSprite, NULL);*/

            // Пишем счет
            sfRenderWindow_drawText(window, scoreText, NULL);

            // Выводим надпись при поражении
            if (isGameOver == 1) {
                sfRenderWindow_drawText(window, gameOverText, NULL);
            } else {

            // Рисуем персонажа
            sfRenderWindow_drawSprite(window, characterSprite, NULL);

            // Рисуем препятствие
            sfRenderWindow_drawSprite(window, obstacleSprite, NULL);
            sfSprite_setPosition(obstacleSprite, obstacle_position);

            }

            // Отображаем содержимое окна
            sfRenderWindow_display(window);
            // Обрабатываем события
            sfEvent event;
            while (sfRenderWindow_pollEvent(window, &event)) {
                if (event.type == sfEvtClosed)
                    sfRenderWindow_close(window);
                if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp && isJumping == 0 && isGameOver == 0) {
                    isJumping = 1;
                    jumpVelocity = -JUMP_SPEED;
                }
                if (event.type == sfEvtKeyPressed && event.key.code == sfKeyR && isGameOver == 1) {
                    // Очищаем окно
                    //sfRenderWindow_drawSprite(window, characterSprite, NULL);
                    //sfSprite* obstacleSprite = sfSprite_create();
                    //sfSprite_setTexture(obstacleSprite, obstacleTexture, sfTrue);
                    /*sfVector2f*/ obstacle_position = {WINDOW_WIDTH, 175}; //WINDOW_HEIGHT - OBSTACLE_HEIGHT}; // начальная позиция препятствия
                    sfSprite_setPosition(obstacleSprite, obstacle_position);//obstacle_position);

                    printf("gameover: %d\n",isGameOver);
                    //sfSprite* characterSprite = sfSprite_create();
                    //sfSprite_setTexture(characterSprite, characterTexture, sfTrue);
                    //sfIntRect rect = (sfIntRect){0, 0, RUN_WIDTH, RUN_HEIGHT};
                    //sfSprite_setTextureRect(characterSprite, rect);
                    //sfVector2f player_position = {200, 135};//WINDOW_HEIGHT - FRAME_HEIGHT}; //начальная позиция персонажа
                    //sfSprite_setPosition(characterSprite, player_position);
                    //obstacle_bounds = sfSprite_getGlobalBounds(obstacleSprite);
                    //player_bounds = sfSprite_getGlobalBounds(characterSprite);
                    score = 0;
                    isGameOver = 0;
                }
            }
        // Обновляем время
        float deltaTime = sfTime_asSeconds(sfClock_restart(clock));

        if (isGameOver == 0){
            // Обновляем позицию игрока
            if (isJumping) {
                player_position.y += jumpVelocity * deltaTime;
                jumpVelocity += GRAVITY * deltaTime;
                if (player_position.y >= 135){//WINDOW_HEIGHT - FRAME_HEIGHT) {
                    player_position.y = 135; //WINDOW_HEIGHT - FRAME_HEIGHT;
                    isJumping = 0;
                }
                sfSprite_setPosition(characterSprite, player_position);
            }

            // Обновляем позицию препятствия
            obstacle_position.x -= OBSTACLE_SPEED * deltaTime;
            if (obstacle_position.x < -RUN_WIDTH) {
                obstacle_position.x = WINDOW_WIDTH + rand() % WINDOW_WIDTH;
                nextObstacleSpawnTime = 1 + rand()%(3 - 1 + 1);
                if (!isJumping){
                    score++;
                }
            }
            sfSprite_setPosition(obstacleSprite, obstacle_position);

            char scoreStr[20];
            sprintf(scoreStr, "Score: %d", score);
            sfText_setString(scoreText, scoreStr);
            sfText_setPosition(scoreText, (sfVector2f){10, 10});

            // Анимация персонажа (без прыжка)
            if (!isJumping) {
                animation_timer += deltaTime;
                if (animation_timer >= ANIMATION_SPEED) {
                    animation_timer = 0;
                    frame = (frame + 1) % TOTAL_FRAMES;
                    rect.left = RUN_WIDTH * frame;
                    sfSprite_setTextureRect(characterSprite, rect);
                }
            }

            player_bounds = sfSprite_getGlobalBounds(characterSprite);
            obstacle_bounds = sfSprite_getGlobalBounds(obstacleSprite);

            // Проверка столкновения

            if (sfFloatRect_intersects(&player_bounds, &obstacle_bounds, NULL) && isGameOver == 0) {
                printf("intersects\n");
                printf("%f %f\n", sfSprite_getPosition(obstacleSprite).x, sfSprite_getPosition(obstacleSprite).y);
                //sfSprite_destroy(characterSprite);

                //sfSprite* stopSprite = sfSprite_create();
                //sfSprite_setTexture(stopSprite, stopTexture, sfTrue);
                //sfIntRect rect = {0, 0, STOP_WIDTH, STOP_HEIGHT};
                //sfSprite_setTextureRect(stopSprite, rect);
                //sfVector2f player_position = {200, 135};//WINDOW_HEIGHT - FRAME_HEIGHT};
                //sfSprite_setPosition(stopSprite, player_position);
                //sfSprite_setPosition(obstacleSprite,(sfVector2f){WINDOW_WIDTH,175});
                //obstacle_bounds = sfSprite_getGlobalBounds(obstacleSprite);
                //player_bounds=(sfFloatRect){0,0,0,0};
                //obstacle_bounds=(sfFloatRect){1,1,0,0};
                isGameOver = 1; // Выводим надпись
            }
        }
        // Очищаем окно
        sfRenderWindow_clear(window, sfBlack);

}
    // Освобождаем ресурсы
    sfText_destroy(scoreText);
    sfText_destroy(gameOverText);
    sfFont_destroy(font);
    /*sfClock_destroy(obstacleClock);
    sfClock_destroy(clock);*/
    sfSprite_destroy(obstacleSprite);
    sfTexture_destroy(obstacleTexture);
    sfSprite_destroy(characterSprite);
    sfTexture_destroy(characterTexture);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
    sfRenderWindow_destroy(window);
    return 0;
}
