// #include "map.h"

// int main(){
//     Map<int, int> m; // Map template will be instanticated here
//     Map<string, string> m; // Map template will be instanticated here
// }

/** 
 * CS515 Assignment 9
 * File: maptest.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 14 April 2022
 * Collaboration Declaration: online resources 
 */ 

/* These are test for map inerface methods using Google Test */
#include "map.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

//The constructor should create a map with zero size
TEST(MapTest, constructorCreatesZeroSizeMap)
{
    Map<string, string> m0;

    EXPECT_EQ(0, m0.size());
}

//Inserting into an empty map should return true and result in a size of one
TEST(MapTest, insertWhileEmptyReturnsTrueAndMapSizeIsOne)
{
    Map<string, string> m1;

    EXPECT_TRUE(m1.insert("TEST", "PASS"));
    EXPECT_EQ(1, m1.size());
}

//Inserting a key that already exists should fail and not change the map size
TEST(MapTest, insertOfSameKeyReturnsFalseAndMapSizeRemainsSame)
{
    /*
        FIXED   (broken 4) Should pass but fails
    */

    Map<string, string> m2;

    m2.insert("TEST", "PASS");

    EXPECT_FALSE(m2.insert("TEST", "FAIL"));
    EXPECT_EQ(1, m2.size());
}

//Accessing an existing item using [] should return correct value and not
//change the map size
TEST(MapTest, indexOperatorOfExistingKeyReturnsProperValueAndSizeIsSame)
{
    Map<string, string> m3;

    m3.insert("TEST0", "PASS0");
    m3.insert("TEST1", "PASS1");
    m3.insert("TEST2", "PASS2");
    m3.insert("TEST3", "PASS3");

    EXPECT_EQ("PASS0", m3["TEST0"]);  
    EXPECT_EQ("PASS1", m3["TEST1"]);
    EXPECT_EQ("PASS2", m3["TEST2"]);
    EXPECT_EQ("PASS3", m3["TEST3"]);
    EXPECT_EQ(4, m3.size());
}

//Using [] to set an item in an empty map should add the item with an
//appropriate value and increase the map size to one
TEST(MapTest, indexOperatorOnEmptyMapProperlySetsValueAndSizeIsOne)
{
    Map<string, string> m4;

    m4["TEST"] = "PASS";

    EXPECT_EQ("PASS", m4["TEST"]);
    EXPECT_EQ(1, m4.size());
}

//Using [] to set an item in a map that already contains other items
//inserts and updates the size appropriately
TEST(MapTest, indexOperatorOnMissingKeyProperlySetsValueAndIncrementsSize)
{
    Map<string, string> m5;

    m5.insert("TEST0", "PASS0");
    m5.insert("TEST1", "PASS1");
    m5.insert("TEST2", "PASS2");
    m5["TEST3"] = "PASS3";

    EXPECT_EQ("PASS3", m5["TEST3"]);
    EXPECT_EQ(4, m5.size());
}

//Erasing a key that exists in the map succeeds and decrements the map size
TEST(MapTest, eraseOfExistingKeyReturnsTrueAndDecrementsSize)
{
    Map<string, string> m6;

    m6.insert("TEST", "ERASE");
    m6.insert("extra", "extra");

    EXPECT_TRUE(m6.erase("TEST"));
    EXPECT_EQ(1, m6.size());
}

//Erase on an empty map fails and keeps the map size at zero
TEST(MapTest, eraseOnEmptyMapReturnsFalseAndSizeRemainsZero)
{
    Map<string, string> m7;

    EXPECT_FALSE(m7.erase("TEST"));
    EXPECT_EQ(0, m7.size());
}

//Erase of a non-existant key fails and does not change the map size
TEST(MapTest, eraseOfMissingKeyReturnsFalseAndSizeRemainsSame)
{
    Map<string, string> m8;

    m8.insert("TEST", "INSERT");

    EXPECT_FALSE(m8.erase("ERASE"));
    EXPECT_EQ(1, m8.size());
}

//Using the copy constructor results in two maps of the same, correct size
TEST(MapTest, copyConstructorMakesCorrectSize)
{
    Map<string, string> m9;

    m9.insert("TEST0", "PASS0");
    m9.insert("TEST1", "PASS1");
    m9.insert("TEST2", "PASS2");

    Map<string, string> m9C (m9);

    EXPECT_EQ(m9.size(), m9C.size());
    EXPECT_EQ(3, m9.size());
    EXPECT_EQ(3, m9C.size());
}

