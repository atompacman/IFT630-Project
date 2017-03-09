#ifndef PLH_WORKER
#define PLH_WORKER

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>

#include <plh/Resource.h>

#include <list>

class Workshop;

/*================================================================================================\\
| Autonomous entity running on its own thread that manipulates resources in the stacks of a workshop
|--------------------------------------------------------------------------------------------------|
| In the constructor, a thread is started where the worker continuously queries its workshop for
| resources in stacks, transport them and manipulate them.
\=================================================================================================*/

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