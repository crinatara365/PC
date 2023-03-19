#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util/scrabble.h"
#include "util/print_board.h"
int main () {
    char board[15][15], input[35];
    int i, j, task;
    fgets(input, 35, stdin); //prima citire din input care este numarul task-ului
    task = atoi(input); //convertim caracterul '0','1','2','3','4','5','6' in numarul 0,1,2,3,4,5,6
    for(i = 0; i < 15; i++)
        for(j = 0; j < 15; j++)
            board[i][j] = '.';


    if(task == 0)
        print_board(board);


    int N, Y, X, D;
    if(task == 1) {
        fgets(input, 35, stdin);
        N = atoi(input); //numarul de cuvinte primite
        for(i = 0; i < N; i++) { //pentru fiecare cuvant
            fgets(input, 35, stdin);
            char *p;
            p = strtok(input, " ");
            Y = atoi(p); //coord pe verticala
            p = strtok(NULL, " ");
            X = atoi(p); //coord pe orizontala
            p = strtok(NULL, " ");
            D = atoi(p); //directia pe care este scris cuvantul
            p = strtok(NULL, " "); //in p ramane cuvantul 
            if(D == 0) { //scriu cuvantul p in matrice pe orizontala
                board[Y][X] = p[0];
                int nr = 1;
                int len = strlen(p) - 1;
                for(j = X+1; j < len+X; j++) {
                    board[Y][j] = p[nr];
                    nr++;
                }
            }
            if(D == 1) { //scriu cuvantul p in matrice pe verticala 
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
            for(j = 0; j < len; j++) { //parcurg fiecare litera a cuvantului
                c = p[j] - 65; //obtin pozitia literei 
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
            if(strstr(p, XX)) { //caut XX in cuvantul p
                if(D == 0) { //caut pe orizontala
                    for(k = X; k < len+X; k++) {
                        if(bonus_board[Y][k] == 1)
                            a++; //retinem cati de 1 gasim in tabla de bonus 
                    }
                }
                if(D == 1) { //caut pe verticala
                    for(q = Y; q < len+Y; q++) {
                        if(bonus_board[q][X] == 1)
                            a++;
                    }
                }
                if(i % 2 == 0) { //punctajul primului jucator
                    while(a != 0) {
                        W = W * 2;
                        a--;
                    }
                }
                else { //punctajul celui de-al doilea jucator
                    while(a != 0){
                        T = T * 2;
                        a--;
                    }
                }
            }

            if(p[len-1] == YY[1] && p[len-2] == YY[0]) { //caut YY la finalul cuvantului p 
                if(D == 0) { //caut pe orizontala
                    for(k = X; k < len+X; k++) {
                        if(bonus_board[Y][k] == 2)
                            b++; //retin cati de 2 gasesc in tabla de bonus pe pozitiile literelor cuvantului p  
                    }
                }
                if(D == 1) { //caut pe verticala
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
            //resetez variabilele
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
        for(i = 0; i < N; i++) { //citesc fiecare cuvant
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
            p[c] = '\0'; //sterg spatiul de pe ultima pozitie a fiecarui cuvant
            if(D == 0) { //scriu cuvantul citit pe tabla de joc
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
                    vector[k] = 1; //ca sa stiu ca (,) cuvantul a fost folosit
            }
        }
        for(k = 0; k < 100; k++) { //parcurg vectorul v
            if(vector[k] == 0) {//cuvantul de la indicele j nu a fost folosit
                strcpy(x, words[k]);
                int s = strlen(x);
                for(i = 0; i < 15; i++) {
                    for(j = 0; j < 15; j++) {
                        contor1 = 0; contor2 = 0;
                        if(board[i][j] == x[0]) { //se afla pe tabla prima litera a cuvantului x
                            if(s + j - 1 < 15)
                                for(int a = j+1; a < s+j; a++) { //verific daca cuv x are loc pe orizontala
                                        if(board[i][a] != '.')
                                            contor1++; //daca contor creste am gasit o litera, deci cuv x nu are loc                            
                                }
                            else contor1 = 1;
                            if(contor1 != 0) { //verific daca cuv are loc pe verticala
                                if(s + i - 1 < 15)
                                    for(int b = i+1; b < s+i; b++) {     
                                            if(board[b][j] != '.')
                                                contor2++;    
                                    }
                                else contor2 = 1;
                            }
                            if(contor1 == 0 || contor2 == 0) { //are loc ori pe oriz, ori pe verticala
                                if(contor1 == 0) {//adaug cuv pe oriz
                                    nr = 1;
                                    for(l = j+1; l < s+j; l++) {
                                        board[i][l] = x[nr]; 
                                        nr++;
                                    }
                                    print_board(board);
                                    return 0; //opresc programul pentru ca gasit primul cuvant 
                                }
                                if(contor2 == 0 && contor1 != 0){ //adaug pe verticala
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