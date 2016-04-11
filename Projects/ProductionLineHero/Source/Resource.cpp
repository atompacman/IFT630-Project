#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>

#include <plh/Resource.h>

#include <algorithm>

void Resource::render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos) const
{
    render(i_Renderer, i_Pos, 0);
}

void Resource::drawRaffinment(sptr<alpp::render::Renderer> i_Renderer, 
                              WorldCoords                  i_Pos, 
                              uint8_t                      i_ScaleLvl) const
{
    if (m_RaffinementLvl == 0)
    {
        return;
    }

    auto colorID = std::min<>(static_cast<size_t>(m_RaffinementLvl), 
                              RAFFINEMENT_COLORS.size() / 3 - 1);

    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    auto delta = 5 * 10 * std::pow(0.5, i_ScaleLvl);
    cmd->UpperLeftPos  = i_Pos - WorldCoords(delta, delta);
    cmd->LowerRightPos = i_Pos + WorldCoords(delta, delta);
    cmd->Color         = getRaffinementColor(static_cast<uint8_t>(colorID));
    i_Renderer->enqueueCommand(cmd);
}

void BasicResource::render(sptr<alpp::render::Renderer> i_Renderer, 
                           WorldCoords                  i_Pos, 
                           uint8_t                      i_ScaleLvl) const
{
    drawRaffinment(i_Renderer, i_Pos, i_ScaleLvl);

    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPos = i_Pos;
    cmd->Radius    = 5 *   10 * std::pow(0.5, i_ScaleLvl);
    cmd->Color     = getResourceColor(m_ColorID);
    i_Renderer->enqueueCommand(cmd);
}

void CompositeResource::render(sptr<alpp::render::Renderer> i_Renderer, 
                               WorldCoords                  i_Pos, 
                               uint8_t                      i_ScaleLvl) const
{
    drawRaffinment(i_Renderer, i_Pos, i_ScaleLvl);

    ++i_ScaleLvl;
    auto delta = 5 *   8 * pow(0.5, i_ScaleLvl);
    if (m_SubResource[2])
    {
        m_SubResource[0]->render(i_Renderer, i_Pos + WorldCoords(-delta,  delta), i_ScaleLvl);
        m_SubResource[1]->render(i_Renderer, i_Pos + WorldCoords( delta,  delta), i_ScaleLvl);
        m_SubResource[2]->render(i_Renderer, i_Pos + WorldCoords(     0, -delta), i_ScaleLvl);
    }
    else
    {
        m_SubResource[0]->render(i_Renderer, i_Pos + WorldCoords(-delta, 0), i_ScaleLvl);
        m_SubResource[1]->render(i_Renderer, i_Pos + WorldCoords( delta, 0), i_ScaleLvl);
    }
}