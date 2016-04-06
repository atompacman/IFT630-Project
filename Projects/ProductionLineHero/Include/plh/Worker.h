#ifndef PLH_WORKER
#define PLH_WORKER

#include <alpp/Core.h>
#include <alpp/Render/Renderer.h>

#include <plh/Common.h>
#include <plh/Resource.h>

#include <list>

class Workshop;

class Worker
{
public:

    explicit Worker(sptr<Workshop> i_Workshop, double i_Speed);
    ~Worker();

    void render(sptr<alpp::render::Renderer> i_Renderer) const;

private:

    void runWorkerThread();
    void walk(RealCoords i_DestPos, RealCoords i_Step);

    RealCoords m_Pos;
    double     m_Speed;

    std::list<Resource> m_ResourcesHeld;

    sptr<Workshop> m_Workshop;
};

#endif // PLH_WORKER