#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm> // Necessário para next_permutation

using namespace std;

#define INF 1e9

// --- Estruturas Básicas ---
struct Aresta {
    int destino;
    double custo;      // R$
    double distancia;  // km
    double tempo;      // horas
};

struct No {
    int id;
    double valor;
    bool operator>(const No& outro) const {
        return valor > outro.valor;
    }
};

// --- Classe Principal ---
class EuroTripGrafo {
private:
    int numVertices;
    vector<string> nomesCidades;
    vector<vector<Aresta>> adj;
    
    // Matrizes para acesso rápido
    vector<vector<double>> matrizCusto;
    vector<vector<double>> matrizDist;
    vector<vector<double>> matrizTempo;

public:
    EuroTripGrafo(int v, vector<string> nomes) : numVertices(v), nomesCidades(nomes) {
        adj.resize(v);
        matrizCusto.assign(v, vector<double>(v, INF));
        matrizDist.assign(v, vector<double>(v, INF));
        matrizTempo.assign(v, vector<double>(v, INF));
    }

    void adicionarAresta(int u, int v, double dist, double tempo, double custo) {
        adj[u].push_back({v, custo, dist, tempo});
        adj[v].push_back({u, custo, dist, tempo});
    }

    // --- 1. PREPARAÇÃO DOS DADOS (Floyd-Warshall) ---
    void preencherMatrizesCompletas() {
        // Inicializa com dados diretos
        for(int i=0; i<numVertices; i++) {
            matrizCusto[i][i] = 0; matrizDist[i][i] = 0; matrizTempo[i][i] = 0;
            for(auto& a : adj[i]) {
                matrizCusto[i][a.destino] = a.custo;
                matrizDist[i][a.destino] = a.distancia;
                matrizTempo[i][a.destino] = a.tempo;
            }
        }

        // Calcula conexões indiretas
        for(int k=0; k<numVertices; k++) {
            for(int i=0; i<numVertices; i++) {
                for(int j=0; j<numVertices; j++) {
                    if(matrizCusto[i][k]!=INF && matrizCusto[k][j]!=INF)
                        matrizCusto[i][j] = min(matrizCusto[i][j], matrizCusto[i][k] + matrizCusto[k][j]);
                    
                    if(matrizDist[i][k]!=INF && matrizDist[k][j]!=INF)
                        matrizDist[i][j] = min(matrizDist[i][j], matrizDist[i][k] + matrizDist[k][j]);

                    if(matrizTempo[i][k]!=INF && matrizTempo[k][j]!=INF)
                        matrizTempo[i][j] = min(matrizTempo[i][j], matrizTempo[i][k] + matrizTempo[k][j]);
                }
            }
        }
    }

    // --- 2. CAIXEIRO VIAJANTE (TSP) ---
    void resolverTSP(int origem) {
        cout << "\n==============================================" << endl;
        cout << "      OTIMIZACAO DE ROTEIRO (TSP)             " << endl;
        cout << "==============================================" << endl;
        cout << "[STATUS] Gerando 720 combinacoes de rotas..." << endl;
        cout << "[STATUS] Calculando o menor custo total..." << endl;

        vector<int> cidades;
        for(int i=0; i<numVertices; i++) {
            if(i != origem) cidades.push_back(i);
        }

        double menorCusto = INF;
        vector<int> melhorRota;
        
        do {
            double custoAtual = 0;
            int atual = origem;
            
            for(int prox : cidades) {
                custoAtual += matrizCusto[atual][prox];
                atual = prox;
            }
            custoAtual += matrizCusto[atual][origem];

            if(custoAtual < menorCusto) {
                menorCusto = custoAtual;
                melhorRota = cidades;
            }

        } while(next_permutation(cidades.begin(), cidades.end()));

        // --- EXIBIÇÃO BONITA DO ROTEIRO ---
        cout << "\n[SUCESSO] Melhor itinerario encontrado!\n" << endl;
        
        double tempoTotal = 0;
        double distTotal = 0;
        int atual = origem;
        int passo = 1;

        cout << "   " << passo++ << ". " << nomesCidades[origem] << " (Partida)" << endl;

        for(int prox : melhorRota) {
            cout << "      | " << endl;
            cout << "      v " << endl;
            cout << "   " << passo++ << ". " << nomesCidades[prox] << endl;
            
            tempoTotal += matrizTempo[atual][prox];
            distTotal += matrizDist[atual][prox];
            atual = prox;
        }
        // Volta
        cout << "      | " << endl;
        cout << "      v " << endl;
        cout << "   " << passo << ". " << nomesCidades[origem] << " (Chegada)" << endl;
        
        tempoTotal += matrizTempo[atual][origem];
        distTotal += matrizDist[atual][origem];

        cout << "\n   ---------------------------------" << endl;
        cout << "   RESUMO DA VIAGEM:" << endl;
        cout << "   $$ Custo:     R$ " << fixed << setprecision(2) << menorCusto << endl;
        cout << "   >> Distancia: " << (int)distTotal << " km" << endl;
        cout << "   O  Tempo:     " << (int)tempoTotal << " horas de voo" << endl;
        cout << "   ---------------------------------" << endl;
    }

