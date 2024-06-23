
/*int main() {

  FILE *f;
  char op;

  setlocale(LC_ALL, "portuguese");

  if ((f = fopen("Hotel.txt", "r+b")) == NULL) {
    printf("Arquivo não existia... criando arquivo!\n");
    if ((f = fopen("Hotel.txt", "w+b")) == NULL) {
      printf("Erro na criação do arquivo!!\n");
      exit(1);
    }


  }

  if((f = fopen("clientes.txt", "r+b")) == NULL){
    printf("Arquivo não existia... criando arquivo!\n");
    if ((f= fopen("clientes.txt", "w+b")) == NULL){
      printf("Erro na criação do arquivo!!\n");
      exit(1);
    }
  }
  do {
    printf("\nEscolha:\n");
    printf("1- Cadastrar cliente\n");
    printf("2- Cadastrar funcionario\n");
    printf("3- Cadastrar quarto\n");
    printf("4- Sair da aplicação\n");
    printf("5- Procurar um funcionário\n");
    printf("6- Procurar um cliente\n");


    op = getchar();
    switch (op) {
    case '1':
      cadastraCliente(f);
      break;
    case '2':
      cadastrarFuncionario(f);
      break;
    case '3':
      cadastraQuarto(f);
    case '4':
      printf("Saindo da aplicação...\n");
      system("pause");
      break;
    case '5':
      search_funcionario();
    case '6':
      search_cliente();



    }

  } while (op != '4');
  fclose(f);
  return 0;
}
*/

