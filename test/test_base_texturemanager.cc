#include "base/glwindow.h"
#include "base/texturemanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class TextureManagerTest : public ::testing::Test {
protected:

    TextureManagerTest() {
        GLWindow window = GLWindow();
        window.Start();
    }

    TextureManager* tm;

    void SetUp() {
        tm = new TextureManager();
        tm->Start();
    }

    void TearDown() {
        tm->Stop();
        delete tm;
    }
};

TEST_F(TextureManagerTest, noloadedtexturesmeansnoboundtextures) {
    EXPECT_EQ(0, tm->GetBoundTexture());
}

TEST_F(TextureManagerTest, noloadedtexturesmeanshasnotextures) {
    EXPECT_FALSE(tm->HasTexture("dummytexture"));
}

TEST_F(TextureManagerTest, loadtexturemeanshastextures) {
    EXPECT_TRUE(tm->LoadTexture("testtexture"));
    EXPECT_TRUE(tm->HasTexture("testtexture"));
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
