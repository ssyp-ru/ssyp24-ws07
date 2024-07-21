#include <stdlib.h>
#include <stdint.h>
#include "list.h"


list_t* create_head(){
    //list_t*head = (list_t*)malloc(sizeof(list_t));
    return NULL;
}

list_t* create_one_of_list(list_t* head,unit_t* a,list_t* next){
    list_t*one_of = (list_t*)malloc(sizeof(list_t));
    one_of->data=a;
    one_of->next=next;
    return one_of;
}

int list_len(list_t* head){
    int len = 0;
    if (head != NULL){
        list_t*next_in_list = head;
        while(next_in_list != NULL){
            len++;
            next_in_list = next_in_list->next;
        }
        return len;
    }
    else{
        return len;
    }
}

list_t* list_append(list_t* head,unit_t*data){
    if (head == NULL){
        list_t* new = create_one_of_list(head,data,NULL);
        head = new;
    }
    else{
        list_t*last = head;
        for (int i = 1; i < list_len(head);i++){
            last = last->next;
        }
        list_t*new1 = create_one_of_list(head,data,NULL);
        last->next = new1;
    }
    return head;

}

list_t* appstart(list_t*head,unit_t*data){
    list_t*first = head;
    list_t*new_first = create_one_of_list(head,data,first);
    head = new_first;
    return head;
}

list_t* list_delete(list_t*head){
    list_t*last = head;
    int len = list_len(head);
    for (int i = 0; i < len;i++){
        list_t*next_last = last->next;
        free(last);
        last = next_last;
    }
    head = NULL;
    return head;
}

list_t* list_insert(list_t* head,uint32_t index,unit_t*data){
    if (head == NULL){
        list_t*new1 = create_one_of_list(head,data,NULL);
        head = new1;
    }else if(index == 0 && list_len(head) == 1){
        list_t*new_last = head->next;
        list_t*new1 = create_one_of_list(head,data,new_last);
        head = new1;
    }
    else{
        list_t*last = head;
        for (int i = 1; i < index;i++){
            last = last->next;
        }
        if (last->next != NULL){
            list_t*new_last = last->next;
            list_t*new1 = create_one_of_list(head,data,new_last);
            last->next = new1;
        }

    return head;

    }
}

unit_t* list_index(list_t* head,uint32_t index){
    list_t*last = head;
    for (int i = 1; i < list_len(head);i++){
        last = last->next;
    }
    return last->data;
}

list_t* list_pop(list_t* head,list_t*pop){
    list_t*last = head;
    list_t*before_last=NULL;
    if (last != NULL){
        for (int i = 0;i < list_len(head); i++){
            if (last == pop){
                if (i != 0){
                    before_last->next = last->next;
                } else{
                    head=last->next;
                }

                free(last);
                return head;
            }
            before_last=last;
            last = last->next;
        }

    }else if(last == NULL){
        unit_t* a = last->data;
        free(last);
        head = NULL;
        return head;
    }


}


