#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Audio.h>
#include <stdio.h>

void resetGame(sfVector2f* dinoPosition, sfVector2f* obstaclePosition, int* score, int* gameOver) {
  //  *dinoPosition = (sfVector2f){90, 240};
    *obstaclePosition = (sfVector2f){500, 253};
    *score = 0;
    *gameOver = 0;
}

int main() {
    sfRenderWindow* window;
    sfVideoMode mode = {500, 400, 32};
    window = sfRenderWindow_create(mode, "Dino Game", sfResize | sfClose, NULL);

    sfTexture* dinoTexture = sfTexture_createFromFile("dinoz.png", NULL);
    sfSprite* dinoSprite = sfSprite_create();
    sfSprite_setTexture(dinoSprite, dinoTexture, sfTrue);
    sfVector2f dinoPosition = {90, 240};
    sfSprite_setPosition(dinoSprite, dinoPosition);

    sfTexture* obstacleTexture = sfTexture_createFromFile("cactus.png", NULL);
    sfSprite* obstacleSprite = sfSprite_create();
    sfSprite_setTexture(obstacleSprite, obstacleTexture, sfTrue);
    sfVector2f obstaclePosition = {500, 253};

    sfTexture* backgroundTexture = sfTexture_createFromFile("back.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);

    sfClock* clock = sfClock_create();
    float jumpSpeed = 0;
    float gravity = 0.004f; // Сила гравитации
    int isJumping = 0;
    int score = 0;
    int max_score = 0;
    int gameOver = 0;
    char scoreText[20];
    char max_scoreText[20];

    sfFont* font = sfFont_createFromFile("impact2.ttf");
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 40);
    sfText_setFillColor(text, sfBlack);

    // Текст Game Over
    sfText* gameOverText = sfText_create();
    sfText_setFont(gameOverText, font);
    sfText_setCharacterSize(gameOverText, 50);
    sfText_setFillColor(gameOverText, sfRed);
    sfText_setString(gameOverText, "GAME OVER");

    // Текст Restart
    sfText* restartText = sfText_create();
    sfText_setFont(restartText, font);
    sfText_setCharacterSize(restartText, 30);
    sfText_setFillColor(restartText, sfRed);
    sfText_setString(restartText, "press Enter to restart");

    //Музыка
    sfMusic* music = sfMusic_createFromFile("music.ogg");
    sfMusic_setLoop(music, sfTrue);
    sfMusic_play(music);
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeySpace && !isJumping && !gameOver) {
                    jumpSpeed = -1;
                    isJumping = 1;
                }
                if (event.key.code == sfKeyEnter && gameOver) {
                    resetGame(&dinoPosition, &obstaclePosition, &score, &gameOver);
                }
            }
        }

        float deltaTime = sfTime_asSeconds(sfClock_restart(clock));

        if (!gameOver) {
            if (isJumping) {
                dinoPosition.y += jumpSpeed;
                jumpSpeed += gravity;
                if (dinoPosition.y >= 240) {
                    dinoPosition.y = 240;
                    isJumping = 0;
                    jumpSpeed = 0;
                }
                sfSprite_setPosition(dinoSprite, dinoPosition);
            }

            obstaclePosition.x -= 350 * deltaTime;
            if (obstaclePosition.x < -50) {
                obstaclePosition.x = 600;
                score++;
            }
            sfSprite_setPosition(obstacleSprite, obstaclePosition);

            sfFloatRect dinoBounds = sfSprite_getGlobalBounds(dinoSprite);
            sfFloatRect obstacleBounds = sfSprite_getGlobalBounds(obstacleSprite);
            if (sfFloatRect_intersects(&dinoBounds, &obstacleBounds, NULL)) {
                gameOver = 1;
            }

            sprintf(scoreText, "Score: %d", score);
            sfText_setString(text, scoreText);
        }
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawSprite(window, dinoSprite, NULL);
        sfRenderWindow_drawSprite(window, obstacleSprite, NULL);
        sfRenderWindow_drawText(window, text, NULL);

        if (gameOver) {
            sfText_setPosition(gameOverText, (sfVector2f){150, 150});
            sfRenderWindow_drawText(window, gameOverText, NULL);
            sfText_setPosition(restartText, (sfVector2f){150, 220});
            sfRenderWindow_drawText(window, restartText, NULL);
             if(score > max_score){
             max_score = score;
             }
            sprintf(max_scoreText, "Max score: %d", max_score);
            sfText_setString(text, max_scoreText);
        }

        sfRenderWindow_display(window);
    }

    // Очищаем ресурсы
    sfSprite_destroy(dinoSprite);
    sfTexture_destroy(dinoTexture);
    sfSprite_destroy(obstacleSprite);
    sfTexture_destroy(obstacleTexture);
    sfRenderWindow_destroy(window);
    sfMusic_destroy(music);
    sfClock_destroy(clock);
    sfFont_destroy(font);
    sfText_destroy(text);
    sfText_destroy(gameOverText);
    sfText_destroy(restartText);
//    sfText_destroy(max_scoreText);
    sfTexture_destroy(backgroundTexture);
    sfSprite_destroy(backgroundSprite);

    return 0;
}
