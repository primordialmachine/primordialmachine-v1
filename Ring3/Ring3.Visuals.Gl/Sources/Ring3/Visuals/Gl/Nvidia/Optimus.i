
// In hybrid systems (usually low-perf intel + high-perf nvidia)
// ensure the high-perf card is selected.
#include <Windows.h>
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
