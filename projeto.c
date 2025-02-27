#include <stdio.h>
#include <math.h>

// Função que representa a equação diferencial dT/dt = -k(T - T_infinito)
double derivada(double T, double T_infinito, double k) {
    return -k * (T - T_infinito);
}

// Solução analítica
double solucao_analitica(double t, double T0, double T_infinito, double k) {
    return T_infinito + (T0 - T_infinito) * exp(-k * t);
}

int main() {
    double T0 = 100.0; // Temperatura inicial
    double T_infinito = 25.0; // Temperatura ambiente
    double k = 0.07; // Constante de resfriamento
    double dt = 5.0; // Passo de tempo
    double tempo_final = 50.0; // Tempo final
    int num_passos = (int)(tempo_final / dt) + 1;
	int i;
    // Alocação de memória para os resultados
    double tempo[num_passos];
    double temperatura_euler[num_passos];
    double temperatura_euler_melhorado[num_passos];
    double temperatura_analitica[num_passos];

    // Condições iniciais
    tempo[0] = 0.0;
    temperatura_euler[0] = T0;
    temperatura_euler_melhorado[0] = T0;
    temperatura_analitica[0] = solucao_analitica(0, T0, T_infinito, k);

    // Métodos numéricos
    for ( i = 1; i < num_passos; i++) {
        tempo[i] = i * dt;

        // Método de Euler
        temperatura_euler[i] = temperatura_euler[i - 1] + dt * derivada(temperatura_euler[i - 1], T_infinito, k);

        // Método de Euler Melhorado
        double k1 = derivada(temperatura_euler_melhorado[i - 1], T_infinito, k);
        double k2 = derivada(temperatura_euler_melhorado[i - 1] + dt * k1, T_infinito, k);
        temperatura_euler_melhorado[i] = temperatura_euler_melhorado[i - 1] + dt * (k1 + k2) / 2.0;

        // Solução analítica
        temperatura_analitica[i] = solucao_analitica(tempo[i], T0, T_infinito, k);
    }

    // Tabela de resultados
    printf("Tempo (min)\tEuler\tEuler Melhorado\tAnalitico\n");
    for (i = 0; i < num_passos; i++) {
        printf("%.2f\t%.4f\t%.4f\t%.4f\n", tempo[i], temperatura_euler[i], temperatura_euler_melhorado[i], temperatura_analitica[i]);
    }

    // Geração do gráfico (usando gnuplot)
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "set title 'Resfriamento do Corpo'\n");
    fprintf(gnuplotPipe, "set xlabel 'Tempo (min)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Temperatura (°C)'\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Euler', '-' with lines title 'Euler Melhorado', '-' with lines title 'Analítico'\n");

    for (i = 0; i < num_passos; i++) {
        fprintf(gnuplotPipe, "%lf %lf\n", tempo[i], temperatura_euler[i]);
    }
    fprintf(gnuplotPipe, "e\n");

    for (i = 0; i < num_passos; i++) {
        fprintf(gnuplotPipe, "%lf %lf\n", tempo[i], temperatura_euler_melhorado[i]);
    }
    fprintf(gnuplotPipe, "e\n");

    for (i = 0; i < num_passos; i++) {
        fprintf(gnuplotPipe, "%lf %lf\n", tempo[i], temperatura_analitica[i]);
    }
    fprintf(gnuplotPipe, "e\n");

    fclose(gnuplotPipe);

    return 0;
}
