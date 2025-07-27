#include "include.h"

#include "player.h"
#include "world.h"

int main() {


    InitWindow(800, 600, "My Game");
    SetTargetFPS(60);

    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 800.0f, 600.0f };
    camera.target = (Vector2){ 800.0f, 600.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Player player((Vector2){ 20.0f, 300.0f }, 200.0f);
    World world(12, 10);

    while (!WindowShouldClose()) {

        if (true)
        {
            /* code */
        }
        
        //logic+movement
        player.Update(camera, world);

        //rendering
        BeginDrawing();
        ClearBackground(BLUE);
        
        BeginMode2D(camera);
        DrawText("Hello, World!", 350, 280, 20, WHITE);
        
        world.Draw();
        player.Draw();
        
        DrawRectangle(1000, 0, 800, 600, Fade(BLACK, 0.5f)); // Example of drawing a rectangle
        
        EndMode2D();
        DrawText(TextFormat("%d", GetFPS()), 10, 10, 30, BLACK);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}