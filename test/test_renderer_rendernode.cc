#include "renderer/rendernode.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_RenderNode, coordinates) {
    RenderNode r = RenderNode();
    EXPECT_EQ(0.0f, r.GetX());
    EXPECT_EQ(0.0f, r.GetY());
}

TEST(Renderer_RenderNode, visibility) {
    RenderNode r = RenderNode();
    EXPECT_TRUE(r.IsVisible());
    r.Hide();
    EXPECT_FALSE(r.IsVisible());
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
