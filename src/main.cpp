#include "head.h"

int main(int argc, char *argv[])
{
    std::thread assistant_Th(_assistant::assist);
    while (!_assistant::assistant_.load())
        ;
    try
    {
        time_t begin = clock();
        if (argc == 2)
        {
            std::string tmp = argv[1];
            if (tmp == "-build")
                asm_ = true;
        }
        StreamEI::SEI_();
        ConsoleManage::CM(argc, argv);
        time_t end = clock();
        printf("Runtime - %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
    }
    catch (std::exception &ex_err)
    {
        _assistant::_error_hand::errorUS_create(ex_err);
        while (_assistant::assistant_.load())
            ;
        assistant_Th.detach();
        exit(1);
    }
    _assistant::assistant_.exchange(false);
    assistant_Th.join();
    return 0;
}