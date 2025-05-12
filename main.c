#include <stdio.h>
#include <string.h>  // 문자열 사용
#include <stdlib.h>  // 랜덤 난수 값
#include <time.h>  // 난수 값 초기화를 위한 시간
#include <stdbool.h>  // true, false

// 난수를 이용해 랜덤 정답 값을 설정
void generateRandomNumbers(int* numbers, int count) {
    bool used[10] = { false };  // 0~9 숫자의 사용 여부를 체크
    int i = 0;

    // count 개수 다 채울때까지 반복
    while (i < count) {
        int num = rand() % 10;  // 0~9 범위의 랜덤 숫자

        if (!used[num]) {
            numbers[i] = num;
            used[num] = true;
            i++;
        }
        // 중복이면 다시 뽑음
    }
}

int main(void)

{
    printf("Game Start\n");

    srand(time(NULL));  // 난수 초기화
    int CorrectNumber[3] = {0, 0, 0};

    generateRandomNumbers(CorrectNumber, 3);

    // 숫자 입력받기
    while (true) {
        int AnswerNumber[3];

        printf("숫자 입력 : ");
        for (int i = 0; i < 3; i++) {
            scanf_s("%1d", &AnswerNumber[i]);
        }
        
        printf("입력한 숫자 : ");
        for (int i = 0; i < 3; i++) {
            printf("%d", AnswerNumber[i]);
        }
        printf("\n\n");

        // S, B, OUT 여부 판별
        printf("검증 시작\n");
        char NumStatus[3] = {'O', 'O', 'O'};
        for (int i = 0; i < 3; i++) {
            if (CorrectNumber[i] == AnswerNumber[i]) {  // S 여부 판별
                NumStatus[i] = 'S';
            } else {  // S가 아닌 경우, B 여부 판별
                for (int j = 0; j < 3; j++) {
                    if (CorrectNumber[j] == AnswerNumber[i]) {
                        NumStatus[i] = 'B';
                    }
                }
            }
            // S도 B도 아닌 경우, OUT
        }

        printf("결과 : ");
        int countS = 0;
        int countB = 0;

        for (int i = 0; i < 3; i++) {
            if (NumStatus[i] == 'S') { countS++; }
            if (NumStatus[i] == 'B') { countB++; }
        }

        if (countS == 0 && countB == 0) {  // 모두 OUT일 경우
            printf("OUT...");
        } else if (countS == 3) {  // 모두 Strike인 경우, 정답
            printf("3 Strike !!!!\n");
            printf("정답 값 : ");
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

    printf("~~~ 게임 종료 ~~~");

    return 0;
}