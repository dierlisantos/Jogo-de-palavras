#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
using namespace std;

string buscaPalavraRandom() {
    srand(time(NULL));
    int num = (rand() % 98) + 1;

    FILE* myfile;
    errno_t err;

    err = fopen_s(&myfile, "myfile.txt", "r");

    if (err != 0) {
        cout << "Erro ao abrir o arquivo";
        exit(0);
    }

    char linha[100];
    string resultado;
    int i = 1;

    while (fgets(linha, 128, myfile) != NULL) {
        if (i == num) {
            resultado = linha;
            cout << "A palavra e: " << resultado << endl;
            break;
        }
        i++;
    }
    fclose(myfile);
    return resultado;
}

bool existeLetraNaPalavra(char letra, string palavra) {
    for (int i = 0; i <= 4; i++) {
        if (letra == palavra[i])
            return true;  
    }
    return false;
}

int main() {
    char repetir = ' ';
    do {
        string palavraDescon = "";
        string palavraUsuario = "     ";
        string palavraFechada = "_____";
        int tentativa = 0;
        palavraDescon = buscaPalavraRandom();

        cout << "Vamos jogar um jogo de palavras! Veja as regras!\n";
        cout << "Descubra a palavra escondida. Ela possui 5 letras, em Portugues. Voce tem 5 tentativas\n";

        for (; tentativa <= 4; tentativa++) {
            cout << "Digite uma palavra\n";
            getline(cin, palavraUsuario);
            transform(palavraUsuario.begin(), palavraUsuario.end(), palavraUsuario.begin(), ::toupper);

            if (palavraUsuario.size() < 5 || palavraUsuario.size() > 5) {
                cout << "A palavra precisa ter 5 letras\n";
                tentativa--;
                continue; 
            }
            palavraUsuario = palavraUsuario+"\n";
          
            if (palavraUsuario == palavraDescon) {
                cout << "Parabens, voce acertou!" << endl;
                break;
            }
            else if (palavraUsuario != palavraDescon) {
                for (int j = 0; j <= 4; j++) {
                    if (palavraUsuario[j] == palavraDescon[j]) {
                        cout << "Voce acertou a letra  " << palavraUsuario[j] << " na " << j + 1 << "o posicao  " << endl;
                        palavraFechada[j] = palavraDescon[j];
                    }
                    else if (!existeLetraNaPalavra(palavraUsuario[j], palavraDescon)) {
                        cout << "A letra " << palavraUsuario[j] << " nao consta na palavra" << endl;
                    }
                    else {
                        cout << "Voce acertou a letra " << palavraUsuario[j] << " mas a posicao esta errada " << endl;
                    }
                }

                cout << "Atual: " << palavraFechada << endl;
            }
        }

        //chegou aqui com as tentativas esgotadas
        if (tentativa == 4)
            cout << "Voce esgotou as suas tentativas! A palavra era " << palavraDescon << endl <<
                    "Deseja tentar novamente? (S/N)\n";
        //chegou aqui porque acertou
        else
            cout << "Pretende recomecar o jogo? S ou N\n";

        cin >> repetir;
        cin.ignore();

        repetir = toupper(repetir);
    }

    while (repetir == 'S');
}
