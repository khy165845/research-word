//4rd report
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define max_size 100

// data 구조체
typedef struct Dstruct {
    char word[max_size];
    int count;
    int line;
    int line_s[max_size];
} Dstruct;

// 이진 트리 노드 구조 정의
typedef struct Tnode {
    struct Tnode* left;
    Dstruct data;
    struct Tnode* right;
} Tnode;

// 이진 트리의 헤드 노드 구조 정의
typedef struct LinkedBT {
    Tnode* root;
} LinkedBT;

// 트리 초기화
void init_BT(LinkedBT** root) {
    *root = NULL;
}

// 새로운 노드 생성
Tnode* new_node(Dstruct word,int line_num) {
    Tnode* new = (Tnode*)malloc(sizeof(Tnode));
    if (new == NULL) {
        printf("메모리 할당 오류");
        exit(1);
    }
    new->data = word; //새로운 노드에 단어 저장
    new->left = new->right = NULL; 
    new->data.count = 1; //count 1로 초기화
    new->data.line_s[0] = line_num; //단어 나올때마다 줄 번호 저장
    new->data.line = 1; //줄 번호 저장했으므로 1로 초기화
    return new;
}

// 노드 삽입
Tnode* insert_node(Tnode* node, Dstruct word, int line_num) {
    if (node == NULL) {
        return new_node(word,line_num); // 새로운 노드를 생성하여 반환
    }

    int cmp = strcmp(word.word, node->data.word); //새로운 단어와 노드에 입력된 단어 비교
    if (cmp < 0) {
        node->left = insert_node(node->left, word, line_num); // 왼쪽 서브트리에 삽입
    }
    else if (cmp > 0) {
        node->right = insert_node(node->right, word, line_num); // 오른쪽 서브트리에 삽입
    }
    else {
        node->data.count++; // 이미 존재하는 단어인 경우 count 1증가
        node->data.line_s[node->data.line++] = line_num; //line_s에 줄 번호 저장
    }
    return node; 
}
//단어 등장횟수와 줄 번호 출력
void print_word_count(Tnode* node) {
    int wordcount=0;
    if (node != NULL) {
        print_word_count(node->left);
        printf("%s\t%d\t", node->data.word, node->data.count); //단어 횟수 출력
        for (int i = 0; i < node->data.line; ++i) {
            printf("%d ", node->data.line_s[i]); //줄 번호 모두 출력
        }
        printf("\n");
        print_word_count(node->right);
    }
}
//전체 단어 수 (계)
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

    err = fopen_s(&fp, "example.txt", "rt"); //텍스트 파일 열기
    if (err != 0) {
        printf("파일 열기 실패");
        return 1;
    }
    //printf("파일 열기 성공\n");

    while (NULL != fgets(sample, sizeof(sample), fp)) //파일의 문자열을 줄 단위로 처리
    {
        char* tok = strtok(sample, " \t\n.,?!"); // 문장을 단어로 분리
        while (tok != NULL) {
            Dstruct word;
            strcpy(word.word, tok);
            bst.root = insert_node(bst.root, word, line);
            tok = strtok(NULL, " \t\n.,?!");
        }
        line++;
    }
    fclose(fp);

    printf("단어\t횟수\t줄\n");
    print_word_count(bst.root);

    word_hap(bst.root, &wordhap);
    printf("계\t%d", wordhap);
    return 0;
}