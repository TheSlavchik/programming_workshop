#include "linked_list.h"
#include <stdlib.h>

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List *make_list()
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
    if (list == NULL || id < 0)
    {
        return -1;
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
                return -2;
            }
        }
    }

    prev->next = new;
    new->next = last;

    return 0;
}

int delete(int data, List *list)
{
    Node *current_node = list->head;
    Node *previous_node = current_node;

    while (current_node != NULL)
    {
        if (current_node->data == data)
        {
            previous_node->next = current_node->next;

            if (current_node == list->head)
            {
                list->head = current_node->next;
            }

            free(current_node);

            return 0;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }

    return -1;
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

void clear(List *list)
{
    Node *current_node = list->head;
    Node *next_node = current_node;

    while (next_node != NULL)
    {
        next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }

    free(list);
}