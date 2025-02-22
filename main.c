#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "henrique.h"
#include "arthur.h"
#include "cliente.h"
#include "estadia.h"
#include "funcionario.h"
#include "quarto.h"
//#include "search_cliente.h"
int main() {
  FILE *fileClientes, *fileFuncionarios, *fileQuartos, *fileEstadias;

  fileClientes = fopen("clientes.dat", "rb+");
  if (fileClientes == NULL) {
    fileClientes = fopen("clientes.dat", "wb+");
    if (fileClientes == NULL) {
      perror("Não foi possível abrir o arquivo de clientes");
      return EXIT_FAILURE;
    }
  }

  fileFuncionarios = fopen("funcionarios.dat", "rb+");
  if (fileFuncionarios == NULL) {
    fileFuncionarios = fopen("funcionarios.dat", "wb+");
    if (fileFuncionarios == NULL) {
      perror("Não foi possível abrir o arquivo de funcionários");
      fclose(fileClientes);
      return EXIT_FAILURE;
    }
  }

  fileQuartos = fopen("quartos.dat", "rb+");
  if (fileQuartos == NULL) {
    fileQuartos = fopen("quartos.dat", "wb+");
    if (fileQuartos == NULL) {
      perror("Não foi possível abrir o arquivo de quartos");
      fclose(fileClientes);
      fclose(fileFuncionarios);
      return EXIT_FAILURE;
    }
  }

  fileEstadias = fopen("estadias.dat", "rb+");
  if (fileEstadias == NULL) {
    fileEstadias = fopen("estadias.dat", "wb+");
    if (fileEstadias == NULL) {
      perror("Não foi possível abrir o arquivo de estadias");
      fclose(fileClientes);
      fclose(fileFuncionarios);
      fclose(fileQuartos);
      return EXIT_FAILURE;
    }
  }

  int option;
  do {
    printf("Escolha uma opção:\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Funcionário\n");
    printf("3. Cadastrar Quarto\n");
    printf("4. Procurar cliente\n");
    printf("5. Procurar funcionário\n");
    printf("6. Cadastrar Estadia\n");
    printf("7. Dar baixa em uma estadia\n");
    printf("8. Listar estadias e mostrar pontos de fidelidade de um cliente\n");
    


    printf("0. Sair\n");
    scanf("%d", &option);

    switch (option) {
    case 1:
      cadastraCliente(fileClientes);
      break;
    case 2:
      cadastrarFuncionario(fileFuncionarios);
      break;
    case 3:
      cadastraQuarto(fileQuartos);
      break;
    case 4:
      search_cliente();
      break;
    case 5:
      search_funcionario();
      break;
    case 6:
      cadastraEstadia(fileEstadias, fileQuartos);
      break;
    case 7:
      baixa_estadia();
      break;
    case 8:
      pontos_fidelidade();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  } while (option != 0);

  fclose(fileClientes);
  fclose(fileFuncionarios);
  fclose(fileQuartos);
  fclose(fileEstadias);

  return EXIT_SUCCESS;
}
