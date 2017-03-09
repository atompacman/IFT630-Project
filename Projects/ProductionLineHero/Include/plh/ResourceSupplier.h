#ifndef PLH_RESOURCE_SUPPLIER
#define PLH_RESOURCE_SUPPLIER

#include <alpp/Event/Agent.h>

#include <plh/ResourceStack.h>

// Represents a resource supplier, which is used to generate resources in input to a workshop
class ResourceSupplier : public alpp::event::Agent
{
public:

    explicit ResourceSupplier(sptr<BasicResource> i_RsrcArchetype,
                              sptr<ResourceStack> i_StackToSupply,
                              float               i_SpeedSec);
    ~ResourceSupplier();

    bool handleEvent(ALLEGRO_EVENT i_Event) override;

protected:

    ALLEGRO_EVENT_SOURCE * getEventSource() const override;

private:

    ALLEGRO_TIMER *     m_Ticker;
    sptr<ResourceStack> m_StackToSupply;    // Stack in which the generated resources are added
    sptr<BasicResource> m_RsrcArchetype;    // Resource type
};

#endif // PLH_RESOURCE_SUPPLIER