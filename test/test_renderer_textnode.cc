#include "base/glwindow.h"
#include "renderer/textnode.h"
#include "renderer/shadermanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_TextNode, coordinates) {
    GLWindow window = GLWindow();
    window.Start();

    FontManager* f = new FontManager("resources/graphics/fonts", "fonts.json");
    f->Start();

    ShaderManager* s = new ShaderManager();
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
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
