#include <gtest/gtest.h>
#include "dna.h"

TEST(dna, constructor) {
    dna d;
    EXPECT_EQ(d.size(), 2);
    for (int i = 0; i < d.size(); i++) {
        EXPECT_EQ(d.at(i), 'X');
    }
    EXPECT_EQ(d.toString(), "XX");
    EXPECT_EQ(d.isLinked(), true);
    // TO DO: write lots of assertions here.
}

TEST(dna, secondConstructor) {
    string dnastr = "AGATC";
    dna d(dnastr);
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), dnastr);
    EXPECT_EQ(d.size(), dnastr.length());
    // TO DO: write lots of assertions here.
}

TEST(dna, emptyString) {
    string str = "";
    dna d(str);
    EXPECT_EQ(d.size(), 0);
}
TEST(dna, size) {
    // TO DO: write lots of assertions here.
}

TEST(dna, toString) {
    // TO DO: write lots of assertions here.
    string str = "ABCABCABC";
    dna d(str);
    EXPECT_EQ(d.toString(), str);
}

TEST(dna, at) {
    string str = "AAAAAA";
    dna d(str);
    for (int i = 0; i < d.size(); i++) {
        EXPECT_EQ(d.at(i), 'A');
    }
}

TEST(dna, clear) {
    // TO DO: write lots of assertions here.
}

TEST(dna, copyConstructor) {
    string str = "ABCABC";
    dna d1(str);
    dna d2(d1);
    EXPECT_EQ(d1.size(), d2.size());
    // TO DO: write lots of assertions here.
}

TEST(dna, equalsOperator) {
    string str = "AGTG";
    string str2 = "AGTG";
    dna d1(str);
    dna d2(str2);
    EXPECT_EQ(d1==d2, true);
}

TEST(dna, equalsOperator2) {
    string str = "";
    string str2 = "";
    dna d1(str);
    dna d2(str2);
    EXPECT_EQ(d1==d2, true);
}

TEST(dna, equalsOperator3) {
    string str = "AGT";
    string str2 = "";
    dna d1(str);
    dna d2(str2);
    EXPECT_EQ(d1==d2, false);
}


TEST(dna, splice) {
    string str1 = "CATAAAAA";
    dna d1(str1);
    string str21 = "CAT";
    dna d2(str21);
    EXPECT_EQ(d1.splice(d2), true);
    EXPECT_EQ(d1.size(), 5);
    for (int i = 0; i < d1.size(); i++) {
        EXPECT_EQ(d1.at(i), 'A');
    }
    
     string str2 = "AACATAAA";
    dna d3(str2);
    string str22 = "CAT";
    dna d4(str22);
    EXPECT_EQ(d3.splice(d4), true);
    EXPECT_EQ(d3.size(), 5);
    for (int i = 0; i < d1.size(); i++) {
        EXPECT_EQ(d1.at(i), 'A');
    }
    
     string str3 = "CACATATA";
    dna d5(str3);
    string str23 = "CAT";
    dna d6(str23);
    EXPECT_EQ(d5.splice(d6), true);
    EXPECT_EQ(d5.size(), 5);

}

// TO DO: write more tests here too.  
