
#include <iostream>

typedef struct {
    int x;
    int y;
} Point;

Point p = {
        .x = 10, 
        .y = 20
};

int main() {

    printf("Point coordinates: (%d, %d)\n", p.x, p.y);
    return 0;
}