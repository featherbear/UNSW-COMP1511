//
// Created by Andrew on 8/04/2018.
//

// Write a C program crack_substitution.c which decrypts text encrypted by an unknown s cipher.
// Your program should make no assumptions about the language of the original text - don't assume its English.
//
// In other words don't hard code English properties into your program,
// extract the statistical properties from the sample plain text.
//
// Your program will be given as a command-line argument the name of a file containing
// a large amount of unencrypted text in the same language as the encrypted text.
//
// Your program will be given the encrypted text on standard input.
// You may read it all before printing the decryption.
//
// You may assume the encrypted text contains at most 10000 characters.

// Hint: you will need to look at the probabilities of sequences of 2 or
//       perhaps 3 letters occurring or perhepas the probabilities of words.

// An autotest is available to help you test your program but because this is a
// difficult problem it is possible very good attempts at the problem won't pass the autotests.

#include <stdio.h>

char substitute(int c, char cipher[]) {
    if (c >= 'a' && c <= 'z') return cipher[c - 'a'];
    if (c >= 'A' && c <= 'Z') return cipher[c - 'A'] - 32;
    return c;
}

int toLowerCase(char c) {
    return ('A' <= c && c <= 'Z') ? c + 32 : c;
}

int isLetter(char c) {
    c = toLowerCase(c);
    return 'a' <= c && c <= 'z';
}

int indexPos(char c) {
    return toLowerCase(c) - 'a';
}


