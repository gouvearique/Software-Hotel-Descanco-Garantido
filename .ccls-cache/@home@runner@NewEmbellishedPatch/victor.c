#include "cliente.h"
#include "estadia.h"
#include "funcionario.h"
#include "quarto.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arthur.h"
// Estrutura para armazenar os dados respectivos ao endereço do cliente
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

// Função para localizar o codigo do cliente
int localiza_codigo_cliente(FILE *f, int codigo) {
  int posicao = 0;
  cliente c;
  fseek(f, 0, SEEK_SET);
  while (fread(&c, sizeof(c), 1, f)) {
    if (c.codigoCliente == codigo) {
      return posicao;
    }
    posicao++;
  }
  return -1;
}

// Função para gerar o próximo código disponível para clientes
int proximo_codigo_cliente(FILE *f) {
  int max_codigo = 10;
  cliente c;
  fseek(f, 0, SEEK_SET);
  while (fread(&c, sizeof(c), 1, f)) {
    if (c.codigoCliente > max_codigo) {
      max_codigo = c.codigoCliente;
    }
  }
  return max_codigo + 1;
}

// Função para gerar o próximo código disponível para funcionários
int proximo_codigo_funcionario(FILE *f) {
  int max_codigo = 0;
  funcionario func;
  fseek(f, 0, SEEK_SET);
  while (fread(&func, sizeof(func), 1, f)) {
    if (func.codigoFuncionario > max_codigo) {
      max_codigo = func.codigoFuncionario;
    }
  }
  return max_codigo + 1;
}

// Função para gerar o próximo número de quarto
int proximo_numero_quarto(FILE *f) {
  int max_numero = 100;
  quarto q;
  fseek(f, 0, SEEK_SET);
  while (fread(&q, sizeof(q), 1, f)) {
    if (q.numero > max_numero) {
      max_numero = q.numero;
    }
  }
  return (max_numero % 100 == 4) ? max_numero + 97 : max_numero + 1;
}

// Função para localizar o codigo do funcionario
int localiza_codigo_funcionario(FILE *f, int codigo) {
  int posicao = 0;
  funcionario func;
  fseek(f, 0, SEEK_SET);
  while (fread(&func, sizeof(func), 1, f)) {
    if (func.codigoFuncionario == codigo) {
      return posicao;
    }
    posicao++;
  }
  return -1;
}

// Função para localizar o numero do quarto
int localiza_numero_quarto(FILE *f, int numero) {
  int posicao = 0;
  quarto q;
  fseek(f, 0, SEEK_SET);
  while (fread(&q, sizeof(q), 1, f)) {
    if (q.numero == numero) {
      return posicao;
    }
    posicao++;
  }
  return -1;
}

/* Função para localizar o codigo da estadia
int localiza_codigo_estadia(FILE *f, int codigo) {
  int posicao = 0;
  estadia e;
  fseek(f, 0, SEEK_SET);
  while (fread(&e, sizeof(e), 1, f)) {
    if (e.codigoEstadia == codigo) {
      return posicao;
    }
    posicao++;
  }
  return -1;
}

int proximo_codigo_estadia(FILE *f) {
  int max_codigo = 0;
  estadia e;
  fseek(f, 0, SEEK_SET);
  while (fread(&e, sizeof(e), 1, f)) {
    if (e.codigoEstadia > max_codigo) {
      max_codigo = e.codigoEstadia;
    }
  }
  return max_codigo + 1;
}
*/

/*


/*Função auxiliar para converter uma data em número de dias desde um ponto de
referência*/
int totalDias(data d) { return d.ano * 365 + d.mes * 30 + d.dia; }

// Função para calcular a diaria do quarto
int calcularDiarias(data entrada, data saida) {

  int totalDiasEntrada = totalDias(entrada);
  int totalDiasSaida = totalDias(saida);

  return totalDiasSaida - totalDiasEntrada;
}

// Procedimento para cadastrar cliente
void cadastraCliente(FILE *f) {
  cliente c;

  // Geração automática do próximo código de cliente
  c.codigoCliente = proximo_codigo_cliente(f);
  printf("Código do cliente: %d\n", c.codigoCliente);

  // Coleta das informações do cliente
  printf("Digite o nome do cliente: ");

  // limpando o buffer
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
  fgets(c.nome, sizeof(c.nome), stdin);

  printf("Digite a rua do cliente: ");
  fgets(c.endereco.rua, sizeof(c.endereco.rua), stdin);

  printf("Digite o número da respectiva rua: ");
  scanf("%d", &c.endereco.numero);

  printf("Digite o CEP: ");
  scanf("%d", &c.endereco.cep);

  // Gravação do cliente no arquivo
  fseek(f, 0, SEEK_END);
  fwrite(&c, sizeof(c), 1, f);
  fflush(f);

  printf("Cliente cadastrado com sucesso!\n");
}

