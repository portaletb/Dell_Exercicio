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
        int ranking;

        cout << "\nJogador " << (i + 1) << ":\n";
        cout << "Nome completo: ";
        cin.ignore(); 
        getline(cin, nome);

        cout << "Nickname: ";
        cin >> nick;
       
        do {
            cout << "Pontuação de ranking (1 a 15000): ";
            cin >> ranking;
    
            if (ranking < 1 || ranking > 15000) {
                cout << " Número inválido. Digite novamente.\n";
            }
    
        } while (ranking < 1 || ranking > 15000);
    
        jogadores.emplace_back(Pessoa(nome, nick, ranking));
    }

    if (qtd < 4 || qtd > 8 || qtd % 2 != 0) {
        cout << "O número de jogadores no torneio é inválido" << endl;
    } else {
        // Embaralhar os jogadores
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(jogadores.begin(), jogadores.end(), default_random_engine(seed));

        // Criar vetor de ponteiros
        vector<Pessoa*> jogadoresAtivos;
        for (auto& p : jogadores) {
            jogadoresAtivos.push_back(&p);
        }

        // Executar torneio recursivo
        Torneio t;
        t.executarTorneioRecursivo(jogadoresAtivos);
    }

    return 0;
}
