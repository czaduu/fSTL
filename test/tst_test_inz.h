#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../lib/WrappedSequenceContainer.h"
#include <chrono>

using namespace testing;

TEST(vectorMultipleOperation, vectorReduceLeftWithMiltiplyOperation)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                            .reduceLeft([] (int i, int j) {return i * j;});

    auto i = (1 * 2 * 3 * 4 * 5);

    ASSERT_EQ(v, i);
}


TEST(vectorMultipleOperation, vectorReduceLeftWithSubstractionOperation)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                            .reduceLeft([] (int i, int j) {return i - j;});

    auto i = (1 - 2 - 3 - 4 - 5);

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorReduceRightWithMiltiplyOperation)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                            .reduceRight([] (int i, int j) {return i * j;});

    auto i = (5 * 4 * 3 * 2 * 1);

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorReduceRightWithSubstractionOperation)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                            .reduceRight([] (int i, int j) {return i - j;});

    auto i = (5 - 4 - 3 - 2 - 1);

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorReduceLeftWithFindingMin)
{
    std::vector<int> vect = {5,2,1,4,3};
    auto min = wrap(vect)
                            .reduceLeft([] (int i, int j) {return std::min(i,j);});

    auto expectedMin = std::min_element(std::begin(vect), std::end(vect));

    ASSERT_EQ(min, *expectedMin);
}

TEST(vectorMultipleOperation, vectorReduceLeftWithFindingMax)
{
    std::vector<int> vect = {5,2,1,4,3};
    auto max = wrap(vect)
                            .reduceLeft([] (int i, int j) {return std::max(i,j);});

    auto expectedMax = std::max_element(std::begin(vect), std::end(vect));

    ASSERT_EQ(max, *expectedMax);
}

TEST(vectorMultipleOperation, vectorFilterAndReduceLeftWithMiltiplyOperation)
{
    std::vector<int> vect = {5,2,1,4,3};
    auto v = wrap(vect)
                            .filter([] (int i) {return i>2;})
                            .reduceLeft([] (int i, int j) {return (i*j);});

    auto i = (3 * 4 * 5);

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorFilterAndSize)
{
    std::vector<int> vect = {5,2,1,4,3};
    auto v = wrap(vect)
                            .filter([] (int i) {return i>3;})
                            .size();

    size_t i = 2;

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorMapToStringAndReduceLeftToConcate)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                            .map([](auto i) {return std::to_string(i);})
                            .reduceLeft([] (std::string lhs, std::string rhs) {return lhs + "_" + rhs;});

    auto i = "1_2_3_4_5";

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorReverseAndMapToStringAndReduceLeftToConcate)
{
    std::vector<int> vect = {1,2,3,4,5};
    auto v = wrap(vect)
                       .reverse()
                       .map([](auto i) {return std::to_string(i);})
                       .reduceLeft([] (std::string lhs, std::string rhs) {return lhs + "_" + rhs;});

    auto i = "5_4_3_2_1";

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorGroupByResultOfPotentiation)
{
    std::ostringstream oss;
    std::vector<int> vect = {1,2,-1,-2};
    auto v = wrap(vect)
                        .groupBy([](int i) {return i*i;});

    for(const auto& pair : v)
    {
        oss << "key: " << pair.first << " value: [ " ;
        for( double d : pair.second ) oss << d << " " ;
        oss << "]\n" ;
    }

    std::string i = "key: 1 value: [ 1 -1 ]\nkey: 4 value: [ 2 -2 ]\n";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, vectorGroupByResultOfCompareOperation)
{
    std::ostringstream oss;
    std::vector<int> vect = {1,2,11,20};
    auto v = wrap(vect)
                        .groupBy([](int i) {return i>10;});

    for(const auto& pair : v)
    {
        oss << "key: " << pair.first << " value: [ " ;
        for( double d : pair.second ) oss << d << " " ;
        oss << "]\n" ;
    }

    std::string i = "key: 0 value: [ 1 2 ]\nkey: 1 value: [ 11 20 ]\n";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, vectorOfPairsGroupByResultOfCompareOperation)
{
    std::ostringstream oss;
    std::vector<std::pair<std::string, int>> vect = { {"Justin", 0}, {"Matt", 4}, {"Brandon", 3}, {"Charles", 0} };

    auto v = wrap(vect)
                        .groupBy([](auto i) {return i.second > 0 ;});

    for(const auto& pair : v)
    {
        oss << "key: " << pair.first << " value: [ " ;
        for( auto d : pair.second ) oss << d.first << " " ;
        oss << "]\n" ;
    }

    std::string i = "key: 0 value: [ Justin Charles ]\nkey: 1 value: [ Matt Brandon ]\n";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, vectorOfPairsGroupByWorkplace)
{
    std::ostringstream oss;
    std::vector<std::pair<std::string, std::string>> vect = { {"layer", "Justin"}, {"doctor", "Matt"}, {"salesman", "Brandon"}, {"layer", "Charles"}, {"doctor", "Tim"} };

    auto v = wrap(vect)
                        .groupBy([](auto i) {return i.first;});

    for(const auto& pair : v)
    {
        oss << "workplace: " << pair.first << " names: [ " ;
        for( auto d : pair.second ) oss << d.second << " " ;
        oss << "]\n" ;
    }

    std::string i = "workplace: doctor names: [ Matt Tim ]\nworkplace: layer names: [ Justin Charles ]\nworkplace: salesman names: [ Brandon ]\n";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, vectorFlatMap)
{
    std::vector<int> vect = {1, 2, 3, 4};

    auto v = wrap(vect)
                .flatMap([](int i) {return std::vector{i-1, i, i+1};})
                .map([](auto i) {return std::to_string(i);})
                .reduceLeft([] (std::string lhs, std::string rhs) {return lhs + "_" + rhs;});

    std::string i = "0_1_2_1_2_3_2_3_4_3_4_5";

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, vectorFlatMap2)
{
    std::vector<int> vect = {1, 2, 3};

    auto v = wrap(vect)
                .flatMap([](int i) {return std::vector{std::to_string(i-1), std::to_string(i), std::to_string(i+1)};})
                .reduceLeft([] (std::string lhs, std::string rhs) {return lhs + "_" + rhs;});

    std::string i = "0_1_2_1_2_3_2_3_4";

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, exceptionVectorEmpty)
{
    std::vector<int> vect = {};

    EXPECT_THROW(wrap(vect), std::invalid_argument);
}

