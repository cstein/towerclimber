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

TEST_F(TextureManagerTest, NoLoadedTexturesMeansNoBoundTextures) {
    EXPECT_EQ(0, tm->GetBoundTexture());
}

TEST_F(TextureManagerTest, NoLoadedTexturesMeansHasNoTextures) {
    EXPECT_FALSE(tm->HasTexture("dummytexture"));
}

TEST_F(TextureManagerTest, LoadTextureMeansHasTexture) {
    EXPECT_TRUE(tm->LoadTexture("testtexture"));
    EXPECT_TRUE(tm->HasTexture("testtexture"));
}

TEST_F(TextureManagerTest, LoadTextureUnloadTexture) {
    EXPECT_TRUE(tm->LoadTexture("testtexture"));
    EXPECT_EQ(1, tm->GetNumLoadedTextures());
    EXPECT_TRUE(tm->UnloadTexture("testtexture"));
    EXPECT_EQ(0, tm->GetNumLoadedTextures());
    EXPECT_FALSE(tm->HasTexture("testtexture"));
}

TEST_F(TextureManagerTest, LoadTextureTwice) {
    EXPECT_EQ(0, tm->GetNumLoadedTextures());
    EXPECT_TRUE(tm->LoadTexture("testtexture"));
    EXPECT_EQ(1, tm->GetNumLoadedTextures());

    tm->BindTexture("testtexture");
    GLuint id = tm->GetBoundTexture();
    EXPECT_EQ(1, id);

    // loading (and binding) the same texture twice should return old one.
    EXPECT_TRUE(tm->LoadTexture("testtexture"));
    tm->BindTexture("testtexture");
    EXPECT_EQ(id, tm->GetBoundTexture());
    EXPECT_EQ(1, tm->GetNumLoadedTextures()); 
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
