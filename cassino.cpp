#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Jogador {
private:
    string nome;
    int saldo;

public:
    Jogador(string nome = "Jogador", int saldoInicial = 1000) {
        this->nome = nome;
        this->saldo = saldoInicial;
    }

    void depositar(int valor) {
        if (valor > 0) {
            saldo += valor;
        }
    }

    bool retirar(int valor) {
        if (valor > 0 && valor <= saldo) {
            saldo -= valor;
            return true;
        }
        return false;
    }

    int getSaldo() const {
        return saldo;
    }

    void setNome(string nome) {
        this->nome = nome;
    }

    string getNome() const {
        return nome;
    }

    void salvarProgresso() const {
        ofstream arquivo("progresso.txt");
        if (arquivo.is_open()) {
            arquivo << nome << endl;
            arquivo << saldo << endl;
            arquivo.close();
        }
    }

    void carregarProgresso() {
        ifstream arquivo("progresso.txt");
        if (arquivo.is_open()) {
            getline(arquivo, nome);
            arquivo >> saldo;
            arquivo.close();
        }
    }
};

void jogarRoleta(Jogador &jogador);
void jogarBlackjack(Jogador &jogador);
void jogarCacaNiqueis(Jogador &jogador);

void exibirMenu() {
    cout << "Bem-vindo ao Cassino C++!" << endl;
    cout << "1. Jogar Roleta" << endl;
    cout << "2. Jogar Blackjack" << endl;
    cout << "3. Jogar Caca-niqueis" << endl;
    cout << "4. Ver Saldo" << endl;
    cout << "5. Carregar Progresso" << endl;
    cout << "6. Salvar Progresso" << endl;
    cout << "7. Sair" << endl;
}

int main() {
    srand(time(0));
    Jogador jogador;
    int escolha;

    do {
        exibirMenu();
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                jogarRoleta(jogador);
                break;
            case 2:
                jogarBlackjack(jogador);
                break;
            case 3:
                jogarCacaNiqueis(jogador);
                break;
            case 4:
                cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;
                break;
            case 5:
                jogador.carregarProgresso();
                cout << "Progresso carregado com sucesso!" << endl;
                break;
            case 6:
                jogador.salvarProgresso();
                cout << "Progresso salvo com sucesso!" << endl;
                break;
            case 7:
                cout << "Obrigado por jogar! Ate mais!" << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
    } while (escolha != 7);

    return 0;
}

void jogarRoleta(Jogador &jogador) {
    cout << "Bem-vindo a Roleta!" << endl;
    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;

    int aposta, valorAposta;
    int numeroSorteado;

    cout << "Escolha o tipo de aposta:" << endl;
    cout << "1. Numero especifico (0 a 36)" << endl;
    cout << "2. Vermelho ou Preto" << endl;
    cout << "3. Par ou Impar" << endl;
    cout << "Opcao: ";
    cin >> aposta;

    if (aposta < 1 || aposta > 3) {
        cout << "Opcao invalida!" << endl;
        return;
    }

    cout << "Digite o valor da aposta: ";
    cin >> valorAposta;

    if (!jogador.retirar(valorAposta)) {
        cout << "Voce nao tem saldo suficiente para essa aposta." << endl;
        return;
    }

    numeroSorteado = rand() % 37;
    cout << "A roleta girou... O numero sorteado e: " << numeroSorteado << endl;

    switch (aposta) {
        case 1: {
            int numeroEscolhido;
            cout << "Digite um numero entre 0 e 36: ";
            cin >> numeroEscolhido;

            if (numeroEscolhido == numeroSorteado) {
                int ganho = valorAposta * 35;
                jogador.depositar(ganho);
                cout << "Parabens! Voce ganhou " << ganho << " fichas!" << endl;
            } else {
                cout << "Voce perdeu a aposta." << endl;
            }
            break;
        }
        case 2: {
            string escolha;
            cout << "Escolha Vermelho (V) ou Preto (P): ";
            cin >> escolha;

            bool sorteadoVermelho = (numeroSorteado % 2 == 1 && numeroSorteado != 0);
            if ((escolha == "V" && sorteadoVermelho) || (escolha == "P" && !sorteadoVermelho)) {
                int ganho = valorAposta * 1;
                jogador.depositar(ganho);
                cout << "Parabens! Voce ganhou " << ganho << " fichas!" << endl;
            } else {
                cout << "Voce perdeu a aposta." << endl;
            }
            break;
        }
        case 3: {
            string escolha;
            cout << "Escolha Par (P) ou Impar (I): ";
            cin >> escolha;

            bool sorteadoPar = (numeroSorteado % 2 == 0);
            if ((escolha == "P" && sorteadoPar) || (escolha == "I" && !sorteadoPar)) {
                int ganho = valorAposta * 1;
                jogador.depositar(ganho);
                cout << "Parabens! Voce ganhou " << ganho << " fichas!" << endl;
            } else {
                cout << "Voce perdeu a aposta." << endl;
            }
            break;
        }
    }

    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;
}

