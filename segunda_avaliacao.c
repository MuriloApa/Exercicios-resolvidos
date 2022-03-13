/*Aqui está minha solução para o problema proposto como segunda avaliação da disciplina de Algoritmos e Programação II no curso de Sistemas de Informação
ministrada na UFMS câmpus de Três Lagoas
  O enunciado, bem como exemplos de entrada e saída, estão num arquivo em formato pdf neste mesmo repositório com o mesmo nome deste código escrito em c*/

/*Trabalho realizado em dupla. 
Integrantes: Murilo Aparecido Carvalho Nascimento e Rafael Andrade Meneghette*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Esta primeira parte do código é onde estão localizados os formatos das listas com cabeça encadeadas dinamicamente, além de conter 
também as diversas funções utilizadas pelo código principal*/

/*Este primeiro registro diz respeito ao formato das células para a lista das palavras*/
/*a chave, ou campo de identificação, será a própria palavra. A string tem tamanho máximo de 45 caracteres, pois, considera a maior palavra
do idioma inglês, pneumonoultramicroscopicsilicovolcanoconiosis*/
/*O campo freq registra quantas vezes a palavra foi mencionada no texto*/
struct cel{
    char chave[46];
    int freq;
    struct cel *prox;
};

typedef struct cel celula;

/*O registro abaixo é para a lista que conterá as tags, a única diferença dele para o acima é o tamanho da string para chave*/
/*O tamanho reduzido se deve ao fato das tags serem menores que as palavras*/
struct cel2{
    char chave[6];
    int freq;
    struct cel2 *prox;
};

typedef struct cel2 celula2;

/*A função abaixo é responsável por alocar uma nova célula para a lista que contém as palavras*/
celula *aloca_cc (char *word)
{
    celula *nova;
    nova=(celula*) malloc(sizeof(celula));
    if (nova==NULL)
    {
        fprintf(stderr, "Erro ao alocar nova célula\n");
        return NULL;
    }
    else
    {
        strcpy(nova->chave, word);
        nova->prox=NULL;
        nova->freq=1;
        return nova;
    } 
}

/*A função abaixo é responsável por alocar uma nova célula para a lista que contém as tags*/
celula2 *aloca_cc2 (char *word)
{
    celula2 *nova;
    nova=(celula2*) malloc(sizeof(celula2));
    if (nova==NULL)
    {
        fprintf(stderr, "Erro ao alocar nova célula\n");
        return NULL;
    }
    else
    {
        strcpy(nova->chave, word);
        nova->prox=NULL;
        nova->freq=1;
        return nova;
    } 
}

/*Fazendo uso da função de alocação, a função abaixo realiza a inserção de forma manter a ordem alfabética*/
void insercao_alfabetica (celula *lst, char *word)
{
    celula *pt, *nova;
    if (lst->prox==NULL)
    {
        lst->prox=aloca_cc(word);
    }
    else
    {
        pt=lst;
        while (pt->prox!=NULL && strcmp(pt->prox->chave, word)<0)
        {
            pt=pt->prox;
        }
        nova=aloca_cc(word);
        nova->prox=pt->prox;
        pt->prox=nova;
    }
}

/*Função semelhante a descrita anteriomente, com a diferença que esta é para a lista das tags*/
void insercao_alfabetica2 (celula2 *lst, char *word)
{
    celula2 *pt, *nova;
    if (lst->prox==NULL)
    {
        lst->prox=aloca_cc2(word);
    }
    else
    {
        pt=lst;
        while (pt->prox!=NULL && strcmp(pt->prox->chave, word)<0)
        {
            pt=pt->prox;
        }
        nova=aloca_cc2(word);
        nova->prox=pt->prox;
        pt->prox=nova;  
    }
}

/*Função para buscar uma palavra dentro da lista*/
celula *busca (celula *lista, char *word)
{
    celula *pt;
    pt=lista->prox;
    while (pt!=NULL && strcmp(pt->chave, word)!=0)
    {
        pt=pt->prox;
    }
    return pt;
}

/*Função para buscar uma tag já armazenada na lista*/
celula2 *busca2 (celula2 *lista, char *word)
{
    celula2 *pt;
    pt=lista->prox;
    while (pt!=NULL && strcmp(pt->chave, word)!=0)
    {
        pt=pt->prox;
    }
    return pt;
}

