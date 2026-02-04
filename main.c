#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float SAQUE_MAX = 1000.00;
int op;

typedef struct
{
	int numero_conta;
	char nome[50];
	float saldo;
	int senha;
}Conta;

Conta contas[] = 
{
	{0, "Admin", 0.0, 999},
	{1, "Henrique", 1000.00, 123},
	{2, "Maria", 2500.00, 456},
	{3, "Joao", 500.00, 789}
};

Conta * autptr = NULL;

void autenticar_conta();
void verificar_nulo();
void verificar_saldo();
void depositar_dinheiro();
void sacar_dinheiro();
void transferir_dinheiro();
void deslogar();
void alterar_saquemax();

int main()
{
	while(1)
	{
		do
		{
			system("clear");
			printf("<- Bem-vindo ao Banco TADS -> \n");
			printf("------------------------------------ \n");
			printf("1) LOGIN \n2) VERIFICAR SALDO \n3) DEPOSITAR DINHEIRO \n4) SACAR DINHEIRO \n5) TRANSFERIR DINHEIRO \n6) SAIR DO USUARIO ATUAL \n7) ENCERRAR PROGRAMA\n");
			printf("------------------------------------ \n");
			printf("Digite o que deseja fazer: ");
			scanf("%d", &op);
			switch(op)
			{
    			case 1:
    				autenticar_conta();
    				break;
    			case 2:
    				verificar_nulo(verificar_saldo);
    				break;
    			case 3:
    				verificar_nulo(depositar_dinheiro);
    				break;
    			case 4:
    				verificar_nulo(sacar_dinheiro);
    				break;
    			case 5:
    				verificar_nulo(transferir_dinheiro);
    				break;
    			case 6:
    				deslogar();
    				break;
    			case 7:
    				printf("Saindo... \n");
    				return 0;
    				break;
    			default:
    				printf("Opcao invalida!\n");
			}
		} while ((autptr != &contas[0]) && (op != 7));


		if(autptr -> numero_conta == 0)
		{
			op = -1;
			do
			{
				system("clear");
				printf("Iniciando... \n");
				printf("<- Menu de Admnistrador -> \n");
				printf("1) Alterar Saque-MAX ----- 2) Sair \n");
				scanf("%d", &op);
				switch(op)
				{
    				case 1:
    					alterar_saquemax();
    					break;
    				case 2:
    					printf("Saindo... \n");
    					autptr == NULL;
    					sleep(3);
    					break;
    				default:
    					printf("Opcao invalida \n");
				}
			}while(op != 2);
		}
	}
}

void autenticar_conta()
{
	int verificar_conta, verificar_senha;
	printf("Digite a conta: ");
	scanf("%d", &verificar_conta);
	printf("Digite a senha: ");
	scanf("%d", &verificar_senha);
	for(int i = 0; i <= sizeof(contas)/sizeof(Conta) - 1; i++)
	{
		if (contas[i].numero_conta == verificar_conta && contas[i].senha == verificar_senha)
		{
			autptr = &contas[i];
			break;
		}
	}
	if (autptr == NULL)
	{
		printf("Login invalido \n");
	}
}

void deslogar()
{
	if(autptr == NULL)
	{
		printf("Voce nao encontra-se logado! \n");
		sleep(3);
	}
	else
	{
		int lop;
		do
		{
			printf("Realmente deseja deslogar?\n");
			printf("(1) Sim ------- (2) Nao \n");
			if(lop == 1)
			{
				autptr == NULL;
			}
			else
			{
				break;
			}
		} while(lop != 1 || lop != 0);
	}
}

void verificar_nulo(void (*funcptr)())
{
	if(autptr == NULL)
	{
		printf("Necessario fazer login! \n");
		sleep(2);
	}
	else
	{
		funcptr();
	}
}

void verificar_saldo()
{
	printf("Seu saldo atual: %.2f \n", autptr->saldo);
	sleep(5);
}

void sacar_dinheiro()
{
	float saque;
	if(autptr->saldo < 0)
	{
		printf("Saldo Negativado! \n");
		sleep(5);
	}
	else
	{
		do
		{
			printf("Quanto deseja sacar: ");
			scanf("%f", &saque);
			if((saque > SAQUE_MAX) || (saque > autptr -> saldo))
			{
				printf("O saque extrapola o valor maximo de: %.2f \n", SAQUE_MAX);
			}
		}
		while(saque > SAQUE_MAX || saque > autptr -> saldo);
		autptr -> saldo -= saque;
		printf("Valor de %.2f retirado! \n", saque);
	}
}

void depositar_dinheiro()
{
	float deposito;
	printf("Insira um valor a ser depositado: ");
	do
	{
		scanf("%f", &deposito);
		if(deposito < 0)
		{
			printf("Valores negativos nao sao validos \n");
		}
	} while(deposito < 0);
	printf("Valor de %.2f depositado! \n", deposito);
	autptr -> saldo += deposito;
}

void transferir_dinheiro() {
	int verificar_conta;
	float valor_transferir;
	Conta * transfptr = NULL;
	printf("Digite a conta a ser transferido o valor: ");
	scanf("%d", &verificar_conta);
	for(int i = 0; i <= sizeof(contas)/sizeof(Conta) - 1; i++)
	{
		if (contas[i].numero_conta == verificar_conta)
		{
			transfptr = &contas[i];
			printf("Digite o valor que voce deseja transferir: ");
			do
			{
				scanf("%f", &valor_transferir);
				if(valor_transferir < 0)
				{
					printf("Valor negativo invalido! Digite novamente: \n");
				}
			} while(valor_transferir < 0 || valor_transferir > autptr -> saldo);
			break;
		}
	}
	if (transfptr == NULL) {
		printf("Conta a transferir inexistente! \n");
	}
	else
	{
		printf("Valor transferido: %.2f \n", valor_transferir);
		autptr -> saldo -= valor_transferir;
		transfptr -> saldo += valor_transferir;
	}
}

void alterar_saquemax()
{
	float * sqmax_ptr = &SAQUE_MAX;
	int op = -1;
	do
	{
		printf("Insira o valor do saque maximo \n");
		scanf("%f", sqmax_ptr);
		printf("Saque max alterado para %.2f \n", SAQUE_MAX);
		while(op != 0 || op != 1)
		{
			printf("Deseja confirmar a operacao? \n");
			printf("1) Sim | 0) Nao \n");
			scanf("%d", &op);
			if(op != 0 && op != 1)
			{
				printf("Opcao invalida! \n");
			}
			else
			{
		    	break;
			}
		}
	} while(op != 1);
	printf("Operacao confirmada! \n");
	sleep(1);
}