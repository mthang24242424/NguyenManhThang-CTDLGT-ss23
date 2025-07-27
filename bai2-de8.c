#include<stdio.h>
#include<string.h>

typedef struct Request {
    int id;
    char issue[50];
    int priority;
}Request;

void addRequest(Request high[],Request low[], int *countH, int * countL) {
    Request temp;
    printf("Nhap id yeu cau: ");
    scanf("%d",&temp.id);
    getchar();

    printf("Nhap yeu cau can xu ly: ");
    fgets(temp.issue,50,stdin);
    temp.issue[strlen(temp.issue)-1] = '\0';

    printf("Nhap do uu tien cua yeu cau(1:cao, 2:thap): ");
    scanf("%d",&temp.priority);
    if (temp.priority == 1) {
        high[*countH] = temp;
        (*countH)++;
    }else {
        low[*countL] = temp;
        (*countL)++;
    }
}
void deleteRequest(Request high[],Request low[], int *countH, int * countL) {
    if (*countH == 0 && *countL == 0) {
        printf("ko co yeu cau nao can xu ly");
        return;
    }
    if (*countH > 0) {
        for (int i =0; i < *countH; i++) {
            high[i] = high[i+1];
        }
        (*countH)--;
    }else {
        for (int i = 0; i < *countL; i++) {
            low[i] = low[i+1];
        }
        (*countL)--;
    }
    printf("xu ly thanh cong\n");
}
void printNextRequest(Request high[], Request low[], int countH, int countL) {
    if (countH == 0 && countL == 0) {
        printf("Khong co yeu cau nao can xu ly\n");
        return;
    }
    if (countH > 0) {
        printf("Yeu cau gan nhat (Uu tien cao): %s\n", high[0].issue);
    } else {
        printf("Yeu cau gan nhat (Uu tien thap): %s\n", low[0].issue);
    }
}

void printList(Request high[],Request low[], int countH, int countL) {
    if (countH == 0 && countL == 0) return;
    for (int i = 0; i < countH; i++) {
        printf("%s \n", high[i].issue);
    }
    for (int i = 0; i < countL; i++) {
        printf("%s \n", low[i].issue);
    }
}
int main() {
    Request high[] = {
        {1,"lam bai tap",1},
        {4,"chuan bi bua toi", 1}
    };
    Request low[] ={
        {2,"quet nha",2},
        {3,"di choi", 2}
    };
    int countH = 2, countL = 2;
    int choice;
    do {
        printf("REQUEST SYSTEM MENU\n"
               "1. Gui yeu cau ho tro\n"
               "2. Xu ly yeu cau\n"
               "3. Xem yeu cau gan nhat can xu ly\n"
               "4. Hien thi toan bo yeu cau\n"
               "5. Thoat\n"
               "Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                addRequest(high, low, &countH, &countL);
                break;
            case 2:
                deleteRequest(high, low, &countH, &countL);
                break;
            case 3:
                printNextRequest(high, low, countH, countL);
                break;
            case 4:
                printList(high, low, countH, countL);
                break;
            case 5:
                printf("thoat chuong trinh");
                return 0;
        }
    }while (choice != 5);
}