/*Função para mostrar a lista das palavras lidas*/
void imprime_lista_cc (celula *lista, FILE *ptsaida)
{
    celula *pt;
    pt=lista->prox;
    if (pt!=NULL)
    {
        while (pt->prox!=NULL)
        {
            fprintf(ptsaida,"%s, %d\n", pt->chave, pt->freq);
            pt=pt->prox;
        }
        fprintf(ptsaida,"%s, %d", pt->chave, pt->freq);
    }
}

/*Função para mostrar a lista das tags lidas*/
void imprime_lista_cc2 (celula2 *lista, FILE *ptsaida)
{
    celula2 *pt;
    pt=lista->prox;
    while (pt!=NULL)
    {
        fprintf(ptsaida,"%s, %d\n", pt->chave, pt->freq);
        pt=pt->prox;
    }
}

/*Função responsável por converter os caracteres maiúsculos em minúsculos*/
void transforma_em_minusculo (char *word)
{
    int i=0;
    while (word[i]!='\0')
    {
        /*A função "islower" da biblioteca ctýpe.h verifica se o caracter lido é maiúsculo. A função retorna 0 quando o caracter lido é maiúsculo*/
        /*Verifica-se cada letra*/
        if (islower(word[i])==0)
        {
            /*Se a letra for maiúscula, usa-se, então, a função "tolower", que converterá o caracter em sua respectiva correspondência minúscula*/
            word[i]=tolower(word[i]);
        }
        i++;
    }  
}

/*Função para liberar cada célula alocada para a lista das palavras*/
/*Ao ler a função abaixo, perceberá que a cabeça da lista também é apagada*/
void remove_tudo_cc (celula *lst)
{
    celula *pt;
    pt=lst;
    while (pt!=NULL)
    {
        pt=pt->prox;
        free(lst);
        lst=pt;
    }
}

/*Função com o mesmo propósito da acima, com a diferença de, agora, ser para a lista das tags*/
void remove_tudo_cc2 (celula2 *lst)
{
    celula2 *pt;
    pt=lst;
    while (pt!=NULL)
    {
        pt=pt->prox;
        free(lst);
        lst=pt;
    }
}

/*ʕ•́ᴥ•̀ʔっ-------------------------------------------------------------------------------------------------------------------------ʕ•́ᴥ•̀ʔっ*/

/*A função principal, a "main", está dividida em 3 partes: a primeira, que será explicada agora, é onde está a declaração das variáveis, bem 
como a verificação da entrada e da abetura dos arquivos; a segunda diz respeito a resolução do problema proposto para a segunda avaliação e a
terceira é onde ocorre a liberação dos espaços de memória alocados e fechamento dos arquivos*/

