#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
Node* insert(Node* root, int data) {
    if (root == NULL) {
        printf("Them thanh cong\n");
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        printf("Gia tri da ton tai\n");
    }
    return root;
}
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
Node* delete(Node* root, int data) {
    if (root == NULL) {
        printf("Gia tri khong ton tai\n");
        return NULL;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            printf("Xoa thanh cong\n");
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            printf("Xoa thanh cong\n");
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}
int countLeaves(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->left == NULL && root->right == NULL) {
        count++;
    }
    count += countLeaves(root->left);
    count += countLeaves(root->right);
    return count;
}
int height(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
int main() {
    // Node* root = NULL;
    Node* root = createNode(2);
    Node* node1 = createNode(1);
    Node* node2 = createNode(3);
    root->left = node1;
    root->right = node2;
    int choice;
    do{
        printf("\nBINARY SEARCH TREE\n"
           "1. Them gia tri\n"
           "2. Xoa gia tri\n"
           "3. Duyet gia tri\n"
           "4. Dem la\n"
           "5. Chieu cao\n"
           "6. Thoat\n"
           "Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                int data;
                printf("Nhap gia tri can them: ");
                scanf("%d", &data);
                root = insert(root,data);
                break;
            case 2:
                int value;
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                root = delete(root,value);
                break;
            case 3:
                if (root == NULL) {
                    printf("tree is empty\n");
                }else {
                    inorder(root);
                }
                break;
            case 4:
                printf("So la cua cay = %d\n",countLeaves(root));
                break;
            case 5:
                printf("Chieu cao cua cay la %d\n",height(root));
                break;
            case 6:
                printf("Thoat chuong trinh ");
                return 0;
            default:
                printf("Lua chon ko hop le\n");
                break;
        }
    }while (choice != 6);
}