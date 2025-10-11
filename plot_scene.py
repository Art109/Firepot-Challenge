import matplotlib.pyplot as plt

fig, ax = plt.subplots()

lights = []
receptors = []

with open("scene_debug.txt") as f:
    for line in f:
        line = line.strip()
        if not line or line.startswith("#"):
            continue

        parts = line.split()
        t = parts[0]

        # Ignora títulos
        if t in ["OBSTACULOS", "LIGHTS", "POINTS"]:
            continue

        if t == "R":
            x, y, w, h = map(float, parts[1:])
            ax.add_patch(plt.Rectangle((x, y), w, h, fill=False, color='red', lw=1.5))
        elif t == "C":
            x, y, r = map(float, parts[1:])
            ax.add_patch(plt.Circle((x, y), r, fill=False, color='blue', lw=1.5))
        elif t == "L":
            x1, y1, x2, y2 = map(float, parts[1:])
            ax.plot([x1, x2], [y1, y2], 'g-', lw=1.5)
        elif t == "P":
            x, y = map(float, parts[1:])
            receptors.append((x, y))
            ax.plot(x, y, 'mo', markersize=10, label='Receptor' if 'Receptor' not in ax.get_legend_handles_labels()[1] else "")
        elif t == "F":
            x, y, intensity = map(float, parts[1:4])
            lights.append((x, y))
            ax.plot(x, y, 'yo', markersize=6, label='Fonte' if 'Fonte' not in ax.get_legend_handles_labels()[1] else "")


# Traça linhas de cada luz para cada receptor
for lx, ly in lights:
    for rx, ry in receptors:
        ax.plot([lx, rx], [ly, ry], 'y--', lw=1)

ax.set_aspect('equal')
ax.invert_yaxis()
ax.legend()
ax.set_title("Visualização da Cena (Fontes, Obstáculos e Receptores)")
plt.show()

