#pragma once

// alpp
#include <Core.h>
#include <Render/Command.h>
#include <Render/Renderer.h>

// std
#include <cstdint>

class Worker
{
public:
    Worker();
    Worker(uint16_t posX, uint16_t posY, float speed);
    ~Worker();
    void render(sptr<alpp::render::Renderer> i_Renderer);

private:
    void runWorkerThread();
    void work();

    uint16_t m_PosX;
    uint16_t m_PosY;
    float    m_Speed;
    // possible additions : color, texture

    static uint16_t const RADIUS = 10;
};