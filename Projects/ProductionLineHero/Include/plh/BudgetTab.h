#ifndef PLH_BUDGET_TAB
#define PLH_BUDGET_TAB

#include <plh/Budget.h>
#include <plh/UIElement.h>

class BudgetTab : public UIElement
{
public:

    explicit BudgetTab(WorldCoords i_Position, WorldCoords i_Size, ALLEGRO_COLOR i_Color, Budget const & i_Budget) :
        UIElement(i_Position, i_Size, i_Color),
        m_Budget(i_Budget)
    {}

    void render(sptr<alpp::render::Renderer> i_Renderer) const override;

private:
    
    Budget const & m_Budget;
};

#endif // PLH_BUDGET_TAB