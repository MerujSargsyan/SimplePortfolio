#include <stdio.h>
#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

#define BOXSZ 500

int main(void) {
    int printed = 0;
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawRectangle((WIDTH - BOXSZ)/2, (HEIGHT - BOXSZ)/2, BOXSZ, BOXSZ, BLACK);
            Image img = LoadImage("GraphGeneratorImg.png");
            if(IsImageReady(img) && !printed)  {
                printf("Image loaded\n");
                printed = 1;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

