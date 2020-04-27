#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
typedef struct
{
    float xmin;
    float ymin;
    float xmax;
    float ymax;
    float score;
} Bbox;

struct list_node
{
    Bbox *val;
    struct list_node *next, *prev;
};

typedef struct list_node *ptr_to_node;
typedef ptr_to_node List;
typedef ptr_to_node Node;
List initial_list();
Node Delete(Node node);
void Insert(Bbox *box, List L);
void printlist();
void print_box(float *bbox);
bool sort_score(Bbox *box1, Bbox *box2);
float iou(Bbox *box1, Bbox *box2);

int NMS(Bbox *input)
{
    List head = initial_list();
    List cur = head;
#if 1
    for (int i = 0; i < 200; i++)
    {
        if (input[i].score > 0.1)
        {
            Insert(&input[i], cur);
            cur = cur->next;
        }
    }
#else

#endif
    //printlist(head);
    List posi = head->next;
    while (posi->next != NULL)
    {
        Node temp = posi->next;
        while (temp->next != NULL)
        {
            //printf("temp_val:%d\n", temp->val);
            if (iou((temp->val), (posi->val)) > 0.45)
            {
                //printf("%f\n", iou((temp->val), (posi->val)));
                temp = Delete(temp);
            }
            if (temp->next != NULL)
                temp = temp->next;
        }

        if (iou((temp->val), (posi->val)) > 0.45)
            Delete(temp);
        //break;
        if (posi->next != NULL)
            posi = posi->next;
    }
    printf("Result\n");
    printlist(head);
    return 0;
}

List initial_list()
{
    List ini = (List)malloc(sizeof(struct list_node));
    ini->next = ini;
    ini->prev = ini;
    ini->val = NULL;
    return ini;
}

void Insert(Bbox *val, List L)
{
    Node temp = (Node)malloc(sizeof(struct list_node));
    L->next = temp;
    temp->next = NULL;
    temp->prev = L;
    temp->val = val;
}

Node Delete(Node node)
{
    Node prev = node->prev;
    Node cur = prev->next;
    node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    free(cur);
    return prev;
}

void printlist(List L)
{
    int count = 0;
    Node cur = L;
    cur = cur->next;
    while (cur->next != NULL)
    {
        count++;
        print_box(&(cur->val->xmin));
        cur = cur->next;
    }
    count++;
    print_box(&(cur->val->xmin));
    printf("The total count: %d\n", count);
}

void print_box(float *bbox)
{
    for (float *temp = bbox; temp < bbox + sizeof(Bbox) / sizeof(float); temp++)
        printf("%2f\t", *(float *)temp);
    printf("\n");
}

bool sort_score(Bbox *box1, Bbox *box2)
{
    return (box1->score > box2->score);
}

float iou(Bbox *box1, Bbox *box2)
{
    float x1 = MAX(box1->xmin, box2->xmin);
    float y1 = MAX(box1->ymin, box2->ymin);
    float x2 = MIN((box1->xmax), (box2->xmax));
    float y2 = MIN((box1->ymax), (box2->ymax));

    if (x2 < x1)
        return 0;
    float over_area = (x2 - x1) * (y2 - y1);

    float box1_w = (box1->xmax - box1->xmin);
    float box1_h = (box1->ymax - box1->ymin);
    float box2_w = (box2->xmax - box2->xmin);
    float box2_h = (box2->ymax - box2->ymin);

    float iou = over_area / (box1_w * box1_h + box2_w * box2_h - over_area);
    return iou;
}
