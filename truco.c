#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define NUM_CARTAS 40
#define RANDOM_INDEX() (rand()%(NUM_CARTAS))

typedef struct
{
    char numero[3];
    char naipe[10];
    int peso;
    bool estaForaDoMonte;
} Carta;

typedef struct
{
    Carta carta;
    int jogador;
} Jogada;

// DECLARACAO DAS FUNCOES 
void printLogo();
void moverCartas(Carta monteInicial[], Carta destino[], int indiceDestino);
void distribuirCartas();
void mostrarInformacoesRodada();
void jogada(int jogador);
void jogarCarta(int jogador);
void aumentarValor(int jogador);
void aceitarAumento(int jogador);
void processarAcaoJogador(int opcao, int jogador);
void mostrarCartasDoJogador(int jogador);

// VARIAVEIS GLOBAIS
Carta monte[40] = { // O monte contendo todas as cartas do jogo
    {"1","Espadas",12,false},{"2","Espadas",5,false},{"3","Espadas",6,false},{"4","Espadas",7,false},{"5","Espadas",8,false},{"6","Espadas",9,false},{"7","Espadas",10,false},{"10","Espadas",1,false},{"11","Espadas",2,false},{"12","Espadas",3,false},
    {"1","Copas",4,false},{"2","Copas",5,false},{"3","Copas",6,false},{"4","Copas",7,false},{"5","Copas",8,false},{"6","Copas",9,false},{"7","Copas",13,false},{"10","Copas",1,false},{"11","Copas",2,false},{"12","Copas",3,false},
    {"1","Ouros",4,false},{"2","Ouros",5,false},{"3","Ouros",6,false},{"4","Ouros",7,false},{"5","Ouros",8,false},{"6","Ouros",9,false},{"7","Ouros",10,false},{"10","Ouros",1,false},{"11","Ouros",2,false},{"12","Ouros",3,false},
    {"1","Paus",11,false},{"2","Paus",5,false},{"3","Paus",6,false},{"4","Paus",14,false},{"5","Paus",8,false},{"6","Paus",9,false},{"7","Paus",10,false},{"10","Paus",1,false},{"11","Paus",2,false},{"12","Paus",3,false}};
Carta cartasJogador1[3];
Carta cartasJogador2[3];

int rodadaAtual = 1;
int valorDaRodada = 1;
bool rodadaAcabou = false;

int pontosJogador1 = 0, pontosJogador2 = 0;

bool aumentoPendente = false;
int ultimoAumento = 0;
bool realizouAcao = false;

int turnoAtual = 1;
Jogada jogadas[2];

int vencedoresDasMaos[3]; // 0 - empate, 1 e 2
int maoAtual = 1;

int main() {
    srand(time(0));

    printLogo();
    printf("\tJOGO INICIANDO...\n");

    while (pontosJogador1 < 12 || pontosJogador2 < 12){ // partida completa
        distribuirCartas();
        
        while (!rodadaAcabou) { // rodada
            while (jogadas[0].carta.numero != 0 && jogadas[1].carta.numero != 0) { // mao
                jogada(1);
                jogada(2);
            }

            
        } 
        


    };
}

void moverCartas (Carta monteInicial[], Carta destino[], int indiceDestino) {
    int randIndex;
    do {
        randIndex = RANDOM_INDEX();
    } while (monteInicial[randIndex].estaForaDoMonte);
    destino[indiceDestino] = monteInicial[randIndex];
    monteInicial[randIndex].estaForaDoMonte = true;

}

void distribuirCartas() {
    moverCartas(monte, cartasJogador1, 0);
    moverCartas(monte, cartasJogador2, 0);
    moverCartas(monte, cartasJogador1, 1);
    moverCartas(monte, cartasJogador2, 1);
    moverCartas(monte, cartasJogador1, 2);
    moverCartas(monte, cartasJogador2, 2);
}

void mostrarInformacoesRodada() {
    printf("-----------------\n");
    printf("== RODADA %d ==\n", rodadaAtual);
    printf("Valor da rodada: %d\n", valorDaRodada);
    printf("Pontuacao partida: Jogador 1 [%d] x [%d] Jogador 2\n", pontosJogador1, pontosJogador2);
};

