

class player
{
public:
    Vector3 position = (Vector3){0,0,0.5};
    void set(int screenWidth,int screenHeight)
    {w=screenWidth;h=screenHeight;
         player.materials[0].maps[MATERIAL_MAP_ALBEDO].color = (Color){219, 219, 219,255};
    }
    void look_at(float x,float y)
    {
        pos_x=x;pos_y=y;
    }
    void draw(float x, float y)
    {
        pos_x = x;
        pos_y = y;
        w = GetRenderWidth();
        h = GetRenderHeight();
         DrawModelEx(player, (Vector3){ 0.0f, 0.5f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, -atan(((h/2)-pos_y)/((w/2)-pos_x))* (180.0 / M_PI), (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
       //DrawModelEx(player, (Vector3){ 0.0f, 0.0f, 0.5f }, (Vector3){ 0.0f, 1.0f, 0.0f }, -atan(((h/2)-GetMousePosition().y)/((w/2)-GetMousePosition().x))* (180.0 / M_PI), (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
    }
private:
    float pos_x,pos_y;
    int w,h;
    Model player = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));

};
