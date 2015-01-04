#include "base/sdlwindow.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(SDLWindow, window_size_width_default) {
    SDLWindow window = SDLWindow();
    window.Start();
    EXPECT_EQ(640, window.GetWidth());
}

TEST(SDLWindow, window_size_height_default) {
    SDLWindow window = SDLWindow();
    window.Start();
    EXPECT_EQ(480, window.GetHeight());
}

TEST(SDLWindow, window_size_width_custom) {
    SDLWindow window = SDLWindow();
    window.Start(800, 600);
    EXPECT_EQ(800, window.GetWidth());
}

TEST(SDLWindow, window_size_height_custom) {
    SDLWindow window = SDLWindow();
    window.Start(800, 600);
    EXPECT_EQ(600, window.GetHeight());
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
