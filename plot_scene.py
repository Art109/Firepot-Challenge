"""
plot_scene.py
-------------
Script auxiliar para visualizar a cena descrita em 'scene_debug.txt'.

Ele exibe:
 - Obstáculos (retângulos, círculos e linhas)
 - Fontes de luz (em amarelo)
 - Receptores (em magenta)
 - Linhas tracejadas representando a conexão entre fontes e receptores

Este arquivo é opcional e serve apenas para depuração e conferência visual.
"""

import matplotlib.pyplot as plt

fig, ax = plt.subplots()
lights = []
receptors = []

# --- Leitura e interpretação do arquivo exportado ---
with open("scene_debug.txt") as f:
    for line in f:
        line = line.strip()
        if not line or line.startswith("#"):
            continue

        parts = line.split()
        t = parts[0]

        # Ignora seções descritivas
        if t in ["OBSTACULOS", "LIGHTS", "POINTS"]:
            continue

        # Desenha cada tipo de elemento conforme o tipo
        if t == "R":  # Retângulo
            x, y, w, h = map(float, parts[1:])
            ax.add_patch(plt.Rectangle((x, y), w, h, fill=False, color='red', lw=1.5))

        elif t == "C":  # Círculo
            x, y, r = map(float, parts[1:])
            ax.add_patch(plt.Circle((x, y), r, fill=False, color='blue', lw=1.5))

        elif t == "L":  # Linha
            x1, y1, x2, y2 = map(float, parts[1:])
            ax.plot([x1, x2], [y1, y2], 'g-', lw=1.5)

        elif t == "P":  # Receptor
            x, y = map(float, parts[1:])
            receptors.append((x, y))
            ax.plot(x, y, 'mo', markersize=10, label='Receptor' if 'Receptor' not in ax.get_legend_handles_labels()[1] else "")

        elif t == "F":  # Fonte
            x, y, intensity = map(float, parts[1:4])
            lights.append((x, y))
            ax.plot(x, y, 'yo', markersize=6, label='Fonte' if 'Fonte' not in ax.get_legend_handles_labels()[1] else "")

# --- Ligações visuais entre fontes e receptores ---
for lx, ly in lights:
    for rx, ry in receptors:
        ax.plot([lx, rx], [ly, ry], 'y--', lw=1)

# --- Configuração final do gráfico ---
ax.set_aspect('equal')
#ax.invert_yaxis()
ax.legend()
ax.set_title("Visualização da Cena (Fontes, Obstáculos e Receptores)")
plt.show()
