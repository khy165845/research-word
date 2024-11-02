//4rd report
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define max_size 100

// data ����ü
typedef struct Dstruct {
    char word[max_size];
    int count;
    int line;
    int line_s[max_size];
} Dstruct;

// ���� Ʈ�� ��� ���� ����
typedef struct Tnode {
    struct Tnode* left;
    Dstruct data;
    struct Tnode* right;
} Tnode;

// ���� Ʈ���� ��� ��� ���� ����
typedef struct LinkedBT {
    Tnode* root;
} LinkedBT;

// Ʈ�� �ʱ�ȭ
void init_BT(LinkedBT** root) {
    *root = NULL;
}

// ���ο� ��� ����
Tnode* new_node(Dstruct word,int line_num) {
    Tnode* new = (Tnode*)malloc(sizeof(Tnode));
    if (new == NULL) {
        printf("�޸� �Ҵ� ����");
        exit(1);
    }
    new->data = word; //���ο� ��忡 �ܾ� ����
    new->left = new->right = NULL; 
    new->data.count = 1; //count 1�� �ʱ�ȭ
    new->data.line_s[0] = line_num; //�ܾ� ���ö����� �� ��ȣ ����
    new->data.line = 1; //�� ��ȣ ���������Ƿ� 1�� �ʱ�ȭ
    return new;
}

// ��� ����
Tnode* insert_node(Tnode* node, Dstruct word, int line_num) {
    if (node == NULL) {
        return new_node(word,line_num); // ���ο� ��带 �����Ͽ� ��ȯ
    }

    int cmp = strcmp(word.word, node->data.word); //���ο� �ܾ�� ��忡 �Էµ� �ܾ� ��
    if (cmp < 0) {
        node->left = insert_node(node->left, word, line_num); // ���� ����Ʈ���� ����
    }
    else if (cmp > 0) {
        node->right = insert_node(node->right, word, line_num); // ������ ����Ʈ���� ����
    }
    else {
        node->data.count++; // �̹� �����ϴ� �ܾ��� ��� count 1����
        node->data.line_s[node->data.line++] = line_num; //line_s�� �� ��ȣ ����
    }
    return node; 
}
//�ܾ� ����Ƚ���� �� ��ȣ ���
void print_word_count(Tnode* node) {
    int wordcount=0;
    if (node != NULL) {
        print_word_count(node->left);
        printf("%s\t%d\t", node->data.word, node->data.count); //�ܾ� Ƚ�� ���
        for (int i = 0; i < node->data.line; ++i) {
            printf("%d ", node->data.line_s[i]); //�� ��ȣ ��� ���
        }
        printf("\n");
        print_word_count(node->right);
    }
}
//��ü �ܾ� �� (��)
void word_hap(Tnode* node,int* wordhap) {
    if (node != NULL) {
        word_hap(node->left, wordhap);
        *wordhap += node->data.count;
        word_hap(node->right, wordhap);
    }
}

int main() {
    LinkedBT bst;
    init_BT(&bst.root);

    char sample[max_size];
    FILE* fp;
    errno_t err;

    int line = 1;
    int wordhap = 0;

    err = fopen_s(&fp, "example.txt", "rt"); //�ؽ�Ʈ ���� ����
    if (err != 0) {
        printf("���� ���� ����");
        return 1;
    }
    //printf("���� ���� ����\n");

    while (NULL != fgets(sample, sizeof(sample), fp)) //������ ���ڿ��� �� ������ ó��
    {
        char* tok = strtok(sample, " \t\n.,?!"); // ������ �ܾ�� �и�
        while (tok != NULL) {
            Dstruct word;
            strcpy(word.word, tok);
            bst.root = insert_node(bst.root, word, line);
            tok = strtok(NULL, " \t\n.,?!");
        }
        line++;
    }
    fclose(fp);

    printf("�ܾ�\tȽ��\t��\n");
    print_word_count(bst.root);

    word_hap(bst.root, &wordhap);
    printf("��\t%d", wordhap);
    return 0;
}