#include <allegro5/bitmap.h>

#include <alpp/Event/Mouse.h>
#include <alpp/Event/GameLoop.h>
#include <alpp/Event/Keyboard.h>
#include <alpp/Render/Camera.h>
#include <alpp/Render/WindowSettings.h>

#include <easylogging++.h>

#include <plh/Factory.h>
#include <plh/Threadmill.h>

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

        for (auto threadmill : m_Threadmills)
        {
            threadmill->render(Renderer);
        }

        ++currTick;

        return true;
    }

private:

    Factory m_Factory;
    std::list<sptr<Threadmill>> m_Threadmills;
};

class MyMouse : public event::Mouse
{
public:

    explicit MyMouse(sptr<render::Camera> io_Camera) : 
        Mouse(500),
        m_Camera(io_Camera) 
    {}

protected:

    void onScroll() override { LOG(INFO) << "onScroll"; };

    void onLeftClick() override { LOG(INFO) << "onLeftClick"; };
    void onRightClick() override { LOG(INFO) << "onRightClick"; };
    void onMiddleClick() override { LOG(INFO) << "onMiddleClick"; };
    void onOtherButtonClick(Button i_Button) override { LOG(INFO) << "onOtherButtonClick"; };

    void onLeftPressed() override { LOG(INFO) << "onLeftPressed"; };
    void onRightPressed() override { LOG(INFO) << "onRightPressed"; };
    void onMiddlePressed() override { LOG(INFO) << "onMiddlePressed"; };
    void onOtherButtonPressed(Button i_Button) override { LOG(INFO) << "onOtherButtonPressed"; };

    void onLeftReleased() override { LOG(INFO) << "onLeftReleased"; };
    void onRightReleased() override { LOG(INFO) << "onRightReleased"; };
    void onMiddleReleased() override { LOG(INFO) << "onMiddleReleased"; };
    void onOtherButtonReleased(Button i_Button) override { LOG(INFO) << "onOtherButtonReleased"; };

private:

    sptr<render::Camera> m_Camera;
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

    void onCharacterTyped(uint8_t i_Key) override
    {
        WorldCoords translation;

        switch (i_Key)
        {
        case ALLEGRO_KEY_LEFT : translation.x -= m_ScrollSpeed; break;
        case ALLEGRO_KEY_RIGHT: translation.x += m_ScrollSpeed; break;
        case ALLEGRO_KEY_UP   : translation.y -= m_ScrollSpeed; break;
        case ALLEGRO_KEY_DOWN : translation.y += m_ScrollSpeed; break;
        default:                                                break;
        }

        m_Camera->translate(translation);
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
    render::WindowSettings winSettings;
    winSettings.displayMode = render::DisplayMode::WINDOWED;
    winSettings.library     = render::GraphicsLibrary::OPEN_GL;
    winSettings.dimensions  = PixelDimensions(1200, 800);
    winSettings.isResizable = true;
    winSettings.title       = "Test";

    // Create game loop
    auto gameloop = std::make_shared<MyGameLoop>(winSettings);

    // Register custom mouse handler
    gameloop->registerAgent(std::make_shared<MyMouse>(gameloop->Renderer->Camera));

    // Register custom keyboard handler
    gameloop->registerAgent(std::make_shared<MyKeyboard>(gameloop->Renderer->Camera, 10));

    // Run game loop
    gameloop->run();
}