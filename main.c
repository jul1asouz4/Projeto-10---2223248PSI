#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h> 
#define MAX_RESERVAS 100
#define MAX_NOME 50
#define MAX_USUARIOS 100




/* void printWelcomeBanner() {
    printf("********************************************************************************\n");
    printf("*                                                                              *\n");
    printf("*  ########  ######## ##     ##     ##     ##  ######   #### ##    ##  ######  *\n");
    printf("*  ##     ## ##       ##     ##     ##     ## ##    ##   ##  ###   ## ##    ## *\n");
    printf("*  ##     ## ##       ##     ##     ##     ## ##         ##  ####  ## ##       *\n");
    printf("*  ########  ######   ##     ##     ##     ## ##   ####  ##  ## ## ## ##   ####*\n");
    printf("*  ##   ##   ##       ##     ##      ##   ##  ##    ##   ##  ##  #### ##    ## *\n");
    printf("*  ##    ##  ##       ##     ##       ## ##   ##    ##   ##  ##   ### ##    ## *\n");
    printf("*  ##     ## ########  #######         ###     ######   #### ##    ##  ######  *\n");
    printf("*                                                                              *\n");
    printf("********************************************************************************\n");
}

void printSystemInfo() {
    printf("********************************************************************************\n");
    printf("*                                                                              *\n");
    printf("*    Autor: Seu Nome                                                           *\n");
    printf("*    Versão: 1.0                                                               *\n");
    printf("*    Data: 24 de Junho de 2024                                                 *\n");
    printf("*                                                                              *\n");
    printf("********************************************************************************\n");
}

void printDecorativeElements() {
    printf("********************************************************************************\n");
    printf("*                                                                              *\n");
    printf("*      ██████╗ ██████╗ ███████╗███████╗███╗   ██╗                              *\n");
    printf("*     ██╔════╝██╔═══██╗██╔════╝██╔════╝████╗  ██║                              *\n");
    printf("*     ██║     ██║   ██║███████╗█████╗  ██╔██╗ ██║                              *\n");
    printf("*     ██║     ██║   ██║╚════██║██╔══╝  ██║╚██╗██║                              *\n");
    printf("*     ╚██████╗╚██████╔╝███████║███████╗██║ ╚████║                              *\n");
    printf("*      ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═══╝                              *\n");
    printf("*                                                                              *\n");
    printf("********************************************************************************\n\n");
}

void printLoadingAnimation() {
    printf("Carregando");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

int bannerzin() {
    printWelcomeBanner();
    printSystemInfo();
    printDecorativeElements();
    printLoadingAnimation();
    // Seu código aqui
    return 0;
}
 */

void menu()
{
    printf("-----SEJAM BEM-VINDOS AO DREAMQUEST!!!-----\n"
           "|1 - Login.\n"
           "|2 - Criar conta.\n"
           "|3 - Limpar terminal.\n"
           "|4 - Sair.\n"
           "--> Ecolha uma opção: \n");
}

typedef struct
{
    char nome[MAX_NOME];
    char documento[MAX_NOME];
} Passageiro;

typedef struct
{
    int id;
    Passageiro passageiro;
    char destino[MAX_NOME];
} Reserva;

typedef struct
{
    char username[MAX_NOME];
    char password[MAX_NOME];
} Usuario;

void toUppercase(char *str)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *str -= 32;
        }
        str++;
    }
}

int countCharacters(const char *str)
{
    int count = 0;
    while (*str)
    {
        count++;
        str++;
    }
    return count;
}

Reserva reservas[MAX_RESERVAS];
int totalReservas = 0;

Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;

Usuario *usuarioAtual = NULL;

void salvarReservas(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < totalReservas; i++)
    {
        fprintf(file, "%d,%s,%s,%s\n", reservas[i].id, reservas[i].passageiro.nome, reservas[i].passageiro.documento, reservas[i].destino);
    }
    fclose(file);
    printf("Reservas salvas com sucesso!\n");
}

void carregarReservas(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    totalReservas = 0;
    while (fscanf(file, "%d,%49[^,],%49[^,],%49[^\n]\n", &reservas[totalReservas].id, reservas[totalReservas].passageiro.nome, reservas[totalReservas].passageiro.documento, reservas[totalReservas].destino) != EOF)
    {
        totalReservas++;
    }
    fclose(file);
    printf("Reservas carregadas com sucesso!\n");
}

