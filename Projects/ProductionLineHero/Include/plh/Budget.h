#ifndef PLH_BUDGET
#define PLH_BUDGET

#include <plh/Common.h>

#include <mutex>

class Budget
{
public:

    explicit Budget() :
        m_Balance(INITIAL_BALANCE),
        m_Mutex   ()
    {}

    Dollar balance() const { return m_Balance; };

    bool canAfford(Dollar i_Cost) const { return m_Balance >= i_Cost; };

    void deposit (Dollar i_Amount);
    void withdraw(Dollar i_Amount);

private:

    // How much money in this budget
    Dollar m_Balance;

    // Money is serious business
    std::mutex m_Mutex;
};

#endif // PLH_BUDGET