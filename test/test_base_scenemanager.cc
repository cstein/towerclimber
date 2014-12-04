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

TEST_F(SceneManagerTest, insertandgetactive) {
    Scene* s = new Scene();
    sm.PushScene(s);
    EXPECT_EQ(s, sm.GetActiveScene());
}

TEST_F(SceneManagerTest, insertmultipleandgetactive) {
    Scene* s1 = new Scene();
    Scene* s2 = new Scene();
    sm.PushScene(s1);
    sm.PushScene(s2);
    EXPECT_EQ(s2, sm.GetActiveScene());

}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
