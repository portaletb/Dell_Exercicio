#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
using namespace std;

class Pessoa {
    private:
        string nome;
        string nickname;
        int pontuacaoRanking; //pontuação é completamente diferente de pontos, um é apenas visual enquanto o outro é sobre
        int pontos = 70;      //os pontos dentro do torneio
        int acaoUsada[5] = {0}; 
    
    public:
        Pessoa(string n, string nick, int pontuacao)
            : nome(n), nickname(nick), pontuacaoRanking(pontuacao) {}
    
        string getNome() {
            return nome;
        }
    
        string getNickname() {
            return nickname;
        }
    
        int getPontuacaoRanking() {
            return pontuacaoRanking;
        }

        int getPontos(){
            return pontos;
        }

        void atualizarPontos(int delta) {  //delta = variavel aleatória
            pontos += delta;
        }
               
        void registrarAcao(int acao) {
            if (acao >= 1 && acao <= 5) {
                acaoUsada[acao - 1]++;
            }
        }        

        void exibirAcoesUsadas() {
            cout << "Ações usadas por " << nickname << ":\n";
            cout << "1 - Jogada original: " << acaoUsada[0] << "x\n";
            cout << "2 - Gafe: " << acaoUsada[1] << "x\n";
            cout << "3 - Posicionamento vantajoso: " << acaoUsada[2] << "x\n";
            cout << "4 - Desrespeito ao adversário: " << acaoUsada[3] << "x\n";
            cout << "5 - Ataque de fúria: " << acaoUsada[4] << "x\n";
        }
       
        void mostrarRankingGrafico(vector<Pessoa>& jogadores) {
            // Ordenar por pontos (decrescente)
            sort(jogadores.begin(), jogadores.end(), [](Pessoa& a, Pessoa& b) {
                return a.getPontos() > b.getPontos();
            });
        
            cout << "\n===== RANKING FINAL DO TORNEIO =====\n";
            for (auto& jogador : jogadores) {
                cout << "\n👤 " << jogador.getNickname() << " (" << jogador.getPontos() << " pts)\n";
                cout << "   Ações usadas:\n";
        
                // Pegar quantas vezes cada ação foi usada
                const char* nomesAcoes[5] = {
                    "Jogada original     ",
                    "Gafe                ",
                    "Posicionamento vant.",
                    "Desrespeito         ",
                    "Ataque de fúria     "
                };
        
                for (int i = 0; i < 5; ++i) {
                    int vezes = jogador.getPontuacaoRanking();  // método a ser adicionado na classe
                    cout << "   " << nomesAcoes[i] << ": ";
                    for (int j = 0; j < vezes; ++j) cout << "#";
                    cout << " (" << vezes << ")\n";
                }
            }
        }

        vector<bool> acaoContabilizadaRodada = vector<bool>(5, false);

        void resetarAcoesRodada() {
             acaoContabilizadaRodada = vector<bool>(5, false);
        }

