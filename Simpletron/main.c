/******************************************************
 * Nome do arquivo: main.c
 * Autor: Isaque Gabriel
 * Data de criação: quarta-feira, 21 de junho de 2023, 23:30:25
 * Descrição: O Simpletron executa programas escritos apenas na linguagem que entende diretamente, isto é, a Linguagem de Máquina Simpletron (ou LMS).
 ******************************************************/


#include <stdio.h>
#include "computer.h"

int main()
{
    
    /*
        Declaração De Variáveis

        Word -> Variável auxiliar para armazenar as instruções e após verificações armazenar na "Memória"
        Memory[] -> "Memória" Do Simpletron

        Temporary -> Variável auxiliar para armazenar instruções / valores / resultados temporariamente.
        InstructionCounter -> Variável responsável por fazer a contagem das intruções
        OperationCode -> Variável responsável por Armazenar o Código de Operação da Instrução
        Operand -> Variável responsável por Armazenar os últimos dois dígitos da instrução
        Error -> Variável usada para evitar erros durante alguma execução errada do programa.
        Accumulator -> 
        InstructionRegister
    */
    int Word;
    int Memory[100];

    int Temporary = 0;
    unsigned short InstructionCounter = 00;
    unsigned short OperationCode = 00;
    unsigned short Operand = 00;
    unsigned short Error = 0;
    short Accumulator = +0000;
    short InstructionRegister = +0000;
    
    /*
        Funções

        PrintMessages(1) -> Imprime a mensagem inicial do programa.
        ReadWords(Memoria[], &Palavra) -> Armazena na memória as "palavras" digitadas pelo usuário.
        PrintMessages(2) -> Imprime a mensagem de carregamento do programa.
    */
    PrintMessages(1);
    ReadWords(Memory, &Word);
    PrintMessages(2);
    
    /*
        For

        Enquanto o valor da variável "InstructionCounter" for menor que ou igual à 100 E a negação da variável "Error" seja Verdadeiro ou seja (1), Passe para a próxima instrução.

        O Objetivo desse for é processar cada instrução escrita pelo usuário, devemos ter no máximo 100 Instruções já que esse é o limite do nosso Simpletron.

        OBS: O uso do "Error" é para indicar problemas ocorridos durante a execução das instruções.
    */
    for (; InstructionCounter <= 100 && !Error; InstructionCounter++)
    {
        InstructionRegister = Memory[InstructionCounter]; // Coloca a palavra armazenada na variável
        OperationCode = InstructionRegister / 100; // Pega o código de operação da instrução
        Operand = InstructionRegister % 100; // Pega o local da memória onde será armazenado

        /*
            * Ver melhor em computer.c *

            Função responsável por executar o programa, utilizando o valor de operação para decidir qual operação irá ser realizada naquela instrução.
        */
        ProgramExecution(Memory, &OperationCode, &Temporary, &Error, &Operand, &Accumulator, &InstructionCounter);
    }

    /*
        PrintMemory()

        Imprime a Memória do Simpletron, mostrando respectivamente:

        Valor armazenado no acumulador;
        Quantidade de instruções digitadas;
        Valor da última instrução digitada;
        Código de Operação da última instrução digitada;
        Local na memória no qual a última instrução foi aplicada.

        MEMÓRIA DO SIMPLETRON
    */
    
    PrintMemory(Memory, &Accumulator, &InstructionCounter, &InstructionRegister, &OperationCode, &Operand);

    return 0;
}
