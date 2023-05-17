#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../../doctest/doctest/doctest.h"
#include "../CircularSinglyLinkedList.hpp"

namespace CircularSinglyLinkedListTests
{
    bool constructor_single_parameter()
    {
        CircularSinglyLinkedList<int> list(0);
        return list.length() == 1;
    }
    bool constructor_initializer_list_parameter()
    {
        CircularSinglyLinkedList<int> list({1,2,3,4,5});
        return list.length() == 5;
    }
    bool constructor_copy()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        CircularSinglyLinkedList<int> list2 = list1;
        return list1 == list2;
    }
    bool constructor_move()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        CircularSinglyLinkedList<int> list2(std::move(list1));
        return list1.length()==0 && list2.length()==5;
    }
    bool move_assignment()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        CircularSinglyLinkedList<int> list2({0,0,0});
        list2 = std::move(list1);
        return list1.length()==0 && list2.length()==5;    
    }

    bool add_to_start()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_start(0);
        list1.add_to_start(-1);
        list1.add_to_start(-2);
        list1.add_to_start(-3);
        list1.add_to_start(-4);
        CircularSinglyLinkedList<int> expected({-4,-3,-2,-1,0,1,2,3,4,5});
        return list1==expected;
    }

    bool add_to_end()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_end(0);
        list1.add_to_end(-1);
        list1.add_to_end(-2);
        list1.add_to_end(-3);
        list1.add_to_end(-4);
        CircularSinglyLinkedList<int> expected({1,2,3,4,5,0,-1,-2,-3,-4});
        return list1==expected;
    }

    bool delete_start()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        list1.delete_start();
        CircularSinglyLinkedList<int> expected({2,3,4,5});
        return list1==expected;   
    }

    bool delete_end()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        CircularSinglyLinkedList<int> expected({1,2,3,4});
        return list1==expected;;
    }

    bool replace_value()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        list1.replace_value(2,100);
        CircularSinglyLinkedList<int> expected({1,2,100,4,5});
        return list1==expected;

    }

    bool sort()
    {
        CircularSinglyLinkedList<int> list1({10,9,8,7,6,5,4,3,2,1,0});
        list1.sort();
        CircularSinglyLinkedList<int> expected({0,1,2,3,4,5,6,7,8,9,10});
        return list1==expected;
    }
    bool first_value()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        return list1.first_value()==1;
    }
    bool last_value()
    {
        CircularSinglyLinkedList<int> list1({1,2,3,4,5});
        return list1.last_value()==5;
    }
}


TEST_CASE("Constructors")
{
    CHECK(CircularSinglyLinkedListTests::constructor_single_parameter() == true);
    CHECK(CircularSinglyLinkedListTests::constructor_initializer_list_parameter() == true);
    CHECK(CircularSinglyLinkedListTests::constructor_copy() == true);
    CHECK(CircularSinglyLinkedListTests::constructor_move() == true);
    CHECK(CircularSinglyLinkedListTests::move_assignment() == true);
}
TEST_CASE("Copy Assignment")
{
    CircularSinglyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);
    SUBCASE("Assigning into a list of equal length")
    {
        CircularSinglyLinkedList<int> equal({0,0,0,0,0});
        REQUIRE(equal.length()==list.length());
        equal = list;
        CHECK(equal==list);
    }
    SUBCASE("Assigning into a list of smaller length")
    {
        CircularSinglyLinkedList<int> smaller({0});
        REQUIRE(smaller.length()<list.length());
        smaller = list;
        CHECK(smaller==list);        
    }
    SUBCASE("Assigning into a list of larger length")
    {
        CircularSinglyLinkedList<int> larger({0,0,0,0,0,0,0,0,0,0});
        REQUIRE(larger.length()>list.length());
        larger = list;
        CHECK(larger==list);
    }
}

TEST_CASE("Adding Nodes To Start and End")
{
    CHECK(CircularSinglyLinkedListTests::add_to_start() == true);
    CHECK(CircularSinglyLinkedListTests::add_to_end() == true);
}
TEST_CASE("Arbitrary Insertion Of Nodes")
{
    CircularSinglyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);
    SUBCASE("Insert at start")
    {
        list.insert(0,0);
        CircularSinglyLinkedList<int> expected({0,1,2,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at end")
    {
        list.insert(0,list.length()-1);
        CircularSinglyLinkedList<int> expected({1,2,3,4,0,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at middle")
    {
        list.insert(0,2);
        CircularSinglyLinkedList<int> expected({1,2,0,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }

}
TEST_CASE("Deleting Nodes From Start and End")
{
    CHECK(CircularSinglyLinkedListTests::delete_start() == true);
    CHECK(CircularSinglyLinkedListTests::delete_end() == true);  
}

TEST_CASE("Arbitrary Deletion of Nodes")
{
    CircularSinglyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);   
    SUBCASE("Delete at start")
    {
        list.delete_at(0);
        CircularSinglyLinkedList<int> expected({2,3,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    } 
    SUBCASE("Delete at end")
    {
        list.delete_at(list.length()-1);
        CircularSinglyLinkedList<int> expected({1,2,3,4});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
    SUBCASE("Delete at middle")
    {
        list.delete_at(2);
        CircularSinglyLinkedList<int> expected({1,2,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
}

TEST_CASE("Swap Values")
{
    CircularSinglyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);  
    SUBCASE("Index1 is less than index2")
    {
        list.swap_values(0,list.length()-1);
        CircularSinglyLinkedList<int> expected({5,2,3,4,1});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }   
    SUBCASE("Index1 is greater than index2")
    {
        list.swap_values(3,1);
        CircularSinglyLinkedList<int> expected({1,4,3,2,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }
    SUBCASE("Index1 is equal to index2")
    {
        list.swap_values(2,2);
        CircularSinglyLinkedList<int> expected({1,2,3,4,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }

}

TEST_CASE("Accessing")
{
    CircularSinglyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);  
    SUBCASE("Access Start")
    {
        CHECK(list.access(0)==1);
    }
    SUBCASE("Access End")
    {
        CHECK(list.access(list.length()-1)==5);
    }
    SUBCASE("Access Middle")
    {
        CHECK(list.access(2)==3);
    }
    SUBCASE("Access circularly positive")
    {
        CHECK(list.access(11)==2);
    }
    SUBCASE("Accessing circularly negative")
    {
        CHECK(list.access(-14)==2);
    }
}

TEST_CASE("Other Member Functions")
{
    CHECK(CircularSinglyLinkedListTests::replace_value() == true);
    CHECK(CircularSinglyLinkedListTests::sort() == true);
    CHECK(CircularSinglyLinkedListTests::first_value() == true);
    CHECK(CircularSinglyLinkedListTests::last_value() == true);    
}

