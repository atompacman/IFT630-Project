#ifndef PLH_EVENT_GAME_LOOP
#define PLH_EVENT_GAME_LOOP

#include <alpp/Event/Gameloop.h>

#include <plh/Budget.h>
#include <plh/Factory.h>

#include <vector>

class UIElement;

// Represents the state of the game (only Idle and Creation for now)
enum class GameState
{
    IDLE_MODE,
    CREATION_MODE
};

// Represents the actual game, or main game loop since the "tick" method is called each frame
class GameLoop : public alpp::event::GameLoop
{
public:

    explicit GameLoop(alpp::render::WindowSettings i_WinSettings);

    std::vector<UIElement*> getUI() const;

    // Create a factory object, based on the specified position and object type
    void CreateFactoryObject(CreatableObjectType i_ObjectType, WorkshopCoords i_ObjectPos);

    GameState getState() const               { return m_State; }
    void      setState(GameState i_NewState) { m_State = i_NewState; }

    CreatableObjectType getObjectTypeToCreate() const                     { return m_ObjectToCreate; }
    void              setObjectTypeToCreate(CreatableObjectType i_RoomType) { m_ObjectToCreate = i_RoomType; }

    WorldCoords getMouseHoverPosition() { return m_MouseHoverPixelPos; }
    void setMouseHoverPosition(WorldCoords pos) { m_MouseHoverPixelPos = pos; }

    // When in creation mode, we want to display the correct object to create, 
    // which is used to preview how it will be (output direction, etc.)
    void previewCreation();     

    Factory getFactory() { return m_Factory; }

    CardinalDir getCreationDir() { return m_CreationDir; }
    void setCreationDir(CardinalDir dir) { m_CreationDir = dir; }


protected:

    // main game loop method
    bool tick() override;

    void InitUI(alpp::render::WindowSettings i_WinSettings);    // Initial UI settings and creation
    void RenderUI();    // UI rendering
    void ResizeUI(PixelDimensions windowSize);  // UI resizing to adjust when changing window size

    // Sell all resources contained in stacks at the end of production lines
    void sellResources();

private:

    Factory                 m_Factory;  // The factory on which everything is placed
    Budget                  m_Budget; // Player's bank account
    std::vector<UIElement*> m_UI;       // main UI elements (creation menu, more could easily be added)
    GameState               m_State;    // state of the game (idle or creation)
    CreatableObjectType     m_ObjectToCreate;   // What type of object is currenlty selected to be created when in creation mode
    WorldCoords             m_MouseHoverPixelPos;   // position of the mouse when creating object, so we can preview it on the factory
    CardinalDir             m_CreationDir;  // cardinal direction used when creating a workshop (output stack) or a supplier (input stack)
};

#endif // PLH_EVENT_GAME_LOOP