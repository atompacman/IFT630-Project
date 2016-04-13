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

    std::vector<UIElement*> getUI() const;

    void CreateFactoryObject(CreatableObjectType i_RoomType, WorkshopCoords i_RoomPos);

    GameState getState() const               { return m_State; }
    void      setState(GameState i_NewState) { m_State = i_NewState; }

    CreatableObjectType getObjectTypeToCreate() const                     { return m_ObjectToCreate; }
    void              setObjectTypeToCreate(CreatableObjectType i_RoomType) { m_ObjectToCreate = i_RoomType; }

    WorldCoords getMouseHoverPosition() { return m_MouseHoverWorldPos; }
    void setMouseHoverPosition(WorldCoords pos) { m_MouseHoverWorldPos = pos; }

    void previewCreation();

    Factory getFactory() { return m_Factory; }


protected:

    bool tick() override;

    void InitUI(alpp::render::WindowSettings i_WinSettings);
    void RenderUI();
    void ResizeUI(PixelDimensions windowSize);

private:

    Factory                 m_Factory;
    std::vector<UIElement*> m_UI;
    GameState               m_State;
    CreatableObjectType     m_ObjectToCreate;
    WorldCoords             m_MouseHoverWorldPos;
};

#endif // PLH_EVENT_GAME_LOOP