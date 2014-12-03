#include "renderer/rendernode.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class RenderNodeTest : public ::testing::Test {
protected:
    RenderNode r;

    void SetUp() {
        r = RenderNode();
    }
};

TEST_F(RenderNodeTest, coordinates) {
    EXPECT_EQ(0.0f, r.GetX());
    EXPECT_EQ(0.0f, r.GetY());
}

TEST_F(RenderNodeTest, visibility) {
    EXPECT_TRUE(r.IsVisible());
    r.Hide();
    EXPECT_FALSE(r.IsVisible());
    r.Show();
    EXPECT_TRUE(r.IsVisible());
}

TEST_F(RenderNodeTest, hasnoshaderattached) {
    EXPECT_FALSE( r.HasShaderAttached() );
}

TEST_F(RenderNodeTest, attachshadernode) {
    // we avoid initializing the rendering subsystem by using
    // null as a ShaderManager here
    r.AttachShader( nullptr, "font-shader" );
    EXPECT_TRUE( r.HasShaderAttached() );
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
