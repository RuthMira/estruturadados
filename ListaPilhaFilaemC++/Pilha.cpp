#include <iostream>
#include <string>

using namespace std;

struct No {
    string pagina;
    No* proximo;

    No(string p) : pagina(p), proximo(nullptr) {}
};

class Historico {
private:
    No* topo;

public:
    Historico() {
        topo = nullptr;
    }

    ~Historico() {
        while (topo != nullptr) {
            No* removido = topo;
            topo = topo->proximo;
            delete removido;
        }
    }

    void acessarPagina(string pagina) {
        No* novoNo = new No(pagina);
        novoNo->proximo = topo;
        topo = novoNo;

        cout << "Página acessada: " << novoNo->pagina << endl;
    }

    string voltarPagina() {
        if (topo == nullptr) {
            cout << "Não há páginas para voltar." << endl;
            return ""; 
        }

        No* removido = topo;
        topo = topo->proximo;

        string paginaVoltada = removido->pagina;

        delete removido;
        return paginaVoltada;
    }
};

int main() {
    Historico historico;

    historico.acessarPagina("www.google.com.br");
    historico.acessarPagina("www.github.com.br");
    historico.acessarPagina("www.youtrack.com.br");

    string pagina = historico.voltarPagina();
    cout << "\n" << pagina << endl;

    return 0;
}