int main(int argc, char *argv[]) {


#define fileArrMAX 250000
#define inputArrMAX 10000

    int c;

    int fileArr[fileArrMAX] = {'\0'};
    int i = 0;
    FILE *stream = fopen(argv[1], "r");
    while ((c = fgetc(stream)) != EOF) {
        fileArr[i] = toLowerCase(c);
        i++;
    }

    int inputArr[inputArrMAX] = {'\0'};
    i = 0;
    while ((c = getchar()) != EOF) {
        inputArr[i] = c;
        i++;
    }

    char cleanInputArr[inputArrMAX] = {'\0'};
    i = 0;
    int j = 0;
    while ((c = inputArr[i]) != '\0') {
        if (isLetter(c) || c == '\'' || c == ' ' || c == '\n') {
            if (c == ' ' && cleanInputArr[j - 1] == ' ') {
                i++;
                continue;
            }
            if (c == '\n') c = ' ';
            cleanInputArr[j] = toLowerCase(c);
            j++;
        }
        i++;
    }


    char cipherFromTo[26];


















//    int ballparkWords = 0;
//    for (i = 0; cleanInputArr[i]; i++) {
//        if (cleanInputArr[i] == ' ') ballparkWords++;
//    }
//
//    printf("Probably around %d words.\n", ballparkWords);
//    // Analysis
//    i = 0;
//    int fileArrFreqMap[26] = {0};
//    int fileArrDoublesFreqMap[26][26] = {{0}};
//    int fileArrTriplesFreqMap[26][26][26] = {{{0}}};
//    while (fileArr[i] != '\0') {
//        if (isLetter(fileArr[i])) {
//            fileArrFreqMap[indexPos(fileArr[i])]++;
//
//            if (i > 0 && isLetter(fileArr[i - 1])) {
//                fileArrDoublesFreqMap[indexPos(fileArr[i - 1])][indexPos(fileArr[i])]++;
//            }
//
//            if (i > 1 && isLetter(fileArr[i - 1]) && isLetter(fileArr[i - 2])) {
//                fileArrTriplesFreqMap[indexPos(fileArr[i - 2])][indexPos(fileArr[i - 1])][indexPos(fileArr[i])]++;
//            }
//
//
//        }
//
//        i++;
//    }
//    for (i = 0; i < 26; i++) {
//        printf("Letter '%c' has frequency %d\n", i + 'a', fileArrFreqMap[i]);
//    }
//
//    printf("\n");
//    for (i = 0; i < 26; i++) {
//        for (j = 0; j < 26; j++) {
//            if (fileArrDoublesFreqMap[i][j] > ballparkWords/8) {
//                printf("Letter pair '%c%c' has frequency %d\n", i + 'a', j + 'a', fileArrDoublesFreqMap[i][j]);
//            }
//
//        }
//
//    }
//
//


//    printf("\n\nINPUT\n\n");
//    // Analysis
//    i = 0;
//    int inputArrFreqMap[26] = {0};
//    int inputArrDoublesFreqMap[26][26] = {{0}};
//    int inputArrTriplesFreqMap[26][26][26] = {{{0}}};
//    while (cleanInputArr[i] != '\0') {
//        if (isLetter(cleanInputArr[i])) {
//            inputArrFreqMap[indexPos(cleanInputArr[i])]++;
//
//            if (i > 0 && isLetter(cleanInputArr[i - 1])) {
//                inputArrDoublesFreqMap[indexPos(cleanInputArr[i - 1])][indexPos(cleanInputArr[i])]++;
//            }
//
//            if (i > 1 && isLetter(cleanInputArr[i - 1]) && isLetter(cleanInputArr[i - 2])) {
//                inputArrTriplesFreqMap[indexPos(cleanInputArr[i - 2])][indexPos(cleanInputArr[i - 1])][indexPos(
//                        cleanInputArr[i])]++;
//            }
//
//
//        }
//
//        i++;
//    }
//
//// Letter Double Check
//    int _double_highest = 0;
//    int _double_letterFrom = 0;
//
//    int _pair_highest = 0;
//    int _pair_letterFromA = 0;
//    int _pair_letterFromB = 0;
//
//
//    printf("\n");
//    for (i = 0; i < 26; i++) {
//        for (j = 0; j < 26; j++) {
//            if (i == j) {
//                printf("Letter double '%c%c' has frequency %d\n", i + 'a', j + 'a', fileArrDoublesFreqMap[i][j]);
//                if (fileArrDoublesFreqMap[i][j] > _double_highest) {
//                    _double_letterFrom = i;
//                    _double_highest = fileArrDoublesFreqMap[i][j];
//                }
//            }
//
//            if (fileArrDoublesFreqMap[i][j] > _pair_highest) {
//                _pair_letterFromA = i;
//                _pair_letterFromB = j;
//                _pair_highest = fileArrDoublesFreqMap[i][j];
//            }
//
//
//        }
//    }
//
//    _double_highest = 0;
//    int _double_letterTo = 0;
//
//    _pair_highest = 0;
//    int _pair_letterToA = 0;
//    int _pair_letterToB = 0;
//
//    printf("\n");
//    for (i = 0; i < 26; i++) {
//        for (j = 0; j < 26; j++) {
//            if (i == j) {
//                printf("Letter double '%c%c' has frequency %d\n", i + 'a', j + 'a', inputArrDoublesFreqMap[i][j]);
//                if (inputArrDoublesFreqMap[i][j] > _double_highest) {
//                    _double_letterTo = i;
//                    _double_highest = inputArrDoublesFreqMap[i][j];
//                }
//            }
//
//            if (fileArrDoublesFreqMap[i][j] > _pair_highest) {
//                _pair_letterToA = i;
//                _pair_letterToB = j;
//                _pair_highest = fileArrDoublesFreqMap[i][j];
//            }
//        }
//
//    }
//
//
//    cipherFromTo[_double_letterFrom] = _double_letterTo + 'a';
//    printf("%c -> %c\n", _double_letterFrom + 'a', _double_letterTo + 'a');
//
//    cipherFromTo[_pair_letterFromA] = _pair_letterToA + 'a';
//    cipherFromTo[_pair_letterFromB] = _pair_letterToB + 'a';
//    printf("%c%c -> %c%c", _pair_letterFromA + 'a', _pair_letterFromB + 'a', _pair_letterToA + 'a',
//           _pair_letterToB + 'b');













    // FROM // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z //
    //   TO // a b c d e f g h i j k l m n o p q r s t u v w x y z //

    char cipher[26];

    i = j = 0;

    while (i < 26) {
        j = 0;
        while (j < 26) {
            if ('a' + i == cipherFromTo[j]) {
                cipher[i] = 'a' + j;
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (inputArr[i] != '\0') {
        putchar(substitute(c, cipher));
        i++;
    }

}

