#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

#define BOXSZ 500

long get_file_size(FILE* f) {
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return file_size;
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    Image img = LoadImage("lib/images/GraphGeneratorImg.png"); 
    ImageResize(&img, BOXSZ - 50, BOXSZ - 50);

    Texture2D txture = LoadTextureFromImage(img);
    UnloadImage(img);

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            Rectangle rect = {(WIDTH - BOXSZ)/2, (HEIGHT - BOXSZ)/2, BOXSZ, BOXSZ};
            ClearBackground(RAYWHITE);
            DrawRectangleRec(rect, BLACK);
            DrawTexture(txture, rect.x + 25, rect.y + 25, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

