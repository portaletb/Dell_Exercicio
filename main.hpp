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

    };

    class Torneio {
        public:

            void jogo(Pessoa &p1, Pessoa &p2) {
             vector<Pessoa*> vencedores;
             
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
                jogadorEscolhido->registrarAcao(acao); 

        
                cout << jogadorEscolhido->getNickname()
                     << " agora tem " << jogadorEscolhido->getPontos() 
                     << " pontos.\n";
                cout << "Deseja continuar o jogo? (y/n)" << endl;
                cin >> aux;
            }
            cout << "Escolha (1 ou 2) caso tenha ou 0 caso seja empate: ";

            int escolha;
            cin >> escolha;
    
            if (escolha == 1) {
                p1.atualizarPontos(30);
                vencedores.push_back(&p1);
            } else if (escolha == 2) {
                p2.atualizarPontos(30);
                vencedores.push_back(&p2);
            }
            else {
                cout << "Empate! Blitz match ativada...\n";
                random_device rd;
                mt19937 g(rd());
                uniform_int_distribution<int> dist(0, 1);
                int vencedorAleatorio = dist(g);
    
                Pessoa* vencedor = (vencedorAleatorio == 0) ? &p1 : &p2;
                vencedor->atualizarPontos(2);
                cout << "🏁 " << vencedor->getNickname() << " venceu a blitz match (+2 pontos)!\n";
                vencedores.push_back(vencedor);
        }
        
               random_device rd;
               mt19937 g(rd());
               shuffle(vencedores.begin(), vencedores.end(), g);
    
               if(vencedores.size() == 1) {
               cout << "\n🏆 VENCEDOR FINAL: " << vencedores[0]->getNickname()
                 << " com " << vencedores[0]->getPontos() << " pontos!\n";
                 return;
        }
    }
    };
        