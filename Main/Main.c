#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct Item {
    char name[50];
    float chance;
    float min;
    float max;
    int count;
};

void interface() {
    int ItemCount;
    float totalChance = 0.0;
    int LSize;

    printf("Enter items count: ");
    scanf("%d", &LSize);

    struct Item *items;
    items = malloc(LSize * sizeof(struct Item));

    for (int i = 0; i < LSize; i++) {
        printf("Enter chance(%) %d: ", i+1);
        scanf("%f", &items[i].chance);
        totalChance += items[i].chance;

        printf("Enter item's name %d: ", i+1);
        scanf("%49s", items[i].name);

        items[i].max += items[i].chance;
        items[i].min = 0.0;

        if (i > 0) {
            items[i].min = items[i-1].min + items[i-1].chance;
            items[i].max += items[i-1].max;
        }
    }

    if (totalChance != 100.0) {
        LSize++;
        items = realloc(items, LSize * sizeof(struct Item));
        items[LSize-1].chance = 100.0 - totalChance;
        strcpy(items[LSize-1].name, "Undefined");
        items[LSize-1].max = 100.0;
        items[LSize-1].min = items[LSize-2].max;
    }

    // array check with printf
    printf("\n");
    for (int i = 0; i < LSize; i++) {
        printf("%s | chance: %f | min: %f | max: %f\n", items[i].name, items[i].chance, items[i].min, items[i].max);
    }
    printf("\n");


    int Spins;
    double rndNum;
    printf("Enter spins amount: ");
    scanf("%d", &Spins);
    printf("\n");

    for (int i = 0; i < Spins; i++) {
        rndNum = (double)rand() / RAND_MAX * 100.0;

        for (int j = 0; j < LSize; j++) {
            if (rndNum >= items[j].min && rndNum < items[j].max) {
                items[j].count++;
                break;
            }
        }
    }

    // final answer
    printf("\n");
    for (int i = 0; i < LSize; i++) {
        printf("%s | chance: %f | rolls: %d\n", items[i].name, items[i].chance, items[i].count);
    }
    printf("\n");

}


int main() {
    srand(time(NULL));

    interface();

    return 0;
}
