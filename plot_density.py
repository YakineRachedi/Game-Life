import matplotlib.pyplot as plt

def read_data(filename):
    x = []
    y = []
    with open(filename, 'r') as file:
        lines = file.readlines()
        for line in lines:
            cols = line.split()
            x.append(float(cols[0]))
            y.append(float(cols[1]))
    return x, y

# Read data from the file
x, y = read_data("data.txt")

# Plotting the data
plt.plot(x, y, marker='o', linestyle='-', color='red', markersize=8, linewidth=2)
plt.bar(x, y, width=(x[1] - x[0]), align='center', edgecolor='black', color='blue')
plt.xlabel('Probability p')
plt.ylabel('Average Number of Cells')
plt.title('Average Number of Cells vs. Probability')
plt.grid(True)
plt.savefig('Density_plot.png')
plt.show()
