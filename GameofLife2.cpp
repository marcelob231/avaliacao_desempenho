#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#define linhas 20
#define colunas 50

void Sleep(float s){
    int sec = int(s*1000000);
    usleep(sec);
}

void print_matriz (int **matriz){
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%d", matriz[i][j]);
        }
        printf("\n");
    }
}

void copy_matriz(int **matriz, int **matriz_temp){
    for(int j=0; j<colunas; j++){
        for(int i=0; i<linhas; i++){
            matriz[i][j]=matriz_temp[i][j];
        }
    }
}

void transf_matriz(int **matriz, int **matriz_temp){
    for(int j=0; j<colunas-1; j++){
        for(int i=0; i<linhas-1; i++){
            int pontos = 0;

            if (i>=1 && j>=1 && i<=linhas-1 && j<=colunas-1){
                if (matriz[i-1][j]==1) pontos = pontos +1;
                if (matriz[i+1][j]==1) pontos = pontos +1;
                if (matriz[i][j-1]==1) pontos = pontos +1;
                if (matriz[i][j+1]==1) pontos = pontos +1;
                if (matriz[i-1][j-1]==1) pontos = pontos +1;
                if (matriz[i-1][j+1]==1) pontos = pontos +1;
                if (matriz[i+1][j-1]==1) pontos = pontos +1;
                if (matriz[i+1][j+1]==1) pontos = pontos +1;
            }
            else {
                if (i==0 && j>=1){        // linha do topo
                    if (matriz[i][j+1]) pontos = pontos +1;
                    if (matriz[i+1][j+1]) pontos = pontos +1;
                    if (matriz[i+1][j]) pontos = pontos +1;
                    if (matriz[i+1][j-1]) pontos = pontos +1;
                    if (matriz[i][j-1]) pontos = pontos +1;
                } else{
                    if (i>=1 && j==0){        // linha da esquerda
                        if (matriz[i+1][j]) pontos = pontos +1;
                        if (matriz[i+1][j+1]) pontos = pontos +1;
                        if (matriz[i][j+1]) pontos = pontos +1;
                        if (matriz[i-1][j+1]) pontos = pontos +1;
                        if (matriz[i-1][j]) pontos = pontos +1;
                    }else{
                        if (i==linhas && j>=1){   // linha de baixo
                            if (matriz[i-1][j]) pontos = pontos +1;
                            if (matriz[i-1][j-1]) pontos = pontos +1;
                            if (matriz[i][j-1]) pontos = pontos +1;
                            if (matriz[i-1][j+1]) pontos = pontos +1;
                            if (matriz[i][j+1]) pontos = pontos +1;
                        }else{
                            if (i>=1 && j==colunas-1){  // linha da direita
                                if (matriz[i-1][j]) pontos = pontos +1;
                                if (matriz[i-1][j-1]) pontos = pontos +1;
                                if (matriz[i][j-1]) pontos = pontos +1;
                                if (matriz[i+1][j]) pontos = pontos +1;
                                if (matriz[i+1][j-1]) pontos = pontos +1;
                            }else{
                                if (i==0 && j==0){        // canto superior esquerdo
                                    if (matriz[i][j+1]) pontos = pontos +1;
                                    if (matriz[i+1][j+1]) pontos = pontos +1;
                                    if (matriz[i+1][j]) pontos = pontos +1;
                                }else{
                                    if (i==linhas && j==colunas){ // canto inferior direito
                                        if (matriz[i-1][j]) pontos = pontos +1;
                                        if (matriz[i-1][j-1]) pontos = pontos +1;
                                        if (matriz[i][j-1]) pontos = pontos +1;
                                    }else{
                                        if (i==0 && j==colunas-1){        // canto inferior esquerdo
                                            if (matriz[i][j-1]) pontos = pontos +1;
                                            if (matriz[i+1][j-1]) pontos = pontos +1;
                                            if (matriz[i+1][j]) pontos = pontos +1;
                                        }else{
                                            if (i==linhas-1 && j==0){ // canto superior direito
                                                if (matriz[i-1][j]) pontos = pontos +1;
                                                if (matriz[i-1][j+1]) pontos = pontos +1;
                                                if (matriz[i][j+1]) pontos = pontos +1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (matriz[i][j]==1){
                if (pontos ==2 || pontos ==3){
                    matriz_temp[i][j] = 1;
                }else{
                    matriz_temp[i][j] = 0;

                }
            }
            else{
                if(pontos == 3){
                    matriz_temp[i][j] = 1;
                }

            }
        }
    }
}

int main()
{
	int **matriz = new int *[linhas];
    int **matriz_temp = new int *[linhas];

	for(int i=0; i<linhas; i++){
    	matriz[i] = new int [colunas];
	}                                       // Cria matriz de impressão
	for(int i=0; i<linhas; i++){            // e a matriz temporária.
    	matriz_temp[i] = new int [colunas];
	}

	for(int j=0; j<colunas; j++){
    	for(int i=0; i<linhas; i++){
        	matriz[i][j] = 0;
        }                                   // Preenche ambas as matrizes
    }                                       // com zeros.
    for(int j=0; j<colunas; j++){
    	for(int i=0; i<linhas; i++){
        	matriz_temp[i][j] = 0;
        }
    }

	matriz[9][20] = 1;           //Coordenadas com células iniciais.
    matriz[9][21] = 1;
	matriz[9][22] = 1;
	matriz[9][23] = 1;
	matriz[9][24] = 1;
    matriz[9][25] = 1;
	matriz[9][26] = 1;
	matriz[9][27] = 1;
	matriz[9][28] = 1;
    matriz[9][29] = 1;
    matriz[6][10] = 1;
    matriz[6][11] = 1;
    matriz[6][9] = 1;
    matriz[5][10] = 1;
    matriz[7][10] = 2;
    //print_matriz(matriz_temp);

    for(int i=0; i<200000; i++){
        transf_matriz(matriz, matriz_temp);
        copy_matriz(matriz, matriz_temp);
        //print_matriz(matriz_temp);
        //Sleep(0.2);
    }

    for (int i = 0; i < linhas; ++i){
    	delete[] matriz[i];
	}
	for (int i = 0; i < linhas; ++i){
    	delete[] matriz_temp[i];
	}
	delete[] matriz;
    delete[] matriz_temp;
	return 0;
}



