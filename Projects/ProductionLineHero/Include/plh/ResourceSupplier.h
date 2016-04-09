#ifndef PLH_RESOURCE_SUPPLIER
#define PLH_RESOURCE_SUPPLIER

#include <alpp/Event/Agent.h>

#include <plh/ResourceStack.h>

class ResourceSupplier : public alpp::event::Agent
{
public:

    explicit ResourceSupplier(Resource const &    i_RsrcArchetype,
                              sptr<ResourceStack> i_StackToSupply,
                              float               i_SpeedSec);
    ~ResourceSupplier();

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    ALLEGRO_TIMER *     m_Ticker;
    sptr<ResourceStack> m_StackToSupply;
    Resource            m_RsrcArchetype;
};

#endif // PLH_RESOURCE_SUPPLIER