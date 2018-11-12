#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

inline void start_counting();
inline void stop_counting();
struct timeval start, end;

inline void start_counting()
{
    gettimeofday(&start, NULL);
    return;
}

inline void stop_counting()
{
    unsigned long deltaInUSecs;
    gettimeofday(&end, NULL);

    deltaInUSecs = (end.tv_sec - start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec);
    printf("delta in microseconds %lu\n", deltaInUSecs);
    return;
}
