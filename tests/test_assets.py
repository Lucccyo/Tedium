import pygame, math

pygame.init()
MAX_CELL_X = 10
MAX_CELL_Y = 10

block_size = 32
WINDOW_HEIGHT = MAX_CELL_Y*block_size
WINDOW_WIDTH  = MAX_CELL_X*block_size
inner_block = block_size - 2

screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
clock = pygame.time.Clock()

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.dist = math.inf
        self.parent = self
        self.type = "cell"
        self.is_visited = False
    def __str__(self):
      return f'Cell({self.x}, {self.y}, {self.dist}, {self.type}, {self.is_visited})'

cell_grid = []

def init_grid():
  global cell_grid
  for x in range (0, WINDOW_WIDTH, block_size):
    tmp = []
    for y in range (0, WINDOW_HEIGHT, block_size):
      r = pygame.Rect(x, y, block_size, block_size)
      pygame.draw.rect(screen, "gray", r, 1)
      tmp.append(Cell((int)(x/block_size), (int)(y/block_size)))
    cell_grid.append(tmp)


tab = [
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
[  "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png", "a.png"  ],
]

def display_img_array():
  x = 0
  y = 0
  for y in range (0, MAX_CELL_Y):
    for x in range (0, MAX_CELL_X):
      img = pygame.image.load("img/" + (tab[y][x])).convert()
      screen.blit(img, (32 * x, 32 * y))

init_grid()
display_img_array()

while True:
  for event in pygame.event.get():
    if event.type == pygame.MOUSEBUTTONUP:
      pos_x, pos_y = pygame.mouse.get_pos()
      x, _ = divmod(pos_x, block_size)
      y, _ = divmod(pos_y, block_size)
    if event.type == pygame.QUIT:
      pygame.quit()
      sys.exit()
  clock.tick(400)
  pygame.display.update()
pygame.quit()
