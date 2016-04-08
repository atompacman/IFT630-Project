#include <allegro5/bitmap.h>

#include <alpp/Event/Mouse.h>
#include <alpp/Event/GameLoop.h>
#include <alpp/Event/Keyboard.h>
#include <alpp/Render/Camera.h>
#include <alpp/Render/WindowSettings.h>

#include <easylogging++.h>

#include <plh/Factory.h>

using namespace alpp;

std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

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
    };

protected:

    bool tick() override
    {
        static long currTick = 0;

        // Draw factory
        m_Factory.render(Renderer);
        
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

        ++currTick;

        return true;
    }

private:

    Factory m_Factory;
};

class MyMouse : public event::Mouse
{
public:

    explicit MyMouse() : 
        Mouse(500) 
    {}

protected:

    void onScroll() override { LOG(INFO) << "onScroll"; };
};

class MyKeyboard : public event::Keyboard
{
public:

    explicit MyKeyboard(sptr<render::Camera> io_Camera, float i_ScrollSpeed) :
        Keyboard(),
        m_ScrollSpeed(i_ScrollSpeed),
        m_Camera     (io_Camera)
    {}

protected:

    bool onCharacterTyped(uint8_t i_Key) override
    {
        WorldCoords translation;

        switch (i_Key)
        {
        case ALLEGRO_KEY_LEFT   : translation.x -= m_ScrollSpeed; break;
        case ALLEGRO_KEY_RIGHT  : translation.x += m_ScrollSpeed; break;
        case ALLEGRO_KEY_UP     : translation.y -= m_ScrollSpeed; break;
        case ALLEGRO_KEY_DOWN   : translation.y += m_ScrollSpeed; break;
        case ALLEGRO_KEY_ESCAPE : return false;
        }

        m_Camera->translate(translation);
        return true;
    }

private:

    float                m_ScrollSpeed;
    sptr<render::Camera> m_Camera;
};

int main()
{
    // Initialize Allegro++ wrapper
    init(LOGGER_CONFIG_FILE);

    // Set window settings
    PixelDimensions initialWinDim(1200, 800);
    render::WindowSettings winSettings;
    winSettings.displayMode = render::DisplayMode::WINDOWED;
    winSettings.library     = render::GraphicsLibrary::OPEN_GL;
    winSettings.dimensions  = initialWinDim;
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create game loop
    auto gameloop = std::make_shared<MyGameLoop>(winSettings);

    // Center camera (temporary)
    gameloop->Renderer->Camera->translate(WorldCoords(initialWinDim) / 2.f);

    // Register custom mouse handler
    gameloop->registerAgent(std::make_shared<MyMouse>());

    // Register custom keyboard handler
    gameloop->registerAgent(std::make_shared<MyKeyboard>(gameloop->Renderer->Camera, 10));

    // Run game loop
    gameloop->run();
}