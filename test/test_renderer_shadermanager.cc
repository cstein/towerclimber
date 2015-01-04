#include "base/glwindow.h"
#include "base/settingsmanager.h"
#include "renderer/shadermanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class ShaderManagerTest : public ::testing::Test {
protected:
    ShaderManager* s;
    SettingsManager* sm;

    ShaderManagerTest() {
        GLWindow window = GLWindow();
        window.Start();
    }

    void SetUp() {
        sm = new SettingsManager();
        sm->Start();
        s = new ShaderManager( sm );
        s->Start();
    }

    void TearDown() {
        s->Stop();
        delete s;
        sm->Stop();
        delete sm;
    }

};

TEST_F(ShaderManagerTest, HasLoadedShader) {
    EXPECT_TRUE(s->HasShader("font-shader"));
    EXPECT_FALSE(s->HasShader("dummy-shader"));
}

TEST_F(ShaderManagerTest, ShaderPointers) {
    EXPECT_EQ(nullptr, s->GetShader("dummy-shader"));
}

TEST_F(ShaderManagerTest, NoShaderProgramBound) {
    EXPECT_EQ(0, s->GetBoundShaderID());
    EXPECT_EQ(nullptr, s->GetBoundShader());
}

TEST_F(ShaderManagerTest, BindShaderByName) {
    EXPECT_TRUE(s->BindShader("font-shader"));
    EXPECT_EQ(1, s->GetBoundShaderID());
    EXPECT_EQ("font-shader", s->GetBoundShader()->GetName());
}

TEST_F(ShaderManagerTest, BindShaderFailByName) {
    EXPECT_FALSE(s->BindShader("dummy-shader"));
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
