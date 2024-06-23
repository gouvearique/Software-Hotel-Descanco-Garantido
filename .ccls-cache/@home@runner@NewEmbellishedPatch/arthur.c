#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arthur.h"

#include "cliente.h"
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
struct Tfuncionario {
  int codigoFuncionario;
  char nome[50];
  char telefone[20];
  char cargo[20];
  float salario;
};
typedef struct Tfuncionario funcionario;

void baixa_estadia () {
  //Pedir codigo da estadia
  //Achar o numero do quarto no arquivo de estadias
  //Achar numero de diarias no arquivo de estadias

  
  //Achar o numero do quarto no arquivo de quartos
  //Mudar status do quarto no arquivo de quartos para desocupado
  //Achar o valor da diaria do quarto no arquivo de quartos

  
  //Multiplicar o numero de diarias pelo valor da diaria
  //Mostrar ao usuário o valor total a ser pago
  
}
void search_cliente() {
  int codigo;
  printf("Digite o código do cliente: ");
  scanf("%d", &codigo);
  FILE *f = fopen("clientes.dat", "rb");

  cliente c;
  fseek(f, 0, SEEK_SET); // Move to the start of the file

  while (fread(&c, sizeof(c), 1, f)) {
    if (c.codigoCliente == codigo) {
      printf("Cliente encontrado:\n");
      printf("Código: %d\n", c.codigoCliente);
      printf("Nome: %s\n", c.nome);
      printf("Endereço:  %s, Número %d, CEP %d\n", c.endereco.rua, c.endereco.numero, c.endereco.cep);
      printf("Telefone: %d\n", c.telefone);
      return;
    }
  }
  printf("Cliente com o código %d não encontrado.\n", codigo);
}

void search_funcionario()
{
     int codigo;
      printf("Digite o código do funcionario: ");
      scanf("%d", &codigo);
      FILE *f = fopen("funcionarios.dat", "rb");

      funcionario funcionario;
      fseek(f, 0, SEEK_SET); // Move to the start of the file

      while (fread(&funcionario, sizeof(funcionario), 1, f)) {
        if (funcionario.codigoFuncionario == codigo) {
          printf("Cliente encontrado:\n");
          printf("Código: %d\n", funcionario.codigoFuncionario);
          printf("Nome: %s\n", funcionario.nome);
          printf("Cargo: %s\n", funcionario.cargo);
          printf("Salario: %f\n", funcionario.salario);
          printf("Telefone: %s\n", funcionario.telefone);
          return;
        }
      }
      printf("Cliente com o código %d não encontrado.\n", codigo);
    
}