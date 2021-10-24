
// In hybrid systems (usually low-perf intel + high-perf amd)
// ensure the high-perf card is selected.
#include <Windows.h>
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
