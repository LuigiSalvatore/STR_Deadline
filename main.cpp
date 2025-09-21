#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Tarefa {
    int J, C, P, D; // jitter, computação, período, deadline
};

int calcularTempoResposta(const vector<Tarefa>& tarefas, int indice) {
    const Tarefa& ti = tarefas[indice];
    int q = 0;
    int Ri = 0;
    while (true) {
        int Wiq_anterior = -1;
        int Wiq = 0;
        while (Wiq != Wiq_anterior) {
            Wiq_anterior = Wiq;
            Wiq = (q + 1) * ti.C;
            for (int j = 0; j < indice; ++j) {
                const Tarefa& tj = tarefas[j];
                Wiq += ceil((double)(Wiq_anterior + tj.J) / tj.P) * tj.C;
            }
        }
        int Riq = ti.J + Wiq - q * ti.P;
        if (Wiq <= (q + 1) * ti.P) {
            Ri = max(Ri, Riq);
            break;
        }
        Ri = max(Ri, Riq);
        ++q;
        if (q > 1000) break;
    }
    return Ri;
}

int main() {
    int TP;
    while (cin >> TP && TP != 0) {
        vector<Tarefa> tarefas(TP);
        for (int i = 0; i < TP; ++i) {
            cin >> tarefas[i].J >> tarefas[i].C >> tarefas[i].P >> tarefas[i].D;
        }
        for (int i = 0; i < TP; ++i) {
            if (tarefas[i].D > tarefas[i].P) continue;
            int Ri = calcularTempoResposta(tarefas, i);
            cout << i + 1 << " " << Ri << " " << (Ri <= tarefas[i].D ? "YES" : "NO") << endl;
        }
        cout << endl;
    }
    return 0;
}
