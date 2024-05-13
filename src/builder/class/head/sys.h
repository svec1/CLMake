#ifndef SYS__H_
#define SYS__H_

#include "../../../bin/include.h"

namespace systemCl
{
    template <typename T>
    class thread_safe
    {
    public:
        thread_safe()
        {
            threadCurrent_ = false;
        }
        thread_safe(T sData_)
        {
            safe_data = sData_;
            threadCurrent_ = false;
        }
        ~thread_safe()
        {
            threadCurrent_ = false;
        }

    public:
        T load()
        {
            if (threadCurrent_.load())
            {
                while (threadCurrent_.load())
                    ;
            }
            return safe_data;
        }
        void exchange(T newData_)
        {
            if (threadCurrent_.load())
            {
                while (threadCurrent_.load())
                    ;
            }
            threadCurrent_.exchange(true);
            safe_data = newData_;
            threadCurrent_.exchange(false);
        }

    private:
        T safe_data;
        std::atomic<bool> threadCurrent_;
    };
}
#endif