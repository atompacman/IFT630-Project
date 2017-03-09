#include <plh/BudgetTab.h>

void BudgetTab::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
        cmd->UpperLeftPos  = i_Renderer->windowSize() - BUDGET_TAB_SIZE;
        cmd->LowerRightPos = i_Renderer->windowSize();
        cmd->Color         = m_Color;
        cmd->Layer         = alpp::render::Layer::UI;
        i_Renderer->enqueueCommand(cmd);
    }{
        auto cmd = std::make_shared<alpp::render::DrawCenteredText>();
        cmd->CenterPos = i_Renderer->windowSize() - BUDGET_TAB_SIZE / uint16_t(2);
        cmd->Font      = i_Renderer->StandardFont;
        cmd->Color     = al_map_rgb(255, 255, 255);
        cmd->Text      = std::to_string(m_Budget.balance());
        cmd->Layer     = alpp::render::Layer::UI;
        i_Renderer->enqueueCommand(cmd);
    }
}