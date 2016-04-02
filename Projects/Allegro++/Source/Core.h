#ifndef ALPP_CORE
#define ALPP_CORE

#include <easylogging++.h>
#include <memory>
#include <string>

#define CHECK_BOOL_AL_FUNC(funcCall, successFlag, errorMsg) \
    if (!funcCall) \
    { \
        LOG(ERROR) << errorMsg; \
        successFlag = false; \
    }

#define CHECK_AL_FUNC(funcCall, returnVar, successFlag, errorMsg) \
    returnVar = funcCall; \
    if (returnVar == nullptr) \
    { \
        LOG(ERROR) << errorMsg; \
        successFlag = false; \
    }
    
template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using sptrc = std::shared_ptr<T const>;

namespace alpp {

bool init(std::string const & i_LoggerConfigFilePath);

class AllegroInitializable
{
public:

    explicit AllegroInitializable();
    virtual ~AllegroInitializable() { }

    bool isSuccessfullyInitialized() const;

protected:

    bool m_InitSuccess;
};

}

#endif // ALPP_CORE 