#include<stdio.h>
#include<string.h>
#include<stdbool.h>
typedef struct Student {
    int id;
    char name[30];
    bool status;
    int avg;
}Student;

void add(Student students[],int *count) {
    Student s;
    printf("nhap ma sinh vien: ");
    scanf("%d",&s.id);
    getchar();

    printf("nhap ten sinh vien: ");
    fgets(s.name,30,stdin);
    s.name[strlen(s.name)-1] = '\0';

    s.status = true;
    printf("nhap diem trung binh: ");
    scanf("%d",&s.avg);

    students[*count] = s;
    (*count)++;
    printf("them thanh cong\n");

}
void printList(Student students[], int count) {
    printf("DANH SACH SINH VIEN\n-------------------\n");
    for (int i = 0; i < count; i++) {
        printf("sv %d\n",i+1);
        printf("Ma sv: %d\n",students[i].id);
        printf("Ten sv: %s\n",students[i].name);
        printf("Trang thai sv: %s\n", students[i].status ? "Hoat dong" : "Khong hoat dong");
        printf("Diem trung binh: %d\n-------------------\n",students[i].avg);
    }
}
void delete(Student students[], int *count) {
    int idDelete;
    printf("nhap ma sv muon xoa: ");
    scanf("%d", &idDelete);
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (idDelete == students[i].id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Da xoa sinh vien co ma %d\n", idDelete);
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ma %d\n", idDelete);
    }
}
void update(Student students[], int count) {
    int idUpdate;
    printf("nhap ma sv can cap nhat thong tin: ");
    scanf("%d",&idUpdate);
    getchar();
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (idUpdate == students[i].id) {
            printf("nhap ten moi: ");
            fgets(students[i].name,30,stdin);
            students[i].name[strlen(students[i].name)-1] = '\0';

            printf("nhap diem trung binh moi: ");
            scanf("%d",&students[i].avg);
            found = 1;
            printf("cap nhat thanh cong\n");
            break;
        }
    }
    if (!found) {
        printf("ko tim thay sv nao\n");
    }
}
void changeStatus(Student students[], int count) {
    int idChange;
    printf("nhap id sinh vien muon thay doi: ");
    scanf("%d", &idChange);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (idChange == students[i].id) {
            students[i].status = !students[i].status;
            printf("Trang thai moi cua sinh vien la: %s\n", students[i].status ? "Hoat dong" : "Khong hoat dong");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ma %d\n", idChange);
    }
}

void merge(Student arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Student L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i].avg <= R[j].avg) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Student arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void binarySearch(Student students[], int count) {
    int idSearch;
    printf("Nhap ma sinh vien can tim: ");
    scanf("%d", &idSearch);

    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].id == idSearch) {
            printf("Tim thay sinh vien:\n");
            printf("Ma sv: %d\n", students[mid].id);
            printf("Ten sv: %s\n", students[mid].name);
            printf("Trang thai sv: %s\n", students[mid].status ? "Hoat dong" : "Khong hoat dong");
            printf("Diem trung binh: %d\n", students[mid].avg);
            return;
        } else if (students[mid].id < idSearch) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Khong tim thay sinh vien co ma %d\n", idSearch);
}

int main() {
    Student students[] = {
        {1, "Nguyen Van A", true, 85},
        {2, "Tran Thi B", false, 75},
        {3, "Le Van C", true, 90}
    };
    int count = 3;
    int choice;
    do {
        printf("STUDENT MANAGER MENU\n"
           "1. Them sinh vien\n"
           "2. Hien thi sinh vien\n"
           "3. Xoa sinh vien\n"
           "4. Cap nhat thong tin sinh vien\n"
           "5. Thay doi trang thai sinh vien\n"
           "6. Sap xep sinh vien\n"
           "7. Tim kiem sinh vien\n"
           "8. Thoat chuong trinh\n"
           "Lua chon cua ban : ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                add(students, &count);
                break;
            case 2:
                printList(students,count);
                break;
            case 3:
                delete(students, &count);
                break;
            case 4:
                update(students, count);
                break;
            case 5:
                changeStatus(students, count);
                break;
            case 6:
                mergeSort(students, 0, count - 1);
                break;
            case 7:
                binarySearch(students, count);
                break;
            case 8:
                printf("thoat chuong trinh");
                return 0;
        }
    }while (choice != 8);
}
