
#include "utility.h"
#include <raymath.h>



class crosshair{
public:
    float x=0;float y = 0;
    float world_x = 0;float world_y = 0;
    int width = 40;
    int height = 40;
    float speed = 5;
    Color color = BLACK;
    float scale = 1.0;
    void update(float delta,float m_x,float m_y,Camera camera)
    {
        x +=  (m_x - x)*delta*speed;
        y +=  (m_y - y)*delta*speed;
        ray = GetScreenToWorldRay((Vector2){x, y}, camera);
        RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);
        if (groundHitInfo.hit)
        {
            world_x = groundHitInfo.point.x;
            world_y = groundHitInfo.point.z;
        }
    }
    void set_up_texture(const char* path)
    {
        HideCursor();
       crosshair_trxture = LoadTexture( path);
    }
    void draw_3d()
    {
        float correct = 100;//dist_v2(x,y , GetRenderWidth()/2, GetRenderHeight()/2);
        //static void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);

        //DrawCube(Vector3Normalize((Vector3){((GetRenderWidth()/2)-x),0,((GetRenderHeight()/2)-y)}), 0.2f, 0.01f, 0.2f, color);
        DrawCube({(x-(GetRenderWidth()/2))/correct,0,(y-(GetRenderHeight()/2))/correct}, 0.2f, 0.01f, 0.2f, color);
    }
    void draw()
    {
           //    void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
             //DrawTextureEx(crosshair_trxture, (Vector2){x,y}, 0, 0.3, color);  // Draw a Texture2D with extended parameters
            DrawText("×", x-17*scale, y-35*scale, 70*scale, color);
    }
private:
    Texture2D crosshair_trxture;
    Ray ray = { 0 };
    // Ground quad
    Vector3 g0 = (Vector3){ -500.0f, 0.0f, -500.0f };
    Vector3 g1 = (Vector3){ -500.0f, 0.0f,  500.0f };
    Vector3 g2 = (Vector3){  500.0f, 0.0f,  500.0f };
    Vector3 g3 = (Vector3){  500.0f, 0.0f, -500.0f };
};
