
class timer
{
    public:
    void set_wait_time(float time)
    {
        m_wait = time;
    }
    void reset_time()
    {
        m_time = 0;
    }
    bool is_over_time()
    {
        return m_wait>m_time;
    }
    bool is_over_time_and_reset()
    {
        if (m_wait>m_time) 
        {
            m_time = 0;
            return true;
        }
        else 
        {
            return false;
        }
    }
    void update(float delta)
    {
        m_time += delta;
    }
    private:
    float m_wait = 5;
    float m_time = 0;
};