int main(int argc, char *argv[])
{
    FILE *ptentrada, *ptsaida;
    char palavra[46], tag[6], *p, arquivo_saida[50];
    int total=0, diferentes=0;
    celula *lista_words, *posicao;
    celula2 *lista_tags, *posicao2;

    /*Verificação do número de palavras usadas na chamada do programa*/
    /*Deve haver apenas 2 strings, uma para o nome do programa e outra para o nome do arquivo de entrada*/
    /*Se o número de palavras informadas for diferente do esperado, a seguinte mensagem será exibida, e a execução do programa será encerrado*/
    if (argc!=2)
    {
        fprintf(stderr,"Formato de entrada inválido\n");
        return 0;
    }

    /*Abertura no modo de leitura de texto do arquivo informado na chamada do programa*/
    ptentrada=fopen(argv[1], "r");

    /*Caso haja falha na abertura*/
    if(ptentrada==NULL)
    {
        fprintf(stderr,"Falha ao abrir o arquivo %s para leitura\n", argv[1]);
        return 0;
    }

    /*O ponteiro p receberá o endereço da literal que corresponde ao nome do arquivo de entrada apenas até o primeiro ponto, isto é, sem a extensão
    do arquivo de entrada*/
    /*A função "strtok" realizará tal ação*/
    p=strtok(argv[1], ".");

    /*A literal apontado por p será copiada para a cadeia de caracteres "arquivo_saida"*/
    strcpy(arquivo_saida, p);

    /*A string contida em "arquivo_saida" será concatenada com a extensão desejada para o arquivo de saída, .csv*/
    strcat(arquivo_saida, ".csv");

    /*Abertura em modo de escrita de texto do arquivo com o nome contido em "arquivo_saida"*/
    ptsaida=fopen(arquivo_saida, "w");

    /*Caso haja falha na abertura*/
    if(ptsaida==NULL)
    {
        fprintf(stderr,"Falha ao abrir o arquivo %s para escrita\n", argv[1]);
        return 0;
    }

/*ʕ•́ᴥ•̀ʔっ------------------------------------------------------------------------------------------------------------------------ʕ•́ᴥ•̀ʔっ*/

    /*A partir daqui está a segunda parte do programa*/

    /*Criação das listas com cabeça*/
    /*"lista_words" é a lista encadeada dinamicamente para as palavras*/
    lista_words=(celula*) malloc(sizeof(celula));
    lista_words->prox=NULL;

    /*"lista_tags" é a lista encadeada dinamicamente para as tags*/
    lista_tags=(celula2*) malloc(sizeof(celula2));
    lista_tags->prox=NULL;

    /*Leitura da primeira palavra do arquivo de entrada, ela é realizada fora do laço para garantir que o arquivo não está vazio*/
    /*A leitura das palavras tem uma formatação especial, as strings são lidas até que se ache o caracter "/"*/
    fscanf(ptentrada,"%[^/]s", palavra);

    /*Laço repetitivo para realizar a leituras das strings contidas no arquivo até que se chegue no final do mesmo*/
    while (!feof(ptentrada))
    {
        /*Leitura da marcação PoS*/
        fscanf(ptentrada,"/%s", tag);
        /*A tag apenas será aceita caso não seja uma das exceções abaixo*/
        if (strcmp(tag, ".")!=0 && strcmp(tag, ",")!=0 && strcmp(tag, "#")!=0 && strcmp(tag, "$")!=0 && strcmp(tag, ":")!=0 && strcmp(tag, "(")!=0 && strcmp(tag, ")")!=0 && strcmp(tag, "´´")!=0 && strcmp(tag, "’")!=0 && strcmp(tag, "‘")!=0 && strcmp(tag, "“")!=0 && strcmp(tag, "”")!=0 && strcmp(tag, "'")!=0 && tag[0]!=34 && strcmp(tag, "``")!=0 && strcmp(tag, "''")!=0)
        {
            /*"busca2" irá verificar se a tag já está na lista de tags*/
            posicao2=busca2(lista_tags, tag);

            /*Se "posicao2" é diferente de NULL, a tag já foi salva e incrementa-se sua frequência em 1*/
            if (posicao2!=NULL)
            {
                posicao2->freq++;
            }
            /*Senão, têm-se uma tag nova e deve-se salvá-la*/
            else
            {
                insercao_alfabetica2(lista_tags, tag);  
            }

            /*Como a tag é válida, a palavra também é*/
            /*A função "transforma_em_minusculo" irá converter todos os caracters da palavra que estivem maiísculo*/
            transforma_em_minusculo(palavra);

            /*Realização da busca pela palavra na lista*/
            posicao=busca(lista_words, palavra);

            /*Caso a variável "posicao" diferente de NULL, a palavra ja está armazenada*/
            if (posicao!=NULL)
            {
                posicao->freq++;
            }

            /*Senão, têm-se uma palavra nova e deve-se armazená-la*/
            else
            {
                /*Como a palavra ja toda em letras minúsculas, ocorre a inserção da mesma na lista*/
                insercao_alfabetica(lista_words, palavra);

                /*A variável "diferentes" é responsável por contar quantas palavras diferentes foram lidas, logo, é incrementada*/
                diferentes++;
            }
            /*Independe da palavra ser repetida ou não, a variável "total" irá contar todas*/
            total++;
        }
        fscanf(ptentrada," %[^/]s", palavra);
    }
    
    /*Mensagens a serem imprimidas no arquivo de saída*/
    fprintf(ptsaida,"TOTAL DE PALAVRAS, %d\n", total);
    fprintf(ptsaida,"TOTAL DE PALAVRAS DISTINTAS, %d\n\n", diferentes);
    fprintf(ptsaida,"PoS, FREQ\n");

    /*Uso da função para imprimir a lista das tags*/
    imprime_lista_cc2(lista_tags, ptsaida);

    fprintf(ptsaida,"\nPALAVRA, FREQ\n");

    /*Exibição da lista das palavras*/
    imprime_lista_cc(lista_words, ptsaida);


/*ʕ•́ᴥ•̀ʔっ------------------------------------------------------------------------------------------------------------------------ʕ•́ᴥ•̀ʔっ*/

    /*Última parte, aqui são liberados os espaços de memória alocados para a lista e o fechamento dos arquivos*/

    /*Liberação dos blocos de memórias usados para a lista*/
    remove_tudo_cc2(lista_tags);
    remove_tudo_cc(lista_words);

    /*Fechamento dos arquivos de entrada e saída*/
    fclose(ptentrada);
    fclose(ptsaida);

    return 0;
}
