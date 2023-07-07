/******************************************************
 * Nome do arquivo: computer.c
 * Autor: Isaque Gabriel
 * Data de criação: quarta-feira, 21 de junho de 2023, 23:30:25
 * Descrição: Arquivo responsável por inicializar funções utilizadas no arquivos principal.
 ******************************************************/

#include "computer.h"
#include <stdio.h>

/*
    OBS: Porque foi usado ponteiros em funções?
    - Torna o código principal mais limpo;
    - Passar os valores das variáveis por referência facilitando na hora de realizar tarefas e operações.
*/

/*
    Função - PrintMessages()

    - Responsável por imprimir a mensagem inicial do programa e a mensagem de carregamento do programa;
    - De acordo com o valor recebido pela função e verificado na condição será impresso uma das duas mensagens.
*/
void PrintMessages(int NumVar)
{
    if( NumVar == 1 )
        printf("***Bem vindo ao Simpletron! ***\n***Por favor, digite uma instrucao (ou palavra de dados) de seu programa por vez.***\n***Para cada posicao da memoria (indicada por um número de 00 a 99), digite a palavra para aquela posicao.***\n*** Digite o valor sentinela -99999 para encerrar a digitacao de seu programa. ***\n\n");

    else if( NumVar == 2 )
        printf("*** Carregamento do programa concluído ***\n*** Início da execução do programa ***\n\n");
}

/*
    Função - ReadWords()

    - Responsável por ler as instruções digitadas pelo usuário e armazená-las na mémoria.
    - A partir de condições é feito algumas verificações da instrução digitada, sendo elas:
        + Se o valor da instrução é menor que -9999 OU o valor da instrução é maior que 9999;
        + Se a quantidade de instruções digitadas não ultrapassou o limite da memória que é 100;
        + Se o que o usuário digitou foi o valor sentinela -99999.

    OBS: 
    - O For não possui condição pois como a leitura de instruções só irá ser finalizada quando o usuário digitar "-99999" então não há necessidade de se ter um limite para o laço.

    - Por qual motivo o FOR foi usado ao invés do WHILE ou do DO WHILE?
        + Praticidade na hora de inicializar um contador e incrementá-lo.
        + Evitar que eu torne meu laço de repetição infinito.

    - Lembrando que a forma escrita aqui não anula a possibilidade de usar outras estruturas.
*/
void ReadWords(int MemoryVar[], int *WordVar)
{
    for ( int i = 0; ; i++ ) 
    {
        printf("%02d ? ", i);
        scanf("%d", WordVar);

        if ( *WordVar == -99999 ) 
        {
            break;
        }

        if ( *WordVar < -9999 || *WordVar > 9999 && *WordVar != -99999 ) 
        {
            printf("Por favor, insira uma palavra entre -9999 e +9999 inclusivo:\n");
            i--;
            continue;
        }

        if ( i == 100 ) 
        {
            printf("*** ERRO - O TAMANHO DO CODIGO E MAIOR DO QUE A MEMORIA, TENTE NOVAMENTE DENTRO DO LIMITE DE 100 LINHAS ***");
        }

        MemoryVar[i] = *WordVar;
    }
}

/*
    Função - ProgramExecution()

    - Responsável por fazer a análise e execução das intruções armazenadas na memória;
    - Utiliza o SWITCH para indicar em qual caso o Código de Operação irá se encaixar.

    OBS:
    - Porque não foi usado IF'S ao invés do SWITCH?
        + Organização do Código;
        + Praticidade na Lógica.

    - Lembrando que a forma escrita aqui não anula a possibilidade de usar outras estruturas.
*/

