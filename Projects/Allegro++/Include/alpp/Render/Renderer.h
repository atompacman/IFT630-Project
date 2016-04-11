#ifndef ALPP_RENDER_RENDERER
#define ALPP_RENDER_RENDERER

#include <alpp/Core.h>
#include <alpp/Event/Agent.h>
#include <alpp/Render/Command.h>
#include <alpp/Render/WindowSettings.h>

#include <condition_variable>
#include <queue>

struct ALLEGRO_FONT;
struct ALLEGRO_TRANSFORM;

namespace alpp { namespace render {

class  Camera;

class Renderer : public event::Agent
{
public:

    explicit Renderer(WindowSettings i_WinSettings);
    ~Renderer();

    void enqueueCommand(sptr<Command> i_Cmd);
    void flip();

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

    PixelDimensions windowSize() const;

    sptr<Camera>   Camera;
    ALLEGRO_FONT * StandardFont;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    void createWindow(WindowSettings i_WinSettings);
    
    void runRenderThread(WindowSettings i_WinSettings);
    static void executeCommands(ALLEGRO_TRANSFORM * i_Transform, std::queue<sptr<Command>> & i_Queue);

    ALLEGRO_DISPLAY *         m_Window;
    bool                      m_CurrQueue;
    bool                      m_StopRenderThread;
    std::queue<sptr<Command>> m_CmdQueues[2 * static_cast<int>(Layer::MAX)];
    std::mutex                m_RenderThreadMutex;
    std::condition_variable   m_Flip;
    std::condition_variable   m_DrawingStarted;
};

}}

#endif // ALPP_RENDER_RENDERER 