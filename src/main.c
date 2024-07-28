#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <raylib.h>

#define HEIGHT 800
#define WIDTH 800

#define BOXSZ 500
#define BOXOFFSET 50

#define MAX_PATH_SIZE 50

int drawingIdx = 0;

typedef struct {
    Texture2D texture;
    Rectangle rect;
    const char* jarname;
} ImageBlock;

Texture2D init_image(const char* imgsrc) {
    Image img = LoadImage(imgsrc);
    ImageResize(&img, BOXSZ - BOXOFFSET, BOXSZ - BOXOFFSET);

    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);
    return texture;
}

void execute_process(ImageBlock ib) {
    pid_t pid = fork();
    if(pid == 0) {
        char jarpath[MAX_PATH_SIZE] = "lib/executables/";
        strncat(jarpath, ib.jarname, strlen(ib.jarname));
        char* argv[] = {"java", "-jar", jarpath, NULL};
        execvp("java", argv);
    } else {
        wait(NULL);
    }
}

void redraw(ImageBlock ib) {
    DrawRectangleRec(ib.rect, BLACK);
    // magic numbers here
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

// this is my most confusing function, I would love some input
void mouse_input(ImageBlock* ib) {
    Rectangle* rect = &(ib->rect);
    Vector2 mouse_pos = GetMousePosition();
    if(CheckCollisionPointRec(mouse_pos, *rect)) {
        scale_rect(rect, 1);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
           execute_process(*ib);
        }
    } else {
        scale_rect(rect, 0);
    }
}

ImageBlock generate_image(const char* filename, const char* jarname) {
    Rectangle rect = {0,0,0,0};
    ImageBlock ib;
    ib.texture = init_image(filename);
    ib.rect = rect;
    ib.jarname = jarname;

    return ib;
}

void key_input() {
    if(IsKeyPressed(KEY_RIGHT)) {
        drawingIdx++;
    } else if(IsKeyPressed(KEY_LEFT)) {
        drawingIdx--;
    }
    if(drawingIdx > 3) drawingIdx = 0;
    if(drawingIdx < 0) drawingIdx = 2;
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello World");
    SetTargetFPS(30);

    ImageBlock ib = generate_image("lib/images/GraphGeneratorImg.png", "GraphGen.jar");
    ImageBlock ib2 = generate_image("lib/images/ClassicGenImg.png", "ClassicGen.jar");
    ImageBlock ib3 = generate_image("lib/images/MorseTranslatorImg.png", "MorseTranslator.jar");
    ImageBlock ib4 = generate_image("lib/images/GraphGeneratorImg.png", "CellularAutomata");

    ImageBlock ibarr[] = {ib, ib2, ib3, ib4};

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ImageBlock* current = ibarr + drawingIdx;
            ClearBackground(RAYWHITE);
            mouse_input(current);
            key_input();
            redraw(*current);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

