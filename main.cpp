#include "main.hpp"
using namespace std;
int main() {
    vector<Pessoa> jogadores;
    int qtd;

    cout << "Quantos jogadores deseja cadastrar? ";
    cin >> qtd;
    cin.ignore(); // limpar o '\n' do buffer

    for (int i = 0; i < qtd; ++i) {
        string nome, nick;
        int pontos;

        cout << "\nJogador " << (i + 1) << ":\n";
        cout << "Nome completo: ";
        getline(cin, nome);

        cout << "Nickname: ";
        getline(cin, nick);

        cout << "Pontuação no ranking: ";
        cin >> pontos;
        cin.ignore();  // limpar o buffer após número

        jogadores.emplace_back(nome, nick, pontos);
    }

    if(qtd <4 || qtd >8 || qtd %2 != 0){
       cout << "O número de jogadores no torneio é inválido"<<endl;
    }
    else {

    // Embaralhar os jogadores
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(jogadores.begin(), jogadores.end(), default_random_engine(seed));

    // Executar jogos em pares
    Torneio t;
    for (size_t i = 0; i + 1 < jogadores.size(); i += 2) {
        t.jogo(jogadores[i], jogadores[i + 1]);
    }
   
}

    return 0;
}