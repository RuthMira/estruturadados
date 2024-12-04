#include <iostream>
#include <stdexcept>
#include <string>

struct Pessoa {
    std::string nome;
    int idade;
    
    Pessoa(std::string n, int i) : nome(n), idade(i) {}
};

struct No {
    Pessoa pessoa;
    No* proximo;

    No(Pessoa p) : pessoa(p), proximo(nullptr) {}
};

void enfileirar(No** frente, No** final, Pessoa pessoa) {
    No* novono = new No(pessoa);
    if (*final == nullptr) { 
        *frente = novono;
    } else {
        (*final)->proximo = novono; 
    *final = novono; 
}
}

Pessoa desenfileirar(No** frente, No** final) {
    if (*frente == nullptr) {
        throw std::runtime_error("Erro: a fila está vazia");
    }

    No* auxiliar = *frente;
    Pessoa pessoa = auxiliar->pessoa;
    
    *frente = (*frente)->proximo;
    
    if (*frente == nullptr) {
        *final = nullptr;
    }

    delete auxiliar;
    return pessoa;
}

void imprimirFila(No* frente) {
    No* atual = frente;
    while (atual != nullptr) {
        std::cout << "Nome: " << atual->pessoa.nome << ", Idade: " << atual->pessoa.idade << "\n";
        atual = atual->proximo;
    }
}

int main() {
    No* frente = nullptr;
    No* final = nullptr;

    Pessoa p1("Alice", 30);
    Pessoa p2("Bob", 25);

    enfileirar(&frente, &final, p1);
    enfileirar(&frente, &final, p2);

    std::cout << "Fila de Pessoas:\n";
    imprimirFila(frente);

    std::cout << "\nDesenfileirando: " << desenfileirar(&frente, &final).nome << "\n";
    imprimirFila(frente);


    return 0;
}
