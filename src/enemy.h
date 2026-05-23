
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "utility.h"
class enemy{
public:
    float rad = 0.5;
    bool is_dead = true;
    int hp = 100;
    float pos_x;
    float pos_y;
    void update(float delta)
    {
        float l = dist_v2(pos_x,pos_y ,0 ,0 );
        pos_x += -pos_x*delta/l;
        pos_y += -pos_y*delta/l;
    }
   void  draw()
    {
        Vector3 Pos=(Vector3){pos_x,0.5,pos_y};
        DrawSphere(Pos, rad, RED);
    }
private:
};
class enemy_ctrl{
public:
    enemy enemies[16];
    void update(float delta)
    {
        s_timer -= delta;
        if (s_timer<0)
        {
            s_timer = re_time;
            add_enemy(spown_rad);
        }

        for(int i = 0;i<sizeof(enemies)/sizeof(enemy);i++)
        {
            enemies[i].update(delta);
        }

    }
    bool is_collides(float mergen = 0.1)
    {
        bool c = false;
        for (int i = 0;i<sizeof(enemies)/sizeof(enemy) ;i++ ) {
        if (dist_v2(enemies[i].pos_x,enemies[i].pos_y ,0 , 0) <mergen)
        {
            c = true;
            enemies[i].is_dead = true;
        }
    }
    return c;
    }
    void draw()
    {
        for (enemy i  : enemies ) {
            if (!i.is_dead)
            {
                i.draw();
            }

    }
    }
    void set_timer_wait_time(float neo_time) {re_time = neo_time;}
    void set_spown_rad(int neo_rad){spown_rad=neo_rad;}
private:
    int spown_rad = 20;
    float s_timer = 0;
    float re_time = 0.3;

    void add_enemy(int spown_rad)
    {
        for ( int i =0; i <sizeof( enemies)/sizeof(enemy);i++ ) {
        if (enemies[i].is_dead) {
            enemies[i].pos_x = rand_range(-spown_rad,spown_rad);
            enemies[i].pos_y =  rand_range(0,1) ? sqrt(pow(spown_rad,2)-pow(enemies[i].pos_x,2)) :  - sqrt(pow(spown_rad,2)-pow(enemies[i].pos_x,2));
            enemies[i].is_dead = false;
            break;
}
    }

    }
    void crowd_health()
    {
        for ( int i = 0;i<sizeof(enemies)/sizeof(enemy);i++ ) {
            if (enemies[i].hp<=0){
                enemies[i].is_dead = true;
            }}
    }
    void timer(float delta)
    {
        s_timer -=delta;
        if (s_timer<=0)
        {
            s_timer = re_time;
            add_enemy(spown_rad);
        }
    }
};
