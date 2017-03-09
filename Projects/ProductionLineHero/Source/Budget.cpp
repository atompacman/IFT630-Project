#include <plh/Budget.h>

void Budget::deposit(Dollar i_Amount)
{
    std::unique_lock<std::mutex>(m_Mutex);
    m_Balance += i_Amount;
}

void Budget::withdraw(Dollar i_Amount)
{
    std::unique_lock<std::mutex>(m_Mutex);
    m_Balance -= i_Amount;
}