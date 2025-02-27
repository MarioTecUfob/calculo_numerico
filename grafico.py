"""
PROBLEMA PROPOSTO:
Um objeto aquecido a T0 = 100 °C é colocado em um ambiente com temperatura
constante de T_inf = 25 °C. A constante de resfriamento é k = 0.07.

Use os seguintes métodos numéricos para resolver a equação diferencial e estimar a
temperatura do corpo ao longo do tempo para t ∈ [0,50] minutos:
• Método de Euler;
• Método de Euler Melhorado.

Resolva a equação com um passo de tempo Δt = 5 minutos e compare os resultados com
a solução analítica:

T(t) = T_inf + (T0 - T_inf) * exp(-k * t)

O que entregar:
• Código implementando os três métodos numéricos para resolver a EDO.
• Tabela comparando os valores obtidos pelos diferentes métodos com a solução
  analítica.
• Gráfico mostrando a evolução da temperatura T(t) ao longo do tempo para os
diferentes métodos.
• Discussão sobre os resultados:
  o Qual método foi mais preciso?
  o Como a escolha do passo Δt afeta a precisão?
  o Qual a relação entre o erro e o método utilizado?
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Parâmetros do problema
T0 = 100  # Temperatura inicial do objeto
T_inf = 25  # Temperatura ambiente
k = 0.07  # Constante de resfriamento
dt = 5  # Passo de tempo
t_max = 50  # Tempo máximo
n_steps = int(t_max / dt) + 1  # Número de passos

# Solução analítica
t_values = np.arange(0, t_max + dt, dt)
T_analytical = T_inf + (T0 - T_inf) * np.exp(-k * t_values)

# Método de Euler
T_euler = np.zeros(n_steps)
T_euler[0] = T0

for i in range(1, n_steps):
    T_euler[i] = T_euler[i-1] - k * (T_euler[i-1] - T_inf) * dt

# Método de Euler Melhorado (Heun)
T_euler_improved = np.zeros(n_steps)
T_euler_improved[0] = T0

for i in range(1, n_steps):
    T_predict = T_euler_improved[i-1] - k * (T_euler_improved[i-1] - T_inf) * dt
    T_euler_improved[i] = T_euler_improved[i-1] - (k * (T_euler_improved[i-1] - T_inf) + k * (T_predict - T_inf)) * dt / 2

# Criando tabela comparativa
df = pd.DataFrame({
    "Tempo (min)": t_values,
    "Solução Analítica (°C)": T_analytical,
    "Euler (°C)": T_euler,
    "Euler Melhorado (°C)": T_euler_improved
})

print(df)

# Plotando os resultados
plt.figure(figsize=(8, 5))
plt.plot(t_values, T_analytical, label="Solução Analítica", linestyle="dashed", color="black")
plt.plot(t_values, T_euler, label="Método de Euler", marker="o", linestyle="-", color="blue")
plt.plot(t_values, T_euler_improved, label="Método de Euler Melhorado", marker="s", linestyle="-", color="red")

plt.xlabel("Tempo (min)")
plt.ylabel("Temperatura (°C)")
plt.title("Comparação dos Métodos Numéricos")
plt.legend()
plt.grid(True)
plt.show()
