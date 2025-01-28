import sys
import pygame

# Define constants
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
ROOM_RADIUS = 20
ANT_RADIUS = 5
FPS = 60

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)

# Room class
class Room:
    def __init__(self, name, x, y, is_start=False, is_end=False):
        self.name = name
        self.x = x
        self.y = y
        self.is_start = is_start
        self.is_end = is_end
        self.connected_rooms = []

    def connect(self, other_room):
        self.connected_rooms.append(other_room)

# Ant class
class Ant:
    def __init__(self, id, current_room):
        self.id = id
        self.current_room = current_room
        self.target_room = None
        self.progress = 0.0

    def move_to(self, target_room):
        self.target_room = target_room
        self.progress = 0.0

    def update_position(self, speed=0.01):
        if self.target_room:
            self.progress += speed
            if self.progress >= 1.0:
                self.current_room = self.target_room
                self.target_room = None
                self.progress = 0.0

    def get_position(self):
        if self.target_room:
            x = (1 - self.progress) * self.current_room.x + self.progress * self.target_room.x
            y = (1 - self.progress) * self.current_room.y + self.progress * self.target_room.y
            return int(x), int(y)
        return self.current_room.x, self.current_room.y

# Parse input
def parse_input():
    rooms = {}
    connections = []
    movements = []
    num_ants = 0
    current_section = "header"

    for line in sys.stdin:
        line = line.strip()
        if not line or line.startswith("#") and not line.startswith("##"):
            continue

        if line == "##start":
            current_section = "start"
            continue
        elif line == "##end":
            current_section = "end"
            continue

        if current_section == "header":
            try:
                num_ants = int(line)
                current_section = "rooms"
            except ValueError:
                raise ValueError("Invalid number of ants")
        elif current_section == "rooms":
            if "-" in line:
                current_section = "connections"

            if current_section == "rooms":
                parts = line.split()
                if len(parts) == 3:
                    name, x, y = parts
                    x, y = int(x), int(y)
                    is_start = current_section == "start"
                    is_end = current_section == "end"
                    rooms[name] = Room(name, x, y, is_start, is_end)
        elif current_section == "connections":
            if "-" in line:
                room1, room2 = line.split("-")
                connections.append((room1, room2))
                if room1 in rooms and room2 in rooms:
                    rooms[room1].connect(rooms[room2])
                    rooms[room2].connect(rooms[room1])
            else:
                current_section = "movements"

        if current_section == "movements":
            step_movements = []
            for move in line.split():
                ant_id, target_room = move.split("-")
                ant_id = int(ant_id[1:])  # Remove "L" prefix
                step_movements.append((ant_id, target_room))
            movements.append(step_movements)

    return num_ants, rooms, connections, movements

# Visualization
def visualize(rooms, connections, ants, movements):
    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Ant Farm Visualizer")
    clock = pygame.time.Clock()

    movement_index = 0
    running = True
    while running:
        screen.fill(BLACK)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Draw connections
        for room1, room2 in connections:
            pygame.draw.line(screen, WHITE, (rooms[room1].x, rooms[room1].y), (rooms[room2].x, rooms[room2].y), 2)

        # Draw rooms
        for room in rooms.values():
            color = GREEN if room.is_start else RED if room.is_end else BLUE
            pygame.draw.circle(screen, color, (room.x, room.y), ROOM_RADIUS)
            font = pygame.font.SysFont(None, 24)
            text = font.render(room.name, True, WHITE)
            screen.blit(text, (room.x - ROOM_RADIUS, room.y - ROOM_RADIUS - 10))

        # Update ant positions
        for ant in ants:
            ant.update_position()
            ant_x, ant_y = ant.get_position()
            pygame.draw.circle(screen, YELLOW, (ant_x, ant_y), ANT_RADIUS)

        # Process movements
        if movement_index < len(movements):
            current_movements = movements[movement_index]
            for ant_id, target_room_name in current_movements:
                target_room = rooms[target_room_name]
                ants[ant_id - 1].move_to(target_room)
            movement_index += 1

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

# Main function
def main():
    try:
        num_ants, rooms, connections, movements = parse_input()
        print(num_ants)
        print(rooms)
        print(connections)
        print(movements)
        start_room = next(room for room in rooms.values() if room.is_start)
        # ants = [Ant(i + 1, start_room) for i in range(num_ants)]
        # visualize(rooms, connections, ants, movements)
    except Exception as e:
        print(f"Error: {str(e)}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
