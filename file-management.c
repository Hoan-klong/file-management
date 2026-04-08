#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ten[100];
    char duongDan[200];
    float kichThuoc;
    char thoiGian[50];
} File;

typedef struct Node {
    File data;
    struct Node *next;
} Node;

Node* taoNode(File x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

void chenTheoThoiGian(Node **head, File x) {
    Node *p = taoNode(x);

    if (*head == NULL || strcmp(x.thoiGian, (*head)->data.thoiGian) < 0) {
        p->next = *head;
        *head = p;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL &&
           strcmp(x.thoiGian, temp->next->data.thoiGian) > 0) {
        temp = temp->next;
    }

    p->next = temp->next;
    temp->next = p;
}

void copyFile(Node **head) {
    File x;

    printf("Ten file: ");
    scanf("%s", x.ten);

    printf("Duong dan: ");
    scanf("%s", x.duongDan);

    printf("Kich thuoc: ");
    scanf("%f", &x.kichThuoc);

    printf("Thoi gian: ");
    scanf("%s", x.thoiGian);

    chenTheoThoiGian(head, x);
}

float tongKichThuoc(Node *head) {
    float sum = 0;
    while (head != NULL) {
        sum += head->data.kichThuoc;
        head = head->next;
    }
    return sum;
}

Node* timMin(Node *head) {
    Node *min = head;
    while (head != NULL) {
        if (head->data.kichThuoc < min->data.kichThuoc)
            min = head;
        head = head->next;
    }
    return min;
}

void xoaNode(Node **head, Node *target) {
    if (*head == target) {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }

    Node *prev = *head;
    while (prev->next != target)
        prev = prev->next;

    prev->next = target->next;
    free(target);
}

void fitUSB(Node **head) {
    while (tongKichThuoc(*head) > 32000) {
        Node *min = timMin(*head);
        xoaNode(head, min);
    }
}

void hienThi(Node *head) {
    while (head != NULL) {
        printf("%s | %.2f MB | %s\n",
               head->data.ten,
               head->data.kichThuoc,
               head->data.thoiGian);
        head = head->next;
    }
}

int main() {
    Node *head = NULL;
    int n;

    printf("Nhap so file: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        copyFile(&head);
    }

    hienThi(head);
    printf("\nTong: %.2f MB\n", tongKichThuoc(head));

    fitUSB(&head);

    printf("\nSau khi fit USB:\n");
    hienThi(head);

    return 0;
}