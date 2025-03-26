#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

void toUpperCase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void limparEntrada(string &s) {
    s.erase(remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); }), s.end());
}

vector<string> carregarPalavras(const string &nomeArquivo, string &palavraChave) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!\n";
        exit(1);
    }

    int n;
    arquivo >> n;
    vector<string> palavras(n);
    
    for (int i = 0; i < n; i++) {
        arquivo >> palavras[i];
        toUpperCase(palavras[i]); 
    }

    srand(time(0));
    palavraChave = palavras[rand() % n];

    return palavras;
}

string analisarTentativa(const string &tentativa, const string &palavraChave) {
    string resultado = tentativa;
    string letrasNaoPresentes = "";

    for (int i = 0; i < 5; i++) {
        if (tentativa[i] == palavraChave[i]) {
            resultado[i] = toupper(tentativa[i]); 
        } else if (palavraChave.find(tentativa[i]) != string::npos) {
            resultado[i] = tolower(tentativa[i]); 
        } else {
            resultado[i] = '*'; 
            letrasNaoPresentes += tentativa[i]; 
        }
    }

    if (!letrasNaoPresentes.empty()) {
        resultado += " (" + letrasNaoPresentes + ")";
    }

    return resultado;
}

int main() {
    string palavraChave;
    vector<string> palavras = carregarPalavras("palavras.txt", palavraChave);

    cout << "Bem-vindo ao Cwordle!\n";

    int tentativas = 5;
    while (tentativas--) {
        string tentativa;
        cout << "Digite uma palavra de 5 letras: ";
        
        getline(cin, tentativa);  

        
        limparEntrada(tentativa);

        
        if (tentativa.empty()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Entrada inválida! Digite uma palavra de 5 letras.\n";
            tentativas++; // Não conta como erro
            continue;
        }

        toUpperCase(tentativa); 

        if (tentativa.length() != 5) {
            cout << "A palavra deve ter exatamente 5 letras!\n";
            tentativas++;
            continue;
        }

        if (find(palavras.begin(), palavras.end(), tentativa) == palavras.end()) {
            cout << "Palavra inválida! Tente novamente.\n";
            tentativas++; 
            continue;
        }

        string resultado = analisarTentativa(tentativa, palavraChave);
        cout << resultado << endl;

        if (tentativa == palavraChave) {
            cout << "GANHOU!" << endl;
            return 0;
        }
    }
    cout << "PERDEU! A palavra era: " << palavraChave << endl;
    return 0;
}
