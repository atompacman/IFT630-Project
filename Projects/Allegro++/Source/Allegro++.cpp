#include <Allegro++.h>
#include <allegro5/system.h>

INITIALIZE_EASYLOGGINGPP

namespace alpp
{

bool init(std::string const & i_LoggerConfigFilePath)
{
    // Initialize logger library
    el::Configurations conf;
    if (!conf.parseFromFile(i_LoggerConfigFilePath))
    {
        LOG(WARNING) << "Easylogging++ configuration file " << i_LoggerConfigFilePath
                     << " was not found. Using default parameters";
    }
    el::Loggers::reconfigureAllLoggers(conf);

    // Initialize Allegro
    LOG(INFO) << "Initializing Allegro " << ALLEGRO_VERSION_STR;
    auto success = true;
    CHECK_BOOL_AL_FUNC(al_init(), success, "Allegro core library initialization failed");

    return success;
}

}