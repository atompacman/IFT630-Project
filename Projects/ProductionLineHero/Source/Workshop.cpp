// alpp
#include <Render/Command.h>
#include <Render/Renderer.h>

//el
#include <easylogging++.h>

// plh
#include <Factory.h>
#include <Workshop.h>

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

void Workshop::addInputStack(CardinalDir i_Side)
{
    addStack(i_Side, ResourceStack::Type::INPUT);
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
    return m_Pos * WORKSHOP_SIZE_PXL + (m_Pos + PixelCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;
}

void Workshop::render(sptr<alpp::render::Renderer> i_Renderer) const
{
    auto ulPos = getUpperLeftPixelPos();
    auto lrPos = ulPos + WORKSHOP_SIZE_PXL;

    auto cmd = std::make_shared<alpp::render::DrawFilledRectangle>();
    cmd->PosLeft   = ulPos.x;
    cmd->PosRight  = lrPos.x;
    cmd->PosTop    = ulPos.y;
    cmd->PosBottom = lrPos.y;
    cmd->Color     = al_map_rgb(10, 40, 53);
    i_Renderer->enqueueCommand(cmd);

    for (uint8_t i = 0; i < 4; ++i)
    {
        if (m_ResourceStacks[i])
        {
            m_ResourceStacks[i]->render(i_Renderer);
        }
    }

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

void Workshop::addStack(CardinalDir i_Side, ResourceStack::Type i_Type)
{
    LOG_IF(hasStack(i_Side), FATAL) << toString() << ": Cannot add a " 
        << nameOf(i_Side) << "stack: A stack is is already there";

    auto stack = std::make_shared<ResourceStack>(i_Type, m_Pos, i_Side);
    m_ResourceStacks[static_cast<uint32_t>(i_Side)] = stack;
}

void Workshop::removeStack(CardinalDir i_Side)
{
    getStack(i_Side);
    m_ResourceStacks[static_cast<uint32_t>(i_Side)] = nullptr;
}