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

TEST_F(SettingsManagerTest, LoadedSettings) {
    sm->Start();
    EXPECT_TRUE( sm->HasSettingsPath("fonts" ) );
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
