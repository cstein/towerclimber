#include "base/settingsmanager.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class SettingsManagerTest : public ::testing::Test {
protected:

    SettingsManagerTest() {
    }

    SettingsManager* sm;

    void SetUp() {
        sm = new SettingsManager();
    }

    void TearDown() {
        delete sm;
    }
};

TEST_F(SettingsManagerTest, LoadedSettingsHasSettings) {
    sm->Start();
    EXPECT_TRUE( sm->HasSettingsPath("fonts") );
    EXPECT_FALSE( sm->HasSettingsPath("dummy") );
}

TEST_F(SettingsManagerTest, LoadedSettingsGetSettings) {
    sm->Start();
    SettingsPath* s = sm->GetSettingsPath("shaders");
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
