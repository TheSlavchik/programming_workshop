#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

void test_1()
{
    List *list = make_list();

    add_to_end(5, list);
    add_to_start(228, list);
    add_to_end(6, list);
    add_by_id(4, 1, list);

    assert(find_by_id(0, list)->data == 228);
    assert(find_by_id(1, list)->data == 4);
    assert(find_by_id(2, list)->data == 5);
    assert(find_by_id(3, list)->data == 6);
}

void test_2()
{
    List *list = make_list();

    add_to_end(5, list);
    add_to_start(228, list);
    add_to_end(6, list);
    add_by_id(4, 1, list);

    assert(count(list) == 4);

    delete (228, list);

    assert(count(list) == 3);
    assert(find_by_id(0, list)->data == 4);
}

void test_3()
{
    List *list = make_list();

    assert(find_by_id(0, list) == NULL);

    add_to_end(5, list);

    assert(find_by_id(5, list) == NULL);
}

void test_4()
{
    List *list = make_list();

    add_to_end(5, list);

    assert(delete (7, list) == -1);
    assert(delete (5, list) == 0);
}

void test_5()
{
    List *list = make_list();

    add_to_end(5, list);

    assert(add_by_id(7, 5, list) == -2);
    assert(add_by_id(7, 1, list) == 0);
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();

    return 0;
}