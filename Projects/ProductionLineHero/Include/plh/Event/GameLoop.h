#ifndef PLH_EVENT_GAME_LOOP
#define PLH_EVENT_GAME_LOOP

#include <alpp/Event/Gameloop.h>

#include <plh/Factory.h>
#include <vector>

class UIElement;

enum class GameState
{
    IDLE_MODE,
    CREATION_MODE
};

class GameLoop : public alpp::event::GameLoop
{
public:

    explicit GameLoop(alpp::render::WindowSettings i_WinSettings);
    std::vector<UIElement*> getUI();
    void CreateFactoryRoom(CreatableRoomType roomType, WorkshopCoords roomPos);
    GameState getState() { return m_State; }
    void setState(GameState newState) { m_State = newState; }
    CreatableRoomType getRoomTypeToCreate() { return m_RoomToCreate; }
    void setRoomTypeToCreate(CreatableRoomType roomType) { m_RoomToCreate = roomType; }

protected:

    bool tick() override;
    void InitUI(alpp::render::WindowSettings i_WinSettings);
    void RenderUI();
    void ResizeUI(PixelDimensions windowSize);

private:

    Factory m_Factory;
    std::vector<UIElement*> m_UI;
    GameState m_State;
    CreatableRoomType m_RoomToCreate;
};

#endif // PLH_EVENT_GAME_LOOP