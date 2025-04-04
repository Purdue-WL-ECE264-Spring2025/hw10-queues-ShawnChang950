#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t serialized_state = serialize(state);
    insert_at_tail(&q->data, serialized_state);
}

struct game_state dequeue(struct queue *q) { 
    uint64_t serialized_state = remove_from_head(&q->data);
    return deserialize(serialized_state);


}

int number_of_moves(struct game_state start) { 
    struct queue qu = {NULL};
    enqueue(&qu, start); 
    while(qu.data.head != NULL){
        struct game_state state = dequeue(&qu);
        uint16_t prev = state.num_steps;

        int count = 1; //iter thru array
        int complete = 1;
        for(int i = 0; i< 4; i++){
            for(int j = 0; j < 4; j++ ){
                if(state.tiles[i][j] != count)
                {
                    complete = 0;
                }
                count++;
                count %= 16;
            }
        }

        if (complete)
        {
            free_list(qu.data); //complete return
            return state.num_steps;
        }

        struct game_state temp;

        temp = state;
        
        //MOVE UP
        move_up(&temp);
        if(temp.num_steps > prev)
        {
            enqueue(&qu, temp);
        }
        //MOVE DOWN
        temp = state;
        move_down(&temp);
        if(temp.num_steps > prev)
        {
            enqueue(&qu, temp);
        }
        //Move left
        temp = state;
        move_left(&temp);
        if(temp.num_steps > prev)
        {
            enqueue(&qu, temp);
        }

        //MOVE RIGHT
        temp = state;
        move_right(&temp);
        if(temp.num_steps > prev)
        {
            enqueue(&qu, temp);
        }
    }
    free_list(qu.data);
    return -1;
 }
