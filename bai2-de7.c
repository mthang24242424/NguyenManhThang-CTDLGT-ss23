#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Web {
    char url[100];
    char timeStamp[30];
} Web;
typedef struct Stack {
    Web* history;
    int top;
    int cap;
} Stack;

Stack* createStack(int cap) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->history = (Web*)malloc(sizeof(Web) * cap);
    stack->top = -1;
    stack->cap = cap;
    return stack;
}
int isEmpty(Stack* s) {
    return s->top == -1;
}
int isFull(Stack* s) {
    return s->top == s->cap - 1;
}
void push(Stack* s, Web w) {
    if (isFull(s)) {
        printf("Stack day!\n");
        return;
    }
    s->history[++s->top] = w;
}
Web pop(Stack* s) {
    if (isEmpty(s)) {
        Web empty = {"", ""};
        return empty;
    }
    return s->history[s->top--];
}

int main() {
    Stack* back = createStack(100);
    Stack* forward = createStack(100);
    Web current = {"", ""};

    int choice;
    do {
        printf("MENU\n");
        printf("1. VISIT url: Truy cap trang web moi\n");
        printf("2. BACKWARD: Quay lai trang truoc\n");
        printf("3. FORWARD: Di den trang sau\n");
        printf("4. CURRENT: In dia chi hien tai \n");
        printf("5. THOAT\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                Web newPage;
                printf("Nhap dia chi web: ");
                fgets(newPage.url, 100, stdin);
                newPage.url[strcspn(newPage.url, "\n")] = 0;

                printf("Nhap thoi gian: ");
                fgets(newPage.timeStamp, 30, stdin);
                newPage.timeStamp[strcspn(newPage.timeStamp, "\n")] = 0;

                push(back, newPage);
                printf("Truy cap thanh cong\n");
                break;
            }
            case 2: {
                if (isEmpty(back)) {
                    printf("Lich su trong.\n");
                } else {
                    push(forward, current);
                    current = pop(back);
                    printf("BACK thanh cong.\n");
                }
                break;
            }
            case 3: {
                if (isEmpty(forward)) {
                    printf("Lich su trong.\n");
                } else {
                    push(back, current);
                    current = pop(forward);
                    printf("FORWARD thanh cong.\n");
                }
                break;
            }
            case 4: {
                if (strlen(current.url) == 0) {
                    printf("Chua truy cap trang web nao.\n");
                } else {
                    printf("Trang web hien tai: %s\n", current.url);
                    printf("Thoi gian truy cap: %s\n", current.timeStamp);
                }
                break;
            }
            case 5:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 5);
}
