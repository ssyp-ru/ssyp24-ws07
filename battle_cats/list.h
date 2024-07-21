#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <SFML/Graphics.h>
#include <stdint.h>

typedef struct unit{
    float move_spd;
    int dmg;
    int max_health;
    int health;
    int range;
    sfTexture* move_texture;
    sfTexture* attack_texture;
    sfSprite* sprite;
    sfVector2f spawn_point;
    sfVector2f unit_size;
    int frame_count;
    int i;
    char type;
    sfIntRect sfr;
    int move_imgs;
    int attack_imgs;
    int is_attacking;
    int atk_spd;
    int atk_frames;
    int frame_rate;
    int give_money;
    //sfIntRect*texture_rect;
    //unit_t*enemy;

}unit_t;

typedef struct list{
    unit_t*data;
    struct list*next;
}list_t;

list_t* create_head();

list_t* create_one_of_list(list_t* head,unit_t* a,list_t* next);

int list_len(list_t* head);

list_t* list_append(list_t* head,unit_t*data);

list_t* appstart(list_t*head,unit_t*data);

list_t* list_delete(list_t*head);

list_t* list_insert(list_t* head,uint32_t index,unit_t*data);

unit_t* list_index(list_t* head,uint32_t index);

list_t* list_pop(list_t* head,list_t*pop);


#endif // LIST_H_INCLUDED
