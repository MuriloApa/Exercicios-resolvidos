/*Aqui está minha solução para o problema proposto como primeira avaliação da disciplina de Algoritmos e Programação II no curso de Sistemas de Informação
ministrada na UFMS câmpus de Três Lagoas.
  O enunciado, bem como exemplos de entrada e saída, estão num arquivo em formato pdf neste mesmo repositório com o mesmo nome deste código escrito em c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct saidas_posicoes{     /*Registro para salvar as posições das saídas*/
    int x;
    int y;
};

/*Função para alocar dinamicamente o vetor de registro das posições das saídas*/
struct saidas_posicoes *aloca_vetor_registro(int n)                             
{
    struct saidas_posicoes *pt;
    pt= (struct saidas_posicoes*) malloc(n*sizeof(struct saidas_posicoes));
    if (pt==NULL)
    {
        printf("Falha de alocação do vetor de registros\n");
        exit(1);
    }
    return pt;
}

/*Função para alocar dinamicamente as linhas da arena, ou seja, um vetor de caracteres*/
char *linhas_arena(int colunas)
{
    char *pt;
    pt=(char*) malloc(colunas*sizeof(char));
    if (pt==NULL)
    {
        printf("Falha de alocação\n");
        exit(1);
    }
    return pt;
}

/*Função para alocar dinamicamente a matriz de caracteres que irá representar a arena*/
char **aloca_arena(int linhas, int colunas)
{
    char **pt;
    int i;
    pt=(char**) malloc (linhas*sizeof(char*));
    if (pt==NULL)
    {
        printf("Falha de alocação do vetor de ponteiros char\n");
        exit(1);
    }
    for(i=0; i<linhas; i++)
    {
        pt[i]=linhas_arena(colunas);
    }  
    return pt;
}

/*Função para leitura da arena*/
void leitura_arena (int linhas, char **arena, FILE *pt)
{
    int i;
    for(i=0; i<linhas; i++)
    {
        fscanf(pt," %[^\n]s", arena[i]);
    }
}

/*Função para converter um caracter númerico de um bit em um número*/
int char_to_numero (char letra)
{
    int n;
    switch (letra)
    {
        case '0':
            n=0;
        break;
        case '1':
            n=1;
        break;
        case '2':
            n=2;
        break;
        case '3':
            n=3;
        break;
        case '4':
            n=4;
        break;
        case '5':
            n=5;
        break;
        case '6':
            n=6;
        break;
        case '7':
            n=7;
        break;
        case '8':
            n=8;
        break;
        case '9':
            n=9;
        break;
    }
    return n;
}

/*Função para achar as saídas e posição inicial do robô, além de salva-las em suas respectivas variáveis*/
void aloca_saidas_posicoes (int linhas, int colunas, char **arena, int n_saidas, struct saidas_posicoes *saidas_posicoes, struct saidas_posicoes *robo, struct saidas_posicoes *posicao_anterior_robo)
{
    int i=0, j, k=0, n;
    for(i=0; i<linhas; i++)
    {
        j=0;
        while (j<colunas)
        {
            if (!(arena[i][j]==' ' || arena[i][j]=='#' || arena[i][j]=='*') && k<n_saidas)
            {
                n=char_to_numero(arena[i][j]);
                saidas_posicoes[n].x=j;
                saidas_posicoes[n].y=i;
                k++;
            }
            if (arena[i][j]=='*')
            {
                robo->x=j;
                robo->y=i;
                posicao_anterior_robo->x=j+2;   /*Fazer a posição anterior receber a posição inicial do robô adicionada em 2 garante*/
                posicao_anterior_robo->y=i+2;   /*que o primeiro movimento sempre possa acontecer*/
            }
            j++;
        }
    }
}

/*Função para alocar dinamicamente um vetor de inteiros, será usada exclusivamente para a pilha*/
int *aloca_vetor (int n)
{
    int *pt;
    pt = (int *) malloc(n*sizeof(int));
    if (pt==NULL)
    {
        printf("Falha na alocação do vetor\n");
        exit(1);
    }
    return pt;
}

