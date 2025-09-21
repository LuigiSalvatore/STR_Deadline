#include <iostream>
#include <sstream>

#define MAX_TASKS 10

using namespace std;

struct Task {
	int j, c, p, d;
	Task(int p_j=0, int p_c=0, int p_p=0, int p_d=0) {
		j = p_j;
		c = p_c;
		p = p_p;
		d = p_d;
	}
	string str() {
		stringstream ss;
		ss << j << " " << c << " " << p << " " << d;
		return ss.str();
	}
};

int main() {
	Task tasks[MAX_TASKS];
	int numTasks;
	
	while (true) {
		// INPUT
		cin >> numTasks;
		if ( numTasks == 0 ) break;
		for (int i=0; i<numTasks; ++i)
			cin >> tasks[i].j >> tasks[i].c >> tasks[i].p >> tasks[i].d;
		
		for (int i=0; i<numTasks; ++i) {
			if ( tasks[i].d > tasks[i].p ) {
				int r = -1;
				bool sched = false;
				
			// PROCESSING
				Task ti = tasks[i];
				int q = 0;
				int Ri = 0;
				while (true) {
					int Wiq_anterior = -1;
					int Wiq = 0;
					while (Wiq != Wiq_anterior) {
						Wiq_anterior = Wiq;
						Wiq = (q + 1) * ti.c;
						for (int j = 0; j < i; ++j) {
							Task tj = tasks[j];
							Wiq += ((Wiq_anterior + tj.j + tj.p - 1) / tj.p) * tj.c; // ceil()
						}
					}
					int Riq = ti.j + Wiq - q * ti.p;
					Ri = (Riq > Ri) ? Riq : Ri;
					if (Wiq <= (q + 1) * ti.p) {
						break;
					}
					++q;
					if (q > 1000) break; // evitar loop infinito
				}
				r = Ri;
				sched = (Ri <= ti.d);
				// OUTPUT				
				cout << (i+1) << " " << r << " " << (sched?"YES":"NO") << endl;
			}
		}
		cout << endl;
	}
	return 0;
}
