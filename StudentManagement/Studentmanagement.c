# include "StudentSystem.h"

int main() {
    // Dynamically allocate memory for the head node of the linked list and initialize its `next` pointer to NULL.
    Node * head = malloc(sizeof(Node));  // Correct way to use malloc in C++
    head -> next = NULL;
    loadStudent(head);
    welcome();
    int input;

    while(1) {
        printf("Enter your choice: ");
        scanf("%d", &input);
        
        switch (input) {
            case 1:
                inputStudent(head);
                break;
            case 2:
                printStudent(head);
                break;  
            case 3:
                countStudent(head);
                break;
            case 4:
                findStudent(head);
                break; 
            case 5:
                modifyStudent(head);
                break;
            case 6:
                deleteStudent(head);
                break;  
            case 7:
                sortStudent(head);
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Iplease input again\n");
                break;
        }
    } 
    return 0;
}


void welcome() 
{
    printf("*****************************************\n");
    printf("\t Student System Management\t*\n");    // \t : a space
    printf("*****************************************\n");
    printf("*\tplease choose the function list\t*\n");
    printf("*****************************************\n");
    printf("*\t1.Enter student info\t\t*\n");
    printf("*\t2.Print student info\t\t*\n");
    printf("*\t3.Count student number\t\t*\n");
    printf("*\t4.search student info\t\t*\n");
    printf("*\t5.edit student info\t\t*\n");
    printf("*\t6.delete student info\t\t*\n");
    printf("*\t7.sort student by their grade\t*\n");
    printf("*\t8.Exit\t\t\t\t*\n");
    printf("*****************************************\n");
}

//  input new student information
void inputStudent(Node* head)
{
    // firstly:  apply for a space to store student info
    Node* fresh = malloc (sizeof(Node));  // create a new node
    fresh -> next = NULL; // initialize the new node

    printf("please enter studentID, name, grade\n");
    scanf("%d%s%d", &fresh->student.stuNum, fresh->student.name, &fresh->student.score);

    // create a new node to record current node
    Node* move = head;
    while(move->next != NULL) {
        move = move->next;
    }
    // insert a new stu at the end of the list
    move -> next = fresh;

    saveStudent(head);
    printf("added successfully\n");
}

// print all student messages
void printStudent(Node * head)
{
    Node* move = head -> next;
    while(move != NULL) {
        printf("studentID: %d name: %s grade: %d\n", move->student.stuNum, move->student.name, move->student.score); 
        move = move->next;
    }
}

// count the number of students
void countStudent(Node* head)
{
    int count = 0;
    Node* move = head->next;
    while(move != NULL) {
        count++;
        move = move->next;
    }
    printf("the total number of student is %d\n", count);
}

// find whether a student exist or not
void findStudent(Node* head)
{
    printf("please enter studentID: ");
    int stuNum;
    scanf("%d", &stuNum);
    Node* move = head->next;
    while(move != NULL) {
        if (stuNum == move -> student.stuNum) {
            printf("studentID: %d name: %s grade: %d \n", move->student.stuNum, move->student.name, move->student.score);
            return;
        }
        move = move->next;
    } 
    printf("student info not found\n");
}


// 5. modify a student's message
void modifyStudent(Node* head) {
    printf("please enter the studentid of the student that you want to modify\n");
    int stuNum;
    scanf("%d", &stuNum);
    Node* move = head -> next;
    while( move != NULL) {
        if (move -> student.stuNum == stuNum) {
            printf("please input student name and student grade\n");
            scanf("%s%d", move -> student.name, &move -> student.score);
            saveStudent(head);
            printf("edit successfully\n");
            return;
        }
        move = move -> next;
    }
    printf("studentid is not found\n");
}

// save student message into a file
void saveStudent(Node* head)
{
    FILE* file = fopen("./stu.info", "w");

    if (file == NULL)
    {
        printf("fail to open the file\n");
        return;
    }
    Node* move = head-> next;
    while(move != NULL) {
        if (fwrite(&move->student, sizeof(Student), 1, file) != 1) {
            printf("edit fail\n");
            return;
        }
        move = move->next;
    }
    fclose(file);
}

// load student messages
void loadStudent(Node* head) {
    FILE* file = fopen("./stu.info", "r");
    if (!file) {
        printf("File not found\n");
        return;
    }
    while (1) {
        Node* fresh = malloc(sizeof(Node));
        if (!fresh) {
            printf("Memory allocation failed\n");
            break; // Exit if we can't allocate more memory
        }
        fresh->next = NULL;
        if (fread(&fresh->student, sizeof(Student), 1, file) != 1) {
            free(fresh); // Free the node if read was not successful
            break; // Break the loop if reach the end of the file / encounter an error
        }
        // Link the new node to the list
        Node* move = head;
        while (move->next != NULL) move = move->next;
        move->next = fresh;
    }
    fclose(file);
}



// 6. delete a student 
void deleteStudent(Node* head) {
    printf("input the studentid that you want to delete: ");
    int stuNum = 0;
    scanf("%d", &stuNum);
    Node* move = head;

    while(move -> next != NULL) {
        if (move -> next -> student.stuNum == stuNum) {
            Node* tmp = move -> next;
            move -> next = move -> next -> next;
            free(tmp);
            tmp = NULL;
            saveStudent(head);
            printf("delete successfully\n");
            return;
        }
        move = move -> next;
    }
    printf("studentid not found");
}

//7. sort students due to their grades
void sortStudent(Node* head) {
    Node* save = NULL;
    Node* move = NULL;
    for (Node* turn = head -> next ; turn -> next != NULL; turn = turn -> next) {
        for (move = head -> next; move -> next != save; move = move -> next) {
            if (move -> student.score > move -> next -> student.score) {
                Student temp = move -> student;
                move -> student = move -> next -> student;
                move -> next -> student = temp;
            }
        }
        save = move;
    }
    printStudent(head);
}
