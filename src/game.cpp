#include <iostream>
#include "raylib.h"
#include <math.h>
#include "player.h"
#include "crosshair.h"
#include "fire.h"
#include <string>
#include <format>



enum game_state
{
    start,
    playing,
    paused,
    game_over
};
game_state state = start;
int main(void)
{


    bool start_game = false;
    bool exit = false;
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "tri_fire_raylib");
    //MaximizeWindow();
    ToggleFullscreen();
    SetExitKey(KEY_F8);
    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    SetTargetFPS(120);
fire_ctrl gun;
enemy_ctrl crowd;
crosshair x_crosshair;
x_crosshair.set_up_texture("./assets/xcrosshair.png");
player Player;
Player.set(screenWidth,screenHeight );
    while (!WindowShouldClose() & ! exit)    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
    switch(state)
        {
        case playing:
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = paused;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
            gun.fire_a_bullet(-x_crosshair.world_x,-x_crosshair.world_y);
            DrawText("fire!", 20, 80, 20, DARKGRAY);
            }
            if (crowd.is_collides()) 
            {
            state = game_over;
            }
            
            BeginDrawing();
            // Draw model defining: position, size, rotation-axis, rotation (degrees), size, and tint-color

            gun.update(delta, crowd.enemies,sizeof(crowd.enemies)/sizeof(enemy));
            crowd.update(delta);
            
            ClearBackground({243, 247, 205});

            x_crosshair.update(delta,GetMousePosition().x , GetMousePosition().y,camera);

            BeginMode3D(camera);
            //x_crosshair.draw_3d();
            Player.draw(x_crosshair.x,x_crosshair.y);
            gun.draw();
            crowd.draw();


            DrawGrid(100, 1.0f);

            EndMode3D();
            x_crosshair.draw();
            DrawText(std::format("score: {}", gun.score).c_str(), 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);
            break;
        }
        case start:
        {
            ClearBackground({243, 247, 205});
            DrawText("press enter to start the game", GetRenderWidth()/2, GetRenderHeight()/2, 30, BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                state = playing;
            }

            break;
        }
        case game_over:
        {
            ClearBackground({243, 247, 205});
            DrawText(std::format("final score: {}", gun.score).c_str(), GetRenderWidth()/2, GetRenderHeight()/2, 30, BLACK);
            DrawText("press enter to restart the game", GetRenderWidth()/2, GetRenderHeight()/2 + 40, 30, BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                state = playing;
                gun.score = 0;
                for (auto i : crowd.enemies) 
                {
                    i.is_dead = true;
                }
            }
            if (IsKeyPressed(KEY_ESCAPE))
            {
                exit = true;
            }
            break;
        }
        case paused:
        {
            ClearBackground({243, 247, 205});
            DrawText("game paused", GetRenderWidth()/2, GetRenderHeight()/2, 30, BLACK);
            DrawText("press enter to resume the game", GetRenderWidth()/2, GetRenderHeight()/2 + 40, 30, BLACK);
            if (IsKeyPressed(KEY_ENTER) or IsKeyPressed(KEY_ESCAPE))
            {
                state = playing;
            }
            break;
        }
            
        }

        EndDrawing();

    }
    CloseWindow();

    return 0;
}
