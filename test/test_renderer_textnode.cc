#include "base/glwindow.h"
#include "renderer/textnode.h"
#include "renderer/shadermanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_TextNode, coordinates) {
    GLWindow window = GLWindow();
    window.Start();

    SettingsManager* sm = new SettingsManager();
    sm->Start();

    FontManager* f = new FontManager( sm );
    f->Start();

    ShaderManager* s = new ShaderManager( sm );
    s->Start();

    TextNode* t = new TextNode( f );
    //TextNode t(f);
    //t.Create("Ubuntu Mono", 1.0f, 0.0f, 0.0f, "LOL");
    EXPECT_EQ(0.0f, t->GetX());
    EXPECT_EQ(0.0f, t->GetY());

    delete t;
    s->Stop();
    delete s;
    f->Stop();
    delete f;
    sm->Stop();
    delete sm;
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
