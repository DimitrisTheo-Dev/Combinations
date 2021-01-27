#include <stdio.h>
#include <stdlib.h>

void scanNums(int totalNumbers, int *numbers) {
    int number, found, i, j;
    for(i = 0; i < totalNumbers; i++) {
        do {
            printf("Δώσε τον %dο αριθμό: ", i+1);
            scanf("%d", &number);
            if((number < 1) || (number > 49)) {
                printf("Ο αριθμός πρέπει να είναι ανάμεσα από το 1 και το 49! \n");
            }
        } while((number < 1) || (number > 49));
        
        found = 0;
        for (j = 0; j < i ; j++) {
            found = number == *(numbers + j) ? 1 : 0;
            if (found) { break; }
        }
        
        while(found == 1) {
            printf("Αυτός ο αριθμός υπάρχει ήδη! Δοκίμασε ξανά: ");
            scanf("%d", &number);
            found = 0;
            for (j = 0; j < i ; j++) {
                found = number == *(numbers + j) ? 1 : 0;
                if (found) { break; }
            }
        }
        *(numbers + i) = number;
    }
}

void scanInts(int *n1, int *n2, int min, int max, char c) {
    int num;
    do {
        printf("Δώσε %c1: ", c);
        scanf("%d", &num);
        if ((num >= min) && (num <= max)) {
            *n1 = num;
            printf("Δώσε %c2: ", c);
            scanf("%d", &num);
            if ((num >= *n1) && (num <= max)) {
                *n2 = num;
            } else {
                printf("Δοκιμάστε ξανά!\n");
            }
        } else {
            printf("Δοκιμάστε ξανά!\n");
        }
    } while(*n1 > *n2 || *n1 < min || *n2 > max);
}

void sortNumsAsc(int *numbers, int totalNumbers) {
    int k, temp, i = 1, done = 0;
    while ((i < totalNumbers) && (done == 0)) {
        done = 1;
        for (k = (totalNumbers - 1); k >= i; k--) {
            if (*(numbers + (k - 1)) > *(numbers + k)) {
                temp = *(numbers + (k - 1));
                *(numbers + (k - 1)) = *(numbers + k);
                *(numbers + k) = temp;
                done = 0;
            }
        }
        i++;
    }
}

void calcCombos(int *numbers, int totalNumbers, int x1, int x2, int y1, int y2, int K, int **second_B, int *sum, int *termOne, int *termTwo, int *counterOfNumbers, int index, int counterOfEven, int sumOfNum, int i, int counter) {
    int j;
    
    if (counter == K) { return; }
    
    for(; i < totalNumbers; i++) {
        if(counter + ((totalNumbers - K) + 1) <= i) { return; }
        
        index = counter;
        *(*(second_B + index) + 1) = i;
        *(*(second_B + index) + 0)  = *(numbers + i);
        index++;
        
        if (index == K) {
            for (j = 0; j < K; j++) {
                counterOfEven = (*(*(second_B + j) + 0) % 2 == 0) ? counterOfEven + 1 : counterOfEven;
                sumOfNum += (*(*(second_B + j)) + 0);
            }
                if ((counterOfEven >= x1) && (counterOfEven <= x2)) {
                    if((sumOfNum >= y1) && (sumOfNum <= y2)) {
                        for (j = 0; j < K; j++) {
                            printf("%d ", *(*(second_B + j) + 0));
                            (*(counterOfNumbers + (*(*(second_B + j) + 1))))++;
                        }
                        printf("\n");
                        (*sum)++;
                    } else {
                        (*(termTwo))++;
                    }
                } else {
                    (*(termOne))++;
            }
            counterOfEven = 0;
            sumOfNum = 0;
        }
        counter++;
        calcCombos(numbers, totalNumbers, x1, x2, y1, y2, K, second_B, sum, termOne, termTwo, counterOfNumbers, index, counterOfEven, sumOfNum, i+1, counter);
        counter--;
    }
}

