#include "base/glwindow.h"
#include "renderer/shadermanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class ShaderManagerTest : public ::testing::Test {
protected:
    ShaderManager* s;
    ShaderManagerTest() {
        GLWindow window = GLWindow();
        window.Start();
    }

    void SetUp() {
        s = new ShaderManager();
        s->Start();
    }

    void TearDown() {
        s->Stop();
        delete s;
    }

};

TEST_F(ShaderManagerTest, HasLoadedShader) {
    EXPECT_TRUE(s->HasShader("font-shader"));
    EXPECT_FALSE(s->HasShader("dummy-shader"));
}

TEST_F(ShaderManagerTest, ShaderPointers) {
    EXPECT_EQ(nullptr, s->GetShader("dummy-shader"));
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
