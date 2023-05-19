#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../doctest/doctest/doctest.h"
#include "../DoublyLinkedList.hpp"

namespace DoublyLinkedListTests{
    bool constructor_single_parameter()
    {
        DoublyLinkedList<int> list(0);
        return list.length() == 1;
    }
    bool constructor_initializer_list_parameter()
    {
        DoublyLinkedList<int> list({1,2,3,4,5});
        return list.length() == 5;
    }
    bool constructor_copy()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        DoublyLinkedList<int> list2 = list1;
        return list1 == list2;
    }
    bool constructor_move()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        DoublyLinkedList<int> list2(std::move(list1));
        return list1.length()==0 && list2.length()==5;
    }
    bool move_assignment()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        DoublyLinkedList<int> list2({0,0,0});
        list2 = std::move(list1);
        return list1.length()==0 && list2.length()==5;    
    }

    bool add_to_start()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_start(0);
        list1.add_to_start(-1);
        list1.add_to_start(-2);
        list1.add_to_start(-3);
        list1.add_to_start(-4);
        DoublyLinkedList<int> expected({-4,-3,-2,-1,0,1,2,3,4,5});
        return list1==expected;
    }

    bool add_to_end()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        list1.add_to_end(0);
        list1.add_to_end(-1);
        list1.add_to_end(-2);
        list1.add_to_end(-3);
        list1.add_to_end(-4);
        DoublyLinkedList<int> expected({1,2,3,4,5,0,-1,-2,-3,-4});
        return list1==expected;
    }

    bool delete_start()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        list1.delete_start();
        DoublyLinkedList<int> expected({2,3,4,5});
        return list1==expected;   
    }

    bool delete_end()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        DoublyLinkedList<int> expected({1,2,3,4});
        return list1==expected;;
    }

    bool replace_value()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        list1.replace_value(2,100);
        DoublyLinkedList<int> expected({1,2,100,4,5});
        return list1==expected;

    }
    bool sort()
    {
        DoublyLinkedList<int> list1({10,9,8,7,6,5,4,3,2,1,0});
        list1.sort();
        DoublyLinkedList<int> expected({0,1,2,3,4,5,6,7,8,9,10});
        return list1==expected;
    }
    bool first_value()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        return list1.first_value()==1;
    }
    bool last_value()
    {
        DoublyLinkedList<int> list1({1,2,3,4,5});
        return list1.last_value()==5;
    }
}

TEST_CASE("Default Constructor")
{
    DoublyLinkedList<int> list;
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
            DoublyLinkedList<int> expected({0,1,2,3,4});
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
            DoublyLinkedList<int> expected({-4,-3,-2,-1,0});
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
                DoublyLinkedList<int> empty;
                empty=list;
                CHECK(empty.length()==list.length());
            }
            SUBCASE("Empty into non-empty")
            {
                DoublyLinkedList<int> nonEmpty({1,2,3,4,5});
                nonEmpty = list;
                CHECK(nonEmpty.length()==0);
            }
            SUBCASE("Non-empty into empty ")
            {
                DoublyLinkedList<int> nonEmpty({1,2,3,4,5});
                list = nonEmpty;
                CHECK(list.length() == nonEmpty.length());
            }
        }
        SUBCASE("Move")
        {
            DoublyLinkedList<int> list2({0,0,0,0,0});
            list2 = std::move(list);
            CHECK(list2.length()==0);            
        }
    }
}

TEST_CASE("Constructors")
{
    CHECK(DoublyLinkedListTests::constructor_single_parameter() == true);
    CHECK(DoublyLinkedListTests::constructor_initializer_list_parameter() == true);
    CHECK(DoublyLinkedListTests::constructor_copy() == true);
    SUBCASE("Empty Copy Construction")
    {
        DoublyLinkedList<int> list;
        DoublyLinkedList<int> copiedFrom(list);
        CHECK(copiedFrom.length() == list.length());
    }
    CHECK(DoublyLinkedListTests::constructor_move() == true);
    CHECK(DoublyLinkedListTests::move_assignment() == true);
}
TEST_CASE("Copy Assignment")
{
    DoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);

    SUBCASE("Assigning into a list of equal length")
    {
        DoublyLinkedList<int> equal({0,0,0,0,0});
        REQUIRE(equal.length()==list.length());
        equal = list;
        CHECK(equal==list);
    }
    SUBCASE("Assigning into a list of smaller length")
    {
        DoublyLinkedList<int> smaller({0});
        REQUIRE(smaller.length()<list.length());
        smaller = list;
        CHECK(smaller==list);         
    }
    SUBCASE("Assigning into a list of larger length")
    {
        DoublyLinkedList<int> larger({0,0,0,0,0,0,0,0,0,0});
        REQUIRE(larger.length()>list.length());
        larger = list;
        CHECK(larger==list);
    }
}

TEST_CASE("Adding Nodes To Start and End")
{
    CHECK(DoublyLinkedListTests::add_to_start() == true);
    CHECK(DoublyLinkedListTests::add_to_end() == true);
}
TEST_CASE("Arbitrary Insertion Of Nodes")
{
    DoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);
    SUBCASE("Insert at start")
    {
        list.insert(0,0);
        DoublyLinkedList<int> expected({0,1,2,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at end")
    {
        list.insert(0,list.length()-1);
        DoublyLinkedList<int> expected({1,2,3,4,0,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
    SUBCASE("Insert at middle")
    {
        list.insert(0,2);
        DoublyLinkedList<int> expected({1,2,0,3,4,5});
        REQUIRE(expected.length()==6);
        REQUIRE(list.length()==6);
        CHECK(list==expected);
    }
}

TEST_CASE("Deleting Nodes From Start and End")
{
    CHECK(DoublyLinkedListTests::delete_start() == true);
    CHECK(DoublyLinkedListTests::delete_end() == true); 
}

TEST_CASE("Arbitrary Deletion of Nodes")
{
    DoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);   
    SUBCASE("Delete at start")
    {
        list.delete_at(0);
        DoublyLinkedList<int> expected({2,3,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    } 
    SUBCASE("Delete at end")
    {
        list.delete_at(list.length()-1);
        DoublyLinkedList<int> expected({1,2,3,4});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
    SUBCASE("Delete at middle")
    {
        list.delete_at(2);
        DoublyLinkedList<int> expected({1,2,4,5});
        REQUIRE(expected.length()==4);
        REQUIRE(list.length() == 4);
        CHECK(list==expected);
    }
}

TEST_CASE("Swap Values")
{
    DoublyLinkedList<int> list({1,2,3,4,5});
    REQUIRE(list.length()==5);  
    SUBCASE("Index1 is less than index2")
    {
        list.swap_values(0,list.length()-1);
        DoublyLinkedList<int> expected({5,2,3,4,1});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }   
    SUBCASE("Index1 is greater than index2")
    {
        list.swap_values(3,1);
        DoublyLinkedList<int> expected({1,4,3,2,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }
    SUBCASE("Index1 is equal to index2")
    {
        list.swap_values(2,2);
        DoublyLinkedList<int> expected({1,2,3,4,5});
        REQUIRE(expected.length()==5);  
        REQUIRE(list.length()==5);  
        CHECK(list==expected);
    }

}
TEST_CASE("Accessing")
{
    DoublyLinkedList<int> list({1,2,3,4,5});
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
}


TEST_CASE("Other Member Functions")
{
    CHECK(DoublyLinkedListTests::replace_value() == true);
    CHECK(DoublyLinkedListTests::sort() == true);
    CHECK(DoublyLinkedListTests::first_value() == true);
    CHECK(DoublyLinkedListTests::last_value() == true);    
}