    // --- 3. AGM (PRIM) ---
    void primAGM() {
        vector<double> chave(numVertices, INF);
        vector<bool> noMST(numVertices, false);
        vector<int> parente(numVertices, -1);
        priority_queue<No, vector<No>, greater<No>> pq;
        
        chave[0] = 0; 
        pq.push({0,0});
        double total = 0;
        
        cout << "\n==============================================" << endl;
        cout << "      INFRAESTRUTURA MINIMA (AGM)             " << endl;
        cout << "==============================================" << endl;
        cout << "Conectando cidades pelo menor custo..." << endl;
        cout << "Arestas selecionadas:" << endl;

        while(!pq.empty()){
            int u = pq.top().id; pq.pop();
            
            if(noMST[u]) continue;
            noMST[u] = true;
            total += chave[u];
            
            if(parente[u] != -1) {
                cout << "   * " << left << setw(10) << nomesCidades[parente[u]] 
                     << " --- " << nomesCidades[u] << endl;
            }
            
            for(auto& a : adj[u]){
                if(!noMST[a.destino] && a.custo < chave[a.destino]){
                    chave[a.destino] = a.custo;
                    pq.push({a.destino, a.custo});
                    parente[a.destino] = u;
                }
            }
        }
        cout << "\n   $$ Custo Total da Infraestrutura: R$ " << fixed << setprecision(2) << total << endl;
        cout << "==============================================" << endl;
    }

    void imprimirMatrizes() {
        auto print = [&](string tit, vector<vector<double>>& m, string unidade){
            cout << "\n+--------------------------------------------+" << endl;
            cout << "| " << left << setw(42) << tit << " |" << endl;
            cout << "+--------------------------------------------+" << endl;
            
            // Cabeçalho
            cout << "      "; 
            for(auto n : nomesCidades) cout << "  " << n.substr(0,3) << " "; 
            cout << endl;

            // Linhas
            for(int i=0; i<numVertices; i++){
                cout << " " << nomesCidades[i].substr(0,3) << " | ";
                for(int j=0; j<numVertices; j++) {
                    cout << setw(5) << (int)m[i][j] << " ";
                }
                cout << endl;
            }
            cout << "Unidade: " << unidade << endl;
        };
        
        print("TABELA DE CUSTOS (Conexidade)", matrizCusto, "Reais (R$)");
        print("TABELA DE DISTANCIAS", matrizDist, "Quilometros (km)");
        print("TABELA DE TEMPO", matrizTempo, "Horas (h)");
    }
};

int main() {
    // Configuração para acentos (se o console suportar)
    setlocale(LC_ALL, "Portuguese"); 

    vector<string> cidades = {"Curitiba", "Londres", "Paris", "Sevilha", "Berlim", "Florenca", "Atenas"};
    EuroTripGrafo g(7, cidades);

    // --- CARREGANDO DADOS ---
    g.adicionarAresta(0, 1, 9803.0, 24.0, 5780.0);
    g.adicionarAresta(1, 2, 459.9, 1.0, 1187.0);
    g.adicionarAresta(2, 3, 1739.8, 7.0, 1437.0);
    g.adicionarAresta(3, 4, 2780.1, 9.0, 1632.0);
    g.adicionarAresta(5, 6, 1480.6, 4.0, 1060.0);
    g.adicionarAresta(6, 0, 10379.0, 32.0, 9047.0);

    // Extras (Grau >= 3)
    g.adicionarAresta(4, 5, 1233.6, 3.0, 900.0);
    g.adicionarAresta(0, 2, 9747.0, 23.0, 5600.0);
    g.adicionarAresta(3, 1, 2198.6, 5.0, 1500.0);
    g.adicionarAresta(4, 6, 2334.7, 6.0, 1700.0);
    g.adicionarAresta(5, 2, 1181.5, 2.5, 850.0);

    // --- EXECUÇÃO ---
    cout << "**********************************************" << endl;
    cout << "* EUROTRIP PLANNER 2025             *" << endl;
    cout << "* Museus: Louvre, Acropole e muito mais   *" << endl;
    cout << "**********************************************" << endl;
    cout << "Desenvolvido por: Mariana Alves e Giovanna de Melo" << endl; // <--- COMPLETE AQUI
    cout << "----------------------------------------------" << endl;

    g.preencherMatrizesCompletas();
    g.imprimirMatrizes();
    g.resolverTSP(0);
    g.primAGM();
    
    cout << "\nFim do processamento. Boa viagem! :)" << endl;

    return 0;
}