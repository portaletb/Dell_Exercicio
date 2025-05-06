#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

class Pessoa {
    private:
        string nome;
        string nickname;
        int pontuacaoRanking; //pontuação é completamente diferente de pontos, um é apenas visual enquanto o outro é sobre
        int pontos = 70;      //os pontos dentro do torneio
    
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
    };

    class Torneio {
        public:
            void jogo(Pessoa &p1, Pessoa &p2) {
                cout << "\n=== Jogo entre " << p1.getNickname()
                     << " e " << p2.getNickname() << " ===\n";
        
                int escolhaJogador;
                char aux = 'y';
                    while (aux == 'y'){

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
                    return;
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
                        return;
                }
        
                jogadorEscolhido->atualizarPontos(delta);
        
                cout << jogadorEscolhido->getNickname()
                     << " agora tem " << jogadorEscolhido->getPontos() 
                     << " pontos.\n";
                cout << "Deseja continuar o jogo? (y/n)" << endl;
                cin >> aux;
            }
        }
        };
        