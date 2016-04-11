#ifndef PLH_COMMON
#define PLH_COMMON

#include <allegro5/color.h>

#include <alpp/Core.h>

#include <chrono>

#include <easylogging++.h>

using namespace std::chrono_literals;

// Log
std::string const LOGGER_CONFIG_FILE = "../Config/easyloggingpp.config";

// Initial window size
PixelDimensions const INIT_WIN_DIM (1200, 800);

// Keyboard scroll speed
float const KEYBOARD_SCROLL_SPEED (10);

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
    LOG_IF(!(i_WSCoords < MAX_NUM_WORKSHOPS), FATAL)
        << "Invalid workshop position (" << i_WSCoords.x << ", " << i_WSCoords.y << ")";
}

inline WorldCoords workshopCoordsToWorldCoordsULCorner(WorkshopCoords i_WSCoords)
{
    auto p = WorldCoords(i_WSCoords);
    return p * WORKSHOP_SIZE_PXL + (p + WorldCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;
}

// Worker
uint16_t const WORKER_RADIUS         (10);
float    const PATH_WIGGLE_AMPLITUDE (0.3f);
float    const PATH_WIGGLE_FREQUENCY (0.8f);

// Resource stack
WorldCoords const RESRC_STACK_SIZE_PXL (20, 20);

// Treadmill
auto const THREADMILL_SPEED = .001;

// Resources
std::vector<uint16_t> const RESOURCE_COLORS = { 255,   0,   0,
                                                  0, 255,   0,
                                                  0,   0, 255 };

std::vector<uint16_t> const RAFFINEMENT_COLORS = { 224, 200, 143,
                                                    50, 150, 246,
                                                   142,  40,  46 };

inline ALLEGRO_COLOR getColorConstant(uint8_t i_ColorID, std::vector<uint16_t> const & i_Vec)
{
    auto s = i_ColorID * 3;
    LOG_IF(s >= i_Vec.size(), FATAL) << "Invalid color ID";
    return al_map_rgb(i_Vec[s], i_Vec[s + 1], i_Vec[s + 2]);
}

inline ALLEGRO_COLOR getResourceColor(uint8_t i_ColorID)
{
    return getColorConstant(i_ColorID, RESOURCE_COLORS);
}

inline ALLEGRO_COLOR getRaffinementColor(uint8_t i_ColorID)
{
    return getColorConstant(i_ColorID, RAFFINEMENT_COLORS);
}

#endif // PLH_COMMON