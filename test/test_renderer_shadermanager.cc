#include "renderer/shadermanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_ShaderManager, Base) {
    ShaderManager* s = new ShaderManager();
    s->Start();

    s->Stop();
    delete s;
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
