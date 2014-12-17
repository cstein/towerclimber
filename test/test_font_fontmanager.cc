#include "fonts/fontmanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class FontManagerTest : public ::testing::Test {
protected:

    FontManagerTest() {
    }

    FontManager* tm;

    void SetUp() {
        tm = new FontManager();
    }

    void TearDown() {
        delete tm;
    }
};

TEST_F(FontManagerTest, NoLoadedFontsMeansNoBoundFonts) {
    EXPECT_EQ(0, tm->GetNumFonts());
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
