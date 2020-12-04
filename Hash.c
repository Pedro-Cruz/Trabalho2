# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# define TAM_MAX 100000

/******************************************************************************/

struct dados
{
  int info;
  struct dados *prox;
};

typedef struct dados Dados;
typedef Dados* Hash[TAM_MAX];



/*funcaoHash  recebe como parametro uma variavel do tipo inteiro(num),
retorna a  restra da divisao do valor dessa variavel pela TAM_MAXanho da tabela*/
int funcaoHash(int num)
{
  return(num%TAM_MAX);
}

/*O procedimento inicializaHash recebe como parametro uma variavel do tipo
 Hash e sua funcao e que todas as posicoes da tab se tornem nulas*/
void inicializaHash(Hash tab)
{
 int i;
 for(i = 0; i < TAM_MAX; i++)
 {
  tab[i] = NULL;
 }
}
/*O procedimento insererHash recebe como parametro dois argumentos uma
variavel do tipo Hash e outra do tipo num. Sua funcao e inserir os elementos
na tabela atraveis da funcaoHash e caso esta posicao ja esteja preenchida,
como colisao esta sendo adotado neste procedimento o encadeamento direto.*/
void insereHash(Hash tab, int num)
{
 int i = 0;
 int chave = funcaoHash(num);
 Dados* aux = tab[chave];
 while(aux != NULL)
 {
  if(aux->info == num)
  {
   break;
  }
  aux = aux->prox;
 }
 if(aux == NULL)
 {
  aux = (Dados*) malloc (sizeof(Dados));
  aux->info = num;
  aux->prox = tab[chave];
  tab[chave] = aux;
 }
}

/*O procedimento buscaHash recebe como parametro duas variaveis uma do
tipo Hash(tab) e outra do tipo inteiro(num),A variavel tab tem como funcao
 passar a tabela e a variavel num tem como funcao determinar a posicao da
 tabela que o usuario deseja visualizar */
 
void buscaHash(Hash tab,int num)
{
 int pos = num;
 if(num > TAM_MAX || num < 0)
 {
  printf("\nPosicao nao encontrada!");
  return;
 }else
 {
 // imprimeColisao(tab,pos);
}
}

/*O procedimento imprimeColisaon mostra uma posicao
e todas as suas colisoes.*/
void imprimeColisao(Hash tab, int pos)
{
 Dados* aux = tab[pos];
 if(aux == NULL)
 {
  printf("Esta posicao esta vazia!");
  return;
 }else
 {
  if(aux != NULL)
  {
   printf("%3d",aux->info);
   while(aux->prox != NULL)
   {
    printf(" -> %d",aux->prox->info);
    aux = aux->prox;
   }
  }
 }
}

/*O procedimento imprimeHash recebe como parametro uma variavel do tipo Hash.
Sua funcao e imprimir todos os elementos da variavel do tipo Hash*/
void imprimeHash(Hash tab)
{
 int  i = 0,cont = 0;
 printf("Posicoes\tTabela");
 for(i = 0; i < TAM_MAX; i++)
 {
  if(tab[i] != NULL)
  {
   printf("\n  %d\t\t%d",i,tab[i]->info);
   Dados* aux =tab[i]->prox;
   while(aux!=NULL)
   {
    printf(" -> %3d",aux->info);
     aux=aux->prox;
   }
  }
 }
}

/*O procedimento removeHash recebe como parametro uma variavel do tipo Hash
e outra do tipo inteiro, a variavel do tipo Hash serve para termos acesso
a tabela e a variavel do tipo inteiro serve para escolher a posicao que o
usuario deseja visualizar, apos a visualizacao da chave, o usuario escolhe a
informacao da chave que deseja eliminar*/
void removeHash(Hash tab, int num)
{
 int pos = num;
 int ex ;
 if(num > TAM_MAX)
 {
  printf("\nEsta posicao nao existe na tabela!");
 }else{
  if(tab[pos] == NULL)
  {
   printf("Esta chave esta vazia!");
  }else
  {
   printf("\n\n\n");
   imprimeColisao(tab,pos);
   printf("\n\nQual registro deseja apagar =  ");
   scanf("%d",&ex);
   if(tab[pos]->info == ex)
   {
    if(tab[pos]->prox == NULL)
    {
     tab[pos] = NULL;
     return;
    }
    if(tab[pos]->prox != NULL)
    {
     tab[pos]->info = tab[pos]->prox->info;
     tab[pos]->prox = tab[pos]->prox->prox;
     return;
    }
   }else{
   if(tab[pos]->info != ex)
   {

    if(tab[pos]->prox == NULL)
    {
     printf("\nRegistro nao encontrado!");
     getch();
     return;
    }else{
    Dados* ant = NULL;
    Dados* aux = tab[pos]->prox;
    while(aux->prox != NULL  && aux->info != ex)
    {
     ant = aux;
     aux = aux->prox;
    }
    if(aux->info != ex)
    {
     printf("\nRegistro nao encontrado!\n");
     return;
    }else
    {
    if(ant == NULL)
    {
     tab[pos]->prox = aux->prox;
    }else{
         ant->prox = aux->prox;
        }
        aux = NULL;
        free(aux);
        }
      }
     }
    }
   }
  }
}

/******************************************************************************/

typedef struct reg {
	int  item;
	int ocupado;
}HASH2;


int funcaohash(int  chave) {
	return (chave % TAM_MAX);
}

void inicializa(HASH2 tabHash[]) {
	int i;
	for(i=0; i<TAM_MAX; i++)
		tabHash[i].ocupado = 0; // falso
}

