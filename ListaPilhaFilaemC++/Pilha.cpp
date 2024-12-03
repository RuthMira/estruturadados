#include <iostream>
#include <string>


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
            voltarPagina(); 
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
        cout << "Voltando para a página: " << paginaVoltada << endl;

        if (topo != nullptr) {
            cout << "Página atual: " << topo->pagina << endl;
        } else {
            cout << "Página atual: Início" << endl;  
        }
        delete removido; 
        
        return paginaVoltada;  
    }
};

int main() {
    Historico historico;

    historico.acessarPagina("Página 1");
    historico.acessarPagina("Página 2");
    historico.acessarPagina("Página 3");

    string pagina = historico.voltarPagina();
    cout << "Página voltada: " << pagina << endl;


    return 0;
}
