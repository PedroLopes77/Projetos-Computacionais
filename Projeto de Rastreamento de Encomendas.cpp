#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stdexcept>
#include <unordered_map>

class Encomenda {
private:
    std::string id;
    std::string remetente;
    std::string destinatario;
    std::string status;
    std::string localizacao;

public:
    Encomenda() : id(""), remetente(""), destinatario(""), status(""), localizacao("") {}

    Encomenda(std::string id, std::string remetente, std::string destinatario)
        : id(id), remetente(remetente), destinatario(destinatario), status("Em processamento"), localizacao("Centro de Distribuição") {}

    void atualizarStatus(std::string novo_status, std::string nova_localizacao) {
        status = novo_status;
        localizacao = nova_localizacao;
    }

    std::string obterID() const {
        return id;
    }

    std::string obterStatus() const {
        return status;
    }

    std::string obterLocalizacao() const {
        return localizacao;
    }

    void exibirInformacoes() const {
        std::cout << "Encomenda ID: " << id << std::endl;
        std::cout << "Remetente: " << remetente << std::endl;
        std::cout << "Destinatário: " << destinatario << std::endl;
        std::cout << "Status: " << status << std::endl;
        std::cout << "Localização: " << localizacao << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
};

class Fila {
private:
    std::queue<Encomenda> fila;

public:
    void adicionarEncomenda(const Encomenda& encomenda) {
        fila.push(encomenda);
    }

    Encomenda processarProxima() {
        if (fila.empty()) {
            throw std::runtime_error("Nenhuma encomenda na fila.");
        }
        Encomenda encomenda = fila.front();
        fila.pop();
        return encomenda;
    }

    bool estaVazia() const {
        return fila.empty();
    }
};

class SistemaDeRastreamento {
private:
    Fila filaProcessamento;
    Fila filaTransito;
    Fila filaEntrega;
    std::unordered_map<std::string, Encomenda> todasEncomendas;

public:
    void cadastrarEncomenda(const Encomenda& encomenda) {
        todasEncomendas[encomenda.obterID()] = encomenda;
        filaProcessamento.adicionarEncomenda(encomenda);
    }

    void listarEncomendas() const {
        for (const auto& [id, encomenda] : todasEncomendas) {
            encomenda.exibirInformacoes();
        }
    }

    void buscarEncomenda(const std::string& id) const {
        auto it = todasEncomendas.find(id);
        if (it != todasEncomendas.end()) {
            it->second.exibirInformacoes();
        } else {
            std::cout << "Encomenda não encontrada!" << std::endl;
        }
    }

    void processarEncomendas() {
        while (!filaProcessamento.estaVazia()) {
            Encomenda encomenda = filaProcessamento.processarProxima();
            encomenda.atualizarStatus("Em trânsito", "Em rota para o destino");
            filaTransito.adicionarEncomenda(encomenda);
        }

        while (!filaTransito.estaVazia()) {
            Encomenda encomenda = filaTransito.processarProxima();
            encomenda.atualizarStatus("Pronto para entrega", "Centro de distribuição local");
            filaEntrega.adicionarEncomenda(encomenda);
        }

        while (!filaEntrega.estaVazia()) {
            Encomenda encomenda = filaEntrega.processarProxima();
            encomenda.atualizarStatus("Entregue", "Endereço do destinatário");
            encomenda.exibirInformacoes();
        }
    }
};

void exibirMenu() {
    std::cout << "Menu de Rastreamento de Encomendas" << std::endl;
    std::cout << "1. Cadastrar Encomenda" << std::endl;
    std::cout << "2. Listar Todas as Encomendas" << std::endl;
    std::cout << "3. Buscar Encomenda por ID" << std::endl;
    std::cout << "4. Processar Encomendas" << std::endl;
    std::cout << "5. Sair" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main() {
    SistemaDeRastreamento sistema;
    int opcao;

    do {
        exibirMenu();
        std::cin >> opcao;

        switch (opcao) {
        case 1: {
            std::string id, remetente, destinatario;
            std::cout << "ID da Encomenda: ";
            std::cin >> id;
            std::cout << "Remetente: ";
            std::cin >> remetente;
            std::cout << "Destinatário: ";
            std::cin >> destinatario;
            Encomenda encomenda(id, remetente, destinatario);
            sistema.cadastrarEncomenda(encomenda);
            break;
        }
        case 2:
            sistema.listarEncomendas();
            break;
        case 3: {
            std::string id;
            std::cout << "ID da Encomenda: ";
            std::cin >> id;
            sistema.buscarEncomenda(id);
            break;
        }
        case 4:
            sistema.processarEncomendas();
            break;
        case 5:
            std::cout << "Saindo..." << std::endl;
            break;
        default:
            std::cout << "Opção inválida!" << std::endl;
        }

    } while (opcao != 5);

    return 0;
}
