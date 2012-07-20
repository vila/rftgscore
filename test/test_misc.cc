#include "gtest/gtest.h"
#include "misc.hh"

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

TEST(split_line, EmptyString) {
    vector<string> ret = split_line("");

    ASSERT_EQ(0, ret.size());
}

TEST(split_line, ThreeItems) {
    vector<string> ret = split_line("one;two;three");
    
    ASSERT_EQ("one", ret[0]);
    ASSERT_EQ("two", ret[1]);
    ASSERT_EQ("three", ret[2]);
}


TEST(trim, AllSpaces) {
    ASSERT_EQ("", trim("      "));
}

TEST(trim, NoSpaces) {
    ASSERT_EQ("ABC DEF", trim("ABC DEF"));
}

TEST(trim, PreSpaces) {
    ASSERT_EQ("SomeString", trim(" SomeString"));
    ASSERT_EQ("SomeString", trim("  SomeString"));
    ASSERT_EQ("SomeString", trim("   SomeString"));
}

TEST(trim, PostSpaces) {
    ASSERT_EQ("SomeString", trim("SomeString "));
    ASSERT_EQ("SomeString", trim("SomeString   "));
    ASSERT_EQ("SomeString", trim("SomeString     "));
}

TEST(trim, PrePostSpaces) {
    ASSERT_EQ("Some String", trim(" Some String "));
    ASSERT_EQ("Some String", trim("  Some String   "));
    ASSERT_EQ("Some String", trim(" Some String     "));
}

TEST(list_directory, NotEmpty) {
    // not sure how to test this function
    vector<string> files = list_directory(".");
    ASSERT_NE(0, files.size());
}
