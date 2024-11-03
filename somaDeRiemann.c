/**
 * Calculadora de integrais definidas para funcoes polinomiais
 * @author Gloria Eleonor Ferreira Alves
 * @version 2 11/2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

float calcular_distancia_entre_pontos(float b, float a, int n){
    float d = (b-a)/n;
    return d;
}

void calcular_pontos_dir(float pontos[], float a, int n, float d){
    int j = 1;
    for(int i = 0; i < n; i++, j++){
        pontos[i] = a+(j*d);
    }
}

void calcular_pontos_esq(float pontos[], float a, int n, float d){
    for(int i = 0; i < n; i++){
        pontos[i] = a+(i*d);
    }
}

//Funcao calcula e retorna a quantidade de termos de uma funcao polinomial.
int contar_termos(char* s, int tam){
    int c = 1;
    for(int i = 0; i < tam; i++){
        if(s[i] == ' '){
            c++;
        }
    }
    return c;
}

//Funcao preenche dois vetores, um de tipo string que armazena os monomios que compoem a expressao algebrica e outro de tipo int que armazena o valor numerico destes termos.
void dividir_termos_da_funcao(char* f, char** termos, int valor_numerico_dos_termos[], int c){
    
    char sep[] = " ";
    int i = 0;
    char* token;
    token = strtok(f, sep);
    while(token != NULL){
        termos[i++] = token;
        token = strtok(NULL, sep);
    }

    for(int i = 0; i < c; i++){
        valor_numerico_dos_termos[i] = atoi(termos[i]);
    }

    /*
    Obs: se determinado elemento do vetor valor_numerico_dos_termos[] for igual a 0, significa que nao foi possivel transformar o termo correspondente do vetor termos[] em um numero inteiro, ou seja, provavelmente 0 corresponde a x elevado a alguma coisa. Precisamos conservar os dois vetores para conseguir realizar a operacao.
    */   
}

//Funcao retorna se x é negativo.
bool is_x_negativo(char* x){
    bool r = false;
    char primeiro_caractere = x[0];
    if(primeiro_caractere == '-'){
        r = true;
    }
    return r;
}

//Funcao retorna o expoente de x.
int identificar_expoente(char* x){
    int expoente = 1;
    int tam = strlen(x);
    if(tam == 4){
        sscanf(x, " %*c%*c%*c%d", &expoente); //ex: -x^2
    } else {
        sscanf(x, " %*c%*c%d", &expoente); //ex: x^2
    }
    return expoente;
}

float calcular_soma_dir(char* f, int b, int a, int n){
    //calcular delta x (distancia)
    float distancia = calcular_distancia_entre_pontos(b, a, n);
    
    //preencher vetor com valor dos pontos
    float pontos[n];
    calcular_pontos_dir(pontos, a, n, distancia);

    //identificar quantidade de termos/monomios da funcao
    int c = contar_termos(f, strlen(f));
    
    //criar e preencher vetores com termos da funcao (variaveis e numeros)
    char* termos[c];    
    int valor_numerico_dos_termos[c];
    dividir_termos_da_funcao(f, termos, valor_numerico_dos_termos, c);
    
    //declarar vetor que irá armazenar o valor da funcao nos pontos escolhidos 
    float fxi[n];
    //inicializar posicoes de fxi[] com 0 para evitar que o vetor armazene lixo
    for(int i = 0; i < n; i++){
        fxi[i] = 0;
    }

    /*
    CALCULO DO VALOR DA FUNCAO NOS PONTOS ESCOLHIDOS
    O for externo percorre o vetor de pontos[], enquanto o for interno percorre o vetor valor_numerico_dos_termos[] para calcular o termo fxi[i]. Se o valor numerico for 0, analisamos o elemento armazendo no index correspondente do vetor termos[] a fim de calcular qual o valor de x, levando em consideracao se ele é negativo e o valor de seu expoente.
    */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            if(valor_numerico_dos_termos[j] == 0){
                int expoente = identificar_expoente(termos[j]);
                if(expoente == 1){
                    if(is_x_negativo(termos[j])){
                        fxi[i] += -pontos[i];
                    } else {
                        fxi[i] += pontos[i];
                    }
                } else {
                    if(is_x_negativo(termos[j])){
                        fxi[i] += pow((-pontos[i]), expoente);
                    } else {
                        fxi[i] += pow(pontos[i], expoente);
                    }
                }
            } else {
                fxi[i] += valor_numerico_dos_termos[j];
            }
        }
    }

    //CALCULO DO SOMATORIO
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += fxi[i]*distancia;
    }

    return soma;
}

float calcular_soma_esq(char* f, int b, int a, int n){
    float distancia = calcular_distancia_entre_pontos(b, a, n);
    
    float pontos[n];
    calcular_pontos_esq(pontos, a, n, distancia);

    int c = contar_termos(f, strlen(f));
    
    char* termos[c];
    int valor_numerico_dos_termos[c];
    dividir_termos_da_funcao(f, termos, valor_numerico_dos_termos, c);
    
    float fxi[n];
    for(int i = 0; i < n; i++){
        fxi[i] = 0;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            if(valor_numerico_dos_termos[j] == 0){
                int expoente = identificar_expoente(termos[j]);
                if(expoente == 1){
                    if(is_x_negativo(termos[j])){
                        fxi[i] += -pontos[i];
                    } else {
                        fxi[i] += pontos[i];
                    }
                } else {
                    if(is_x_negativo(termos[j])){
                        fxi[i] += pow((-pontos[i]), expoente);
                    } else {
                        fxi[i] += pow(pontos[i], expoente);
                    }
                }
            } else {
                fxi[i] += valor_numerico_dos_termos[j];
            }
        }
    }

    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += fxi[i]*distancia;
    }

    return soma;
}

void imprimir_resultado(char* f, int b, int a, int n){
    printf("\nSoma para N retangulos, quando N = %d\n", n);
    float somaDir = calcular_soma_dir(f, b, a, n);
    float somaEsq = calcular_soma_esq(f, b, a, n);
    printf("Resultado da soma a direita: %.9f\n", somaDir);
    printf("Resultado da soma a esquerda: %.9f\n\n", somaEsq);
}

int main() {
    printf("Obs: Apos o primeiro termo da funcao, o sinal (+ ou -) que acompanha os termos seguintes precisa ser escrito junto do seu respectivo termo (sem espaco), por ex: x^2 +x +1\n\n");
    
    int n1 = 100, n2 = 300, n3 = 600, n4 = 1000, n5 = 1500, n6 = 2000;
    
    char f[101];
    printf("Digite a funcao: ");
    scanf(" %101[^\r\n]", f);
    
    float b = 0, a = 0;
    printf("Digite o intervalo da funcao (formato: a, b): ");
    scanf(" %f %*c %f", &a, &b);
    
    //o resultado do somatorio à direita e à esquerda é impresso para cada n
    imprimir_resultado(f, b, a, n1);
    imprimir_resultado(f, b, a, n2);
    imprimir_resultado(f, b, a, n3);
    imprimir_resultado(f, b, a, n4);
    imprimir_resultado(f, b, a, n5);
    imprimir_resultado(f, b, a, n6);

    return 0;
}