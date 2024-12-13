#include <stdio.h>

#define MAX_SIZE 100
#define FILENAME "students.dat"  // ���� �̸� ����

typedef struct {
    char name[100];
    int koreanScore;
    int englishScore;
    int mathScore;
} Student;

Student students[MAX_SIZE]; 
int std_count = 0;  

int readfile(const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "rb"); // ���� �������� ���� ����
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 0;  
    }

    int count = fread(students, sizeof(Student), MAX_SIZE, file);  
    fclose(file);  

    return count;  
}

void saveStudent(const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "wb");  // ���� �������� ���� ����
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fwrite(students, sizeof(Student), std_count, file);  
    fclose(file);  
    printf("���� �Ϸ�\n");
}

void printStudentGrade() {
    for (int i = 0; i < std_count; i++) {
        int total = students[i].koreanScore + students[i].englishScore + students[i].mathScore;
        double average = total / 3.0;

        printf("�̸�: %s\n", students[i].name);
        printf("����: %d, ����: %d, ����: %d\n", students[i].koreanScore, students[i].englishScore, students[i].mathScore);
        printf("����: %d, ���: %.2f\n\n", total, average);
    }
}

void addStudentInfo() {
    if (std_count >= MAX_SIZE) {
        printf("�� �̻� �л��� �߰��� �� �����ϴ�.\n");
        return;
    }

    printf("�л� �̸��� �Է��ϼ���: ");
    scanf_s("%99s", students[std_count].name, sizeof(students[std_count].name));  
    printf("���� ������ �Է��ϼ���: ");
    scanf_s("%d", &students[std_count].koreanScore);
    printf("���� ������ �Է��ϼ���: ");
    scanf_s("%d", &students[std_count].englishScore);
    printf("���� ������ �Է��ϼ���: ");
    scanf_s("%d", &students[std_count].mathScore);

    std_count++;  // �л� �� ����
    printf("�л� ������ �߰��Ǿ����ϴ�.\n");
}

int main() {
    int choice;
    std_count = readfile(FILENAME);

    do {
        // �޴� ���
        printf("[Menu]\n");
        printf("1. .dat ���Ͽ��� ������ �б�\n");
        printf("2. �߰� �л� ���� �Է�\n");
        printf("3. .dat ���� ����\n");
        printf("4. ���� Ȯ��(��� ��� ��)\n");
        printf("5. ����\n");
        printf("-------------------\n");
        printf("����(1~5): ");
        scanf_s("%d", &choice);  // �޴� ������ scanf_s�� ����

        switch (choice) {
        case 1:
            std_count = readfile(FILENAME);
            break;
        case 2:
            addStudentInfo();
            break;
        case 3:
            saveStudent(FILENAME);
            break;
        case 4:
            printStudentGrade();
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    } while (choice != 5); 

    return 0;
}
