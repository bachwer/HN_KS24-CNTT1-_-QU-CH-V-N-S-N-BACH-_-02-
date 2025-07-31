//
// Created by Macbook on 31/07/2025.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct Contact {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

typedef struct TreeNode {
    Contact data;
    struct TreeNode *left, *right;
} TreeNode;


TreeNode *createNode(const Contact contact) {
    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (newNode != NULL) {

        strcpy(newNode -> data.name,  contact.name);
        strcpy(newNode -> data.phone, contact.phone);
        strcpy(newNode -> data.email, contact.email);
        newNode -> left = newNode -> right = NULL;

    }
    return newNode;

}
char* intput(char *string, char *input) {
    printf("%s: ", input);
    fgets(string, 50, stdin) ;
    string[strlen(string) - 1] = '\0';
    return string;
}


// 1. Thêm người vào danh bạ
TreeNode *addContact(TreeNode *contact, const Contact con ) {
    if (contact == NULL) return createNode(con);

    if (strcmp(con.name, contact->data.name) > 0) {
        contact->right = addContact(contact->right, con);
    } else if (strcmp(con.name, contact->data.name) < 0) {
        contact->left = addContact(contact->left, con);
    } else {
        printf("da ton tai ten \n");
        return contact;
    }
    return contact;
}

void printfContact(Contact cont) {
    printf("\n----------------\n");
    printf("Name: %s\n", cont.name);
    printf("Phone: %s\n", cont.phone);
    printf("Email: %s\n", cont.email);
}
// 2. Hiển thị danh bạ theo ABC
void showAll(const TreeNode *con) {
    if (con == NULL) return;
    showAll(con -> left);
    printfContact(con ->data);
    showAll(con -> right);
}

// 3. Tìm người theo tên

void SearchName(const TreeNode *con, const char *name) {
    if (con == NULL) return;
    int cmp = strcmp(name, con->data.name);
    if (cmp == 0) {
        printfContact(con->data);
    } else if (cmp < 0) {
        SearchName(con->left, name);
    } else {
        SearchName(con->right, name);
    }
}
// 4. Xóa người theo tên


TreeNode* findMin(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode *delete(TreeNode *tree, char *name) {
    if (tree == NULL) return tree;
    if (strcmp(name, tree->data.name) > 0) {
        tree->right = delete(tree->right, name);
    } else if (strcmp(name, tree->data.name) < 0) {
        tree->left = delete(tree->left, name);
    } else if (strcmp(name, tree->data.name) == 0) {
        if (tree->left == NULL) {
            TreeNode* temp = tree->right;
            free(tree);
            return temp;
        }
        if (tree->right == NULL) {
            TreeNode* temp = tree->left;
            free(tree);
            return temp;
        }

        TreeNode* min = findMin(tree->right);
        tree->data = min->data;
        tree->right = delete(tree->right, min->data.name);
    }
    return tree;
}



// 5. Thoát
void freeT(TreeNode *t) {
    if (t == NULL) return;
    freeT(t->left);
    freeT(t->right);
    free(t);
}
 void showMenu() {
     printf("\n---------MENU---------\n");
     printf("1. Thêm người vào danh bạ\n");
     printf("2. Hiển thị danh bạ theo ABC\n");
     printf("3. Tìm người theo tên\n");
     printf("4. Xóa người theo tên\n");
     printf("5. Thoat\n");
 }



int main() {
    int menu;
    TreeNode *contact = NULL;
    char name[100];
    do {
        showMenu();
        scanf("%d", &menu);
        getchar();
        switch (menu) {
            case 1:
                Contact con;
                intput(con.name, "Name ");
                intput(con.phone, "Phone ");
                intput(con.email, "email ");

                contact = addContact(contact, con);
                break;
            case 2:
                showAll(contact);
                break;
            case 3:
                intput(name, "Name ");
                SearchName(contact,name);
                break;
            case 4:
                intput(name, "Name ");
                delete(contact, name);
                break;
            case 5:
                freeT(contact);
                break;
            default: ;
        }
    }while (menu != 5);
}