#include "renderer/textnode.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

TEST(Renderer_TextNode, coordinates) {
    FontManager* f = new FontManager();
    f->Start();
    TextNode* t = new TextNode( f );
    //TextNode t(f);
    //t.Create("Ubuntu Mono", 1.0f, 0.0f, 0.0f, "LOL");
    //EXPECT_EQ(0.0f, t.GetX());
    //EXPECT_EQ(0.0f, t.GetY());
    delete t;
    f->Stop();
    delete f;
}


GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
