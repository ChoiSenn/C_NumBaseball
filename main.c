#define _CRT_SECURE_NO_WARNINGS  // ���� ����

#include <stdio.h>
#include <string.h>  // ���ڿ� ���
#include <stdlib.h>  // ���� ���� ��
#include <time.h>  // ���� �� �ʱ�ȭ�� ���� �ð�
#include <stdbool.h>  // true, false

// ������ �̿��� ���� ���� ���� ����
void generateRandomNumbers(int* numbers, int count) {
    bool used[10] = { false };  // 0~9 ������ ��� ���θ� üũ
    int i = 0;

    // count ���� �� ä�ﶧ���� �ݺ�
    while (i < count) {
        int num = rand() % 10;  // 0~9 ������ ���� ����

        if (!used[num]) {
            numbers[i] = num;
            used[num] = true;
            i++;
        }
        // �ߺ��̸� �ٽ� ����
    }
}

// ������ �α�
void ScoreLogging(int* score, char* name) {
    time_t now_time;
    char buf[256];

    printf("%s %d", name, score);

    time(&now_time);
    ctime_s(buf, sizeof(buf), &now_time);

    FILE* fp = NULL;

    if (fopen_s(&fp, "log_score.json", "a") != 0) {
        perror("���� ���� ����");
        return;
    }

    fprintf(fp, "{ \"score\": \"%d\", \"name\": \"%s\", \"timestamp\": \"%s\" }\n", score, name, buf);

    fclose(fp);
}

void PrintLog() {

}

int main(void)

{
    printf("Game Start\n");

    srand(time(NULL));  // ���� �ʱ�ȭ
    int CorrectNumber[3] = {0, 0, 0};
    int score = 0;  // �� �� �ݺ��Ͽ� �������

    generateRandomNumbers(CorrectNumber, 3);

    // ���� �Է¹ޱ�
    while (true) {
        int AnswerNumber[3];

        score++;

        printf("���� �Է� : ");
        for (int i = 0; i < 3; i++) {
            scanf_s("%1d", &AnswerNumber[i]);
        }
        
        printf("�Է��� ���� : ");
        for (int i = 0; i < 3; i++) {
            printf("%d", AnswerNumber[i]);
        }
        printf("\n\n");

        // S, B, OUT ���� �Ǻ�
        printf("���� ����\n");
        char NumStatus[3] = {'O', 'O', 'O'};
        for (int i = 0; i < 3; i++) {
            if (CorrectNumber[i] == AnswerNumber[i]) {  // S ���� �Ǻ�
                NumStatus[i] = 'S';
            } else {  // S�� �ƴ� ���, B ���� �Ǻ�
                for (int j = 0; j < 3; j++) {
                    if (CorrectNumber[j] == AnswerNumber[i]) {
                        NumStatus[i] = 'B';
                    }
                }
            }
            // S�� B�� �ƴ� ���, OUT
        }

        printf("��� : ");
        int countS = 0;
        int countB = 0;

        for (int i = 0; i < 3; i++) {
            if (NumStatus[i] == 'S') { countS++; }
            if (NumStatus[i] == 'B') { countB++; }
        }

        if (countS == 0 && countB == 0) {  // ��� OUT�� ���
            printf("OUT...");
        } else if (countS == 3) {  // ��� Strike�� ���, ����
            printf("3 Strike !!!!\n");
            printf("���� �� : ");
            for (int i = 0; i < 3; i++) {
                printf("%d", CorrectNumber[i]);
            }
            printf("\n\n");
            break;
        }
        else {
            printf("%d Ball    %d Strike !!", countB, countS);
        }

        printf("\n\n");
        
    }

    printf("~~~ ���� ���� ~~~\n\n");

    char name[100];

    printf("�̸� �Է� : ");
    scanf("%s", name);

    printf("\n�α� : %s %d", name, score);
    ScoreLogging(score, name);

    PrintLog();

    return 0;
}