void salvarUsuarios(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < totalUsuarios; i++)
    {
        fprintf(file, "%s,%s\n", usuarios[i].username, usuarios[i].password);
    }
    fclose(file);
    printf("Usuários salvos com sucesso!\n");
}

void carregarUsuarios(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    totalUsuarios = 0;
    while (fscanf(file, "%49[^,],%49[^\n]\n", usuarios[totalUsuarios].username, usuarios[totalUsuarios].password) != EOF)
    {
        totalUsuarios++;
    }
    fclose(file);
    printf("Usuários carregados com sucesso!\n");
}

int criarConta()
{
    if (totalUsuarios >= MAX_USUARIOS)
    {
        printf("Número máximo de usuários atingido.\n");
        return 0;
    }

    Usuario novoUsuario;
    printf("Insira um nome de usuário: ");
    scanf("%s", novoUsuario.username);
    printf("Insira uma senha: ");
    scanf("%s", novoUsuario.password);

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(usuarios[i].username, novoUsuario.username) == 0)
        {
            printf("Nome de usuário já existe. Tente novamente.\n");
            return 0;
        }
    }

    usuarios[totalUsuarios] = novoUsuario;
    totalUsuarios++;
    printf("Conta criada com sucesso!\n");
    return 1;
}

int login()
{
    char username[MAX_NOME];
    char password[MAX_NOME];

    printf("Insira seu nome de usuário: ");
    scanf("%s", username);
    printf("Insira sua senha: ");
    scanf("%s", password);

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(usuarios[i].username, username) == 0 && strcmp(usuarios[i].password, password) == 0)
        {
            usuarioAtual = &usuarios[i];
            printf("Login bem-sucedido!\n");
            return 1;
        }
    }

    printf("Nome de usuário ou senha incorretos.\n");
    return 0;
}

void adicionarReserva()
{
    if (totalReservas >= MAX_RESERVAS)
    {
        printf("Número máximo de reservas atingido.\n");
        return;
    }

    Reserva *novaReserva = &reservas[totalReservas];
    novaReserva->id = totalReservas + 1;
    printf("Insira o nome do passageiro: ");
    scanf(" %49[^\n]", novaReserva->passageiro.nome);
    printf("Insira o documento do passageiro: ");
    scanf(" %49[^\n]", novaReserva->passageiro.documento);
    printf("Insira o destino: ");
    scanf(" %49[^\n]", novaReserva->destino);

    totalReservas++;
    printf("Reserva adicionada com sucesso!\n");
}

void visualizarReservas()
{
    for (int i = 0; i < totalReservas; i++)
    {
        printf("ID: %d\n", reservas[i].id);
        printf("Nome do Passageiro: %s\n", reservas[i].passageiro.nome);
        printf("Documento do Passageiro: %s\n", reservas[i].passageiro.documento);
        printf("Destino: %s\n", reservas[i].destino);
        printf("-----------------------------\n");
    }
}

int main()
{

    system("65001 Chcp");
    system("cls");

    int opcao;
    bool sair = false;
    char reservasFilename[] = "reservas.txt";
    char usuariosFilename[] = "usuarios.txt";

    carregarUsuarios(usuariosFilename);

    while (!sair)
    {
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 2:
            if (login())
            {
                carregarReservas(reservasFilename);
                while (1)
                {
                    printf("1. Adicionar Reserva\n");
                    printf("2. Visualizar Reservas\n");
                    printf("3. Salvar Reservas\n");
                    printf("4. Carregar Reservas\n");
                    printf("5. Logout\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcao);

                    if (opcao == 1)
                    {
                        adicionarReserva();
                    }
                    else if (opcao == 2)
                    {
                        visualizarReservas();
                    }
                    else if (opcao == 3)
                    {
                        salvarReservas(reservasFilename);
                    }
                    else if (opcao == 4)
                    {
                        carregarReservas(reservasFilename);
                    }
                    else if (opcao == 5)
                    {
                        usuarioAtual = NULL;
                        break;
                    }
                    else
                    {
                        printf("Opção inválida. Tente novamente.\n");
                    }
                }
            }
            break;
        case 3:
            criarConta();
            salvarUsuarios(usuariosFilename);
            break;
        case 1:
            system("cls"); 
            break;
        case 0:
            sair = true;
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    }

    return 0;
}