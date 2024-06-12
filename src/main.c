#include <stdio.h>
#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

