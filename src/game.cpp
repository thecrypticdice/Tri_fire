
#include <iostream>
#include "raylib.h"
#include <math.h>
#include "player.h"
#include "crosshair.h"
#include "fire.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    bool game_over = false;
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
    SetTargetFPS(75);
fire_ctrl gun;
enemy_ctrl crowd;
crosshair x_crosshair;
x_crosshair.set_up_texture("./assets/xcrosshair.png");
player Player;
Player.set(screenWidth,screenHeight );
    while (!WindowShouldClose() & ! game_over)    // Detect window close button or ESC key
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
         gun.fire_a_bullet((GetRenderWidth()/2)-x_crosshair.x,(GetRenderHeight()/2)-x_crosshair.y );
         DrawText("fire!", 20, 80, 20, DARKGRAY);
        }

    float delta = GetFrameTime();
        BeginDrawing();
        // Draw model defining: position, size, rotation-axis, rotation (degrees), size, and tint-color

        gun.update(delta, crowd.enemies,sizeof(crowd.enemies)/sizeof(enemy));
        crowd.update(delta);
        //if (crowd.is_collides(1.1)){game_over = true;}
        ClearBackground({243, 247, 205});

        x_crosshair.update(delta,GetMousePosition().x , GetMousePosition().y);

        BeginMode3D(camera);
        //x_crosshair.draw_3d();
        Player.draw(x_crosshair.x,x_crosshair.y);
        gun.draw();
        crowd.draw();


        DrawGrid(100, 1.0f);

        EndMode3D();
        x_crosshair.draw();
        DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

        DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
