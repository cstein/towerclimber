#include "base/glwindow.h"
#include "base/settingsmanager.h"
#include "renderer/shadermanager.h"
#include "renderer/shader.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class ShaderTest : public ::testing::Test {
protected:
    ShaderManager* s;
    SettingsManager* sm;

    ShaderTest() {
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


TEST_F(ShaderTest, NoVertexShader) {
    Shader s = Shader();
    // it does not work (vertex shader filename missing), so load will return false
    EXPECT_FALSE( s.Load() );
}

TEST_F(ShaderTest, NoFragmentShader) {
    Shader s = Shader();
    s.SetVertexShaderFilename( "font.vert" );
    // it still does not work (fragment shader filename missing), so load will return false
    EXPECT_FALSE( s.Load() );
}

TEST_F(ShaderTest, LoadShader) {
    Shader s = Shader();
    s.SetVertexShaderFilename( "font.vert" );
    s.SetFragmentShaderFilename( "font.frag" );
    s.SetShaderName( "font-shader" );
    EXPECT_TRUE( s.Load() );
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
