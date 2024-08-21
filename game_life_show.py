import matplotlib.pyplot as plt
import matplotlib.patches as patches

def parse_data(filename):
    step_data = []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) == 5:
                x = int(parts[2])
                y = int(parts[3])
                color = parts[4]
                step_data.append((x, y, color))
    return step_data

def draw_grid(step_data):
    fig, ax = plt.subplots()

    max_x = max([x for x, y, _ in step_data], default=0)
    max_y = max([y for x, y, _ in step_data], default=0)
    for i in range(max_x + 2):
        for j in range(max_y + 2):
            ax.add_patch(patches.Rectangle((i, j), 1, 1, fill=False, edgecolor="black", linewidth=1))

    for x, y, color in step_data:
        ax.add_patch(patches.Circle((x + 0.5, y + 0.5), 0.3, facecolor=color, edgecolor="black"))

    ax.set_xlim(0, max_x + 1)
    ax.set_ylim(0, max_y + 1)
    ax.set_aspect('equal')
    ax.axis('off')
    plt.show()

filename = 'realizations.txt'
step_data = parse_data(filename)
draw_grid(step_data)
