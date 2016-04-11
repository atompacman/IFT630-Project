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
PixelDimensions const INIT_WIN_DIM (1500, 900);

// Keyboard scroll speed
float const KEYBOARD_SCROLL_SPEED (10);

// Mouse scroll factor
float const MOUSE_SCROLL_ZOOM_FACTOR (0.05);

// Timing
float const TARGET_FPS        (60);
auto  const THREAD_SLEEP_TIME (16ms);

// Vector types
typedef Vector2D<uint16_t> WorkshopCoords;

// Workshop
uint16_t       const MAX_NUM_WORKSHOPS_X     (8);
uint16_t       const MAX_NUM_WORKSHOPS_Y     (6);
WorkshopCoords const MAX_NUM_WORKSHOPS       (MAX_NUM_WORKSHOPS_X, MAX_NUM_WORKSHOPS_Y);
float          const WORKSHOP_SIDE_SIZE      (150);
WorldCoords    const WORKSHOP_SIZE           (WORKSHOP_SIDE_SIZE, WORKSHOP_SIDE_SIZE);
float          const SPACE_BETWEEN_WORKSHOPS (60);

inline void checkWorkshopCoords(WorkshopCoords i_WSCoords)
{
    LOG_IF(!(i_WSCoords < MAX_NUM_WORKSHOPS), FATAL)
        << "Invalid workshop position (" << i_WSCoords.x << ", " << i_WSCoords.y << ")";
}

inline WorldCoords workshopCoordsToWorldCoordsULCorner(WorkshopCoords i_WSCoords)
{
    auto p = WorldCoords(i_WSCoords);
    return p * WORKSHOP_SIZE + (p + WorldCoords(1, 1)) * SPACE_BETWEEN_WORKSHOPS;
}

inline WorkshopCoords worldCoordsULCornerToWorkshopCoords(WorldCoords i_WCoords)
{
    auto p = WorkshopCoords(i_WCoords);
    return (p - (WorkshopCoords(1, 1) * uint16_t(SPACE_BETWEEN_WORKSHOPS))) / 
        (WorkshopCoords(WORKSHOP_SIZE) + uint16_t(SPACE_BETWEEN_WORKSHOPS));
}

// Resource preview
float const RESRC_PREV_PROPORTION (2 / 3.);
float const RECT_THICKNESS        (1.2);
float const ADDITIONAL_RECT_PROP  (0.9);

// Placeable factory rooms
// #TODO: rename enum...
enum class CreatableRoomType 
{
    WORKSHOP,
    SUPPLIER,
    NONE
};

// Worker
uint16_t const WORKER_RADIUS         (10);
float    const PATH_WIGGLE_AMPLITUDE (0.3f);
float    const PATH_WIGGLE_FREQUENCY (0.8f);

// Resource stack
WorldCoords const RESRC_STACK_SIZE_PXL (20, 20);

// Treadmill
auto const THREADMILL_SPEED (.001);

// Resources
uint8_t const MAX_NUM_RAFFINEMENTS (5);

std::vector<uint16_t> const RESOURCE_COLORS = { 255,   0,   0,
                                                  0, 255,   0,
                                                  0,   0, 255 };

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

#endif // PLH_COMMON