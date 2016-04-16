#ifndef APLIB_DIRECTION_2D
#define APLIB_DIRECTION_2D

/*================================================================================================\\
| Enums and utility methods for manipulating 2D directions
|--------------------------------------------------------------------------------------------------|
| Each enum is strongly typed and has associated maps and methods for converting strings to enum 
| constants and vice-versa.
\=================================================================================================*/

#include <map>

enum class CardinalDir
{
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3
};

enum class Dir2D
{
    UP    = 0,
    RIGHT = 1,
    DOWN  = 2,
    LEFT  = 3
};

enum class Dir2DWithDiag
{
    UP          = 0,
    RIGHT       = 1,
    DOWN        = 2,
    LEFT        = 3,
    UPPER_RIGHT = 4,
    LOWER_RIGHT = 5,
    LOWER_LEFT  = 6,
    UPPER_LEFT  = 7
};

std::map<std::string, CardinalDir> const CARDINAL_DIR_STR_2_VAL =
   {{ "NORTH", CardinalDir::NORTH },
    { "EAST",  CardinalDir::EAST  },
    { "SOUTH", CardinalDir::SOUTH },
    { "WEST",  CardinalDir::WEST  }};

std::map<std::string, Dir2D> const DIR_2D_STR_2_VAL =
   {{ "UP",           Dir2D::UP          },
    { "RIGHT",        Dir2D::RIGHT       },
    { "DOWN",         Dir2D::DOWN        },
    { "LEFT",         Dir2D::LEFT        }};

std::map<std::string, Dir2DWithDiag> const DIR_2D_WTIH_DIAG_STR_2_VAL =
   {{ "UP",           Dir2DWithDiag::UP          },
    { "RIGHT",        Dir2DWithDiag::RIGHT       },
    { "DOWN",         Dir2DWithDiag::DOWN        },
    { "LEFT",         Dir2DWithDiag::LEFT        },
    { "UPPER_RIGHT",  Dir2DWithDiag::UPPER_RIGHT },
    { "LOWER_RIGHT",  Dir2DWithDiag::LOWER_RIGHT },
    { "LOWER_LEFT",   Dir2DWithDiag::LOWER_LEFT  },
    { "UPPER_LEFT",   Dir2DWithDiag::UPPER_LEFT  }};

char const * const CARDINAL_DIR_NAMES[] =
    { "NORTH", 
      "EAST", 
      "SOUTH", 
      "WEST", };

char const * const DIR_2D_NAME[] =
    { "UP",
      "RIGHT",
      "DOWN",
      "LEFT", 
      "UPPER_RIGHT",
      "LOWER_RIGHT",
      "LOWER_LEFT",
      "UPPER_LEFT"  };

inline char const * to_string(CardinalDir i_Dir)
{
    return CARDINAL_DIR_NAMES[static_cast<uint8_t>(i_Dir)];
}

inline char const * to_string(Dir2D i_Dir)
{
    return DIR_2D_NAME[static_cast<uint8_t>(i_Dir)];
}

inline char const * to_string(Dir2DWithDiag i_Dir)
{
    return DIR_2D_NAME[static_cast<uint8_t>(i_Dir)];
}

inline Dir2DWithDiag oppositeOf(Dir2DWithDiag i_Dir)
{
    switch (i_Dir)
    {
    case Dir2DWithDiag::UP          : return Dir2DWithDiag::DOWN;
    case Dir2DWithDiag::RIGHT       : return Dir2DWithDiag::LEFT;
    case Dir2DWithDiag::DOWN        : return Dir2DWithDiag::UP;
    case Dir2DWithDiag::LEFT        : return Dir2DWithDiag::RIGHT;
    case Dir2DWithDiag::UPPER_RIGHT : return Dir2DWithDiag::LOWER_LEFT;
    case Dir2DWithDiag::LOWER_RIGHT : return Dir2DWithDiag::UPPER_LEFT;
    case Dir2DWithDiag::LOWER_LEFT  : return Dir2DWithDiag::UPPER_RIGHT;
    case Dir2DWithDiag::UPPER_LEFT  : return Dir2DWithDiag::LOWER_RIGHT;
    default:                          return Dir2DWithDiag(-1);
    }
}

#endif // APLIB_DIRECTION_2D