#include "base/glwindow.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(GLWindow, window_size_width_default) {
    GLWindow window = GLWindow();
    window.Start();
    EXPECT_EQ(640, window.GetWidth());
}

TEST(GLWindow, window_size_height_default) {
    GLWindow window = GLWindow();
    window.Start();
    EXPECT_EQ(480, window.GetHeight());
}

TEST(GLWindow, window_size_width_custom) {
    GLWindow window = GLWindow();
    window.Start(800, 600);
    EXPECT_EQ(800, window.GetWidth());
}

TEST(GLWindow, window_size_height_custom) {
    GLWindow window = GLWindow();
    window.Start(800, 600);
    EXPECT_EQ(600, window.GetHeight());
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
