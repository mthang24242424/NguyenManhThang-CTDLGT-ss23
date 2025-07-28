#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Order {
    int id;
    char customer[50];
    int status;
    char total[10];
}Order;
typedef struct ListDouble {
    Order * data;
    struct ListDouble *next;
    struct ListDouble *prev;
}ListDouble;
typedef struct ListSingle {
    Order * data;
    struct ListSingle *next;
}ListSingle;

ListDouble* createListDouble(Order order) {
    ListDouble* newList = (ListDouble*)malloc(sizeof(ListDouble));
    newList->data = (Order*)malloc(sizeof(Order));
    *(newList->data) = order;
    newList->next = NULL;
    newList->prev = NULL;
    return newList;
}

ListDouble* head = NULL;
ListSingle* head2 = NULL;
void add() {
    Order order;
    printf("Nhap ma don hang: ");
    scanf("%d", &order.id);
    getchar();
    printf("Nhap ten khach hang: ");
    fgets(order.customer, 50, stdin);
    order.customer[strcspn(order.customer, "\n")] = '\0';
    order.status = 1;
    printf("Nhap gia tien: ");
    fgets(order.total, 10, stdin);
    order.total[strcspn(order.total, "\n")] = '\0';

    ListDouble* newList = createListDouble(order);
    if (head == NULL) {
        head = newList;
    }else {
        ListDouble* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newList;
        newList->prev = temp;
    }
    printf("Da them don hang thanh cong!\n");
}
void printList(ListDouble *list) {
    ListDouble *temp = list;
    if (temp == NULL) {
        printf("Danh sach trong\n");
        return;
    }
    while (temp != NULL) {
        printf("Ma don hang: %d\n",temp->data->id);
        printf("Ten khach hang: %s\n",temp->data->customer);
        if (temp->data->status == 1) {
            printf("Trang thai: Chua giao\n");
        }else {
            printf("Trang thai: Da giao\n");
        }
        printf("Gia tien: %s\n",temp->data->total);
        temp = temp->next;
    }
    printf("\n");
}
void delete(ListDouble *list) {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return;
    }
    ListDouble* current = head;
    int checkId, found = 0;
    printf("Nhap id don hang can xoa: ");
    scanf("%d", &checkId);
    while (current != NULL) {
        if (current->data->id == checkId) {
            found = 1;
            if (current == head) {
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            }
            else {
                if (current->prev != NULL)
                    current->prev->next = current->next;
                if (current->next != NULL)
                    current->next->prev = current->prev;
            }
            free(current->data);
            free(current);
            printf("Xoa thanh cong\n");
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("Khong tim thay ma don hang nao trung khop\n");
    }
}
void update(ListDouble *list) {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return;
    }
    int checkId,found = 0;
    printf("Nhap id don hang can cap nhat: ");
    scanf("%d", &checkId);
    getchar();
    ListDouble* current = head;
    while (current != NULL) {
        if (current->data->id == checkId) {
            found = 1;
            printf("Nhap ten khach hang moi: ");
            fgets(current->data->customer, 50, stdin);
            current->data->customer[strcspn(current->data->customer, "\n")] = '\0';
            printf("Nhap gia tien moi: ");
            fgets(current->data->total, 10, stdin);
            current->data->total[strcspn(current->data->total, "\n")] = '\0';
            printf("Cap nhat thanh cong\n");
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("Ko tim thay ma trung hop\n");
    }
}
void doneOrder() {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return;
    }

    int id;
    printf("Nhap ma don hang can danh dau da giao: ");
    scanf("%d", &id);

    ListDouble* current = head;
    while (current != NULL) {
        if (current->data->id == id) {
            current->data->status = 0;

            ListSingle* newNode = (ListSingle*)malloc(sizeof(ListSingle));
            newNode->data = current->data;
            newNode->next = NULL;

            if (head2 == NULL) {
                head2 = newNode;
            } else {
                ListSingle* temp = head2;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            if (current == head) {
                head = current->next;
                if (head != NULL) head->prev = NULL;
            } else {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
            }
            free(current);
            printf("Da danh dau don hang da giao.\n");
            return;
        }
        current = current->next;
    }
    printf("Khong tim thay don hang voi ID da nhap.\n");
}
void sort(ListDouble *list) {
    if (head == NULL) {
        printf("Danh sach trong\n");
        return;
    }
    int swapped;
    ListDouble *ptr;
    ListDouble *lptr = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            int total1 = atoi(ptr->data->total);
            int total2 = atoi(ptr->next->data->total);

            if (total1 > total2) {
                Order* temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
    printf("Da sap xep don hang theo gia tien tang dan.\n");
}
void searchOrder() {
    char keyword[50];
    getchar();
    printf("Nhap ten khach hang can tim: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;

    ListDouble* temp1 = head;
    while (temp1 != NULL) {
        if (strstr(temp1->data->customer, keyword)) {
            printf("Ma don hang: %d\n", temp1->data->id);
            printf("Ten khach hang: %s\n", temp1->data->customer);
            printf("Trang thai: Chua giao\n");
            printf("Gia tien: %s\n\n", temp1->data->total);
            found = 1;
        }
        temp1 = temp1->next;
    }

    ListSingle* temp2 = head2;
    while (temp2 != NULL) {
        if (strstr(temp2->data->customer, keyword)) {
            printf("Ma don hang: %d\n", temp2->data->id);
            printf("Ten khach hang: %s\n", temp2->data->customer);
            printf("Trang thai: Da giao\n");
            printf("Gia tien: %s\n\n", temp2->data->total);
            found = 1;
        }
        temp2 = temp2->next;
    }

    if (!found) {
        printf("Khong tim thay don hang nao cua '%s'.\n", keyword);
    }
}

int main() {
    int choice;
    do {
        printf("MENU\n"
           "1. Them moi don hang\n"
           "2. Hien thi don hang\n"
           "3. Xoa don hang\n"
           "4. Cap nhat don hang\n"
           "5. Danh dau don hang\n"
           "6. Sap xep don hang\n"
           "7. Tim kiem don hang\n"
           "8. Thoat\n"
           "Lua chon cua ban: ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                printList(head);
                break;
            case 3:
                delete(head);
                break;
            case 4:
                update(head);
                break;
            case 5:
                doneOrder();
                break;
            case 6:
                sort(head);
                break;
            case 7:
                searchOrder();
                break;
            case 8:
                printf("Thoat chuong trinh");
                return 0;
            default:
                printf("Lua chon ko hop le\n");
                break;
        }
    }while (choice != 8);
}
