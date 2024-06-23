#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Tender {
  char rua[50];
  int numero;
  int cep;
};
typedef struct Tender ender;

// Estrutura para armazenar os dados do cliente
struct Tcliente {
  int codigoCliente;
  char nome[20];
  ender endereco;
  int telefone;
};
typedef struct Tcliente cliente;

// Estrutura para armazenar os dados do funcionario
struct Tfuncionario {
  int codigoFuncionario;
  char nome[50];
  char telefone[20];
  char cargo[20];
  float salario;
};
typedef struct Tfuncionario funcionario;

// Estrutura para armazenar os dados do quarto
struct Tquarto {
  int numero;
  int Hospedes;
  float Diaria;
  int status;
};
typedef struct Tquarto quarto;

// Estrutura para armazenar os dados de dataEntrada/Saida
struct TData {
  int dia;
  int mes;
  int ano;
};
typedef struct TData data;

// Estrutura para armazenar os dados da estadia
struct Testadia {
  int codigoEstadia;
  data dataEntrada;
  data dataSaida;
  int quantidadeDiarias;
  int codigoCliente;
  int numeroQuarto;
  int Qhospedes;
};
typedef struct Testadia estadia;
//Função listar_estadias
int listar_estadias(FILE *fileEstadias) {
      int codigo;
      int diariasDoCliente = 0;
      printf("Digite o código do cliente: ");
      scanf("%d", &codigo);
      

      estadia e;
      fseek(fileEstadias, 0, SEEK_SET); 
      int found = 0;
      while (fread(&e, sizeof(e), 1, fileEstadias)) {
        if (e.codigoCliente == codigo) {
          //Cliente achado
          printf("Código de estadia: %d\n", e.codigoEstadia);
          printf("Número do quarto:  %d\n", e.numeroQuarto);
          diariasDoCliente += e.quantidadeDiarias;

          found = 1;

          
        }
      }
      if(!found) {
         printf("Nenhuma estadia encontrada.\n");
         return 0;
          
      }
      return diariasDoCliente;
}
//Função Sistema de Fideldade
void pontos_fidelidade() {
    FILE *fileEstadias = fopen("estadias.dat", "rb+");
    int fidelidade = listar_estadias(fileEstadias);
    if (fidelidade == 0) {
        printf("Nenhuma estadia encontrada para este cliente.\n");
        return;
    }
    int pontos = fidelidade * 10;
    printf("\nPontos de fidelidade: %d\n", pontos);
    return;
    

}