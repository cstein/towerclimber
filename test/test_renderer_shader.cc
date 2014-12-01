#include "base/glwindow.h"
#include "renderer/shadermanager.h"
#include "renderer/shader.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_Shader, NoVertexName) {
    // we need GLWindow to create shader programs
    GLWindow window = GLWindow();
    window.Start();

    // dummy for logging
    ShaderManager *sm = new ShaderManager();
    //Shader s = Shader();

    // it does not work (vertex shader filename missing), so load will return false
    //EXPECT_FALSE( s.Load() );

    delete sm;
    window.Stop();

}

TEST(Renderer_Shader, NoFragmentName) {
    // we need GLWindow to create shader programs
    GLWindow window = GLWindow();
    window.Start();

    // dummy for logging
    ShaderManager *sm = new ShaderManager();
    Shader s = Shader();

    //s.SetVertexShaderFilename( "font.vert" );
    // it still does not work (fragment shader filename missing), so load will return false
    //EXPECT_FALSE( s.Load() );
    EXPECT_FALSE( s.Load() );

    delete sm;
    window.Stop();
}

TEST(Renderer_Shader, Base) {
    // we need GLWindow to create shader programs
    GLWindow window = GLWindow();
    window.Start();

    // dummy for logging
    ShaderManager *sm = new ShaderManager();
    Shader s = Shader();
    s.SetVertexShaderFilename( "font.vert" );
    s.SetFragmentShaderFilename( "font.frag" );
    s.SetShaderName( "font-shader" );
    //EXPECT_TRUE( s.Load() );
    std::cout << s.Load() << " true: " << true << std::endl;

    delete sm;

    window.Stop();
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
