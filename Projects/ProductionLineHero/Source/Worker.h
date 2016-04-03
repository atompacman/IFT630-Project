#ifndef PLH_WORKER
#define PLH_WORKER

// alpp
#include <Core.h>
#include <Render/Renderer.h>

class Worker
{
public:

    explicit Worker(uint16_t i_PosX, uint16_t i_PosY, float i_Speed);
    ~Worker();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    static uint16_t const RADIUS = 10;

    void runWorkerThread();
    void work();

    uint16_t m_PosX;
    uint16_t m_PosY;
    float    m_Speed;

    // possible additions : color, texture
};

#endif // PLH_WORKER