#ifndef PLH_WORKER
#define PLH_WORKER

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>

#include <plh/Resource.h>

#include <list>

class Workshop;

// Represents a worker in a workshop
class Worker
{
public:

    explicit Worker(sptr<Workshop> i_Workshop, float i_Speed);
    ~Worker();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    void runWorkerThread();
    void walk(WorldCoords i_DestPos, WorldCoords i_Step);

    WorldCoords m_Pos;
    float       m_Speed;

    std::list<sptr<Resource>> m_ResourcesHeld;

    sptr<Workshop> m_Workshop;
};

#endif // PLH_WORKER