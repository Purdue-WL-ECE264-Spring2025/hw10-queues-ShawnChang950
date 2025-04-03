#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t serialized_state = serialize(state);
    insert_at_tail(&q->data, serialized_state);
}

struct game_state dequeue(struct queue *q) { 
    
    return (struct game_state){0};
    uint64_t serialized_state = remove_from_head(&q->data);
    return deserialize(serialized_state);


}

int number_of_moves(struct game_state start) { return start.num_steps; }
