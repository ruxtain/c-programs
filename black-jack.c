// @Date:   2018-10-04 20:54:30
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// 游戏规则参考 https://baike.baidu.com/item/21点游戏规则/15541720

#define MORE 1  // 继续发牌
#define STOP 0  // 停止发牌
#define HAND 10 // 手牌数组大小是固定的

void swap(int* a, int* b);
int randint(int a, int b);
void shuffle(int* deck, int size); // 洗牌
int get_score(int hand[]); // 输入手牌 返回分数
void show(int hand[], int size); // 展示手牌
int update_score(int hand[], int card); // 根据手牌数组和新牌，计算并返回分数，同时输出信息

int main(void) {
    int deck[] = {
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
        1,2,3,4,5,6,7,8,9,10,10,10,10,
    };    
    int deck_size = sizeof(deck)/sizeof(int); // 固定的 208 张牌
    int order = MORE; // 指令
    int hand1[HAND] = {0}; // 玩家手牌，经过计算可知，绝对不可能超过这么多张手牌
    int hand2[HAND] = {0}; // 电脑手牌

    int hit1 = 1; // 1 表示用户继续要牌 0 表示用户不要牌
    int hit2 = 1;

    int score1;
    int score2;

    shuffle(deck, deck_size); // 洗牌

    // 说明信息
    printf("My First Simple Game\n");
    printf("Name: Black Jack 0.1\n");
    printf("Author: Michael Tan\n");
    printf("Date: 2018-10-05\n");
    printf("\n");

    // 发牌
    int index = 0; 
    while (hit1 != 0 || hit2 != 0) {
        
        int card = deck[index];

        // 偶数牌给玩家 从 0 开始
        if (index % 2 == 0 && hit1 != 0) {
            printf("\nYour turn:\n");
            score1 = update_score(hand1, card);
            if (score1 >= 21) break;
            else {
                // 玩家判断
                printf("\n\nHit me? (1 for yes, 0 for no) ");
                scanf("%d", &order);   // 阻塞
                if (order == STOP) {
                    hit1 = 0;
                }
            }
        }

        // 奇数牌给电脑
        else if (hit2 != 0) {
            printf("\nComputer's Turn:\n");
            score2 = update_score(hand2, card);
            if (score2 >= 21) break;
            else {
                // 电脑判断，超过16，17或者18时不要，带有随机性
                if (score2 >= randint(16, 18)) {
                    hit2 = 0;
                }
            }
        }

        index+=1;

    } // for loop

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\nFinal scores:\n");
    printf("You: %d\tComputer: %d\n", score1, score2);
    printf("Your cards: ");
    show(hand1, HAND);
    printf("Computer's cards: ");
    show(hand2, HAND);
    printf("\n");

    if (score1 > 21) {
        printf("You're busted! You lose!\n");
    }
    else if (score1 < 21) {
        if (score2 > 21) {
            printf("Computer is busted! You win!\n");
        } 
        else if (score2 < 21) {
            if (score1 > score2) {
                printf("Your score is higher. You win!\n");
            }
            else if (score1 < score2) {
                printf("Computer's score is higher. You lose!\n");
            }
            else {
                printf("Your and computer have a tie. No winners here.\n");
            }
        }
        else {
            printf("Computer has a BLACK JACK, you lose double!\n");
        }

    }
    else {
        printf("You have a BLACK JACK, you win double!\n");
    }
    return 0;
}


int update_score(int hand[], int card) {

    int zero = 0;
    for (int i=0; i<HAND; i++) {
        if (hand[i] == 0) {
            zero += 1;
        }
    }

    hand[HAND - zero] = card;
    printf("Cards: ");
    show(hand, HAND);
    int score = get_score(hand);
    printf("Score: %d\n", score);
    return score;
}

int get_score(int hand[]) {
    int ace = 0;
    int score = 0;
    for (int i = 0; i < HAND; ++i)
    {
        if (hand[i] == 1) {
            ace += 1;   
        }
        else {
            score += hand[i];
        }
    }

    // 总分小于等于21，则A视为11，否则视为1
    // 有多个A时，都视为1
    if (ace == 1 && score + 11 <= 21) {
        score += 11;
    }
    else {
        score += ace;
    }
    return score;
}

void show(int hand[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (hand[i]!=0)
            printf("%d ", hand[i]);
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// 产生一个 [a, b] 区间的随机数，b-a+1 表示 a,b 之间数的个数 
// a=3, b=10, 那么 rand()%(b-a+1) = rand()%8 表示 0-7 的8种随机数
// 再加上 a，于是得到 3-10 的随机数，包括3和10
int randint(int a, int b) {
    if (b < a) swap(&a, &b);
    srand((unsigned)time(NULL));
    return rand()%(b-a+1)+a;
}


// 洗牌 例如 {1,2,3,4,5} 从头开始，取第一张1，然后随机[2,5]之间的一个位置，
// 交换位置，依次后推直到最后。然后反向再来一遍，确保数字打乱得够乱。
void shuffle(int* deck, int size) {
    for (int i=0; i<size; i++) {
        int idx = randint(i, size-1); // size-1 防止取到数组外的数
        swap(&deck[i], &deck[idx]);
    } 
}