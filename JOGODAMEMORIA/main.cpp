#include <iostream>
#include <thread>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <chrono>


using namespace std;

const int linha = 4, coluna = 5, pares = (linha * coluna)/2, delayTime = 7;

int auxiliarPares = pares, linhaAle, colunaAle, pontuacao = 0, x1, y1, x2, y2, auxDelayTime;
char TABGAB[linha][coluna], TABSEC[linha][coluna], letra = 65;

void inicializarTabuleiros() {
    srand(time(NULL));

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            TABGAB[i][j] = '0';   
            TABSEC[i][j] = '*';   
        }
    }
    
    while (auxiliarPares > 0) {
        for (int i = 0; i < 2; i++) {
            do {
                linhaAle = rand() % linha;
                colunaAle = rand() % coluna;
            } while (TABGAB[linhaAle][colunaAle] != '0');
            
            TABGAB[linhaAle][colunaAle] = letra;
        }
        letra++;
        auxiliarPares--;
    }
}

void imprimirTabela() {
    cout << "  ";
    for (int i = 0; i < coluna; i++) {
        cout << setw(4) << i;
    }
    cout << endl;

    for (int i = 0; i < linha; i++) {
        cout << setw(2) << right << i;
        for (int j = 0; j < coluna; j++) {
            cout << setw(4) <<TABSEC[i][j];
        }
        cout << endl;
    }
}

bool validarEntrada(int x, int y) {
    if (x < 0 || x > (linha - 1) || y < 0 || y > (coluna - 1) || TABSEC[x][y] != '*') {
        cout << "Coordenadas inválidas ou carta já revelada! Tente novamente" << endl;
        return false;
    }
    return true;
}


bool verificarCartas(char carta1, char carta2) {
    if (carta1 != carta2) {
        cout << endl << "Cartas diferentes, tente novamente!" << endl;
        auxDelayTime = delayTime;
        while(auxDelayTime >= 0){
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "\rVoce tem " << auxDelayTime << " segundos para memorizar o tabuleiro!";
            cout.flush();
            auxDelayTime--;
        }
        return false;
    } else {
        pontuacao++;
        cout << endl << "Parabéns, você encontrou " << pontuacao << " par(es) de cartas" << endl;
        return true;
    }
}


void jogo() {
    while (pontuacao < pares) {
        cout << endl << "Pontuação: " << pontuacao << endl << endl;
        
        imprimirTabela();

        do {
            cout << endl << "Selecione a primeira carta, digite a linha e coluna: ";
            cin >> x1 >> y1;
            cout << endl;
        } while (!validarEntrada(x1, y1));

        TABSEC[x1][y1] = TABGAB[x1][y1];

        imprimirTabela();
        
        do {
            cout << endl << "Selecione a segunda carta, digite a linha e coluna: ";
            cin >> x2 >> y2;
            cout << endl;
        } while (!validarEntrada(x2, y2));

        TABSEC[x2][y2] = TABGAB[x2][y2];

        imprimirTabela();
        
        if (!verificarCartas(TABSEC[x1][y1], TABSEC[x2][y2])) {
            TABSEC[x1][y1] = '*';
            TABSEC[x2][y2] = '*';
        }
    }

    cout << endl << "Parabéns, você encontrou todos os pares!" << endl;                
}


int main() {
	
	cout << "***************" << endl;
	cout << "JOGO DA MEMÓRIA" << endl;
	cout << "***************" << endl;
    
    inicializarTabuleiros();
    jogo();

    return 0;
}
