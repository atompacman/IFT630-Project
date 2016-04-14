#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>

#include <plh/Resource.h>

#include <algorithm>

void Resource::render(sptr<alpp::render::Renderer> i_Renderer, WorldCoords i_Pos) const
{
    render(i_Renderer, i_Pos, 0);
}

void BasicResource::render(sptr<alpp::render::Renderer> i_Renderer, 
                           WorldCoords                  i_Pos, 
                           uint8_t                      i_ScaleLvl) const
{
    auto radius = WORKSHOP_SIDE_SIZE * RESRC_PREV_PROPORTION * 0.5 * float(pow(0.5, i_ScaleLvl));

    if (m_RaffinementLvl == 0)
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledCircle>();
        cmd->CenterPos = i_Pos;
        cmd->Radius    = radius;
        cmd->Color     = getResourceColor(m_ColorID);
        i_Renderer->enqueueCommand(cmd);
    }
    else if (m_RaffinementLvl == 1)
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledTriangle>();
        cmd->Points[0] = i_Pos + WorldCoords(0,      -radius);
        cmd->Points[1] = i_Pos + WorldCoords(-radius, radius);
        cmd->Points[2] = i_Pos + WorldCoords( radius, radius);
        cmd->Color = getResourceColor(m_ColorID);
        i_Renderer->enqueueCommand(cmd);
    }
    else if (m_RaffinementLvl == 2)
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledRoundedRectangle>();
        cmd->UpperLeftPos  = i_Pos + WorldCoords(-radius, -radius);
        cmd->LowerRightPos = i_Pos + WorldCoords(radius, radius);
        cmd->Radius        = radius * 0.5;
        cmd->Color         = getResourceColor(m_ColorID);
        i_Renderer->enqueueCommand(cmd);
    }
    else
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledDiamond>();
        cmd->UpperLeftPos = i_Pos + WorldCoords(-radius, -radius);
        cmd->LowerRightPos = i_Pos + WorldCoords(radius, radius);
        cmd->Color = getResourceColor(m_ColorID);
        i_Renderer->enqueueCommand(cmd);
    }
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

    for (auto i = 0; i < std::min<>(m_RaffinementLvl, MAX_NUM_RAFFINEMENTS); ++i)
    {
        auto d = WORKSHOP_SIZE * RESRC_PREV_PROPORTION * 0.5f;
        d *= float(pow(0.5, i_ScaleLvl));
        d *= float(pow(ADDITIONAL_RECT_PROP, i));

        auto cmd = std::make_shared<alpp::render::DrawRectangle>();
        cmd->UpperLeftPos  = i_Pos - d;
        cmd->LowerRightPos = i_Pos + d;
        cmd->Color         = al_map_rgb(0, 0, 0);
        cmd->Thickness     = RECT_THICKNESS;
        i_Renderer->enqueueCommand(cmd);
    }
}