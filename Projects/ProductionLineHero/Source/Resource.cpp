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
    for (auto i = 0; i < std::min<>(m_RaffinementLvl, MAX_NUM_RAFFINEMENTS); ++i)
    {
        auto delta = WORKSHOP_SIZE * RESRC_PREV_PROPORTION * 0.5f;
        delta     *= float(pow(0.5, i_ScaleLvl));
        delta     *= float(pow(ADDITIONAL_RECT_PROP, i));

        auto cmd = std::make_shared<alpp::render::DrawRectangle>();
        cmd->UpperLeftPos  = i_Pos - delta;
        cmd->LowerRightPos = i_Pos + delta;
        cmd->Color         = al_map_rgb(0, 0, 0);
        cmd->Thickness     = RECT_THICKNESS;
        i_Renderer->enqueueCommand(cmd);
    }
}

void BasicResource::render(sptr<alpp::render::Renderer> i_Renderer, 
                           WorldCoords                  i_Pos, 
                           uint8_t                      i_ScaleLvl) const
{
    auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
    cmd->CenterPos = i_Pos;
    cmd->Radius    = WORKSHOP_SIDE_SIZE * RESRC_PREV_PROPORTION * 0.5 * float(pow(0.5, i_ScaleLvl));
    cmd->Color     = getResourceColor(m_ColorID);
    i_Renderer->enqueueCommand(cmd);

    drawRaffinment(i_Renderer, i_Pos, i_ScaleLvl);
}

void CompositeResource::render(sptr<alpp::render::Renderer> i_Renderer, 
                               WorldCoords                  i_Pos, 
                               uint8_t                      i_ScaleLvl) const
{
    auto delta = WORKSHOP_SIDE_SIZE * RESRC_PREV_PROPORTION * 0.5f * pow(0.5, i_ScaleLvl + 1);
    if (m_SubResource[2])
    {
        m_SubResource[0]->render(i_Renderer, i_Pos + WorldCoords(-delta,  delta), i_ScaleLvl + 1);
        m_SubResource[1]->render(i_Renderer, i_Pos + WorldCoords( delta,  delta), i_ScaleLvl + 1);
        m_SubResource[2]->render(i_Renderer, i_Pos + WorldCoords(     0, -delta), i_ScaleLvl + 1);
    }
    else
    {
        m_SubResource[0]->render(i_Renderer, i_Pos + WorldCoords(-delta, 0), i_ScaleLvl + 1);
        m_SubResource[1]->render(i_Renderer, i_Pos + WorldCoords( delta, 0), i_ScaleLvl + 1);
    }

    drawRaffinment(i_Renderer, i_Pos, i_ScaleLvl);
}