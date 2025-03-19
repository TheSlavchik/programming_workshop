#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *create_node(int data)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
    {
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List *create_list()
{
    List *list = malloc(sizeof(List));

    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    return list;
}

void add_to_start(int data, List *list)
{
    Node *new = create_node(data);

    if (list == NULL)
    {
        list = create_list();
    }

    new->next = list->head;
    list->head = new;
}

void add_to_end(int data, List *list)
{
    Node *current = NULL;

    if (list->head == NULL)
    {
        list->head = create_node(data);
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = create_node(data);
    }
}

int add_by_id(int data, int id, List *list)
{
    if (list == NULL)
    {
        return EMPTY_LIST;
    }

    if (id < 0)
    {
        return NEGATIVE_ID;
    }

    if (id == 0)
    {
        add_to_start(data, list);
        return 0;
    }

    Node *new = create_node(data);
    Node *last = list->head;
    Node *prev = NULL;

    for (int i = 0; i < id && last != NULL; i++)
    {
        prev = last;
        last = last->next;

        if (last == NULL)
        {
            if (i + 1 == id)
            {
                prev->next = new;
            }
            else
            {
                return ID_GRAETER_THAN_LENGTH;
            }
        }
    }

    prev->next = new;
    new->next = last;

    return 0;
}

int delete(int data, List *list)
{
    Node *current = list->head;
    Node *previous = current;

    while (current != NULL)
    {
        if (current->data == data)
        {
            previous->next = current->next;
            if (current == list->head)
                list->head = current->next;
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }

    return DATA_NOT_FOUND;
}

Node *find_by_id(int id, List *list)
{
    if (id < 0 || list == NULL || list->head == NULL)
    {
        return NULL;
    }

    Node *last = list->head;
    int i = 0;

    while (i < id && last != NULL)
    {
        last = last->next;
        i++;
    }

    if (last == NULL)
    {
        return NULL;
    }

    return last;
}

int count(List *list)
{
    int count = 0;
    Node *head = list->head;

    while (head != NULL)
    {
        head = head->next;
        count++;
    }

    return count;
}
