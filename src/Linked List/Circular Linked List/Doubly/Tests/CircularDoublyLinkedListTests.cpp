#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../../doctest/doctest/doctest.h"
#include "../CircularDoublyLinkedList.hpp"

namespace CircularDoublyLinkedListTests{
    bool constructor_single_parameter()
    {
        CircularDoublyLinkedList<int> list(0);
        return list.length() == 1;
    }
    bool constructor_initializer_list_parameter()
    {
        CircularDoublyLinkedList<int> list({1,2,3,4,5});
        return list.length() == 5;
    }
    bool constructor_copy()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        CircularDoublyLinkedList<int> list2 = list1;
        return list1 == list2;
    }
    bool constructor_move()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        CircularDoublyLinkedList<int> list2(std::move(list1));
        return list1.length()==0 && list2.length()==5;
    }
    bool move_assignment()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        CircularDoublyLinkedList<int> list2({0,0,0});
        list2 = std::move(list1);
        return list1.length()==0 && list2.length()==5;    
    }

    bool add_to_start()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_start(0);
        list1.add_to_start(-1);
        list1.add_to_start(-2);
        list1.add_to_start(-3);
        list1.add_to_start(-4);
        CircularDoublyLinkedList<int> expected({-4,-3,-2,-1,0,1,2,3,4,5});
        return list1==expected;
    }

    bool add_to_end()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_end(0);
        list1.add_to_end(-1);
        list1.add_to_end(-2);
        list1.add_to_end(-3);
        list1.add_to_end(-4);
        CircularDoublyLinkedList<int> expected({1,2,3,4,5,0,-1,-2,-3,-4});
        return list1==expected;
    }

    bool replace_value()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        list1.replace_value(2,100);
        CircularDoublyLinkedList<int> expected({1,2,100,4,5});
        return list1==expected;

    }
    bool sort()
    {
        CircularDoublyLinkedList<int> list1({10,9,8,7,6,5,4,3,2,1,0});
        list1.sort();
        CircularDoublyLinkedList<int> expected({0,1,2,3,4,5,6,7,8,9,10});
        return list1==expected;
    }
    bool first_value()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        return list1.first_value()==1;
    }
    bool last_value()
    {
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        return list1.last_value()==5;
    }
}

TEST_CASE("Default Constructor")
{
    CircularDoublyLinkedList<int> list;
    REQUIRE(list.length()==0);
    SUBCASE("Adding nodes")
    {
        SUBCASE("To End")
        {
            list.add_to_end(0);
            list.add_to_end(1);
            list.add_to_end(2);
            list.add_to_end(3);
            list.add_to_end(4);        
            CircularDoublyLinkedList<int> expected({0,1,2,3,4});
            REQUIRE(expected.length() == list.length());
            CHECK(list==expected);
        }
        SUBCASE("To Start")
        {
            list.add_to_start(0);
            list.add_to_start(-1);
            list.add_to_start(-2);
            list.add_to_start(-3);
            list.add_to_start(-4);        
            CircularDoublyLinkedList<int> expected({-4,-3,-2,-1,0});
            REQUIRE(expected.length() == list.length());
            CHECK(list==expected);            
        }
    }
    SUBCASE("Deleting nodes")
    {
        list.add_to_end(0);
        list.add_to_end(1);
        list.add_to_end(2);
        list.add_to_end(3);
        list.add_to_end(4);   
        list.delete_end();  
        list.delete_end();             
        list.delete_end();             
        list.delete_end();             
        list.delete_end();             
        CHECK(list.length() == 0);
    }
    SUBCASE("Assigning")
    {
        SUBCASE("Copy")
        {
            SUBCASE("Empty into empty")
            {
                CircularDoublyLinkedList<int> empty;
                empty=list;
                CHECK(empty.length()==list.length());
            }
            SUBCASE("Empty into non-empty")
            {
                CircularDoublyLinkedList<int> nonEmpty({1,2,3,4,5});
                nonEmpty = list;
                CHECK(nonEmpty.length()==0);
            }
            SUBCASE("Non-empty into empty ")
            {
                CircularDoublyLinkedList<int> nonEmpty({1,2,3,4,5});
                list = nonEmpty;
                CHECK(list.length() == nonEmpty.length());
            }
        }
        SUBCASE("Move")
        {
            CircularDoublyLinkedList<int> list2({0,0,0,0,0});
            list2 = std::move(list);
            CHECK(list2.length()==0);            
        }
    }
}

