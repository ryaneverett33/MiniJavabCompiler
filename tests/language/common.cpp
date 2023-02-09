#include "common.h"
#include <stdexcept>
#if defined(MACOS)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#endif


#if defined(MACOS)
std::filesystem::path getTestDirectoryMac() {
    // Mostly stolen from https://stackoverflow.com/a/1024933
    char pathBuffer[PATH_MAX+1];
    uint32_t size = sizeof(pathBuffer);
    if (_NSGetExecutablePath(pathBuffer, &size) == 0) {
        return std::filesystem::path(pathBuffer).parent_path();
    }
    throw new std::runtime_error("Failed to get current executable path"); 
}
#endif

void LanguageTests::SetUp() {
#if defined(MACOS)
    TestDirectory = getTestDirectoryMac();
#elif defined(WINDOWS)
    throw new std::runtime_error("Windows testing not supported yet");
#elif defined(LINUX)
    throw new std::runtime_error("Linux testing not supported yet");
#endif
}