/*Função que decidirá qual movimento o robô deverá fazer com base em sua posição atual, na anterior, na posição da saída e 
nos obstáculos encontrados*/
char movimento1 (struct saidas_posicoes *robo, struct saidas_posicoes *saida, struct saidas_posicoes *anterior, int *tempo, char **a, int i)
{
    char text[2];
    /*A função sprintf converte um inteiro numa string, esta string será utilizada para verificar se dada posição corresponde a saída desejada*/
    sprintf(text, "%d", i);
    /*As decisões sobre para qual direção seguir começam pelas escolhas mais óbvias, andar para o lado que mais faz sentido*/
    /*Por exemplo: Se o robo está mais acima da saída, então ele deve andar para baixo*/
    if (robo->y<saida[i].y && a[robo->y+1][robo->x]!='#' && robo->y+1!=anterior->y)
    {
        /*Essas duas verificações a seguir resolvem o problema do robo entrar numa saida que não estava procurando*/
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    /*Se o robo está mais abaixo da saída, então ele deve andar para cima*/
    if (robo->y>saida[i].y && a[robo->y-1][robo->x]!='#' && robo->y-1!=anterior->y)
    {

        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        { 
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    /*Se o robo está mais à esquerda da saída, então ele deve andar para a direta*/
    if (robo->x<saida[i].x && a[robo->y][robo->x+1]!='#' && robo->x+1!=anterior->x)
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    /*Se o robo está mais à direta da saída, então ele deve andar para a esquerda*/
    if (robo->x>saida[i].x && a[robo->y][robo->x-1]!='#' && robo->x-1!=anterior->x)
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }        
    }
    /*Se o programa chegou até aqui, então ele não foi nem capaz de realizar um movimento intuitivo em direção a saída nem de desviar de
    um obstáculo mudando a direção de acordo com que mais fazia sentido*/
    /*Tentaremos, então, desviar o obstáculo indo pelo lado não intuitivo (andar para uma posição que aumente a diferença entre as coordenadas
    do robô e da saída*/
    /*Se a coordenada x ainda não coincide com a saída, tenta-se primeiro um desvio para cima*/
    if (robo->x!=saida[i].x && robo->y-1!=anterior->y && a[robo->y-1][robo->x]!='#')
    {
        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    /*Se a coordenada y ainda não coincide com a saída, tenta-se primeiro um desvio para a esquerda*/
    if (robo->y!=saida[i].y && robo->x-1!=anterior->x && a[robo->y][robo->x-1]!='#')
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
    }
    /*Se a coordenada x ainda não coincide com a saída, tenta-se agora um desvio para baixo*/
    if (robo->x!=saida[i].x && robo->y+1!=anterior->y && a[robo->y+1][robo->x]!='#')
    {
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    /*Se a coordenada y ainda não coincide com a saída, tenta-se primeiro um desvio para a direta*/
    if (robo->y!=saida[i].y && robo->x+1!=anterior->x && a[robo->y][robo->x+1]!='#')
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    /*Ao chegar aqui, a coordenada x do robô ainda difere da saída e não pôde andar pela vertical, então vamos dar um passo para trás*/
    /*Se o robô está mais à esquerda e não pode andar nem para a direta nem para cima ou para baixo, ele deve dar um passo para a esquerda*/
    if (robo->x < saida[i].x && a[robo->y][robo->x-1]!='#' && robo->x-1!=anterior->x)
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
    }
    /*Se o robô está mais à direita e não pode andar nem para esquerda nem para cima ou para baixo, ele deve dar um passo para a direta*/
    if (robo->x > saida[i].x && a[robo->y][robo->x+1]!='#' && robo->x+1!=anterior->x)
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    /*De forma análoga ao que foi feito com a coordenada x, com a y será a mesma coisa:*/
    /*A coordenada y do robô ainda difere da saída e não pôde andar pela horizontal, então vamos dar um passo para trás*/
    /*Se o robô está acima e não pode andar nem para baixo nem para direita ou esquerda, ele deve dar um passo para a para cima (parece até que o robô sobe pelas paredes kkkkkkk*/
    if (robo->y < saida[i].y && a[robo->y-1][robo->x]!='#' && robo->y-1!=anterior->y)
    {
        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    /*Se o robô está abaixo e não pode andar nem para cima nem para direita ou esquerda, ele deve dar um passo para a para baixo*/
    if (robo->y > saida[i].y && a[robo->y+1][robo->x]!='#' && robo->y+1!=anterior->y)
    {
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    *tempo=*tempo-1;
    /*A função sempre tem que retornar algo, então, se houver uma situação em que nenhum dos movimentos acima possa ser realizado
    a função irá retornar o caracter h*/
    return 'h';
}


/*Segunda versão da função que determina o movimento do robô*/
/*Esta, por sua vez, começa verificando pela horizontal (direita e esquerda)*/
/*Os passos são os mesmos da função anterior, estão apenas em ordem diferente, logo, entendo que seria redundante colocar todas as
explicações novamente*/
char movimento2 (struct saidas_posicoes *robo, struct saidas_posicoes *saida, struct saidas_posicoes *anterior, int *tempo, char **a, int i)
{
    char text[2];
    sprintf(text, "%d", i);
    if (robo->x>saida[i].x && a[robo->y][robo->x-1]!='#' && robo->x-1!=anterior->x)
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }        
    }
    if (robo->x<saida[i].x && a[robo->y][robo->x+1]!='#' && robo->x+1!=anterior->x)
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    if (robo->y>saida[i].y && a[robo->y-1][robo->x]!='#' && robo->y-1!=anterior->y)
    {

        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        { 
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    if (robo->y<saida[i].y && a[robo->y+1][robo->x]!='#' && robo->y+1!=anterior->y)
    {
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    if (robo->y!=saida[i].y && robo->x+1!=anterior->x && a[robo->y][robo->x+1]!='#')
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    if (robo->y!=saida[i].y && robo->x-1!=anterior->x && a[robo->y][robo->x-1]!='#')
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
    }
    if (robo->x!=saida[i].x && robo->y+1!=anterior->y && a[robo->y+1][robo->x]!='#')
    {
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    if (robo->x!=saida[i].x && robo->y-1!=anterior->y && a[robo->y-1][robo->x]!='#')
    {
        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    if (robo->y < saida[i].y && a[robo->y-1][robo->x]!='#' && robo->y-1!=anterior->y)
    {
        if (a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9' && a[robo->y-1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
        if (!(a[robo->y-1][robo->x]>='0' && a[robo->y-1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y-1;
            *tempo=*tempo-1;
            return 'c';
        }
    }
    if (robo->y > saida[i].y && a[robo->y+1][robo->x]!='#' && robo->y+1!=anterior->y)
    {
        if (a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9' && a[robo->y+1][robo->x]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
        if (!(a[robo->y+1][robo->x]>='0' && a[robo->y+1][robo->x]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->y=robo->y+1;
            *tempo=*tempo-1;
            return 'b';
        }
    }
    if (robo->x < saida[i].x && a[robo->y][robo->x-1]!='#' && robo->x-1!=anterior->x)
    {
        if (a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9' && a[robo->y][robo->x-1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
        if (!(a[robo->y][robo->x-1]>='0' && a[robo->y][robo->x-1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x-1;
            *tempo=*tempo-1;
            return 'e';
        }
    }
    if (robo->x > saida[i].x && a[robo->y][robo->x+1]!='#' && robo->x+1!=anterior->x)
    {
        if (a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9' && a[robo->y][robo->x+1]==text[0])
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
        if (!(a[robo->y][robo->x+1]>='0' && a[robo->y][robo->x+1]<='9'))
        {
            anterior->x=robo->x;
            anterior->y=robo->y;
            robo->x=robo->x+1;
            *tempo=*tempo-1;
            return 'd';
        }
    }
    *tempo=*tempo-1;
    return 'h';
}

/*Função empilha*/
void empilha_seq(int *t, int *P, int y, int n_saidas)
{
    if (*t != n_saidas - 1) {
        (*t)++;
        P[*t] = y;
    }
    else
        printf("Pilha cheia!\n");
}

/*Função desempilha*/
int desempilha_seq(int *t, int *P)
{
    int r;
    if (*t != -1) {
        r = P[*t];
        (*t)--;
    } else {
        r = -1;
        printf("Pilha vazia!\n");
    }
    return r;
}

int main(int argc, char *argv[])
{
    FILE *ptentrada, *ptsaida;
    int tempo1, tempo2, n_saidas, linhas, colunas, i, alcancadas=0, proxima;
    char **arena, nome_instancia[52], arquivo_saida[60], **percurso, *percursotemp;
    struct saidas_posicoes *saidas_posicoes, robo, robo2, posicao_anterior_robo1, posicao_anterior_robo2;
    int t1=-1, *P1; /*Pilha 1 para salvar as posições das saídas mais próximas*/

    /*Abertura para leitura do arquivo que contém a arena*/
    ptentrada=fopen(argv[1], "r");
    if(ptentrada==NULL)
    {
        printf("Falha ao abrir o arquivo %s\n", argv[1]);
        return 0;
    }   

    /*Leitura dos dados contidos no arquivo de entrada*/
    fscanf(ptentrada,"Instância %s\nOrçamento: %d\nSaídas: %d\nDimensões: %dx%d",nome_instancia, &tempo1, &n_saidas, &linhas, &colunas);

    /*Criando uma string com o nome da instância e a concatenando com ".out"*/
    strcpy(arquivo_saida, nome_instancia);
    strcat(arquivo_saida, ".out");

    /*Criação do arquivo para escrever as repostas*/
    ptsaida=fopen(arquivo_saida, "w");

    /*Alocação do vetor de caracteres para os caminhos*/
    percurso=aloca_arena(n_saidas, tempo1+1);
    percursotemp=linhas_arena(tempo1+1);

    /*Alocação da pilha para as saídas mais próximas*/
    P1=aloca_vetor(n_saidas);

    /*Alocação da Arena para uso no programa*/
    arena=aloca_arena(linhas, colunas+1); 

    /*Leitura da arena*/
    leitura_arena(linhas, arena, ptentrada);

    /*Alocação do vetor de registros que conterá as coordenadas das saídas*/
    saidas_posicoes=aloca_vetor_registro(n_saidas);

    /*Salva as posições das saídas e inicial do robô no vetor de registros alocado anteriormente*/
    aloca_saidas_posicoes(linhas, colunas, arena, n_saidas, saidas_posicoes, &robo, &posicao_anterior_robo1);

    /*Caso onde não há saídas*/
    if (n_saidas==0 && ptentrada!=NULL)
    {
        printf("Instancia %s\nOrçamento disponível: %d\nSem saída!\n\nArquivo %s gerado com sucesso!\n", nome_instancia, tempo1, arquivo_saida);
        fprintf(ptsaida,"Posição inicial [x, y]: [%d, %d]\nOrçamento disponível: %d\n\nArena sem saída!\n\n", robo.x, robo.y, tempo1);
    }
    else
    {
        /*Este laço será o responsável por determinar os caminhos*/
        for (i=0; i<n_saidas; i++)
        {
            tempo2=tempo1;
            robo2=robo;
            posicao_anterior_robo2=posicao_anterior_robo1;
            /*A função movimento irá ser chamada até o tempo se esgotar ou até a posição do robô coincidir com a saída*/
            while (tempo2!=0 && (robo2.x!=saidas_posicoes[i].x || robo2.y!=saidas_posicoes[i].y))
            {
                percurso[i][tempo1-tempo2]=movimento1(&robo2, saidas_posicoes, &posicao_anterior_robo2, &tempo2, arena, i);
                percurso[i][tempo1-tempo2+1]='\0';
            }
            /*Caso o tempo se esgote e as posição do robô e da saída sejam diferentes, entende-se que a saída não foi alcançada */
            if (tempo2==0 && (robo2.x!=saidas_posicoes[i].x || robo2.y!=saidas_posicoes[i].y))
            {
                strcpy(percurso[i], "Não alcançada!");
            }
            tempo2=tempo1;
            robo2=robo;
            posicao_anterior_robo2=posicao_anterior_robo1;
            /*Mesmo processo aqui, mas agora com a segunda versão da função movimento*/
            while (tempo2!=0 && (robo2.x!=saidas_posicoes[i].x || robo2.y!=saidas_posicoes[i].y))
            {
                percursotemp[tempo1-tempo2]=movimento2(&robo2, saidas_posicoes, &posicao_anterior_robo2, &tempo2, arena, i);
                percursotemp[tempo1-tempo2+1]='\0';
            }
            if (tempo2==0 && (robo2.x!=saidas_posicoes[i].x || robo2.y!=saidas_posicoes[i].y))
            {
                strcpy(percursotemp, "Não alcançada!");
            }
            /*Esses dois desvios condicionais irão determinar qual caminho é mais vantajoso*/
            /*O caminho escolhido sempre será salvo no vetor percurso*/
            /*o caminho contido em "percursotemp" será copiado na variável "percurso" se nesta não tiver sido encontrado caminho e na outra sim*/
            if (strcmp(percurso[i],"Não alcançada!")==0 && strcmp(percursotemp,"Não alcançada!")!=0)
            {
                strcpy(percurso[i], percursotemp);
            }
            /*Se houver um trajeto nas duas variáveis e o da variável "percursotemp" for menor, este caminho será copiado na variável "percurso"*/
            if (strcmp(percurso[i],"Não alcançada!")!=0 && strcmp(percursotemp,"Não alcançada!")!=0 && strlen(percursotemp)<strlen(percurso[i]))
            {
                strcpy(percurso[i], percursotemp);
            }
        }
        /*Calculo de quantas saídas foram alcançadas*/
        for(i=0; i<n_saidas; i++)
        {
            if (strcmp(percurso[i], "Não alcançada!")!=0)
            {
                alcancadas++;
            }
        }
        /*Se nenhuma saída for alcançada, as seguintes mensagens serão passadas*/
        if (alcancadas==0)
        {
            fprintf(ptsaida,"Posição inicial [x, y]: [%d, %d]\nOrçamento disponível: 0 segundos\n\n", robo.x, robo.y);
            for(i=0; i<n_saidas; i++)
            {
                fprintf(ptsaida,"Saída %d: %s\n", i, percurso[i]);
            }
            fprintf(ptsaida,"\n");
            printf("Instância %s\nOrçamento disponível: 0 segundos\n", nome_instancia);
            printf("Sem saída!\n\n");
            printf("Arquivo %s gerado com sucesso!\n", arquivo_saida);
        }
        /*Caso não*/
        else
        {
            /*A variável "proxima" guarda o número de movimentos da saída mais próxima alcançada até o momento*/
            /*"proxima" foi inicializada com o caminho para a saída 0*/
            proxima=strlen(percurso[0]);
            /*A pilha P1 guarda as posições das saídas mais próximas*/
            empilha_seq(&t1, P1, 0, n_saidas);
            fprintf(ptsaida,"Posição inicial [x, y]: [%d, %d]\nOrçamento disponível: %d segundos\n\n", robo.x, robo.y, tempo1);
            /*Este laço realiza duas tarefas simultaneamente, ele escreve os caminhos para as saídas no arquivo e faz a busca das mais próximas */
            for(i=0; i<n_saidas; i++)
            {
                if (strcmp(percurso[i], "Não alcançada!")!=0)
                {
                    fprintf(ptsaida,"Saída %d: %ld segundos -> %s\n", i, strlen(percurso[i]), percurso[i]);
                    /*Se "proxima" é maior que o caminho para a saída "i", então o caminho para esta é menor e deve-se atualizar "proxima" e "P1"*/
                    if (proxima>strlen(percurso[i]))
                    {
                        proxima=strlen(percurso[i]);
                        /*Deve-se desempilhar toda a pilha, pois se encontrou um caminho menor que todos os outros salvos até agora*/
                        while (t1>-1)
                        {
                            desempilha_seq(&t1, P1);
                        }
                        empilha_seq(&t1, P1, i, n_saidas);
                    }
                    /*Se "proxima" é igual ao caminho para a saída "i" e o último elemento da pilha é diferente de "i", então se encontrou
                    mais um caminho de tamanho igual ao menor anterior e salva-se ele na pilha*/
                    if (proxima==strlen(percurso[i]) && P1[t1]!=i)
                    {
                        empilha_seq(&t1, P1, i, n_saidas);
                    }  
                }
                else
                {
                    fprintf(ptsaida,"Saída %d: %s\n", i, percurso[i]);
                }
            }
            printf("Instância %s\nOrçamento disponível: %d segundos\nQuantidade de saídas alcançadas: %d\n", nome_instancia, tempo1, alcancadas);
            printf("Saída(s) mais próxima(s): %d segundo(s)\n\n", proxima);
            for(i=0; i<=t1; i++)
                printf("Saída %d: %s\n", P1[i], percurso[P1[i]]);
            printf("\n");
            printf("Arquivo %s gerado com sucesso!\n", arquivo_saida);
        }
    }
    
    /*Devolvendo os blocos de memória alocados dinamicamente*/
    free(saidas_posicoes);
    for (i=0; i<linhas; i++)
    {
        free(arena[i]);
    }
    for (i=0; i<n_saidas; i++)
    {
        free(percurso[i]);
    }
    free(percursotemp);
    free(P1);
    
    /*fechando os arquivos*/
    fclose(ptentrada);
    fclose(ptsaida);
    return 0;
}
