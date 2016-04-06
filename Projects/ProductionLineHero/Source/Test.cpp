#include <allegro5/bitmap.h>

#include <alpp/Event/Mouse.h>
#include <alpp/Event/GameLoop.h>
#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>
#include <alpp/Render/WindowSettings.h>

#include <plh/Factory.h>
#include <plh/Threadmill.h>

using namespace alpp;

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

WorldCoords objPos;

class MyMouse : public event::Mouse
{
protected:

    void onMouseMoved() override
    {
        objPos = m_Pos;
    }

    void onButtonPressed(uint8_t i_Button) override
    {

    }

    void onButtonReleased(uint8_t i_Button) override
    {

    }
};

class MyGameLoop : public event::GameLoop
{
public:

    explicit MyGameLoop(render::WindowSettings i_WinSettings) :
        GameLoop(i_WinSettings, TARGET_FPS),
        m_Factory()
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            auto workshop = m_Factory.buildWorkshop(WorkshopCoords(i + 1, 1), CardinalDir::EAST);
            workshop->addInputStack(CardinalDir::WEST);
            for (uint8_t j = 0; j < 5; ++j)
            {
                workshop->addWorker(0.7 + j * 0.1);
            }
        }

        for (uint8_t i = 0; i < 2; ++i)
        {
            auto src  = m_Factory.getWorkshop(WorkshopCoords(i + 1, 1));
            auto dest = m_Factory.getWorkshop(WorkshopCoords(i + 2, 1));
            auto threadmill = std::make_shared<Threadmill>(src->getStack(CardinalDir::EAST),
                                                           dest->getStack(CardinalDir::WEST));
            m_Threadmills.push_back(threadmill);
        }
    };

protected:

    bool tick() override
    {
        static long currTick = 0;

         // Draw a circle at mouse position
        auto cmd = std::make_shared<render::DrawFilledCircle>();
        cmd->CenterPos = objPos;
        cmd->Radius    = 10;
        cmd->Color     = al_map_rgb(20, 20, 150);
        m_Renderer->enqueueCommand(cmd);

        // Draw factory
        m_Factory.render(m_Renderer);
        
        // Regularly add resource to input stack
        if (currTick % 120 == 0)
        {
            for (uint8_t i = 0; i < 3; ++i)
            {
                auto stack = m_Factory.getWorkshop(WorkshopCoords(i + 1, 1))->getStack(CardinalDir::WEST);
                for (uint8_t j = 0; j < 3; ++j)
                {
                    stack->push(Resource());
                }
            }
        }

        for (auto threadmill : m_Threadmills)
        {
            threadmill->render(m_Renderer);
        }

        ++currTick;

        return true;
    }

private:

    Factory m_Factory;
    std::list<sptr<Threadmill>> m_Threadmills;
};

int main()
{
    // Initialize Allegro++ wrapper
    init(LOGGER_CONFIG_FILE);

    // Set window settings
    render::WindowSettings winSettings;
    winSettings.displayMode = render::DisplayMode::WINDOWED;
    winSettings.library     = render::GraphicsLibrary::OPEN_GL;
    winSettings.dimensions  = PixelDimensions(1200, 800);
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create game loop
    auto gameLoop = std::make_shared<MyGameLoop>(winSettings);

    // Register custom mouse handler
    gameLoop->registerAgent(std::make_shared<MyMouse>());

    // Run game loop
    gameLoop->run();
}