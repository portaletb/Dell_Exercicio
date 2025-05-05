#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pessoa {
private:
    string nome;
    string nickname;
    int pontuacaoRanking;
    int armazenaPonto = 70;

public:
    // Construtor com 3 parâmetros
    Pessoa(string n, string nick, int pontuacao) {
        nome = n;
        nickname = nick;
        pontuacaoRanking = pontuacao;
    }

    // Getters
    string getNome() {
        return nome;
    }

    string getNickname() {
        return nickname;
    }

    int getPontuacaoRanking() {
        return pontuacaoRanking;
    }
};

class Menu {
    public:
        void exibirMenu() {
            int opcao;

cout << "Pressione 1 para Jogada orginal (+5pts)" <<endl;
cout << "Pressione 2 para Gafe (-3pts)" <<endl;
cout << "Pressione 3 para Posicionamento vantajoso (+2pts)"<<endl;
cout << "Pressione 4 para Desrespeito ao adversário (-5pts)"<<endl;
cout << "Pressione 5 Ataque de fúria (-7pts)"<<endl;