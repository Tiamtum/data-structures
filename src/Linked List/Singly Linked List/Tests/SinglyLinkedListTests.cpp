#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../../doctest/doctest/doctest.h"
#include "../SinglyLinkedList.hpp"

//testing functions
size_t constructor_single_parameter()
{
    SinglyLinkedList<int> list(0);
    return list.length();
}
size_t constructor_initializer_list_parameter()
{
    SinglyLinkedList<int> list({1,2,3,4,5});
    return list.length();
}
bool constructor_copy()
{
    SinglyLinkedList<int> list1({1,2,3,4,5});
    SinglyLinkedList<int> list2 = list1;
    return list1 == list2;

}


TEST_CASE("Testing Singly Linked List Functions")
{
    CHECK(constructor_single_parameter() == 1);
    CHECK(constructor_initializer_list_parameter() == 5);
    CHECK(constructor_copy() == true);

}

