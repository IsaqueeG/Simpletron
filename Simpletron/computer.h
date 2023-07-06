/******************************************************
 * Nome do arquivo: computer.h
 * Autor: Isaque Gabriel
 * Data de criação: quarta-feira, 21 de junho de 2023, 23:30:25
 * Descrição: Arquivo de cabeçalho responsável por inicializar funções utilizadas no arquivos principal e estruturadas no arquivo "computer.c".
 ******************************************************/

#include <stdio.h>
// Operações de entrada e saída:
#define READ 10
#define WRITE 11

//Operações de carregamento e armazenamento:
#define LOAD 20
#define STORE 21

//Operações aritméticas:
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

//Operações de transferência de controle:
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43




/*
    Protótipos de Funções

    Tarefas realizadas pelas funções explicadas no arquivo "main.c"
*/
void PrintMessages(int);
void PrintMemory(int[], short*, unsigned short*, short*, unsigned short*, unsigned short*);
void ReadWords(int[], int*);
void ProgramExecution(int[], unsigned short*, int*, unsigned short*, unsigned short*, short*, unsigned short*);