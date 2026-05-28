#include "utility.h"
#include "enemy.h"
#include <string>
class fire{
    public:

        float rad = 0.112;
        bool is_fired = false;
        float speed = 6;
        float pos_x;
        float pos_y;
        float blind_pos_x;
        float blind_pos_y;
        void set_pos_n_dir(float pos_x,float pos_y,float target_x, float target_y)
        {
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->target_x = target_x;
            this->target_y = target_y;
        }
        void update(float delta)
        {
            dir_x = target_x - pos_x;
            dir_y = target_y - pos_y;
            float lenth = dist_v2(0,0 ,dir_x ,dir_y );
            dir_x = dir_x/lenth;
            dir_y = dir_y/lenth;
            blind_pos_x = pos_x;
            blind_pos_y = pos_y;
            pos_x -= dir_x*delta*speed;
            pos_y -=dir_y*delta*speed;
            blind_pos_x = (pos_x+blind_pos_x)/2;
            blind_pos_y = (pos_y+blind_pos_y)/2;
            if (dist_v2(0,0 ,pos_x ,pos_y )>50.0)
            {
                is_fired = false;
            }
        }
        void draw()
        {
          DrawSphere((Vector3){pos_x,0.5,pos_y}, rad, GOLD);

        }
    private:
        float target_x;
        float target_y;
        float dir_x;
        float dir_y;
};
class fire_ctrl{
    public:
        int score=0;
        void fire_a_bullet(float c_pos_x, float c_pos_y)
        {
            for (int i = 0;i<sizeof(m_bullets)/sizeof(fire) ;i++ )
            {
                if (!m_bullets[i].is_fired)
                {
                    m_bullets[i].is_fired = true;
                    m_bullets[i].set_pos_n_dir(0,0 , c_pos_x,c_pos_y );
                    break;
                }
            }
        }
        void update(float delta, enemy *crowd,int crowdSize)
        {
            for (int i = 0;i<sizeof(m_bullets)/sizeof(fire);i++)
            {
                if (m_bullets[i].is_fired)
                {
                    m_bullets[i].update(delta);
                    for (int n = 0; n<crowdSize;n++ )
                    {
                        if (!crowd[n].is_dead)
                        {
                        bool col = dist_v2(m_bullets[i].pos_x,m_bullets[i].pos_y ,crowd[n].pos_x,crowd[n].pos_y)<m_bullets[i].rad+crowd[n].rad;
                        bool blind_col = dist_v2(m_bullets[i].blind_pos_x,m_bullets[i].blind_pos_y ,crowd[n].pos_x,crowd[n].pos_y)<m_bullets[i].rad+crowd[n].rad;

                        if (col or blind_col)
                        {
                            DrawText( bool_to_string(col or blind_col), 40, 80, 20, DARKGRAY);
                            m_bullets[i].is_fired = false;
                            crowd[n].is_dead = true;
                            when_hit();
                        }
                        }
                    }
                    m_bullets[i].update(delta);
                }
            }

        }
        void draw()
        {
            for (int i = 0;i<sizeof(m_bullets)/sizeof(fire);i++)
            {
                if (m_bullets[i].is_fired)
                {
                    m_bullets[i].draw();
                }
            }
        }
    private:
        fire m_bullets[32];

        void when_hit()
        {
            score++;
        }
};
