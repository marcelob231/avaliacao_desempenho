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

void print_matriz (int *matriz){
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%d", matriz[i*colunas+j]);
        }
        printf("\n");
    }
}

void copy_matriz(int *matriz, int *matriz_temp){
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matriz[i*colunas+j]=matriz_temp[i*colunas+j];
        }
    }
}

void transf_matriz(int *matriz, int *matriz_temp){
    for(int i=0; i<linhas-1; i++){
        for(int j=0; j<colunas-1; j++){
            int pontos = 0;

            if (i>=1 && j>=1 && i<=linhas-1 && j<=colunas-1){
                if (matriz[(i-1)*colunas+j]==1) pontos = pontos +1;
                if (matriz[(i+1)*colunas+j]==1) pontos = pontos +1;
                if (matriz[i*colunas+j-1]==1) pontos = pontos +1;
                if (matriz[i*colunas+j+1]==1) pontos = pontos +1;
                if (matriz[(i-1)*colunas+j-1]==1) pontos = pontos +1;
                if (matriz[(i-1)*colunas+j+1]==1) pontos = pontos +1;
                if (matriz[(i+1)*colunas+j-1]==1) pontos = pontos +1;
                if (matriz[(i+1)*colunas+j+1]==1) pontos = pontos +1;
            }
            else {
                if (i==0 && j>=1){        // linha do topo
                    if (matriz[i*colunas+j+1]) pontos = pontos +1;
                    if (matriz[(i+1)*colunas+j+1]) pontos = pontos +1;
                    if (matriz[(i+1)*colunas+j]) pontos = pontos +1;
                    if (matriz[(i+1)*colunas+j-1]) pontos = pontos +1;
                    if (matriz[i*colunas+j-1]) pontos = pontos +1;
                } else{
                    if (i>=1 && j==0){        // linha da esquerda
                        if (matriz[(i+1)*colunas+j]) pontos = pontos +1;
                        if (matriz[(i+1)*colunas+j+1]) pontos = pontos +1;
                        if (matriz[i*colunas+j+1]) pontos = pontos +1;
                        if (matriz[(i-1)*colunas+j+1]) pontos = pontos +1;
                        if (matriz[(i-1)*colunas+j]) pontos = pontos +1;
                    }else{
                        if (i==linhas && j>=1){   // linha de baixo
                            if (matriz[(i-1)*colunas+j]) pontos = pontos +1;
                            if (matriz[(i-1)*colunas+j-1]) pontos = pontos +1;
                            if (matriz[i*colunas+j-1]) pontos = pontos +1;
                            if (matriz[(i-1)*colunas+j+1]) pontos = pontos +1;
                            if (matriz[i*colunas+j+1]) pontos = pontos +1;
                        }else{
                            if (i>=1 && j==colunas-1){  // linha da direita
                                if (matriz[(i-1)*colunas+j]) pontos = pontos +1;
                                if (matriz[(i-1)*colunas+j-1]) pontos = pontos +1;
                                if (matriz[i*colunas+j-1]) pontos = pontos +1;
                                if (matriz[(i+1)*colunas+j]) pontos = pontos +1;
                                if (matriz[(i+1)*colunas+j-1]) pontos = pontos +1;
                            }else{
                                if (i==0 && j==0){        // canto superior esquerdo
                                    if (matriz[i*colunas+j+1]) pontos = pontos +1;
                                    if (matriz[(i+1)*colunas+j+1]) pontos = pontos +1;
                                    if (matriz[(i+1)*colunas+j]) pontos = pontos +1;
                                }else{
                                    if (i==linhas && j==colunas){ // canto inferior direito
                                        if (matriz[(i-1)*colunas+j]) pontos = pontos +1;
                                        if (matriz[(i-1)*colunas+j-1]) pontos = pontos +1;
                                        if (matriz[i*colunas+j-1]) pontos = pontos +1;
                                    }else{
                                        if (i==0 && j==colunas-1){        // canto inferior esquerdo
                                            if (matriz[i*colunas+j-1]) pontos = pontos +1;
                                            if (matriz[(i+1)*colunas+j-1]) pontos = pontos +1;
                                            if (matriz[(i+1)*colunas+j]) pontos = pontos +1;
                                        }else{
                                            if (i==linhas-1 && j==0){ // canto superior direito
                                                if (matriz[(i-1)*colunas+j]) pontos = pontos +1;
                                                if (matriz[(i-1)*colunas+j+1]) pontos = pontos +1;
                                                if (matriz[i*colunas+j+1]) pontos = pontos +1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (matriz[i*colunas+j]==1){
                if (pontos ==2 || pontos ==3){
                    matriz_temp[i*colunas+j] = 1;
                }else{
                    matriz_temp[i*colunas+j] = 0;

                }
            }
            else{
                if(pontos == 3){
                    matriz_temp[i*colunas+j] = 1;
                }

            }
        }
    }
}

int main()
{
	int *matriz = new int [linhas*colunas];
    int *matriz_temp = new int [linhas*colunas];


	for(int i=0; i<linhas; i++){
    	for(int j=0; j<colunas; j++){
        	matriz[i*colunas+j] = 0;
        }                                   // Inicializa ambas as matrizes
    }                                       // com zeros.
    for(int i=0; i<linhas; i++){
    	for(int j=0; j<colunas; j++){
        	matriz_temp[i*colunas+j] = 0;
        }
    }

	matriz[9*colunas+20] = 1;           //Coordenadas com células iniciais.
    matriz[9*colunas+21] = 1;
	matriz[9*colunas+22] = 1;
	matriz[9*colunas+23] = 1;
	matriz[9*colunas+24] = 1;
    matriz[9*colunas+25] = 1;
	matriz[9*colunas+26] = 1;
	matriz[9*colunas+27] = 1;
	matriz[9*colunas+28] = 1;
    matriz[9*colunas+29] = 1;
    matriz[6*colunas+10] = 1;
    matriz[6*colunas+11] = 1;
    matriz[6*colunas+9] = 1;
    matriz[5*colunas+10] = 1;
    matriz[7*colunas+10] = 2;
    //print_matriz(matriz_temp);

    for(int i=0; i<200000; i++){
        transf_matriz(matriz, matriz_temp);
        copy_matriz(matriz, matriz_temp);
        //print_matriz(matriz_temp);
        //Sleep(0.2);
    }

	delete[] matriz;
    delete[] matriz_temp;
	return 0;
}