void mostrarMenuAcoes(int jogador) {
    printf("\nMENU\n");
    if (aumentoPendente && ultimoAumento != jogador) { // outro jogador propos um aumento
        printf("2. Aceitar e aumentar mais\n");
        printf("3. Aceitar aumento\n");
        printf("4. Desistir\n");
    }

    if (aumentoPendente && ultimoAumento == jogador) { // esse jogador propos o aumento
        printf("4. Desistir\n");
        printf("5. Terminar turno\n");
    }
    
    if (!aumentoPendente) { // nao tem aumento pendente
        if (!realizouAcao || turnoAtual == jogador) {
            printf("1. Jogar carta\n");
        }
        if (ultimoAumento != jogador) { // se o ultimo aumento foi proposto por esse jogador, entao ele n pode aumentar dnv
            printf("2. Aumentar\n");
        }
        printf("4. Desistir\n");
        if (realizouAcao == true) // se ja realizou alguma acao, pode encerrar o turno
            printf("5. Terminar turno\n");
    }
    printf("Digite: ");
};

void jogada(int jogador) {
    mostrarInformacoesRodada();
    printf("\nTURNO DO JOGADOR %d\n", jogador);
    mostrarCartasDoJogador(jogador);
    int opcao = 0;
    while (opcao != 5) { // Enquanto o jogador nao finalizar a rodada, nao passa para o outro
        mostrarMenuAcoes(jogador);
        fflush(stdin);
        scanf("%d", &opcao);
        processarAcaoJogador(opcao, jogador);
    }
    realizouAcao = false;
}

void processarAcaoJogador(int opcao, int jogador) {
    switch (opcao) {
        case 1:
            jogarCarta(jogador);
            break;
        case 2:
            aumentarValor(jogador);
            break;
        case 3:
            aceitarAumento(jogador);
            break;
        case 4:
            break;
        case 5:
            break;
    }
}

void jogarCarta(int jogador) {
    mostrarCartasDoJogador(jogador);
    printf("Escolha uma carta: ");
    fflush(stdin);
    int indexCarta;
    scanf("%d", &indexCarta);
    if (jogador == 1) {
        jogadas[0].carta = cartasJogador1[indexCarta]; 
    } else {
        jogadas[1].carta = cartasJogador2[indexCarta]; 
    }
    turnoAtual = jogador == 1 ? 2 : 1; //so muda o turno quando o jogador jogar uma carta
}

void aumentarValor(int jogador) {
    if (aumentoPendente) {
        if (valorDaRodada == 1)
            valorDaRodada = 3;
        else {
            valorDaRodada += 3;
        }
    }
    int valorTemp = valorDaRodada == 1 ? 3 : valorDaRodada+3;
    ultimoAumento = jogador;
    aumentoPendente = true;
    printf("\n==> O jogador %d propos um aumento para %d pontos\n", jogador, valorTemp);
    realizouAcao = true;
}

void aceitarAumento(int jogador) {
    if (valorDaRodada == 1)
        valorDaRodada = 3;
    else {
        valorDaRodada += 3;
    }
    aumentoPendente = false;
    realizouAcao = true;
}

void mostrarCartasDoJogador(int jogador) {
    printf("\nSuas cartas sao:\n");
    if (jogador == 1) {
        for (int i = 0 ; i < 3 ; i++) {
            printf("%d. %s - %s\n", i+1, cartasJogador1[i].numero, cartasJogador1[i].naipe);
        }
    }

    else {
        for (int i = 0 ; i < 3 ; i++) {
            printf("%d. %s - %s\n", i+1, cartasJogador2[i].numero, cartasJogador2[i].naipe);
        }
    }
}

void definirVencedorDaMao() {
    if (jogadas[0].carta.peso > jogadas[1].carta.peso)
        vencedoresDasMaos[maoAtual] = 1;
    else if (jogadas[1].carta.peso > jogadas[0].carta.peso)
        vencedoresDasMaos[maoAtual] = 2;
    else
        vencedoresDasMaos[maoAtual] = 0;
    maoAtual++;

}

void printLogo() {
    printf(".------..------..------..------..------.\n");
    printf("|T.--. ||R.--. ||U.--. ||C.--. ||O.--. |\n");
    printf("| :/\\: || :(): || (\\/) || :/\\: || :/\\: |\n");
    printf("| (__) || ()() || :\\/: || :\\/: || :\\/: |\n");
    printf("| '--'T|| '--'R|| '--'U|| '--'C|| '--'O|\n");
    printf("`------'`------'`------'`------'`------'\n");
}
