#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <time.h>
#include <string.h>

unit_t* create_unit(float move_spd,int dmg,int max_health,int range,char type,int move_imgs,int attack_imgs,int atk_spd,int frame_rate,sfTexture*move_texture,sfTexture*attack_texture,sfVector2f spawn_point,sfVector2f unit_size,sfIntRect sfr){
    unit_t*unit = (unit_t*)malloc(sizeof(unit_t));
    unit->move_spd=move_spd;
    unit->dmg=dmg;
    unit->max_health=max_health;
    unit->health=unit->max_health;
    unit->range=range;
    unit->move_texture=move_texture;
    unit->attack_texture=attack_texture;
    unit->spawn_point=spawn_point;
    unit->unit_size=unit_size;
    unit->frame_count=0;
    unit->atk_spd=atk_spd;
    unit->type = type;
    unit->move_imgs=move_imgs;
    unit->attack_imgs=attack_imgs;
    unit->is_attacking=0;
    unit->i=0;
    unit->atk_frames=0;
    unit->frame_rate=frame_rate;
    unit->give_money=0;
    //unit->texture_rect=texture_rect;
    unit->sfr=sfr;
    unit->sprite = sfSprite_create();
    sfSprite_setTexture(unit->sprite,unit->move_texture,sfFalse);
    sfIntRect sfr_cat = (sfIntRect){0,0,unit->unit_size.x,unit->unit_size.y};
    sfSprite_setTextureRect(unit->sprite,sfr_cat);
    sfSprite_setPosition(unit->sprite,spawn_point);
    return unit;

}

list_t* die(list_t*unit,list_t*head,sfTexture*soul,sfTexture*base,sfText*base_text){
    if (unit->data->health <= 0){
        if (unit->data->move_texture == base){
            sfText_setString(base_text,"0");
        }
        sfSprite_destroy(unit->data->sprite);
        head = list_pop(head,unit);
    }
    return head;
}

list_t* attack(list_t*head,sfTexture*soul,sfTexture*base,sfText*base_text){
    list_t*nearest=NULL;
    float nearest_dis = 10000000.0;
    list_t*last1 = head;
    list_t*last2 = head;
    for (int i = 0;i<list_len(head);i++){
        nearest = NULL;
        last2 = head;
        nearest_dis = 10000000.0;
        for (int k = 0;k<list_len(head);k++){
            if (last1 != last2){
                if (last1->data->type == 'c'){
                    if (last2->data->type == 'e'){
                        float distance = (sfSprite_getPosition(last1->data->sprite).x) - (sfSprite_getPosition(last2->data->sprite).x+last2->data->unit_size.x);
                        if (distance < nearest_dis){
                            nearest_dis = distance;
                            nearest = last2;
                        }

                    }
                }
                if (last2->data->type == 'c'){
                    if (last1->data->type == 'e'){
                        float distance = (sfSprite_getPosition(last2->data->sprite).x) - (sfSprite_getPosition(last1->data->sprite).x + last1->data->unit_size.x);
                        if (distance < nearest_dis){
                            nearest = last2;
                            nearest_dis = distance;

                        }

                    }
                }
            }
            last2 = last2->next;


        }
        if (nearest_dis <= last1->data->range){
            last1->data->is_attacking = 1;
            if (last1->data->atk_frames % (last1->data->frame_rate * last1->data->attack_imgs) == 0){
                nearest->data->health -= last1->data->dmg;
                if (nearest->data->health <= 0){
                    last1->data->give_money=1;
                }
                head = die(nearest,head,soul,base,base_text);
            }
            last1->data->atk_frames+=1;
            //printf("len(after dead): %d",list_len(head));
        }else{
            last1->data->is_attacking = 0;
            last1->data->atk_frames=0;
        }
        last1 = last1->next;
    }
    return head;
}

void move(int move_spd,sfSprite*sprite,unit_t*unit){
    int x = sfSprite_getPosition(sprite).x;
    if (unit->type == 'c'){
        sfSprite_setPosition(sprite,(sfVector2f){x-move_spd,sfSprite_getPosition(sprite).y});
    }
    else{
        sfSprite_setPosition(sprite,(sfVector2f){x+move_spd,sfSprite_getPosition(sprite).y});
    }

}

int check_for_enemies(list_t*head){
    int check=0;
    list_t*last=head;
    for (int i = 0;i<list_len(head);i++){
        if (last->data->type == 'e'){
            check = 1;
        }
        last=last->next;
    }
    return check;
}