TEST_CASE("Constructors")
{
    CHECK(CircularDoublyLinkedListTests::constructor_single_parameter() == true);
    CHECK(CircularDoublyLinkedListTests::constructor_initializer_list_parameter() == true);
    CHECK(CircularDoublyLinkedListTests::constructor_copy() == true);
    SUBCASE("Empty Copy Construction")
    {
        CircularDoublyLinkedList<int> list;
        CircularDoublyLinkedList<int> copiedFrom(list);
        CHECK(copiedFrom.length() == list.length());
    }    
    CHECK(CircularDoublyLinkedListTests::constructor_move() == true);
    CHECK(CircularDoublyLinkedListTests::move_assignment() == true);
}
TEST_CASE("Copy Assignment")
{
    CircularDoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);

    SUBCASE("Assigning into a list of equal length")
    {
        CircularDoublyLinkedList<int> equal({0,0,0,0,0});
        REQUIRE(equal.length()==list.length());
        equal = list;
        CHECK(equal==list);
    }
    SUBCASE("Assigning into a list of smaller length")
    {
        CircularDoublyLinkedList<int> smaller({0});
        REQUIRE(smaller.length()<list.length());
        smaller = list;
        CHECK(smaller==list);         
    }
    SUBCASE("Assigning into a list of larger length")
    {
        CircularDoublyLinkedList<int> larger({0,0,0,0,0,0,0,0,0,0});
        REQUIRE(larger.length()>list.length());
        larger = list;
        CHECK(larger==list);
    }
}

TEST_CASE("Adding Nodes To Start and End")
{
    CHECK(CircularDoublyLinkedListTests::add_to_start() == true);
    CHECK(CircularDoublyLinkedListTests::add_to_end() == true);
}
TEST_CASE("Arbitrary Insertion Of Nodes")
{
    CircularDoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);
    SUBCASE("Insert at start")
    {
        list.insert(0,0);
        CircularDoublyLinkedList<int> expected({0,1,2,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at end")
    {
        list.insert(0,list.length()-1);
        CircularDoublyLinkedList<int> expected({1,2,3,4,0,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at middle")
    {
        list.insert(0,2);
        CircularDoublyLinkedList<int> expected({1,2,0,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
}

TEST_CASE("Deleting Nodes From Start")
{
        CircularDoublyLinkedList<int> list1({1,2,3,4,5});
        list1.delete_start();
        CircularDoublyLinkedList<int> expected({2,3,4,5});
        CHECK(list1==expected); 
}
TEST_CASE("Deleting Nodes From End")
{
    CircularDoublyLinkedList<int> list1({1,2,3,4,5});
    list1.delete_end();
    CircularDoublyLinkedList<int> expected({1,2,3,4});
    CHECK(list1==expected);
}


TEST_CASE("Arbitrary Deletion of Nodes")
{
    CircularDoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);   
    SUBCASE("Delete at start")
    {
        list.delete_at(0);
        CircularDoublyLinkedList<int> expected({2,3,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    } 
    SUBCASE("Delete at end")
    {
        list.delete_at(list.length()-1);
        CircularDoublyLinkedList<int> expected({1,2,3,4});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
    SUBCASE("Delete at middle")
    {
        list.delete_at(2);
        CircularDoublyLinkedList<int> expected({1,2,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
}

TEST_CASE("Swap Values")
{
    CircularDoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);  
    SUBCASE("Index1 is less than index2")
    {
        list.swap_values(0,list.length()-1);
        CircularDoublyLinkedList<int> expected({5,2,3,4,1});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }   
    SUBCASE("Index1 is greater than index2")
    {
        list.swap_values(3,1);
        CircularDoublyLinkedList<int> expected({1,4,3,2,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }
    SUBCASE("Index1 is equal to index2")
    {
        list.swap_values(2,2);
        CircularDoublyLinkedList<int> expected({1,2,3,4,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }

}
TEST_CASE("Accessing")
{
    CircularDoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);  
    SUBCASE("Access Start")
    {
        CHECK(list.access_from_start(0)==1);
    }
    SUBCASE("Access End")
    {
        CHECK(list.access_from_end(list.length()-1)==5);
    }
    SUBCASE("Access Middle")
    {
        CHECK(list.access_from_start(2)==3);
    }
    // SUBCASE("Access circularly positive")
    // {
    //     CHECK(list.access(11)==2);
    // }
    // SUBCASE("Accessing circularly negative")
    // {
    //     CHECK(list.access(-14)==2);
    // }
}


TEST_CASE("Other Member Functions")
{
    CHECK(CircularDoublyLinkedListTests::replace_value() == true);
    CHECK(CircularDoublyLinkedListTests::sort() == true);
    CHECK(CircularDoublyLinkedListTests::first_value() == true);
    CHECK(CircularDoublyLinkedListTests::last_value() == true);    
}