// Procedimento para cadastrar funcionário
void cadastrarFuncionario(FILE *arquivo) {
  funcionario func;

  // Geração automática do próximo código de funcionário
  func.codigoFuncionario = proximo_codigo_funcionario(arquivo);
  printf("Código do funcionário: %d\n", func.codigoFuncionario);

  // Coleta das informações do funcionário
  printf("Digite o nome do funcionário: ");
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
  fgets(func.nome, sizeof(func.nome), stdin);

  printf("Digite o telefone do funcionário: ");
  fgets(func.telefone, sizeof(func.telefone), stdin);

  printf("Digite o cargo do funcionário: ");
  fgets(func.cargo, sizeof(func.cargo), stdin);

  printf("Digite o salário do funcionário: ");
  scanf("%f", &func.salario);

  // Gravação do funcionário no arquivo
  fseek(arquivo, 0, SEEK_END);
  fwrite(&func, sizeof(func), 1, arquivo);
  fflush(arquivo);

  printf("Funcionário cadastrado com sucesso!\n");
}

// Procedimento para cadastrar quarto
void cadastraQuarto(FILE *arquivo) {
  quarto q;

  // Geração automática do próximo número de quarto
  q.numero = proximo_numero_quarto(arquivo);
  printf("Número do quarto: %d\n", q.numero);

  // Coleta das informações do quarto
  printf("Digite a quantidade de hóspedes: ");
  scanf("%d", &q.Hospedes);

  printf("Digite o valor da diária: ");
  scanf("%f", &q.Diaria);

  printf("Digite o status do quarto (1 para Ocupado, 2 para Desocupado): ");
  scanf("%d", &q.status);
  while (q.status != 1 && q.status != 2) {
    printf("Erro, digite 1 para Ocupado ou 2 para Desocupado: ");
    scanf("%d", &q.status);
  }

  // Gravação do quarto no arquivo
  fseek(arquivo, 0, SEEK_END);
  fwrite(&q, sizeof(q), 1, arquivo);
  fflush(arquivo);

  printf("Quarto cadastrado com sucesso!\n");
}

int localizarQuartoDisponivel(quarto quartos[], int numQuartos, int Qhospedes,int status) {
  for (int i = 0; i < numQuartos; i++) {
    if (quartos[i].status == status && quartos[i].Hospedes >= Qhospedes) {
      return i; // Retorna o índice do quarto encontrado
    }
  }
  return -1; // Retorna -1 se nenhum quarto for encontrado
}

// Procedimento para cadastrar uma estadia
void cadastraEstadia(FILE *arquivoEstadias, quarto *quartos, int numQuartos) {
  estadia e;

  printf("Digite o código do cliente: ");
  if (scanf("%d", &e.codigoCliente) != 1) {
    printf("Erro ao ler o código do cliente.\n");
    return;
  }

  printf("\nNumero de hospedes:");
  if (scanf("%d", &e.Qhospedes) != 1) {
    printf("Erro ao ler o número de hóspedes.\n");
    return;
  }

  int quartoIndex =
      localizarQuartoDisponivel(quartos, numQuartos, e.Qhospedes, 0);
  if (quartoIndex == -1) {
    printf("Nenhum quarto disponível encontrado para a quantidade de hóspedes "
           "fornecida.\n");
    return;
  } else {
    printf("Quarto encontrado: Número%d\n", quartos[quartoIndex].numero);
    quartos[quartoIndex].status = 1; // Atualiza o status do quarto para ocupado

    // Atualiza o arquivo com o novo status do quarto
    FILE *arquivoQuartos = fopen("quartos.dat", "r+b");
    if (arquivoQuartos != NULL) {
      fseek(arquivoQuartos, quartoIndex * sizeof(quarto), SEEK_SET);
      fwrite(&quartos[quartoIndex], sizeof(quarto), 1, arquivoQuartos);
      fclose(arquivoQuartos);
    } else {
      printf("Erro ao abrir o arquivo de quartos para atualizar o status.\n");
    }
  }

  printf("Digite a data de entrada (DD MM AAAA): ");
  if (scanf("%d %d %d", &e.dataEntrada.dia, &e.dataEntrada.mes,
            &e.dataEntrada.ano) != 3) {
    printf("Erro ao ler a data de entrada.\n");
    return;
  }

  printf("Digite a data de saída (DD MM AAAA): ");
  if (scanf("%d %d %d", &e.dataSaida.dia, &e.dataSaida.mes, &e.dataSaida.ano) !=
      3) {
    printf("Erro ao ler a data de saída.\n");
    return;
  }

  e.quantidadeDiarias = calcularDiarias(e.dataEntrada, e.dataSaida);

  // Salvar a estadia no arquivo
  fwrite(&e, sizeof(estadia), 1, arquivoEstadias);
}

void carregarQuartos(FILE *fileQuartos, quarto **quartos, int *numQuartos) {
  fseek(fileQuartos, 0, SEEK_END);
  long fileSize = ftell(fileQuartos);
  rewind(fileQuartos);

  *numQuartos = fileSize / sizeof(quarto);
  *quartos = (quarto *)malloc(fileSize);
  if (*quartos == NULL) {
    printf("Erro ao alocar memória.\n");
    *numQuartos = 0;
    return;
  }

  fread(*quartos, sizeof(quarto), *numQuartos, fileQuartos);
}
