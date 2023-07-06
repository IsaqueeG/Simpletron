#include "computer.h"
#include <stdio.h>

void PrintMessages(int NumVar)
{
    /*
        Estrutura Condicional

        De acordo com o valor passado para a função o programa imprimirá uma determinada mensagem.
    */
    if(NumVar == 1)
        printf("***Bem vindo ao Simpletron! ***\n***Por favor, digite uma instrucao (ou palavra de dados) de seu programa por vez.***\n***Para cada posicao da memoria (indicada por um número de 00 a 99), digite a palavra para aquela posicao.***\n*** Digite o valor sentinela -99999 para encerrar a digitacao de seu programa. ***\n\n");

    else if(NumVar == 2)
        printf("*** Carregamento do programa concluído ***\n*** Início da execução do programa ***\n\n");
}

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

void ProgramExecution( int MemoryVar[], unsigned short *CodeVar, int *TemporaryVar, unsigned short *ErrorVar, unsigned short *OperandVar, short *AccumulatorVar, unsigned short *CounterVar )
{
    switch ( *CodeVar )
        {
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
            
            case WRITE:
                printf("%+05d\n", MemoryVar[*OperandVar]);
                break;
                
            case LOAD:
                *AccumulatorVar = MemoryVar[*OperandVar];
                break;
                
            case STORE:
                MemoryVar[*OperandVar] = *AccumulatorVar;
                break;
                
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
                
            case DIVIDE:
                if (*AccumulatorVar == 0)
                {
                    printf("*** ERRO CRITICO - DIVISAO POR ZERO ***\n");
                    *ErrorVar = 1;
                    break;
                }

                *AccumulatorVar = MemoryVar[*OperandVar] / *AccumulatorVar;
                break;
            
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
                
            case BRANCH:
                *CounterVar = *OperandVar - 1;
                break;
                
            case BRANCHNEG:
                if (*AccumulatorVar < 0)
                {
                    *CounterVar = *OperandVar - 1;
                }
                break;
            
            case BRANCHZERO:
                if (*AccumulatorVar == 0)
                {
                    *CounterVar = *OperandVar - 1;
                }
                break;
                
            case HALT:
                *ErrorVar = 1;
                break;
                
        }
}

void ReadWords(int MemoryVar[], int *WordVar)
{
    for ( int i = 0; ; i++ ) 
    {
        printf("%02d ? ", i);
        scanf("%d", WordVar);

        if (*WordVar == -99999) 
        {
            break;
        }

        if (*WordVar < -9999 || *WordVar > 9999 && *WordVar != -99999) 
        {
            printf("Por favor, insira uma palavra entre -9999 e +9999 inclusivo:\n");
            i--;
            continue;
        }

        if (i == 100) 
        {
            printf("*** ERRO - O TAMANHO DO CODIGO E MAIOR DO QUE A MEMORIA, TENTE NOVAMENTE DENTRO DO LIMITE DE 100 LINHAS ***");
        }

        MemoryVar[i] = *WordVar;
    }
}