void printTheResults(int totalNumbers, int K, int termOne, int termTwo, int sum, int *sumOfNums, int *nums, int x1, int x2, int y1, int y2) {
    int i;
    printf("Οι όροι είναι: \n");
    printf("1) Το πλήθος των άρτιων αριθμών του συνδυασμού να βρίσκεται στο διάστημα: [%d … %d] \n", x1, x2);
    printf("2) Το άθροισμα των έξι αριθμών του συνδυασμού να βρίσκεται στο διάστημα:  [%d … %d] \n", y1, y2);
    printf("Το πλήθος όλων των συνδυασμών των %d αριθών να είναι ανά %d\n", totalNumbers, K);
    printf("Οπότε έχουμε: \n");
    printf("Το πλήθος όλων των συνδυασμών %d ανά %d είναι: %d \n\n", totalNumbers, K, (termOne + termTwo + sum));
    printf("Το πλήθος των συνδυασμών που δεν πληρούσαν τον πρώτο όρο: %d\n\n", termOne);
    printf("Το πλήθος των συνδυασμών που πληρούσαν τον πρώτο, αλλά δεν πληρούσαν τον δεύτερο όρο: %d\n\n", termTwo);
    printf("Το πλήθος των συνδυασμών που πληρούν τις προϋποθέσεις είναι: %d \n\n", sum);
    for (i = 0; i < totalNumbers; i++) {
        printf("Ο αριθμός %d εμφανίστηκε %d φορές.\n", *(nums+i), *(sumOfNums + i));
    }
    printf("\n");
}


int *mallocTheArray(int totalNumbers) { return (int*) malloc(totalNumbers * sizeof(int)); }

void enterTheNumbers(int *totalNumbers) {
    do {
        printf("εισαγωγή N: ");
        scanf("%d", totalNumbers);
    } while(*totalNumbers < 6 || *totalNumbers > 49);
}

void enterK(int *K, int totalNumbers) {
    do {
        printf("εισαγωγή K: ");
        scanf("%d", K);
    } while(*K > totalNumbers);
}

int main() {
    int i, x1, x2, y1, y2, K, totalNumbers, *numbers, *sumOfNums, **second_B, *pointer_sum, *pointer_termOne, *pointer_termTwo, termOne = 0, termTwo = 0, sum = 0;
    
    pointer_sum = &sum;
    pointer_termOne = &termOne;
    pointer_termTwo = &termTwo;
    
    enterTheNumbers(&totalNumbers);
    enterK(&K, totalNumbers);

    second_B = (int **) malloc(K * sizeof(int*));
    for (i = 0; i < K; i++) {
        *(second_B + i) = mallocTheArray(2);
        if (second_B == NULL) {
            printf("Δυστυχώς δεν υπάρχει αρκετός χώρος! Έξοδος...\n");
            exit(1);
        }
    }
    
    numbers = mallocTheArray(totalNumbers);
    if (numbers == NULL) {
        printf("Δυστυχώς δεν υπάρχει αρκετός χώρος! Έξοδος...\n");
        exit(1);
    }
    
    sumOfNums = (int *) calloc(totalNumbers, sizeof(int));
    if(sumOfNums == NULL) {
        printf("Δυστυχώς δεν υπάρχει αρκετός χώρος! Έξοδος...\n");
        exit(1);
    }
    
    scanNums(totalNumbers, numbers);
    sortNumsAsc(numbers, totalNumbers);
    scanInts(&x1, &x2, 0, 6, 'X');
    scanInts(&y1, &y2, 21, 279, 'Y');
    calcCombos(numbers, totalNumbers, x1, x2, y1, y2, K, second_B, pointer_sum, pointer_termOne, pointer_termTwo, sumOfNums, 0, 0, 0, 0, 0);
    printTheResults (totalNumbers, K, termOne, termTwo, sum, sumOfNums, numbers, x1, x2, y1, y2);
    free(numbers);
    free(second_B);
    free(sumOfNums);
}

