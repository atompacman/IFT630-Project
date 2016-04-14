#include <alpp/Render/Command.h>
#include <alpp/Render/Renderer.h>

#include <plh/Factory.h>
#include <plh/Workshop.h>

Workshop::Workshop(WorkshopCoords i_Pos, CardinalDir i_OutputStackSide) :
    m_Pos            (i_Pos),
    m_ResourceStacks (),
    m_OutputStackSide(i_OutputStackSide),
    m_Workers        ()
{
    addStack(m_OutputStackSide, ResourceStack::Type::OUTPUT);
}

void Workshop::addWorker(double i_Speed)
{
    auto worker = std::make_shared<Worker>(shared_from_this(), i_Speed);
    m_Workers.emplace_back(worker);
}

void Workshop::moveOutputStack(CardinalDir i_Side)
{
    addStack(i_Side, ResourceStack::Type::OUTPUT);
    removeStack(m_OutputStackSide);
    m_OutputStackSide = i_Side;
}

sptr<ResourceStack> Workshop::addInputStack(CardinalDir i_Side)
{
    return addStack(i_Side, ResourceStack::Type::INPUT);
}

void Workshop::removeInputStack(CardinalDir i_Side)
{
    LOG_IF(i_Side == m_OutputStackSide, FATAL) << toString() << ": Cannot remove " 
        << nameOf(i_Side) << " input stack:  Stack is in reality the output stack";
    removeStack(i_Side);
}

bool Workshop::hasStack(CardinalDir i_Side) const
{
    return m_ResourceStacks[static_cast<uint32_t>(i_Side)] != nullptr;
}

std::list<sptr<ResourceStack>> Workshop::getInputStacks() const
{
    std::list<sptr<ResourceStack>> list;

    for (uint8_t i = 0; i < 4; ++i)
    {
        auto stack = m_ResourceStacks[i];
        if (stack && stack->type() == ResourceStack::Type::INPUT)
        {
            list.push_back(stack);
        }
    }
    return list;
}

sptr<ResourceStack> Workshop::getOutputStack() const
{
    return getStack(m_OutputStackSide);
}

sptr<ResourceStack> Workshop::getStack(CardinalDir i_Side) const
{
    LOG_IF(!hasStack(i_Side), FATAL) << toString() << ": Cannot get " 
        << nameOf(i_Side) << "stack: No stack found";
    return m_ResourceStacks[static_cast<uint32_t>(i_Side)];
}

PixelCoords Workshop::getUpperLeftPixelPos() const
{
    return workshopCoordsToWorldCoordsULCorner(m_Pos);
}

void Workshop::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    // Floor
    {
        auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
        cmd->UpperLeftPos  = getUpperLeftPixelPos();
        cmd->LowerRightPos = cmd->UpperLeftPos + WORKSHOP_SIZE;
        cmd->Color         = al_map_rgb(10, 40, 53);
        i_Renderer->enqueueCommand(cmd);
    }
    // Last produced resource visualization (and worth)
    auto lastPushed = getOutputStack()->lastPushedResource();
    if (lastPushed)
    {
        lastPushed->render(i_Renderer, WorldCoords(getUpperLeftPixelPos()) + WORKSHOP_SIZE / 2.f);

        // Display resource worth
        {
            std::stringstream ss;
            ss << "(" << lastPushed->worth() << "$)";

            auto cmd = std::make_shared<alpp::render::DrawCenteredText>();
            cmd->CenterPos = getUpperLeftPixelPos();
            cmd->Color     = al_map_rgb(0, 0, 0);
            cmd->Font      = i_Renderer->StandardFont;
            cmd->Text      = ss.str();
            i_Renderer->enqueueCommand(cmd);
        }
    }

    // Resource stacks
    for (uint8_t i = 0; i < 4; ++i)
    {
        if (m_ResourceStacks[i])
        {
            m_ResourceStacks[i]->render(i_Renderer);
        }
    }

    // Workers
    for (auto const & worker : m_Workers)
    {
        worker->render(i_Renderer);
    }
}

std::string Workshop::toString() const
{
    std::stringstream ss;
    ss << "Workshop at " << m_Pos.toString();
    return ss.str();

}

sptr<ResourceStack> Workshop::addStack(CardinalDir i_Side, ResourceStack::Type i_Type)
{
    LOG_IF(hasStack(i_Side), FATAL) << toString() << ": Cannot add a " 
        << nameOf(i_Side) << "stack: A stack is is already there";

    auto stack = std::make_shared<ResourceStack>(i_Type, m_Pos, i_Side);
    m_ResourceStacks[static_cast<uint32_t>(i_Side)] = stack;
    return stack;
}

void Workshop::removeStack(CardinalDir i_Side)
{
    getStack(i_Side);
    m_ResourceStacks[static_cast<uint32_t>(i_Side)] = nullptr;
}