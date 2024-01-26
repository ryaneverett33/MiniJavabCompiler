#include <gtest/gtest.h>
#include <string>
#include <filesystem>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define WINDOWS
#elif defined(__APPLE__)
    #define MACOS
#elif defined(__linux__)
    #define LINUX
#endif

class LanguageTests : public ::testing::Test {
    public:
        /// @brief Directory containing the test executables and test data directories
        std::filesystem::path TestDirectory;
    protected:
        void SetUp() override;
};