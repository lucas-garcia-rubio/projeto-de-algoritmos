# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>

int menor_distancia(int **matriz, int *draft, int *visitado, int atual, int n, int carga);
int **cria_matriz(int n);
int *cria_vetor(int tam);
void libera_matriz(int **matriz, int nlinhas);
void libera_vetor(int *vetor);

int main(){

    DIR *dir;
    struct dirent *lsdir;

    dir = opendir("C:\\Users\\lucas\\Desktop\\PA\\processados");

    while ( ( lsdir = readdir(dir) ) != NULL ){
        if(lsdir->d_name[0] != '.'){ //tava bugado essa struct, as duas primeiras sempre estavam sendo pontos
            char local_arquivo[60];
            strcpy(local_arquivo, "C:\\Users\\lucas\\Desktop\\PA\\processados\\");
            strcat(local_arquivo, lsdir->d_name);

            FILE *arq;
            arq = fopen(local_arquivo, "r");

            int n=0; //quantidade n�s
            fscanf(arq, "%d", &n); //automaticamente l� uma linha e pula pra pr�xima
            printf("%d\n", n);
            int **matriz = cria_matriz(n); //matriz de adjac�ncia
            int *draft = cria_vetor(n); //draft de cada n�
            int *percurso = cria_vetor(n); //armazena a sequ�ncia de n�s visitados
            int *visitado = cria_vetor(n); //vator booleano, 0 quando n�o visitado, 1 quando j�
            int atual = 0; //vari�vel que armazena o n� atual
            int carga = n-1;
            int dist_percorrida = 0;
            int ultimo_visitado;

            int i, j;

            for(i=0; i<n; i++)
                for(j=0; j<n; j++)
                    fscanf(arq, "%d", &matriz[i][j]);

            for(i=0; i<n; i++)
                fscanf(arq, "%d", &draft[i]);

            for(i=0; i<n; i++){
                percurso[i] = 0;
                visitado[i] = 0;
            }

            // Iniciando o m�todo guloso
            // Preciso de uma vari�vel que armazena a menor dist�ncia do n� atual at� o n� mais perto

            percurso[0] = 0; //sempre parte do n� 0
            visitado[0] = 1;
            int iteracao = 1; //o while j� vai come�ar preenchendo o percurso da pos 1
            while(carga>0){
                ultimo_visitado = atual;
                atual = menor_distancia(matriz, draft, visitado, atual, n, carga);
                visitado[atual] = 1;
                percurso[iteracao] = atual;
                dist_percorrida += matriz[ultimo_visitado][atual];
                carga--;
                iteracao++;
            }

            printf("%s:\n", lsdir->d_name); //printa o arquivo que est� sendo processado
            for(i=0; i<n; i++) //printa o percurso do m�todo guloso
                printf("%d ", percurso[i]);
            printf("\n");

            printf("Distancia percorrida: %d\n", dist_percorrida); //printa a dist�ncia percorrida do m�todo guloso

            libera_matriz(matriz, n);
            libera_vetor(draft);
            libera_vetor(percurso);
            libera_vetor(visitado);
            fclose(arq);
            free(arq);
        }
    }
}

int menor_distancia(int **matriz, int *draft, int *visitado, int atual, int n, int carga){
    int i;
    int pos_menor = 0;
    int dist_menor = 1000000;

    for(i=0; i<n; i++)
        if(matriz[atual][i] <= dist_menor && draft[i] >= carga && atual != i && visitado[i] == 0){
            dist_menor = matriz[atual][i];
            pos_menor = i;
        }

    return pos_menor;
}

int **cria_matriz(int n)
{
  register int i;
  int **matriz;

  matriz = (int **) malloc(n*sizeof(int *));
  if (!matriz) {
        printf("Falta memoria para alocar a matriz de ponteiros if 1\n");
        exit(1);
  }
  for (i=0; i < n; i++) {
    matriz[i] = (int *) malloc(n*sizeof(int));
    if (!matriz[i]){
      printf("Falta memoria para alocar a matriz de ponteiros.\n");
      exit(1);
    }
  }
  return matriz;
}

int *cria_vetor(int tam)
{
  int *vetor;

  vetor = (int *) malloc(tam*sizeof(int));
  if (!vetor){
  	printf("Falta memoria para alocar o vetor de ponteiros");
    exit(1);
  }
  return vetor;
}

void libera_matriz(int **matriz, int nlinhas)
{
  register int i;

  for (i=nlinhas-1; i >= 0; i--)
    free((int *) matriz[i]);
  free((int *) matriz);
}

void libera_vetor(int *vetor)
{
  free(vetor);
}
