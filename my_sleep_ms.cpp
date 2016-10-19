#include "my_sleep_ms.h"

#ifdef unix
#include <unistd.h>

void my_sleep_ms(int sleepMs){
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second microsecond)
}

#elif  defined _WIN32 || defined _WIN64
#include <windows.h>
void my_sleep_ms(int sleepMs){
    Sleep(sleepMs);
}
#endif