void ProgramExecution( int MemoryVar[], unsigned short *CodeVar, int *TemporaryVar, unsigned short *ErrorVar, unsigned short *OperandVar, short *AccumulatorVar, unsigned short *CounterVar )
{
    switch ( *CodeVar )
        {
            /*
                Caso - Leitura
                
                - Solicita ao usuário que digite um valor
                    + Caso o valor seja menor que -9999 ou maior que +9999 o programa indica que há um erro.
                    + Caso o valor esteja dentro dos limites o valor é armazenado no LOCAL da memória indicado pelo usuário.
            */
            case READ:
                printf("? ");
                scanf("%d", TemporaryVar);
                
                if ( *TemporaryVar < -9999 || *TemporaryVar > +9999 )
                {
                    printf("*** ERRO CRITICO - VALOR INSERIDO NAO SUPORTADO ***\n");
                    *ErrorVar = 1;
                    break;
                }
                
                MemoryVar[*OperandVar] = *TemporaryVar;
                break;
            /*
                Caso - Escrever

                - Escreve no Terminal o LOCAL da memória passado pelo usuário.
            */
            case WRITE:
                printf("%+05d\n", MemoryVar[*OperandVar]);
                break;
            
            /*
                Caso - Carregar

                - Carrega no acumulador o valor armazenado no LOCAL da memória passado pelo usuário.
            */
            case LOAD:
                *AccumulatorVar = MemoryVar[*OperandVar];
                break;

            /*
                Caso - Armazenar

                - Armazena no LOCAL da memória o valor armazenado no acumulador.
            */
                
            case STORE:
                MemoryVar[*OperandVar] = *AccumulatorVar;
                break;

            /*
                Caso - Somar

                - Utiliza uma variável temporária parar somar o valor presente no acumulador com o valor armazenado na memória
                - Verifica se o valor na variável está dentro do intervalo descrito na condição
                - Caso passe na verificação, armazena no Acumulador o resultado da soma.
            */
            
            case ADD:
                *TemporaryVar = *AccumulatorVar + MemoryVar[*OperandVar];
                if ( *TemporaryVar > +9999 || *TemporaryVar < -9999 )
                {
                    printf("*** ERRO CRITICO - TENTATIVA DE OVERFLOW DO ACUMULADOR ***\n");
                    *ErrorVar = 1;
                    break;
                }
                
                *AccumulatorVar = *TemporaryVar;
                break;

            /*
                Caso - Subtrair

                - Utiliza uma variável temporária parar subtrair o valor presente no acumulador com o valor armazenado na memória
                - Verifica se o valor na variável está dentro do intervalo descrito na condição
                - Caso passe na verificação, armazena no Acumulador o resultado da subtração.
            */
                
            case SUBTRACT:
                *TemporaryVar = *AccumulatorVar - MemoryVar[*OperandVar];
                if ( *TemporaryVar > +9999 || *TemporaryVar < -9999 )
                {
                    printf("*** ERRO CRITICO - TENTATIVA DE OVERFLOW DO ACUMULADOR ***\n");
                    *ErrorVar = 1;
                    break;
                }
                
                *AccumulatorVar = *TemporaryVar;
                break;

            /*
                Caso - Dividir

                - Verifica se o valor do acumulador é zero, caso seja não permite a divisão por zero.
                - Caso passe na verificação, armazena no Acumulador o resultado da divisão.

                OBS:
                    - Variável temporária não foi usada pois como só a necessidade de verificar se o acumulador é zero não se tem a necessidade de usá-la.
            */
                
            case DIVIDE:
                if (*AccumulatorVar == 0)
                {
                    printf("*** ERRO CRITICO - DIVISAO POR ZERO ***\n");
                    *ErrorVar = 1;
                    break;
                }

                *AccumulatorVar = MemoryVar[*OperandVar] / *AccumulatorVar;
                break;

            /*
                Caso - Multiplicar

                - Utiliza uma variável temporária parar multiplicar o valor presente no acumulador com o valor armazenado na memória.
                - Verifica se o valor na variável está dentro do intervalo descrito na condição
                - Caso passe na verificação, armazena no Acumulador o resultado da multiplicação.
            */
            
            case MULTIPLY:
                *TemporaryVar = *AccumulatorVar * MemoryVar[*OperandVar];

                if (*TemporaryVar > +9999 || *TemporaryVar < -9999)
                {
                    printf("*** ERRO CRITICO - TENTATIVA DE OVERFLOW DO ACUMULADOR ***\n");
                    *ErrorVar = 1;
                    break;
                }
                
                *AccumulatorVar = *TemporaryVar;
                break;
            
            /*
                Caso - Desvio
                - Desvia o programa para o local de memória indicado
                    + EX.: 4009 -> Desvia o programa para o local 09 da memória
            */
            case BRANCH:
                *CounterVar = *OperandVar - 1;
                break;
            
            /*
                Caso - Desvio Negativo
                - Desvia o programa para o local de memória indicado, se e somente se, o ACUMULADOR, for menor que zero
                    + EX.: 4109 -> Desvia o programa para o local 09 da memória caso o valor armazenado no ACUMULADOR seja menor que zero.
            */
            case BRANCHNEG:
                if (*AccumulatorVar < 0)
                {
                    *CounterVar = *OperandVar - 1;
                }
                break;
            
            /*
                Caso - Desvio De Zero
                - Desvia o programa para o local de memória indicado, se e somente se, o ACUMULADOR, for igual a zero
                    + EX.: 4209 -> Desvia o programa para o local 09 da memória caso o valor armazenado no ACUMULADOR seja igual a zero.
            */
            
            case BRANCHZERO:
                if (*AccumulatorVar == 0)
                {
                    *CounterVar = *OperandVar - 1;
                }
                break;
            
            /*
                Caso - Parar
                - Terminar as instruções
                    + Error recebe 1 que ao chega no laço de repetição irá indicar 0 já que:
                        * "!Error" -> Ou seja o inverso de erro
                            - Quando Erro for 1 no loop será 0 
                            - Quando Erro for 0 no loop será 1
            */
                
            case HALT:
                *ErrorVar = 1;
                break;
                
        }
}

/*
    Função - PrintMemory()
    - Responsável por Imprimir a tela de despejo da memória

    OBS: 
    - %0xd limita a quantidade de dígitos será impresso na tela
    - Explicando o FOR:
        - Considere o primeiro Laço FOR (int i = 0)
            + printf("%+05d  ", MemoryVar[(10 * 0 + 0)] % 10000); -> MemoryVar[0]
            + printf("%+05d  ", MemoryVar[(10 * 0 + 1)] % 10000); -> MemoryVar[1]
            + ...
        - "i" é a Linha da memória enquanto "j" é a coluna.
        - %10000 é usado para extrair um valor menor dos lixos de memória gerados pelos espaços não usados e garantir um padrão de números na hora de imprimir.
        
*/
void PrintMemory( int MemoryVar[], short *AccumulatorVar, unsigned short *CounterVar, short *RegisterVar, unsigned short *CodeVar, unsigned short *OperandVar )
{
    printf("REGISTRADORES:\n\n");
    printf("Acumulador %+05d\n", *AccumulatorVar);
    printf("ContadorInstrucao %02d\n", *CounterVar - 1);
    printf("RegistroInstrucao %+05d\n", *RegisterVar);
    printf("CodigoOperacao %02d\n", *CodeVar);
    printf("Operando %02d\n\n", *OperandVar);
    
    printf("MEMORIA:\n\n");
    printf("            0      1      2      3      4      5      6      7      8      9\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%02d      ", 10 * i);
        for (int j = 0; j < 10; j++)
        {
           printf("%+05d  ", MemoryVar[(10 * i + j)] % 10000);
        }
        printf("\n");
    }

}