TEST(vectorMultipleOperation, vectorUnwrapping)
{
    std::vector<int> vect = {5,2,1,4,3};

    auto v = wrap(vect).filter([] (int i) {return i>2;});
    vect = v.unWrap();

    std::vector<int> i = {5,4,3};
    ASSERT_EQ(vect, i);
}

TEST(vectorMultipleOperation, mapReduceFirst)
{
    std::string s = "An eye for an eye and a tooth for a tooth";
    std::string delimiter = " ";
    std::vector<std::string> vect = {};

    std::string word = "";
    for (auto x : s)
       if (x == ' ')
       {
           vect.emplace_back(word);
           word = "";
       }
       else
           word = word + x;
    vect.emplace_back(word);
    //std::vector<std::string> vect = {"An", "eye", "for", "an", "eye", "and", "a",
    //                                 "tooth", "for", "a", "tooth"};
    auto a = count(wrap(vect).
                                  groupBy([](auto i) {return i.length();} )
                       );

    std::ostringstream oss;
    for(const auto& pair : a)
    {
        oss << "" << pair.first << ":" << pair.second << " " ;
    }

    std::string i = "1:2 2:2 3:5 5:2 ";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, mapReduceSecond)
{
    std::string s = "Deer Bear River Car Car River Car Bear";
    std::string delimiter = " ";
    std::vector<std::string> vect = {};

    std::string word = "";
    for (auto x : s)
       if (x == ' ')
       {
           vect.emplace_back(word);
           word = "";
       }
       else
           word = word + x;
    vect.emplace_back(word);

    auto a = count(wrap(vect)
                                 .groupBy([](auto i) {return i;} )
                       );

    std::ostringstream oss;
    for(const auto& pair : a)
    {
        oss << "" << pair.first << ":" << pair.second << " " ;
    }

    std::string i = "Bear:2 Car:3 Deer:1 River:2 ";

    ASSERT_EQ(oss.str(), i);
}

TEST(vectorMultipleOperation, solution1)
{
    std::vector<int> vec = {1,2,3,4,5};
    auto v = wrap(vec)
                       .map([](auto i) {return std::to_string(i);})
                       .reduceLeft([] (auto l, auto r){return l + "," + r;});

    std::string i = "1,2,3,4,5";

    ASSERT_EQ(v, i);
}

TEST(vectorMultipleOperation, solution2int)
{
    std::vector<int> vec = {1,3,4};
    auto result = wrap(vec)
                          .filter([] (auto i) {return i%2;})
                          .filter([] (auto i) {return i>1;})
                          .filter([] (auto i) {return i<5;});

    size_t i = 1;

    ASSERT_EQ(result.size(), i);
}

TEST(vectorMultipleOperation, solution2string)
{
    std::vector<std::string> vec = {"Hello", "World", "!"};
    auto result = wrap(vec)
                          .filter([] (auto i) {return i.length()>3;})
                          .filter([] (auto i) {return i>"Hello";});

    size_t i = 1;

    ASSERT_EQ(result.size(), i);
}
