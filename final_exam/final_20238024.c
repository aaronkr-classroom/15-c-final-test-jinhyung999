#include <stdio.h>

#define MAX_SIZE 100
#define FILENAME "students.dat"  // 파일 이름 정의

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
    fopen_s(&file, filename, "rb"); // 이진 형식으로 파일 열기
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 0;  
    }

    int count = fread(students, sizeof(Student), MAX_SIZE, file);  
    fclose(file);  

    return count;  
}

void saveStudent(const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "wb");  // 이진 형식으로 파일 열기
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fwrite(students, sizeof(Student), std_count, file);  
    fclose(file);  
    printf("저장 완료\n");
}

void printStudentGrade() {
    for (int i = 0; i < std_count; i++) {
        int total = students[i].koreanScore + students[i].englishScore + students[i].mathScore;
        double average = total / 3.0;

        printf("이름: %s\n", students[i].name);
        printf("국어: %d, 영어: %d, 수학: %d\n", students[i].koreanScore, students[i].englishScore, students[i].mathScore);
        printf("총점: %d, 평균: %.2f\n\n", total, average);
    }
}

void addStudentInfo() {
    if (std_count >= MAX_SIZE) {
        printf("더 이상 학생을 추가할 수 없습니다.\n");
        return;
    }

    printf("학생 이름을 입력하세요: ");
    scanf_s("%99s", students[std_count].name, sizeof(students[std_count].name));  
    printf("국어 점수를 입력하세요: ");
    scanf_s("%d", &students[std_count].koreanScore);
    printf("영어 점수를 입력하세요: ");
    scanf_s("%d", &students[std_count].englishScore);
    printf("수학 점수를 입력하세요: ");
    scanf_s("%d", &students[std_count].mathScore);

    std_count++;  // 학생 수 증가
    printf("학생 정보가 추가되었습니다.\n");
}

int main() {
    int choice;
    std_count = readfile(FILENAME);

    do {
        // 메뉴 출력
        printf("[Menu]\n");
        printf("1. .dat 파일에서 데이터 읽기\n");
        printf("2. 추가 학생 정보 입력\n");
        printf("3. .dat 파일 저장\n");
        printf("4. 성적 확인(평균 계산 등)\n");
        printf("5. 종료\n");
        printf("-------------------\n");
        printf("선택(1~5): ");
        scanf_s("%d", &choice);  // 메뉴 선택을 scanf_s로 변경

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
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    } while (choice != 5); 

    return 0;
}
