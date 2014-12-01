#include "base/glwindow.h"
#include "renderer/shadermanager.h"
#include "renderer/shader.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_Shader, Base) {
    GLWindow window = GLWindow();
    window.Start();
    // use shadermanager as a dummy to set up the logging functions properly.
    ShaderManager *sm = new ShaderManager();

    Shader s = Shader();

    // it does not work (vertex shader filename missing), so load will return false
    EXPECT_FALSE( s.Load() );

    s.SetVertexShaderFilename( "font.vert" );
    // it still does not work (fragment shader filename missing), so load will return false
    EXPECT_FALSE( s.Load() );

    s.SetFragmentShaderFilename( "font.frag" );
    EXPECT_TRUE( s.Load() );

    delete sm;
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
