#ifndef PLH_COMMON
#define PLH_COMMON

#include <aplib/Vector2D.h>

#include <chrono>

#include <easylogging++.h>

using namespace std::chrono_literals;

// Timing
float const TARGET_FPS        (60);
auto  const THREAD_SLEEP_TIME (16ms);

// Vector types
typedef Vector2D<uint16_t> WorkshopCoords;

// Workshop
uint16_t       const MAX_NUM_WORKSHOPS_X     (6);
uint16_t       const MAX_NUM_WORKSHOPS_Y     (6);
WorkshopCoords const MAX_NUM_WORKSHOPS       (MAX_NUM_WORKSHOPS_X, MAX_NUM_WORKSHOPS_Y);
WorldCoords    const WORKSHOP_SIZE_PXL       (150, 150);
float          const SPACE_BETWEEN_WORKSHOPS (60);

inline void checkWorkshopCoords(WorkshopCoords i_WSCoords)
{
    LOG_IF(!(i_WSCoords <= MAX_NUM_WORKSHOPS), FATAL)
        << "Invalid workshop position (" << i_WSCoords.x << ", " << i_WSCoords.y << ")";
}

inline WorldCoords workshopCoordsToWorldCoordsULCorner(WorkshopCoords i_WSCoords)
{
    auto p = WorldCoords(i_WSCoords);
    return p * WORKSHOP_SIZE_PXL + (p + WorldCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;
}

// Worker
uint16_t const WORKER_RADIUS         (10);
float    const PATH_WIGGLE_AMPLITUDE (0.2f);
float    const PATH_WIGGLE_FREQUENCY (0.5f);

// Resource stack
PixelCoords const RESRC_STACK_SIZE_PXL (20, 20);

// Treadmill
auto const THREADMILL_SPEED = .001;

#endif // PLH_COMMON