// allegro
#include <allegro5/system.h>

// alpp
#include <Core.h>

// el
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

bool alpp::init(std::string const & i_LoggerConfigFilePath)
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

alpp::AllegroInitializable::AllegroInitializable() :
    m_InitSuccess(true)
{
    
}

bool alpp::AllegroInitializable::isSuccessfullyInitialized() const
{
    return m_InitSuccess;
}