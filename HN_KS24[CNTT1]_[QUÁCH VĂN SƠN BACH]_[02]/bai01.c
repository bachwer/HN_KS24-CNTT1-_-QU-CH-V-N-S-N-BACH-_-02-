#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
char* intput(char *string) {
    printf("Input: ");
    fgets(string, 50, stdin) ;
    string[strlen(string) - 1] = '\0';
    return string;
}


typedef struct Node {
    char name[50];
    struct Node *next;
}Node;

typedef struct Stack {
    Node *top;
}Stack;

Node* createNode(char *name) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode != NULL) {
        printf("%s", name);
      strcpy(newNode -> name, name);
      newNode -> next = NULL;
    }
    return newNode;
}

Stack *newStack() {
    Stack *newStack = malloc(sizeof(Stack));
    if (newStack != NULL) {
        newStack -> top = NULL;
    }
    return newStack;
}


void push(Stack *s, const char *name) {
    Node *newNode = createNode(name);
    if (newNode == NULL) {
        printf("Push that bai\n");
        return;
    }
    if (s -> top == NULL) {
        s -> top = newNode;
    }else {
        newNode -> next = s -> top;
        s -> top = newNode;
    }
}


char *pop(Stack *s) {
    if (s->top == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    Node *temp = s->top;
    char *name = malloc(strlen(temp->name) + 1);
    if (name != NULL) {
        strcpy(name, temp->name);
    }
    s->top = s->top->next;
    free(temp);
    return name;
}

Node *peek(const Stack *s) {
    if (s == NULL) return s -> top;
    if (s -> top == NULL) {
        printf("List is empty\n");
        return s -> top;
    }

    return  s -> top;
}


// Stack 1 (clipboardStack): quản lý các nội dung đã copy.
// Stack 2 (redoStack): lưu trữ các nội dung vừa undo để có thể redo.
// Chuỗi (string): dùng để nhập nội dung và hiển thị.


//
//
// 1.	COPY : Sao chép đoạn văn bản mới (nhập một chuỗi)
void COPY(Stack *s) {
    if (s == NULL) {
        printf("Error\n");
        return;
    }
    char name[50];
    getchar();
    push(s,intput(name));
}
// 2.	PASTE: Dán nội dung vừa sao chép
void PASTE(const Stack *s) {
    if (s == NULL) return;
    printf("%s \n", s -> top -> name);
}


// 3.	UNDO: Hoàn tác lệnh sao chép gần nhất (xóa khỏi clipboardStack)
void UNDO(Stack *s, Stack *s1){
    if (s == NULL) return;
    if (s -> top == NULL) return;
    char *popped = pop(s);
    if (popped != NULL) {
        push(s1, popped);
        free(popped);
    }
}
// 4.	REDO: Phục hồi lệnh vừa undo
void REDO(Stack *s, Stack *s1){
    if (s == NULL) return;
    if (s1 == NULL) return;
    if (s1 -> top == NULL) return;
    char *popped = pop(s1);
    if (popped != NULL) {
        push(s, popped);
        free(popped);
    }
}

// 5.	HIỂN THỊ: In toàn bộ nội dung clipboard (từ mới nhất đến cũ nhất)
void showCopy(const Stack *s) {
    if (s == NULL) return;
    if (s -> top == NULL) {
        printf("List is empty !! \n");
        return;
    }
    Node *current = s -> top;
    int i = 1;
    while (current != NULL) {
        printf("%d| %s\n", i, current -> name);

        i++;
        current = current -> next;
    }

}
// 6.	THOÁT: Kết thúc chương trình
//


void showMenu() {
    printf("\n—————————— CLIPBOARD MANAGER ————————\n");
    printf("1. COPY\n");
    printf("2. PASTE\n");
    printf("3. UNDO\n");
    printf("4. REDO\n");
    printf("5. HIỂN THỊ\n");
    printf("6. THOÁT\n");
}
void freeS(Stack *s) {
    if (s == NULL) {
        free(s);
        return;
    }
    while (s -> top != NULL) {
        pop(s);
    }
    free(s);
}




int main(void) {
    Stack *copy = newStack();
    Stack *redo =  newStack();
    int menu;

    do {
        showMenu();
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                COPY(copy);
                break;
            case 2:
                PASTE(copy);
                break;
            case 3:
                UNDO(copy, redo);
                break;
            case 4:
                REDO(copy, redo);
                break;
            case 5:
                showCopy(copy);
                break;
            case 6:
                freeS(copy);
                freeS(redo);
                break;
            default:
                printf("Invalid");
        }

    }while (menu != 8);
    return 0;
}

