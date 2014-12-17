#include "base/settingsmanager.h"
#include "fonts/fontmanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

#include <iostream>

_INITIALIZE_EASYLOGGINGPP

class FontManagerTest : public ::testing::Test {
protected:

    FontManagerTest() {
    }

    FontManager* tm;
    SettingsManager* sm;

    void SetUp() {
        sm = new SettingsManager();
        sm->Start();

        SettingsPath* sp = sm->GetSettingsPath("fonts");
        tm = new FontManager(sp->GetPath(), sp->GetName());
    }

    void TearDown() {
        delete sm;
        delete tm;
    }
};

TEST_F(FontManagerTest, NoLoadedFontsMeansNoBoundFonts) {
    EXPECT_EQ(0, tm->GetNumFonts());
}

TEST_F(FontManagerTest, LoadedFontsMeansBoundFonts) {
    tm->Start();
    EXPECT_EQ(3, tm->GetNumFonts());
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
