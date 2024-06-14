#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

#define BOXSZ 500
#define BOXOFFSET 50

int drawingIdx = 0;

typedef struct {
    Texture2D texture;
    Rectangle rect;
} ImageBlock;

Texture2D init_image(const char* imgsrc) {
    Image img = LoadImage(imgsrc);
    ImageResize(&img, BOXSZ - BOXOFFSET, BOXSZ - BOXOFFSET);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

void redraw(ImageBlock ib) {
    DrawRectangleRec(ib.rect, BLACK);
    DrawTexture(ib.texture, WIDTH/4 - BOXOFFSET/2, HEIGHT/4 - BOXOFFSET/2, WHITE);
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
           drawingIdx++;
           if(drawingIdx> 2) drawingIdx = 0;
        }
    } else {
        scale_rect(rect, 0);
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    Rectangle rect = {0,0,0,0};

    ImageBlock ib;
    ib.texture = init_image("lib/images/GraphGeneratorImg.png");
    ib.rect = rect;

    ImageBlock ib2;
    ib2.texture = init_image("lib/images/ClassicGenImg.png");
    ib2.rect = rect;

    ImageBlock ib3;
    ib3.texture = init_image("lib/images/MorseTranslatorImg.png");
    ib3.rect = rect;

    ImageBlock ibarr[] = {ib, ib2, ib3};
    int idx = 0;

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ImageBlock* current = ibarr + drawingIdx;
            ClearBackground(RAYWHITE);
            mouse_input(&(current->rect));
            redraw(*current);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

