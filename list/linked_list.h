typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
} List;

List *make_list();
void add_to_start(int data, List *list);
void add_to_end(int data, List *list);
int add_by_id(int data, int id, List *list);
int delete(int data, List *list);
Node *find_by_id(int id, List *list);
int count(List *list);