        int calcularPontosRodada() {
         int pontos = 0;
         if (acaoContabilizadaRodada[0]) pontos += 5;   // Jogada original
         if (acaoContabilizadaRodada[1]) pontos -= 3;   // Gafe
         if (acaoContabilizadaRodada[2]) pontos += 2;   // Posicionamento vantajoso
         if (acaoContabilizadaRodada[3]) pontos -= 5;   // Desrespeito
         if (acaoContabilizadaRodada[4]) pontos -= 7;   // Ataque de fúria
         return pontos;
}
    };
        
    class Torneio {
        private:
        map<string, int> apostasFeitas;
        map<string, int> fichasGanhas;
        map<string, int> fichasPerdidas;
        int fichasAtuais = 1000;  // banca inicial do sistema fictício
        
        
        public:

            Pessoa* jogo(Pessoa &p1, Pessoa &p2) {
             vector<Pessoa*> vencedores;
             
                cout << "\n=== Jogo entre " << p1.getNickname()
                     << " e " << p2.getNickname() << " ===\n";
        
                cout << "💰 Aposta: Em quem você deseja apostar 100 fichas?\n";
                cout << "1 - " << p1.getNickname() << "\n";
                cout << "2 - " << p2.getNickname() << "\n";
                int aposta;
                    cin >> aposta;

                Pessoa* jogadorApostado = (aposta == 1) ? &p1 : &p2;
                string nickApostado = jogadorApostado->getNickname();
                apostasFeitas[nickApostado] += 10;
                fichasAtuais -= 100;

                
                int escolhaJogador;

                bool aux = true;
                    while (aux == true){
                cout << "Quem fará a jogada?\n";
                cout << "1 - " << p1.getNickname() << "\n";
                cout << "2 - " << p2.getNickname() << "\n";
                cout << "Escolha (1 ou 2): ";
                cin >> escolhaJogador;
        
                Pessoa* jogadorEscolhido = nullptr;
        
                if (escolhaJogador == 1)
                    jogadorEscolhido = &p1;
                else if (escolhaJogador == 2)
                    jogadorEscolhido = &p2;
                else {
                    cout << "Opção inválida. Ninguém jogou.\n";
                    return nullptr;
                }
        
                cout << "\nEscolha a ação:\n";
                cout << "1 - Jogada original (+5pts)\n";
                cout << "2 - Gafe (-3pts)\n";
                cout << "3 - Posicionamento vantajoso (+2pts)\n";
                cout << "4 - Desrespeito ao adversário (-5pts)\n";
                cout << "5 - Ataque de fúria (-7pts)\n";
                cout << "Digite sua escolha: ";
        
                int acao;
                cin >> acao;
        
                int delta = 0;
        
                switch (acao) {
                    case 1:
                        delta = 5;
                        break;
                    case 2:
                        delta = -3;
                        break;
                    case 3:
                        delta = 2;
                        break;
                    case 4:
                        delta = -5;
                        break;
                    case 5:
                        delta = -7;
                        break;
                    default:
                        cout << "Ação inválida.\n";
                        return nullptr;
                }
        
                jogadorEscolhido->atualizarPontos(delta);
                jogadorEscolhido->registrarAcao(acao); 

       

                cout << jogadorEscolhido->getNickname()
                     << " agora tem " << jogadorEscolhido->getPontos() 
                     << " pontos.\n";
                     char n;
                     cout << "Deseja continuar o jogo? (y/n)" << endl;
                     cin >> n;
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');  // limpa até o '\n'
                     
                     if (n == 'y' || n == 'Y') {
                         aux = true;
                     } else {
                         aux = false;
                     }                
            }
            Pessoa* vencedor = nullptr;

            if (p1.getPontos() > p2.getPontos()) {
           cout << "🏆 " << p1.getNickname() << " venceu a rodada com mais pontos!\n";
               p1.atualizarPontos(30);  // bônus pela vitória
               vencedor = &p1;
          } else if (p2.getPontos() > p1.getPontos()) {
           cout << "🏆 " << p2.getNickname() << " venceu a rodada com mais pontos!\n";
               p2.atualizarPontos(30);  // bônus pela vitória
               vencedor = &p2;
          } else {
           cout << "🤝 Empate detectado! Blitz match ativada...\n";
               random_device rd;
               mt19937 g(rd());
               uniform_int_distribution<int> dist(0, 1);
              vencedor = (dist(g) == 0) ? &p1 : &p2;
              vencedor->atualizarPontos(2);
              cout << vencedor->getNickname() << " venceu a blitz match (+2 pontos)!\n";
}
                int pontosP1 = p1.calcularPontosRodada();
                int pontosP2 = p2.calcularPontosRodada();               

                p1.atualizarPontos(pontosP1);
                p2.atualizarPontos(pontosP2);               

                p1.resetarAcoesRodada();
                p2.resetarAcoesRodada();                

                cout << p1.getNickname() << " ganhou " << pontosP1 << " pontos por ações distintas.\n";
                cout << p2.getNickname() << " ganhou " << pontosP2 << " pontos por ações distintas.\n";

            if (vencedor == jogadorApostado) {
                cout << "🎉 Aposta vencida! Você ganhou 200 fichas.\n";
                fichasGanhas[nickApostado] += 200;
                fichasAtuais += 200;
            } else {
                cout << "😢 Aposta perdida. Você perdeu 100 fichas.\n";
                fichasPerdidas[nickApostado] += 100;
            }

            return vencedor;

        }
    
            Pessoa* executarTorneioRecursivo(vector<Pessoa*>& jogadores) {
                if (jogadores.size() == 1) {
                    cout << "\n🏆 VENCEDOR FINAL: " << jogadores[0]->getNickname()
                         << " com " << jogadores[0]->getPontos() << " pontos!\n";
                    jogadores[0]->exibirAcoesUsadas();
                    return jogadores[0];

                    cout << "\n📊 Estatísticas das Apostas Virtuais:\n";
                    cout << "Fichas finais do sistema: " << fichasAtuais << "\n";
    
                    string maisApostado, maiorLucro, maiorPrejuizo;
                    int maxApostas = 0, maxGanho = 0, maxPerda = 0;
    
                    for (auto& [nick, total] : apostasFeitas) {
                    cout << "Jogador: " << nick 
                    << " | Apostado: " << total
                    << " | Ganho: " << fichasGanhas[nick]
                    << " | Perdido: " << fichasPerdidas[nick] << "\n";
             
                    if (total > maxApostas) {
                    maxApostas = total;
                    maisApostado = nick;
                    }
                    if (fichasGanhas[nick] > maxGanho) {
                    maxGanho = fichasGanhas[nick];
                    maiorLucro = nick;
                    }
                    if (fichasPerdidas[nick] > maxPerda) {
                    maxPerda = fichasPerdidas[nick];
                    maiorPrejuizo = nick;
                    }
    }
    
                    cout << "\n🏅 Jogador mais apostado: " << maisApostado << endl;
                    cout << "💰 Jogador que mais rendeu: " << maiorLucro << endl;
                    cout << "📉 Jogador que mais causou prejuízo: " << maiorPrejuizo << endl;
    

                }
        
                cout << "\n--- NOVA FASE DO TORNEIO COM " << jogadores.size() << " JOGADORES ---\n";
        
                random_device rd;
                mt19937 g(rd());
                shuffle(jogadores.begin(), jogadores.end(), g);
        
                vector<Pessoa*> vencedores;
        
                vector<pair<Pessoa*, Pessoa*>> partidas;
                for (size_t i = 0; i + 1 < jogadores.size(); i += 2) {
                partidas.push_back({jogadores[i], jogadores[i + 1]});
    }

                while (!partidas.empty()) {
                cout << "\n🎯 Partidas disponíveis nesta fase:\n";
                for (size_t i = 0; i < partidas.size(); ++i) {
                cout << i + 1 << " - " << partidas[i].first->getNickname()
                 << " vs " << partidas[i].second->getNickname() << "\n";
    }

                int escolha;
                 cout << "Digite o número da partida que deseja assistir (ou 0 para simular todas): ";
                 cin >> escolha;

                if (escolha == 0) {
             // Simula todas as partidas restantes
                for (auto& par : partidas) {
                Pessoa* vencedor = (par.first->getPontos() >= par.second->getPontos()) ? par.first : par.second;
                vencedor->atualizarPontos(30);
                cout << "⚙️  Simulado: " << vencedor->getNickname() << " venceu automaticamente.\n";
                vencedores.push_back(vencedor);
        }
                partidas.clear();
    }           else if (escolha > 0 && escolha <= partidas.size()) {
                auto par = partidas[escolha - 1];
                Pessoa* vencedor = jogo(*par.first, *par.second);
                 if (vencedor)
                vencedores.push_back(vencedor);
                partidas.erase(partidas.begin() + (escolha - 1));
    }            else {
                cout << "Opção inválida. Tente novamente.\n";
    }
}

                return executarTorneioRecursivo(vencedores);}
    };