void jogarBlackjack(Jogador &jogador) {
    cout << "Bem-vindo ao Blackjack!" << endl;
    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;

    int valorAposta;
    cout << "Digite o valor da aposta: ";
    cin >> valorAposta;

    if (!jogador.retirar(valorAposta)) {
        cout << "Voce nao tem saldo suficiente para essa aposta." << endl;
        return;
    }

    vector<int> maoJogador, maoDealer;
    maoJogador.push_back(rand() % 11 + 1);
    maoJogador.push_back(rand() % 11 + 1);
    maoDealer.push_back(rand() % 11 + 1);
    maoDealer.push_back(rand() % 11 + 1);

    cout << "Sua mao: ";
    for (int carta : maoJogador) {
        cout << carta << " ";
    }
    cout << endl;

    cout << "Carta visivel do dealer: " << maoDealer[0] << endl;

    char escolha;
    while (true) {
        cout << "Deseja pedir uma carta (P) ou parar (S)? ";
        cin >> escolha;

        if (escolha == 'P' || escolha == 'p') {
            maoJogador.push_back(rand() % 11 + 1);
            cout << "Sua mao: ";
            for (int carta : maoJogador) {
                cout << carta << " ";
            }
            cout << endl;

            int pontuacao = 0;
            for (int carta : maoJogador) {
                pontuacao += carta;
            }

            if (pontuacao > 21) {
                cout << "Voce estourou! Fim de jogo." << endl;
                return;
            }
        } else if (escolha == 'S' || escolha == 's') {
            break;
        } else {
            cout << "Escolha invalida! Tente novamente." << endl;
        }
    }

    cout << "Mao do dealer: ";
    for (int carta : maoDealer) {
        cout << carta << " ";
    }
    cout << endl;

    int pontuacaoJogador = 0;
    for (int carta : maoJogador) {
        pontuacaoJogador += carta;
    }

    int pontuacaoDealer = 0;
    for (int carta : maoDealer) {
        pontuacaoDealer += carta;
    }

    while (pontuacaoDealer < 17) {
        maoDealer.push_back(rand() % 11 + 1);
        pontuacaoDealer = 0;
        for (int carta : maoDealer) {
            pontuacaoDealer += carta;
        }
        cout << "Dealer pediu uma carta. Nova mao do dealer: ";
        for (int carta : maoDealer) {
            cout << carta << " ";
        }
        cout << endl;
    }

    cout << "Sua pontuacao: " << pontuacaoJogador << endl;
    cout << "Pontuacao do dealer: " << pontuacaoDealer << endl;

    if (pontuacaoJogador > 21) {
        cout << "Voce estourou e perdeu a aposta." << endl;
    } else if (pontuacaoDealer > 21 || pontuacaoJogador > pontuacaoDealer) {
        int ganho = valorAposta * 2;
        jogador.depositar(ganho);
        cout << "Voce ganhou " << ganho << " fichas!" << endl;
    } else if (pontuacaoJogador == pontuacaoDealer) {
        jogador.depositar(valorAposta);
        cout << "Empate! Sua aposta foi devolvida." << endl;
    } else {
        cout << "Voce perdeu a aposta." << endl;
    }

    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;
}

void jogarCacaNiqueis(Jogador &jogador) {
    cout << "Bem-vindo ao Caca-niqueis!" << endl;
    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;

    int valorAposta;
    cout << "Digite o valor da aposta: ";
    cin >> valorAposta;

    if (!jogador.retirar(valorAposta)) {
        cout << "Voce nao tem saldo suficiente para essa aposta." << endl;
        return;
    }

    string simbolos[] = {"7", "BAR", "Cereja", "Sino"};
    string rolo1 = simbolos[rand() % 4];
    string rolo2 = simbolos[rand() % 4];
    string rolo3 = simbolos[rand() % 4];

    cout << "Rolos: [" << rolo1 << "] [" << rolo2 << "] [" << rolo3 << "]" << endl;

    if (rolo1 == rolo2 && rolo2 == rolo3) {
        int multiplicador = 0;

        if (rolo1 == "7") {
            multiplicador = 10;
        } else if (rolo1 == "BAR") {
            multiplicador = 5;
        } else if (rolo1 == "Cereja") {
            multiplicador = 3;
        } else if (rolo1 == "Sino") {
            multiplicador = 2;
        }

        int ganho = valorAposta * multiplicador;
        jogador.depositar(ganho);
        cout << "Parabens! Voce ganhou " << ganho << " fichas!" << endl;
    } else {
        cout << "Nenhuma combinacao vencedora. Tente novamente!" << endl;
    }

    cout << "Seu saldo atual: " << jogador.getSaldo() << " fichas." << endl;
}