#include <gtest/gtest.h>

extern "C" {
  #include "search.h"  
  #include "limits.h"
}

TEST(BSearchInt, ExactMatch) {
    int arr[] = {21, 3, 7, 6, 9, 37, 69};
    int key   = 37;
    int *res  = (int*)bsearch(&key, arr, 7, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 37);
}
TEST(BSearchInt, NumberNotInArray) {
    int arr[] = {21, 3, 7, 6, 9, 37, 69};
    int key   = 75;
    int *res  = (int*)bsearch(&key, arr, 7, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}
TEST(BSearchInt, SingleElementArrayMatch) {
    int arr[] = {42};
    int key = 42;
    int *res = (int*)bsearch(&key, arr, 1, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 42);
}
TEST(BSearchInt, SingleElementArrayNoMatch) {
    int arr[] = {42};
    int key = 10;
    int *res = (int*)bsearch(&key, arr, 1, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}
TEST(BSearchInt, RepeatedElementsArray) {
    int arr[] = {3, 3, 3, 7, 7, 7, 9, 9};
    int key = 7;
    int *res = (int*)bsearch(&key, arr, 8, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 7);
}
TEST(BSearchInt, MinimumIntegerValue) {
    int arr[] = {INT_MIN, -100, 0, 50, 100};
    int key = INT_MIN;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, INT_MIN);
}
TEST(BSearchInt, MaximumIntegerValue) {
    int arr[] = {-100, 0, 50, 100, INT_MAX};
    int key = INT_MAX;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, INT_MAX);
}
TEST(BSearchInt, AllSameElementsMatch) {
    int arr[] = {42, 42, 42, 42, 42};
    int key = 42;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 42);
}
TEST(BSearchInt, AllSameElementsNoMatch) {
    int arr[] = {42, 42, 42, 42, 42};
    int key = 100;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}
TEST(BSearchInt, FirstElementMatch) {
    int arr[] = {10, 20, 30, 40, 50};
    int key = 10;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 10);
}
TEST(BSearchInt, LastElementMatch) {
    int arr[] = {10, 20, 30, 40, 50};
    int key = 50;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 50);
}
TEST(BSearchInt, KeyLessThanAllElements) {
    int arr[] = {10, 20, 30, 40, 50};
    int key = 5;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}
TEST(BSearchInt, KeyGreaterThanAllElements) {
    int arr[] = {10, 20, 30, 40, 50};
    int key = 60;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}
TEST(BSearchInt, KeyBetweenElements) {
    int arr[] = {10, 20, 30, 40, 50};
    int key = 25;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}


TEST(BSearchInt, EmptyArray) {
    int arr[] = {};
    int key = 10;
    int *res = (int*)bsearch(&key, arr, 0, sizeof *arr, compare_int);

    EXPECT_EQ(res, nullptr);
}

TEST(BSearchInt, NegativeIntegers) {
    int arr[] = {-50, -40, -30, -20, -10};
    int key = -30;
    int *res = (int*)bsearch(&key, arr, 5, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, -30);
}

TEST(BSearchInt, MixedSignIntegers) {
    int arr[] = {-30, -20, -10, 0, 10, 20, 30};
    int key = -10;
    int *res = (int*)bsearch(&key, arr, 7, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, -10);

    key = 0;
    res = (int*)bsearch(&key, arr, 7, sizeof *arr, compare_int);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(*res, 0);
}


TEST(BSearchFloat, ExactMatch) {
    float arr[] = {1.1f, 2.2f, 3.3f};
    float key   = 2.2f;
    float *res  = (float*)bsearch(&key, arr, 3, sizeof *arr, compare_float);

    ASSERT_NE(res, nullptr);
    EXPECT_FLOAT_EQ(*res, 2.2f);
}


TEST(BSearchString, ExactMatchChars) {
    const char *arr[] = {"a","b","c"};
    const char *key   = "b";
    const char **res  = (const char**)bsearch(&key, arr, 3, sizeof *arr, compare_string);

    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(*res, "b");
}
TEST(BSearchString, ExactMatchStrings) {
    const char *arr[] = {"adam","beata","celina"};
    const char *key   = "beata";
    const char **res  = (const char**)bsearch(&key, arr, 3, sizeof *arr, compare_string);

    ASSERT_NE(res, nullptr);
    EXPECT_STREQ(*res, "beata");
}
TEST(BSearchString, CaseSensitivity) {
    const char *arr[] = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};
    const char *key = "banana";
    const char **res = (const char**)bsearch(&key, arr, 5, sizeof *arr, compare_string);

    EXPECT_EQ(res, nullptr);
}

TEST(BSearchStruct, FindsById) {
    Item arr[] = {{1,"one"},{2,"two"}};
    Item key   = {2,""};
    Item *res  = (Item*)bsearch(&key, arr, 2, sizeof *arr, compare_struct_item_by_id);

    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res->id, 2);
}
