#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

#define BOXSZ 500
#define BOXOFFSET 50

Texture2D init_image(const char* imgsrc) {
    Image img = LoadImage(imgsrc);
    ImageResize(&img, BOXSZ - BOXOFFSET, BOXSZ - BOXOFFSET);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

void redraw(Texture2D texture, Rectangle rect) {
    DrawRectangleRec(rect, BLACK);
    //DrawTexture(texture, rect.x + BOXOFFSET/2, rect.y + BOXOFFSET/2, WHITE);
    DrawTexture(texture, WIDTH/4 - BOXOFFSET/2, HEIGHT/4 - BOXOFFSET/2, WHITE);
}

// polarity used to scale and descale
void scale_rect(Rectangle* rect, int should_scale) {
    if(should_scale) {
        rect->x = (WIDTH - BOXSZ - BOXOFFSET)/2;
        rect->y = (WIDTH - BOXSZ - BOXOFFSET)/2;
        rect->width = BOXSZ +  BOXOFFSET;
        rect->height = BOXSZ + BOXOFFSET;
    } else {
        rect->x = (WIDTH - BOXSZ)/2;
        rect->y = (WIDTH - BOXSZ)/2;
        rect->width = BOXSZ;
        rect->height = BOXSZ;
    }
}

void mouse_input(Rectangle* rect) {
    Vector2 mouse_pos = GetMousePosition();
    if(CheckCollisionPointRec(mouse_pos, *rect)) {
        scale_rect(rect, 1);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("Clicked\n");
        }
    } else {
        scale_rect(rect, 0);
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    Texture texture = init_image("lib/images/GraphGeneratorImg.png");
    // base rectangle
    Rectangle base_rect = {0,0,0,0};

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            redraw(texture, base_rect);
            mouse_input(&base_rect);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

