#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arthur.h"
#include "quarto.h"

#include "cliente.h"
struct Tender {
  char rua[50];
  int numero;
  int cep;
};
typedef struct Tender ender;
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
struct TData {
  int dia;
  int mes;
  int ano;
};
typedef struct TData data;

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

struct Tquarto {
  int numero;
  int Hospedes;
  float Diaria;
  int status;
};
typedef struct Tquarto quarto;

void baixa_estadia () {
  int codigo;
  printf("Digite o código da estadia a dar baixa: ");
  scanf("%d", &codigo);

  FILE *f = fopen("estadias.dat", "rb");
  if (!f) {
    printf("Erro ao abrir arquivo de estadias.\n");
    return;
  }

  FILE *temp = fopen("temp.dat", "wb");
  if (!temp) {
    printf("Erro ao criar arquivo temporário.\n");
    fclose(f);
    return;
  }

  estadia e;
  int nQuarto;
  int found = 0;

  while (fread(&e, sizeof(e), 1, f)) {
    if (e.codigoEstadia == codigo) {
      found = 1;
      nQuarto = e.numeroQuarto;
      double custoTotal;
      FILE *fQuarto = fopen("quartos.dat", "rb+");
      if (!fQuarto) {
        printf("Erro ao abrir arquivo de quartos.\n");
        fclose(f);
        fclose(temp);
        return;
      }

      quarto q;
      int quartoFound = 0;
      long pos;

      while (fread(&q, sizeof(quarto), 1, fQuarto)) {
        if (q.numero == nQuarto) {
          quartoFound = 1;
          q.status = 2;
          custoTotal = e.quantidadeDiarias * q.Diaria;
          pos = ftell(fQuarto) - sizeof(quarto); // Posição do registro
          fseek(fQuarto, pos, SEEK_SET); // Volta o ponteiro para a posição do registro
          fwrite(&q, sizeof(quarto), 1, fQuarto); // Atualiza o registro
          fclose(fQuarto);
          printf("Quarto desocupado com sucesso\n");
          printf("O total a ser pago por pessoa é: %.2f\n", custoTotal);
          break;
        }
      }

      if (!quartoFound) {
        printf("Quarto com número %d não encontrado.\n", nQuarto);
        fclose(fQuarto);
      }

    } else {
      fwrite(&e, sizeof(e), 1, temp);
    }
  }

  fclose(f);
  fclose(temp);

  if (found) {
    remove("estadias.dat");
    rename("temp.dat", "estadias.dat");
    printf("Estadia com código %d deletada com sucesso.\n", codigo);
  } else {
    remove("temp.dat");
    printf("Estadia com código %d não encontrada.\n", codigo);
  }
  
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
      fseek(f, 0, SEEK_SET); 

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