#ifndef PLH_COMMON
#define PLH_COMMON

// aplib
#include <aplib/Vector2D.h>

// std
#include <chrono>

using namespace std::chrono_literals;

// Vector types
typedef Vector2D<uint16_t> PixelCoords;
typedef Vector2D<uint16_t> WorkshopCoords;
typedef Vector2D<double>   RealCoords;

// Workshop
uint16_t       const MAX_NUM_WORKSHOPS_X     (6);
uint16_t       const MAX_NUM_WORKSHOPS_Y     (4);
WorkshopCoords const MAX_NUM_WORKSHOPS       (MAX_NUM_WORKSHOPS_X, MAX_NUM_WORKSHOPS_Y);
PixelCoords    const WORKSHOP_SIZE_PXL       (150, 150);
uint16_t       const SPACE_BETWEEN_WORKSHOPS (60);

// Worker
uint16_t const WORKER_RADIUS         (10);
double   const PATH_WIGGLE_AMPLITUDE (0.2);
double   const PATH_WIGGLE_FREQUENCY (0.5);
auto     const WORKER_SLEEP_TIME     (16ms);

// Resource stack
PixelCoords const RESRC_STACK_SIZE_PXL (20, 20);

#endif // PLH_COMMON