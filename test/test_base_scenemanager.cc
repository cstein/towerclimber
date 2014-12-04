#include "base/scenemanager.h"
#include "base/scene.h"
#include "gtest/gtest.h"
#include "easyloggingpp/src/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

class SceneManagerTest : public ::testing::Test {
protected:
    SceneManager sm;

    void SetUp() {
        sm = SceneManager();
    }
};

TEST_F(SceneManagerTest, emptyscene) {
    EXPECT_EQ(nullptr, sm.GetActiveScene());
}

TEST_F(SceneManagerTest, poponemptyscene) {
    EXPECT_EQ(nullptr, sm.PopScene());
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
