#include <gtest/gtest.h>
#include "../Stack.h"

using namespace std;

TEST(Test1, work) {
    Node* root = new Node();
    push(root, 10);
    EXPECT_EQ(peek(root), 10);
}

TEST(Test2, Test_Empty) {
    Node* root = nullptr;
    EXPECT_TRUE(isEmpty(root));
    push(root, 10);
    EXPECT_FALSE(isEmpty(root));
    pop(root);
    EXPECT_TRUE(isEmpty(root));
}

TEST(Test3, Test3) {
    Node* root = nullptr;
    EXPECT_TRUE(isEmpty(root));
}

TEST(Test4, peek) {
    Node* root = nullptr;
    push(root, 10);
    push(root,20);
    EXPECT_EQ(peek(root), 20);
    pop(root);
    EXPECT_EQ(peek(root), 10);
    pop(root);
    EXPECT_TRUE(isEmpty(root));
}

TEST(Test5, test) {
    Node* root = nullptr;
    EXPECT_TRUE(isEmpty(root));
    push(root, 10);
    EXPECT_FALSE(isEmpty(root));
}