void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* citoa(int num, char* str, int base)
{
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {

        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }



    str[i] = '\0';
    reverse(str, i);

    return str;
}

int count_cats(list_t*head,sfTexture*base){
    int count = 0;
    list_t*last=head;
    for (int i = 0;i < list_len(head);i++){
        if (last->data->type == 'c' && last->data->move_texture != base){
            count++;
        }
        last=last->next;
    }
    return count;
}




int main()
{

    list_t*head = create_head();
    // Create the main window
    sfRenderWindow*window = sfRenderWindow_create((sfVideoMode){900, 600,32}, "CSFMLwindow",sfDefaultStyle,NULL);

    // Load a sprite to display

    sfIntRect sfr_button = {0,0,147,114};
    sfTexture*texture_button = sfTexture_createFromFile("cow_icon.png",&sfr_button);
    sfSprite*button_sprite = sfSprite_create();
    sfSprite_setTexture(button_sprite,texture_button,sfFalse);

    sfIntRect sfr_button_cat = {0,0,147,114};
    sfTexture*texture_button_cat = sfTexture_createFromFile("cat_icon.png",&sfr_button_cat);
    sfSprite*button_cat_sprite = sfSprite_create();
    sfSprite_setTexture(button_cat_sprite,texture_button_cat,sfFalse);

    sfIntRect sfr_button_wall = {0,0,147,114};
    sfTexture*texture_button_wall = sfTexture_createFromFile("wall_icon.png",&sfr_button_wall);
    sfSprite*button_wall_sprite = sfSprite_create();
    sfSprite_setTexture(button_wall_sprite,texture_button_wall,sfFalse);

    sfIntRect sfr_base = {0,0,167,331};
    sfTexture*base = sfTexture_createFromFile("base.png",&sfr_base);
    //sfSprite*base_sprite = sfSprite_create();
    //sfSprite_setTexture(base_sprite,base,sfFalse);

    sfIntRect sfr_soul = {0,0,130,130};
    sfTexture*soul = sfTexture_createFromFile("die.png",&sfr_soul);

    sfIntRect sfr_snake = {0,0,322,132};
    sfTexture*texture_snake = sfTexture_createFromFile("snake.png",&sfr_snake);

    sfIntRect sfr_croco = {0,0,443,136};
    sfTexture*texture_croco = sfTexture_createFromFile("croco.png",&sfr_croco);

    sfIntRect sfr_wall = {0,0,790,288};
    sfTexture*texture_wall = sfTexture_createFromFile("wall_cat_real.png",&sfr_wall);

    sfIntRect sfr_worker = {0,0,196,122};
    sfTexture*worker_button = sfTexture_createFromFile("cat_worker.png",&sfr_worker);
    sfSprite*worker_sprite = sfSprite_create();
    sfSprite_setTexture(worker_sprite,worker_button,sfFalse);

    sfIntRect sfr_background = {0,0,700,512};
    sfTexture*texture_background = sfTexture_createFromFile("background.png",&sfr_background);
    sfSprite*background_sprite = sfSprite_create();
    sfSprite_setTexture(background_sprite,texture_background,sfFalse);
    sfSprite_setScale(background_sprite,(sfVector2f){1.28,1.28});

    sfIntRect sfr_cow = {0,0,442,138};
    sfTexture*texture_cow = sfTexture_createFromFile("cow.png",&sfr_cow);

    sfIntRect sfr_cat = {0,0,191,112};
    sfTexture*texture_cat = sfTexture_createFromFile("cat_real.png",&sfr_cat);

    sfIntRect sfr_doge = {0,0,215,116};
    sfTexture*texture_doge = sfTexture_createFromFile("doge.png",&sfr_doge);

    sfIntRect sfr_hippo = {0,0,449,211};
    sfTexture*texture_hippo = sfTexture_createFromFile("hippo.png",&sfr_hippo);

    sfIntRect sfr_big_doge = {0,0,860,464};
    sfTexture*texture_big_doge = sfTexture_createFromFile("doge-transformed.png",&sfr_big_doge);

    int frame_counter = 0;
    int wave_counter = 10;
    int boss_counter = 0;



    sfRenderWindow_setFramerateLimit(window, 60);
    sfMusic*music = sfMusic_createFromFile("aaa.ogg");

    sfMusic_play(music);



	// Start the game loop

    sfFont*font = sfFont_createFromFile("font.ttf");
    if (!font)
    return EXIT_FAILURE;

    sfFont*boss_font = sfFont_createFromFile("boss_font.ttf");
    if (!boss_font)
    return EXIT_FAILURE;
    int show_boss_text = 0;

    sfText*text = sfText_create();
    sfText_setString(text,"Money: ");
    sfText_setCharacterSize(text,35);
    sfText_setFont(text, font);
    sfText_setColor(text,sfBlack);

    unit_t* cat = NULL;
    unit_t* enemy = NULL;

    int frame_counter_for_money = 0;

    sfVector2i mp;

    sfSprite_setPosition(button_wall_sprite,(sfVector2f){720,450});
    sfSprite_setPosition(button_cat_sprite,(sfVector2f){300,450});
    sfSprite_setPosition(button_sprite,(sfVector2f){510,450});


    sfSprite_setPosition(worker_sprite,(sfVector2f){-30,488});

    sfFloatRect wall_rect = (sfFloatRect){720.0,450.0,147.0,114.0};
    //printf("Left: %f Top: %f Width: %f Height: %f\n",cow_rect.left,cow_rect.top,cow_rect.width,cow_rect.height);
    sfFloatRect cat_rect = (sfFloatRect){300.0,450.0,147.0,114.0};
    sfFloatRect cow_rect = (sfFloatRect){510.0,450.0,147.0,114.0};

    sfFloatRect worker_rect = (sfFloatRect){-30.0,488.0,196.0,122.0};

    int money = 4000;
    int money_speed = 100;
    int worker_upgrade_cost = 100;


    char score_char[5];
    sfText*counter_text = sfText_create();
    sfText_setString(counter_text,score_char);
    //sfText_setUnicodeString(counter_text,&score);
    sfText_setCharacterSize(counter_text,35);
    sfText_setFont(counter_text, font);
    sfText_setColor(counter_text,sfBlack);

    sfWindow* window_base = sfWindow_create((sfVideoMode){900, 600,32}, "window",sfDefaultStyle,NULL);
    sfWindow_setVisible(window_base,sfFalse);


    char cat_worker_char[5];
    sfText*cat_worker_text = sfText_create();
    sfText_setString(cat_worker_text,cat_worker_char);
    sfText_setCharacterSize(cat_worker_text,15);
    sfText_setFont(cat_worker_text, font);
    sfText_setStyle(cat_worker_text,sfTextBold);
    sfText_setColor(cat_worker_text,sfBlack);

    char base_health_char[6] = "2000";
    int base_health = 2000;
    sfText*base_text = sfText_create();
    sfText_setString(base_text,base_health_char);
    sfText_setCharacterSize(base_text,20);
    sfText_setFont(base_text, font);
    sfText_setStyle(base_text,sfTextBold);
    sfText_setColor(base_text,sfBlack);

    char wave_char[3] = "1";
    sfText*wave_counter_text = sfText_create();
    sfText_setString(wave_counter_text,wave_char);
    sfText_setCharacterSize(wave_counter_text,35);
    sfText_setFont(wave_counter_text, font);
    sfText_setStyle(wave_counter_text,sfTextBold);
    sfText_setColor(wave_counter_text,sfBlack);

    sfText*wave_text = sfText_create();
    sfText_setString(wave_text,"Wave: ");
    sfText_setCharacterSize(wave_text,35);
    sfText_setFont(wave_text, font);
    sfText_setStyle(wave_text,sfTextBold);
    sfText_setColor(wave_text,sfBlack);

    char limit_char[12] = "0";
    char limit_text_char[9] = "/50 cats";
    sfText*limit_text = sfText_create();
    sfText_setString(limit_text,limit_text_char);
    sfText_setCharacterSize(limit_text,35);
    sfText_setFont(limit_text, font);
    sfText_setStyle(limit_text,sfTextBold);
    sfText_setColor(limit_text,sfBlack);

    sfText*lost_text = sfText_create();
    sfText_setString(lost_text,"YOU LOST");
    sfText_setCharacterSize(lost_text,250);
    sfText_setFont(lost_text, boss_font);
    sfText_setStyle(lost_text,sfTextBold);
    sfText_setColor(lost_text,sfRed);

    sfText*restart_text = sfText_create();
    sfText_setString(restart_text,"Press 'E' to try again");
    sfText_setCharacterSize(restart_text,40);
    sfText_setFont(restart_text, font);
    sfText_setStyle(restart_text,sfTextBold);
    sfText_setColor(restart_text,sfBlack);

    sfText_setPosition(lost_text,(sfVector2f){110,70});
    sfText_setPosition(restart_text,(sfVector2f){250,350});

    sfText*boss_text = sfText_create();
    sfText_setString(boss_text,"BIG DOGE INCOMING");
    sfText_setCharacterSize(boss_text,75);
    sfText_setFont(boss_text, boss_font);
    sfText_setStyle(boss_text,sfTextBold);
    sfText_setColor(boss_text,sfRed);

    int enemies_spawned = 0;
    int lost = 0;

    cat = create_unit(0,0,1000,0,'c',1,1,0,1,base,base,(sfVector2f){733,110},(sfVector2f){167.0,331.0},sfr_base);
    head = list_append(head,cat);

    while (sfRenderWindow_isOpen(window))
    {
        // Process events
        sfEvent event;



        while (sfRenderWindow_pollEvent(window,&event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            //printf("mpx: %d; mpy: %d\n",mp.x,mp.y);

            if (sfKeyboard_isKeyPressed(sfKeyE) && lost == 1){
                //printf("new game");
                money = 300;
                head = list_delete(head);
                wave_counter = 1;
                cat = create_unit(0,0,1000,0,'c',1,1,0,1,base,base,(sfVector2f){733,110},(sfVector2f){167.0,331.0},sfr_base);
                head = list_append(head,cat);
                enemies_spawned = 0;
                boss_counter=0;
                money_speed=10;
                worker_upgrade_cost=100;
                lost = 0;
            }

            if (sfFloatRect_contains(&cow_rect,mp.x,mp.y)){
                if (event.type == sfEvtMouseButtonReleased &&  event.mouseButton.button == sfMouseLeft){
                    if (money >= 300 && count_cats(head,base) < 30){
                        cat = create_unit(4,5,100,20,'c',4,5,60,3,texture_cow,texture_cow,(sfVector2f){820,380},(sfVector2f){88,67},sfr_cow);
                        head = list_append(head,cat);
                        //printf("Len: %d\n",list_len(head));
                        money -= 300;
                    }

                }
            }
            if (sfFloatRect_contains(&wall_rect,mp.x,mp.y)){
                if (event.type == sfEvtMouseButtonReleased &&  event.mouseButton.button == sfMouseLeft){
                    if (money >= 500 && count_cats(head,base) < 30){
                        cat = create_unit(1,18,230,30,'c',5,4,60,12,texture_wall,texture_wall,(sfVector2f){820,330},(sfVector2f){158,144},sfr_wall);
                        head = list_append(head,cat);
                        //printf("Len: %d\n",list_len(head));
                        money -= 500;
                    }

                }
            }
            if (sfFloatRect_contains(&cat_rect,mp.x,mp.y)){
                if (event.type == sfEvtMouseButtonReleased &&  event.mouseButton.button == sfMouseLeft){
                    if (money >= 50 && count_cats(head,base) < 30){
                        cat = create_unit(1,4,30,20,'c',3,4,48,10,texture_cat,texture_cat,(sfVector2f){820,380},(sfVector2f){48,56},sfr_cat);
                        head = list_append(head,cat);
                        //printf("Len: %d\n",list_len(head));
                        money -= 50;
                    }

                }
            }
            if (sfFloatRect_contains(&worker_rect,mp.x,mp.y)){
                if (event.type == sfEvtMouseButtonReleased &&  event.mouseButton.button == sfMouseLeft){
                    if (money >= worker_upgrade_cost){
                        if (money_speed >= 4){
                            money_speed -= 2;
                            money -= worker_upgrade_cost;
                            worker_upgrade_cost += 150;
                        }

                    }

                }
            }

        }

        // Clear screen
        sfRenderWindow_clear(window,sfWhite);

        if (lost == 0){
            sfRenderWindow_drawSprite(window,background_sprite,NULL);
        mp = sfMouse_getPosition(window_base);
        sfWindow_setPosition(window_base,(sfVector2i){sfRenderWindow_getPosition(window).x,sfRenderWindow_getPosition(window).y});

        sfRenderWindow_drawSprite(window,button_sprite, NULL);
        sfRenderWindow_drawSprite(window,button_cat_sprite, NULL);
        sfRenderWindow_drawSprite(window,button_wall_sprite, NULL);

        list_t*last = head;
        for (int j = 0;j < list_len(head);j++){
            if (last->data != NULL && last->data->sprite != NULL){
                //printf("list[%d]: %d",j,last->data);
                sfRenderWindow_drawSprite(window,last->data->sprite,NULL);
                last=last->next;

        }
        }
        sfRenderWindow_drawSprite(window,worker_sprite, NULL);



        last = head;
        for(int j = 0;j < list_len(head);j++){
            if (last->data->frame_count % last->data->frame_rate == 0 && last->data->move_texture != base){
                if (last->data->is_attacking == 0){

                if (last->data->i == last->data->move_imgs){
                    last->data->i = 1;
                }
                last->data->sfr = (sfIntRect){last->data->unit_size.x*(last->data->i-1),0,last->data->unit_size.x,last->data->unit_size.y};
                //printf("%d %d %f %f\n",(last->data->i)-1,0,last->data->unit_size.x,last->data->unit_size.y);
                sfSprite_setTextureRect(last->data->sprite,last->data->sfr);

                    if (last->data->i < last->data->move_imgs){
                        last->data->i += 1;
                    }
                }
                else if (last->data->is_attacking == 1){

                if (last->data->i == last->data->attack_imgs){
                    last->data->i = 1;
                }
                last->data->sfr = (sfIntRect){last->data->unit_size.x*(last->data->i-1),last->data->unit_size.y,last->data->unit_size.x,last->data->unit_size.y};
                //printf("%f %f %f %f\n",last->data->unit_size.x*(last->data->i-1),last->data->unit_size.y,last->data->unit_size.x,last->data->unit_size.y);
                sfSprite_setTextureRect(last->data->sprite,last->data->sfr);

                    if (last->data->i < last->data->attack_imgs){
                        last->data->i += 1;
                    }
                }




        }
        last->data->frame_count += 1;

        last = last->next;
        }


        //wave_counter = wave(head,wave_counter,frame_counter,enemy,texture_doge,sfr_doge,texture_snake,sfr_snake,texture_croco,sfr_croco);
        //printf("counter: %d\n",frame_counter_for_money);
        srand(time(NULL));
        int r;
        int enemies = wave_counter/10;
        int wait = 180;
        if (frame_counter_for_money % wait == 0){
            //printf("enemies: %d",enemies);
            if (enemies_spawned < 3*(enemies+1)){
                //printf("spaaaaaaaawn\n");
                r = rand() % 3;
                //r = 1;
                //printf("random: %d\n",r);
                if (r == 0){
                    enemy = create_unit(1.2,5+(1*(wave_counter/3+1)),75+2*wave_counter,35,'e',3,4,48,13,texture_doge,texture_doge,(sfVector2f){0,380},(sfVector2f){53,58},sfr_doge);
                    head = list_append(head,enemy);
                    enemies_spawned += 1;
                }
                else if(r == 1){
                    enemy = create_unit(1,12+(1*(wave_counter/3+1)),40+2*wave_counter,20,'e',4,4,48,14,texture_snake,texture_snake,(sfVector2f){0,380},(sfVector2f){80.5,66.0},sfr_snake);
                    head = list_append(head,enemy);
                    enemies_spawned += 1;
                }
                else if(r == 2){
                    enemy = create_unit(1.5,7+(1*(wave_counter/3+1)),50+2*wave_counter,40,'e',5,5,60,10,texture_croco,texture_croco,(sfVector2f){0,380},(sfVector2f){88,68},sfr_croco);
                    head = list_append(head,enemy);
                    enemies_spawned += 1;
                }
            }

            if (enemies_spawned == 3*(enemies+1)){
                if (wave_counter % 5 == 0 && wave_counter % 10 != 0 && boss_counter == 0){
                    enemy = create_unit(1,12+1*(wave_counter),200+3*wave_counter,25,'e',4,3,60,15,texture_hippo,texture_hippo,(sfVector2f){0,330},(sfVector2f){112,106},sfr_hippo);
                    head = list_append(head,enemy);
                    boss_counter = 1;
                }
                if (wave_counter % 10 == 0 && boss_counter == 0){
                    show_boss_text = 1;
                    enemy = create_unit(1,25+1*(wave_counter),380+3*wave_counter,70,'e',3,4,60,12,texture_big_doge,texture_big_doge,(sfVector2f){0,230},(sfVector2f){215,232},sfr_big_doge);
                    head = list_append(head,enemy);
                    boss_counter = 1;
                }
                int c = check_for_enemies(head);
                if (c == 0){
                    if (wait >= 50){
                        wait -= 20;
                    }
                    //printf("new wave");
                    show_boss_text = 0;
                    wave_counter += 1;
                    enemies_spawned = 0;
                    boss_counter = 0;
                }

            }



        }

        last = head;
        for (int j = 0;j<list_len(head);j++){
            if (last->data->is_attacking==0){
                move(last->data->move_spd,last->data->sprite,last->data);
            }
            if(last->data->move_texture == base){
                base_health = last->data->health;
                //printf("Base health: %d",last->data->health);
            }
            if (last->data->give_money==1){
                money += 30;
                last->data->give_money=0;
            }
            if (sfSprite_getPosition(last->data->sprite).x <= 0){
                //printf("before delete: %d\n",list_len(head));

                //printf("after delete: %d\n",list_len(head));
                if (sfSprite_getTexture(last->data->sprite) != texture_wall && last->data->type != 'e'){
                    sfSprite_setPosition(last->data->sprite,(sfVector2f){820,380});
                }
                else if (sfSprite_getTexture(last->data->sprite) == texture_wall && last->data->type != 'e'){
                    sfSprite_setPosition(last->data->sprite,(sfVector2f){820,330});
                }

            }

            last=last->next;

        }

        if (frame_counter_for_money % money_speed == 0){
            money += 1;
        }


        frame_counter_for_money += 1;

        frame_counter += 1;

        citoa(base_health, base_health_char,10);
        //printf("baseText: %s\n",sfText_getString(base_text));
        if (!strcmp(sfText_getString(base_text), "0")){
            printf("yes");
            citoa(0, base_health_char,10);
            base_health = 0;
        }else{
            sfText_setString(base_text,base_health_char);
        }


        head = attack(head,soul,base,base_text);
        //sfSprite_setPosition(cat_sprite,(sfVector2f){0,110});

        //sfSprite_setScale(sprite, (sfVector2f){scale,scale});

        sfText_setPosition(text,(sfVector2f){1,7});
        citoa(money,score_char,10);
        sfText_setString(counter_text,score_char);
        //sfText_setUnicodeString(counter_text,&score);
        sfText_setPosition(counter_text,(sfVector2f){175,9});
        sfText_setPosition(cat_worker_text,(sfVector2f){35,582});
        sfText_setPosition(base_text,(sfVector2f){770,90});

        citoa(count_cats(head,base),limit_char,10);
        strcat(limit_char,"/30 cats");
        sfText_setString(limit_text,limit_char);

        sfText_setPosition(limit_text,(sfVector2f){650,10});

        sfText_setPosition(wave_text,(sfVector2f){380,50});
        sfText_setPosition(wave_counter_text,(sfVector2f){510,52});

        sfText_setPosition(boss_text,(sfVector2f){210,120});

        citoa(wave_counter, wave_char,10);
        sfText_setString(wave_counter_text,wave_char);

        citoa(worker_upgrade_cost,cat_worker_char,10);
        char dollar[2] = "$";
        //strcat(&dollar,&cat_worker_char);
        if (worker_upgrade_cost < 700){
            sfText_setString(cat_worker_text,cat_worker_char);
        }else{
            sfText_setString(cat_worker_text,"MAX");
        }

        if (show_boss_text == 1){
            sfRenderWindow_drawText(window,boss_text,NULL);
        }



        sfRenderWindow_drawText(window,text,NULL);
        sfRenderWindow_drawText(window,limit_text,NULL);
        sfRenderWindow_drawText(window,base_text,NULL);
        sfRenderWindow_drawText(window,wave_text,NULL);
        sfRenderWindow_drawText(window,wave_counter_text,NULL);
        sfRenderWindow_drawText(window,counter_text,NULL);
        sfRenderWindow_drawText(window,cat_worker_text,NULL);
        } else if (lost == 1){
            //sfRenderWindow_clear(window,sfWhite);
            sfText_setString(base_text,"1000");
            sfRenderWindow_drawSprite(window,background_sprite,NULL);
            sfRenderWindow_drawText(window,wave_text,NULL);
            sfRenderWindow_drawText(window,wave_counter_text,NULL);
            sfRenderWindow_drawText(window,lost_text,NULL);
            sfRenderWindow_drawText(window,restart_text,NULL);
        }

        if (base_health <= 0){
            //sfRenderWindow_close(window);
            //sfWindow_close(window_base);
            lost = 1;
        }

        //mp_x = sfMouse_getPosition(window).x;
        //mp_y = sfMouse_getPosition(window).y;

        // Update the window
        sfRenderWindow_display(window);
    }

    //sfSprite_destroy(sprite);
    //sfTexture_destroy(texture);
    list_delete(head);
    sfMusic_destroy(music);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
