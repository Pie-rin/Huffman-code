#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct str {
    char str[20];
} str;

typedef struct TreeNode {
    int weight;
    struct str* string;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    struct str* string;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

//���� �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// �ʱ�ȭ �Լ�
void init(HeapType* h) {
    h->heap_size = 0;
}

// ���� �Լ�
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    //  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;     // ���ο� ��带 ����
}

// ���� �Լ�
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        // ���� ����� �ڽĳ���� �� ���� �ڽĳ�带 ã�´�.
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
        if (temp.key <= h->heap[child].key) break;
        // �Ѵܰ� �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// ���� Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {
    //1�� �����ϰ� ��ȯȣ���Ѵ�.
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }

    //0�� �����ϰ� ��ȯȣ���Ѵ�.
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }

    //�ܸ����� �ڵ带 ����Ѵ�.
    if (is_leaf(root)) {
        printf("%c: ", root->string);
        print_array(codes, top);
    }
}

// ������ �ڵ� ���� �Լ�
void huffman_tree(int freq[], str* str_list[], int n) {
    int i;
    TreeNode *node, *x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();
    init(heap);
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.string = node->string = str_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
    }
    for (i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);  // �ּҰ��� ������ �ΰ��� ��带 ����
        e2 = delete_min_heap(heap);

        x = make_tree(e1.ptree, e2.ptree); // �ΰ��� ��带 ��ģ��.
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d+%d->%d \n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }
    e = delete_min_heap(heap); // ���� Ʈ��
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}

int main(void) {
    str str_list[100] = { "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��",
        "��","��","��","��","��","��","��","��","��","��" };

    int freq[100] = { 1,1,1,1,1,1,2,2,2,2,
        2,2,2,3,4,4,4,6,6,6,
        9,9,10,11,12,15,17,17,28,28,
        31,31,33,34,35,63,69,70,75,90,
        96,104,120,121,147,202,248,256,264,265,
        287,368,399,416,437,523,615,657,681,724,
        846,864,1002,1182,1348,1594,1953,1968,2038,2105,
        2712,3225,3310,3503,3580,4499,4581,4705,4862,5889,
        6753,8640,10367,11456,12551,12970,14724,18071,20091,21307,
        21939,21976,23653,25932,31282,43685,56945,58386,150918,152862 };

    huffman_tree(freq, &str_list, 100);
    return 0;
}