//Using the copy constructor with an existing map makes its own
//copy, such that if the value associated with a key is changed
//in the copy it does not change the associated value in the
//original, and inserts/erases on either won't affect the other.
TEST(MapTest, copyConstructorMakesSeparateCopy)
{
    /*
        (broken 1) Should fail but passes
        (broken 3) Should pass but fails
    */

    Map<string, string> m10;

    m10.insert("TEST0", "PASS0");
    m10.insert("TEST1", "PASS1");
    m10.insert("TEST2", "PASS2");

    // Using the copy constructor with an existing map
    Map<string, string> m10C (m10);

    m10C.insert("TEST2", "CHANGED");

    EXPECT_EQ("PASS2", m10["TEST2"]);
    EXPECT_EQ(3, m10.size());

    m10C.insert("TEST4", "PASS4");

    EXPECT_FALSE(m10.erase("TEST4"));
}

//Using the assignment operator results in two maps of the same, correct size
TEST(MapTest, assignmentOperatorMakesCorrectSize)
{
    /*
        (broken 4) Should fail but passes
    */

    Map<string, string> m11;
    m11.insert("TEST1", "PASS1");

    Map<string, string> m11A;
    m11A.insert("TEST2", "PASS2");
    m11A.insert("TEST3", "PASS3");

    m11 = m11A;

    EXPECT_EQ(m11.size(), m11A.size());
    EXPECT_EQ(2, m11.size());
}

//Using the assignment operator with an existing map makes its own
//copy, such that if the value associated with a key is changed
//in the copy it does not change the associated value in the
//original, and inserts/erases on either won't affect the other.
TEST(MapTest, assignmentMakesSeparateCopy)                                 
{
    /*
        (broken 2) Should fail but passes
        (broken 3) Should pass but fails
        (broken 4) Should fail but passes
    */

    Map<string, string> m12;
    Map<string, string> m12A;

    m12.insert("TEST0", "PASS0");
    m12.insert("TEST1", "PASS1");
    m12.insert("TEST2", "PASS2");

    m12A = m12;

    //compare size
    EXPECT_EQ(m12.size(), m12A.size());

    // maipulate
    m12A["TEST0"] = "ASSIGNMENT";

    EXPECT_EQ("PASS0", m12["TEST0"]);
}

//Using the assignment operator with an existing map with over 1000 items
//makes a copy that has correct keys/values at a couple of places deep within
//the map (values that aren't at either end of the range of keys used).
TEST(MapTest, assignmentWithManyItemsHasCorrectValues)
{
    /*
        (broken 2) Should fail but passes
        (broken 4) Should fail but passes
    */

    Map<string, string> m13;
    Map<string, string> m13A;

    for (size_t i = 0; i < 2500; i++)
        m13.insert(to_string(i), to_string(i));

    m13A = m13;

    
    for (int i = 0; i < 1000; i++)
        EXPECT_EQ(m13[to_string(i)], m13A[to_string(i)]);

    for (int i = 1000; i < 2000; i++)
        EXPECT_EQ(m13[to_string(i)], m13A[to_string(i)]);

    for (int i = 2000; i < 2500; i++)
        EXPECT_EQ(m13[to_string(i)], m13A[to_string(i)]);
}

// TEST(MapTest, findReturnsEndOnEmptyMap)
// {
//     Map<string, string> m14;

//     Map<string, string>::Iterator it = m14.end();
//     EXPECT_EQ(m14.find("key"), it);
// }

// TEST(MapTest, findReturnsEndOnMap)
// {
//     Map<string, string> m15;

//     EXPECT_TRUE(m15.insert("Key", "Value"));

//     Map<string, string>::Iterator it = m15.begin();
//     EXPECT_EQ(m15.find("key"), it);
// }

// TEST(MapTest, iteratorBegin)
// {
//     Map<string, string> m16;

//     EXPECT_TRUE(m16.insert("Key", "Value"));

//     Map<string, string>::Iterator it1 = m16.begin();
//     Map<string, string>::Iterator it2 = m16.end();

//     EXPECT_NE(it1, it2);
// }

// TEST(MapTest, iteratorEnd)
// {
//     Map<string, string> m17;

//     //EXPECT_EQ(m17.begin(), 0);
// }

// TEST(MapTest, iteratorDereferenceOperatorOnEmptyMap)
// {
//     Map<string, string> m18;

//     Map<string, string>::Iterator it1 = m18.begin();
//     Map<string, string>::Iterator it2 = m18.end();

//     EXPECT_EQ((*it1).data, (*it2).data);
// }

// TEST(MapTest, iteratorPointerOperator)
// {
//     Map<string, string> m19;

//     Map<string, string>::Iterator it1 = m19.begin();
//     Map<string, string>::Iterator it2 = m19.end();

//     EXPECT_EQ(it1->data, it2->data);
// }

// TEST(MapTest, iteratorEqualityOperator)
// {
//     Map<string, string> m20;

//     Map<string, string>::Iterator it1 = m20.begin();
//     Map<string, string>::Iterator it2 = m20.end();

//     EXPECT_TRUE(it1 == it2);
// }

// TEST(MapTest, iteratorInequalityOperator)
// {
//     Map<string, string> m21;

// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

