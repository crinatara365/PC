#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util/scrabble.h"
#include "util/print_board.h"
int main () {
    char board[15][15], input[35];
    int i, j, task;
    fgets(input, 35, stdin); 
    task = atoi(input); 
    for(i = 0; i < 15; i++)
        for(j = 0; j < 15; j++)
            board[i][j] = '.';


    if(task == 0)
        print_board(board);


    int N, Y, X, D;
    if(task == 1) {
        fgets(input, 35, stdin);
        /* numarul de cuvinte primite */
        N = atoi(input); 
        for(i = 0; i < N; i++) { 
            fgets(input, 35, stdin);
            char *p;
            p = strtok(input, " ");
            /* coord pe verticala */
            Y = atoi(p); 
            p = strtok(NULL, " ");
            /* coord pe orizontala */
            X = atoi(p); 
            p = strtok(NULL, " ");
            /* directia pe care este scris cuvantul */
            D = atoi(p);
            p = strtok(NULL, " ");  
            if(D == 0) { 
                board[Y][X] = p[0];
                int nr = 1;
                int len = strlen(p) - 1;
                for(j = X+1; j < len+X; j++) {
                    board[Y][j] = p[nr];
                    nr++;
                }
            }
            if(D == 1) { 
                board[Y][X] = p[0];
                int nr = 1;
                int len = strlen(p) - 1;
                for(j = Y+1; j < len+Y; j++) {
                    board[j][X] = p[nr];
                    nr++;
                }
            }
        }
        print_board(board);
    }


    int v[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    int val, c, W=0, T=0;
    if(task == 2) {
        fgets(input, 35, stdin);
        N = atoi(input);
        for(i = 0; i < N; i++) {
            fgets(input, 35, stdin);
            char *p;
            p = strtok(input, " ");
            Y = atoi(p);
            p = strtok(NULL, " ");
            X = atoi(p);
            p = strtok(NULL, " ");
            D = atoi(p);
            p = strtok(NULL, " ");
            int len = strlen(p) - 1;
            for(j = 0; j < len; j++) { 
                /* pozitia literei */
                c = p[j] - 65; 
                val = v[c]; 
                if(i % 2 == 0) {
                    W = W + val;
                }
                else {
                    T = T + val;
                }
            }
        }
        printf("Player 1: %d Points\n", W);
        printf("Player 2: %d Points\n", T);
    }


    char XX[3], YY[3];
    int k, q, a=0, b=0, total1=0, total2=0;
    if(task == 3) {
        fgets(input, 35, stdin);
        XX[0] = input[0];
        XX[1] = input[1];
        XX[2] = '\0';
        fgets(input, 35, stdin);
        YY[0] = input[0];
        YY[1] = input[1];
        YY[2] = '\0';
        fgets(input, 35, stdin);
        N = atoi(input);
        for(i = 0; i < N; i++) {
            fgets(input, 35, stdin);
            char *p;
            p = strtok(input, " ");
            Y = atoi(p);
            p = strtok(NULL, " ");
            X = atoi(p);
            p = strtok(NULL, " ");
            D = atoi(p);
            p = strtok(NULL, " ");
            int len = strlen(p) - 1;
            for(j = 0; j < len; j++) {
                c = p[j] - 65;
                val = v[c];
                if(i % 2 == 0) {
                    W = W + val;
                }
                else {
                    T = T + val;
                }
            }
             /* cautam XX in cuvantul p */
            if(strstr(p, XX)) {
                if(D == 0) {
                    for(k = X; k < len+X; k++) {
                        if(bonus_board[Y][k] == 1)
                            /* retinem cati de 1 gasim in tabla de bonus  */
                            a++; 
                    }
                }
                if(D == 1) { 
                    for(q = Y; q < len+Y; q++) {
                        if(bonus_board[q][X] == 1)
                            a++;
                    }
                }
                /* punctajul primului jucator */
                if(i % 2 == 0) { 
                    while(a != 0) {
                        W = W * 2;
                        a--;
                    }
                }
                /* punctajul celui de-al doilea jucator */
                else {
                    while(a != 0){
                        T = T * 2;
                        a--;
                    }
                }
            }

            /* cautam YY la finalul cuvantului p */
            if(p[len-1] == YY[1] && p[len-2] == YY[0]) { 
                if(D == 0) { //caut pe orizontala
                    for(k = X; k < len+X; k++) {
                        if(bonus_board[Y][k] == 2)
                            /* retinem cati de 2 gasesc in tabla de bonus pe pozitiile literelor cuvantului p */  
                            b++; 
                    }
                }
                if(D == 1) { 
                    for(q = Y; q < len+Y; q++) {
                        if(bonus_board[q][X] == 2)
                            b++;
                    }
                }
                if(i % 2 == 0) { 
                    while(b != 0) {
                        W = W * 3;
                        b--;
                    }
                }
                else {
                    while(b != 0){
                        T = T * 3;
                        b--;
                    }
                }
            }
            total1 = total1 + W;
            total2 = total2 + T;
            a=0; b=0; 
            W = 0;
            T = 0;
        }
        
        printf("Player 1: %d Points\n", total1);
        printf("Player 2: %d Points\n", total2);
    }


    int vector[100] = {0}, l;
    int contor1 = 0, contor2 = 0, nr = 1;
    char x[30];
    if(task == 4) {
        fgets(input, 35, stdin);
        XX[0] = input[0];
        XX[1] = input[1];
        XX[2] = '\0';
        fgets(input, 35, stdin);
        YY[0] = input[0];
        YY[1] = input[1];
        YY[2] = '\0';
        fgets(input, 35, stdin);
        N = atoi(input);
        for(i = 0; i < N; i++) { 
            fgets(input, 35, stdin);
            char *p;
            p = strtok(input, " ");
            Y = atoi(p);
            p = strtok(NULL, " ");
            X = atoi(p);
            p = strtok(NULL, " ");
            D = atoi(p);
            p = strtok(NULL, " ");
            int c = strlen(p) - 1;
            /* sterg spatiul de pe ultima pozitie a fiecarui cuvant */
            p[c] = '\0';
            if(D == 0) {
                board[Y][X] = p[0];
                int nr = 1;
                for(j = X+1; j < c+X; j++) {
                    board[Y][j] = p[nr];
                    nr++;
                }
            }
            if(D == 1) {
                board[Y][X] = p[0];
                int nr = 1;
                for(j = Y+1; j < c+Y; j++) {
                    board[j][X] = p[nr];
                    nr++;
                }
            }
            for(k = 0; k < 100; k++) {
                if(strcmp(words[k], p) == 0)
                    /* sa stim daca cuvantul a fost folosit */
                    vector[k] = 1; 
            }
        }
        for(k = 0; k < 100; k++) { 
            if(vector[k] == 0) {
                strcpy(x, words[k]);
                int s = strlen(x);
                for(i = 0; i < 15; i++) {
                    for(j = 0; j < 15; j++) {
                        contor1 = 0; contor2 = 0;
                        /* se afla pe tabla prima litera a cuvantului x */
                        if(board[i][j] == x[0]) { 
                            if(s + j - 1 < 15)
                                /* verificam daca cuvantul are loc pe orizontala */
                                for(int a = j+1; a < s+j; a++) { 
                                        if(board[i][a] != '.')
                                            /* daca contor creste am gasit o litera, deci cuvantul nu are loc */
                                            contor1++;                            
                                }
                            else 
                                contor1 = 1;
                            /* verificam daca cuvantul are loc pe verticala */
                            if(contor1 != 0) { 
                                if(s + i - 1 < 15)
                                    for(int b = i+1; b < s+i; b++) {     
                                            if(board[b][j] != '.')
                                                contor2++;    
                                    }
                                else contor2 = 1;
                            }
                            if(contor1 == 0 || contor2 == 0) { 
                                /* adaugam pe orizontala */
                                if(contor1 == 0) {
                                    nr = 1;
                                    for(l = j+1; l < s+j; l++) {
                                        board[i][l] = x[nr]; 
                                        nr++;
                                    }
                                    print_board(board);
                                    return 0; 
                                }
                                /* adaugam pe verticala */
                                if(contor2 == 0 && contor1 != 0){ 
                                    nr = 1;
                                    for(l = i+1; l < i+s; l++) {
                                        board[l][j] = x[nr];
                                        nr++;
                                    }
                                    print_board(board);
                                    return 0;
                                }
                                
                            
                            }
                        }
                    }
                }
            } 
        }
    }


    
    return 0;
}