void insere(HASH2 tabHash[], int  e) {
	
	if (cheia(tabHash)) { // Se tabela cheia, imprime aviso e sai da função
	//	puts("\n->ATENCAO Tabela cheia");
		return; // saida imediata da função, nao executa os comandos abaixo
	}
	
	int pos = funcaohash(e); // CALCULA POSIÇAO
	
	// INICIO ROTINA TRATAMENTO DE COLISAO
	if (tabHash[pos].ocupado == 1) { // se ocorreu colisao
		if (e==tabHash[pos].item) { // se a chave ja existe
		//	puts("\n->ATENCAO Esse item ja foi cadastrado");
			return; // saida imediata da função
		}
	//	printf("-> Ocorreu uma colisao na posicao %d\n",pos);
		while (pos < TAM_MAX) {
			if (pos==TAM_MAX-1) pos=-1; // volta para o inicio da tabela
			pos++; // incremento mais um no indice
			if (tabHash[pos].ocupado == 0) // se a posição estiver livre
				break; // sai do loop com o indice na posicao correta (pos sem colisão)
		}
	}
	// FIM ROTINA TRATAMENTO DE COLISAO
	
	tabHash[pos].item=e;
	tabHash[pos].ocupado = 1;
//	printf("-> Inserido HASH[%d]",pos);
}

// Retorna -1 se nao encontrou ou a posição caso encontre o item
int busca(HASH2 tabHash[], int  chave) { // Recuperando um elemento
	int pos = funcaohash(chave);
	int iniciobusca = pos;
	if (tabHash[pos].ocupado == 1) { // se nessa posicao esta ocupado 
	
		if (tabHash[pos].item == chave) // Se item e chave são iguais	
			return pos; // saida imediata da função
		
		// INICIO ROTINA TRATAMENTO DE COLISAO	(se o item e chave nao sao iguais)
		while (pos < TAM_MAX) { // percorre proximas posições do vetor
			if (pos==TAM_MAX-1) pos=-1; // volta para o inicio da tabela
			pos++; // incremento mais um no indice
			if (tabHash[pos].ocupado == 1 && tabHash[pos].item == chave) 
			// se o campo esta ocupado e o item foi encontrado
				return pos; // saida imediata da função
			if (pos==iniciobusca) return -1; // se percorreu tudo e nao encontrou
		}
		// FIM ROTINA TRATAMENTO DE COLISAO
		
	}
	return -1; // Se nao existe essa chave
}

void apaga(HASH2 tabHash[], int  chave) {
    int pos = busca(tabHash,chave);
	if (pos!=-1) {
		tabHash[pos].ocupado=0;
		printf("-> Dados HASH[%d] apagados",pos);
	}
	else printf("Item nao encontrado");
}

void imprime(HASH2 tabHash[]) {
	int i;
	for (i=0; i<TAM_MAX; i++)
		if( tabHash[i].ocupado == 1)
			printf("\nCampo [%d] = %d",i,tabHash[i].item);
}

int cheia(HASH2 tabHash[]) {
	int i, qtde=0;
	for (i=0; i<TAM_MAX; i++)
		if( tabHash[i].ocupado == 1)
			qtde++;
	if (qtde == TAM_MAX) return 1;
	else return 0;
}

main() {
	int i, pos;
	HASH2 tab[TAM_MAX]; // criando tabela na memoria
	Hash tabela;
	inicializa(tab);
	inicializaHash(tabela);
	double start, stop, elapsed; // variaveis para medir o tempo
    srand(time(NULL)); // gera valores completamente aleatorios em cada execucao do programa
	int vetorAleatorio[TAM_MAX-1];
	
	printf("Tabela Hash: Tempo de insercao\n");
	/* Inserindo valores Hash Sem Lista */
	 srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC; // inicia a contagem
	for (i = 0; i < TAM_MAX-1; i++){	 /* gerando valores aleatórios entre zero e 100 */
    vetorAleatorio[i] = (rand() % 100);
    insere(tab,vetorAleatorio[i]);
  }
	stop = (double) clock() / CLOCKS_PER_SEC; // para a contagem
  	elapsed = stop - start;   // Tempo 
    printf("Hash sem Lista: %f\n", elapsed);
    /***********************************************/
    
    	/* Inserindo valores Hash com Lista */
	 srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC; // inicia a contagem
	for (i = 0; i < TAM_MAX-1; i++){	 /* gerando valores aleatórios entre zero e 100 */
    insereHash(tabela,vetorAleatorio[i]);
  }
	stop = (double) clock() / CLOCKS_PER_SEC; // para a contagem
  	elapsed = stop - start;   // Tempo 
    printf("Hash com Lista: %f\n", elapsed);
    /***********************************************/
    
    	printf("Tabela Hash: Tempo de Busca\n");
	/* Inserindo valores Hash Sem Lista */
	 srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC; // inicia a contagem
	for (i = 0; i < TAM_MAX-1; i++){	 /* gerando valores aleatórios entre zero e 100 */
    busca(tab, vetorAleatorio[i]);
  }
	stop = (double) clock() / CLOCKS_PER_SEC; // para a contagem
  	elapsed = stop - start;   // Tempo 
    printf("Hash sem Lista: %f\n", elapsed);
    /***********************************************/
    
    	/* Inserindo valores Hash Sem Lista */
	 srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC; // inicia a contagem
	for (i = 0; i < TAM_MAX-1; i++){	 /* gerando valores aleatórios entre zero e 100 */
    buscaHash(tabela,vetorAleatorio[i]);
  }
	stop = (double) clock() / CLOCKS_PER_SEC; // para a contagem
  	elapsed = stop - start;   // Tempo 
    printf("Hash com Lista: %f\n", elapsed);
    /***********************************************/
  
  /*printf("\n\nHASH COM LISTAS\n\n");
  imprimeHash(tabela);
  printf("\n\nHASH SEM LISTAS\n\n");
  imprime(tab);
	*/

}
