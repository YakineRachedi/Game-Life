import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Function to parse the data from the file
def parse_data(filename):
    all_realizations = []  # List to store all realizations
    current_realization = []  # List to store the current realization being read
    is_reading = False  # Flag to check if we're reading a realization block
    
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()  # Remove leading and trailing whitespace
            if line.startswith("Realization start"):  # Start reading a new realization
                is_reading = True
                continue  # Skip to the next line
            elif line.endswith("End realization"):  # End of the current realization
                is_reading = False
                all_realizations.append(current_realization)  # Store the current realization
                current_realization = []  # Reset for the next realization
            elif is_reading:  # Process lines within a realization block
                parts = line.split()  # Split the line into components (x, y, color)
                if len(parts) == 3:  # Ensure the line has the correct format
                    x = int(parts[0])  # Convert x-coordinate to an integer
                    y = int(parts[1])  # Convert y-coordinate to an integer
                    color = parts[2]  # Get the color value (gray or white)
                    current_realization.append((x, y, color))  # Store the parsed data
    return all_realizations  # Return all parsed realizations

# Function to draw all realizations in a grid layout
def draw_all_realizations(all_realizations):
    num_realizations = len(all_realizations)  # Number of realizations detected
    cols = 5  # Number of columns for the grid layout
    rows = (num_realizations + cols - 1) // cols  # Calculate the number of rows needed

    fig, axes = plt.subplots(rows, cols, figsize=(20, 10))  # Create a grid of subplots
    axes = axes.flatten()  # Flatten the axes array for easy indexing

    for i, realization in enumerate(all_realizations):  # Loop through each realization
        ax = axes[i]  # Get the corresponding subplot
        max_x = max([x for x, y, _ in realization], default=0)  # Find the maximum x-coordinate
        max_y = max([y for x, y, _ in realization], default=0)  # Find the maximum y-coordinate

        # Draw the grid for the realization
        for m in range(max_x + 2):  # Loop through x-coordinates
            for n in range(max_y + 2):  # Loop through y-coordinates
                ax.add_patch(patches.Rectangle((m, n), 1, 1, fill=False, edgecolor="black", linewidth=1))  # Draw grid lines

        # Draw the cells based on their color
        for x, y, color in realization:
            if color == "gray":  # If the cell is gray, draw a filled circle
                ax.add_patch(patches.Circle((x + 0.5, y + 0.5), 0.3, facecolor="black", edgecolor="black"))
            elif color == "white":  # If the cell is white, draw an empty rectangle
                ax.add_patch(patches.Rectangle((x, y), 1, 1, fill=False, edgecolor="black", linewidth=1))

        # Set axis limits and appearance
        ax.set_xlim(0, max_x + 1)  # Set x-axis limits
        ax.set_ylim(0, max_y + 1)  # Set y-axis limits
        ax.set_aspect('equal')  # Ensure equal scaling for x and y
        ax.axis('off')  # Hide axis lines and labels
        ax.set_title(f"Realization {i + 1}")  # Set the title for the subplot

    # Hide any unused subplots
    for j in range(num_realizations, len(axes)):
        axes[j].axis('off')

    plt.tight_layout()  # Adjust subplot parameters to give some padding
    plt.savefig("Random_Game.png") # Save plot
    plt.show()  # Display the plot

# Example usage
filename = 'realizations.txt'
all_realizations = parse_data(filename)
print(f"Number of realizations detected: {len(all_realizations)}")
draw_all_realizations(all_realizations)
