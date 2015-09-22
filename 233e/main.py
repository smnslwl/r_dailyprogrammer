import sys
from random import choice

if __name__ == '__main__':
    
    # Read data
    if len(sys.argv) < 2:
        print('No input file specified')
        sys.exit()
    try:
        with open(sys.argv[1]) as f:
            all_lines = f.read().splitlines()
    except IOError:
        print('Could not open {}'.format(sys.argv[1]))
        sys.exit()

    # lines with the actual blueprint
    lines = all_lines[1:]
    
    # height and width of the blueprint
    h, w = int(all_lines[0]), len(lines[-1])

    # height and width of a grid (room) for an asterisk
    hg, wg = 3, 5
    
    # dimensions for the outline (rooms share a common border)
    x, y = (wg - 1) * w + 1, (hg - 1) * h + 1
    
    # list representing the house
    house = [' '] * x * y    
    
    # lists of the centre point of rooms
    rooms = []
    has_room_up = []
    has_room_left = []
    ground_floor = []
    
    # loop through each asterisk in blueprint
    for i in range(h):
        for j in range(len(lines[i])):
            if lines[i][j] == '*':

                # find central point in the outline for each room
                p = (i * 2 + 1) * x + (j * 4 + 2);

                # save all rooms
                rooms.append(p)

                # save ground floor rooms
                if i == (h - 1):
                    ground_floor.append(p)
                
                # filter rooms needing removal of inside edges
                room_up =   [house[pt] == '-' 
                            for pt in range(p, -1, -x*hg)]
                room_left = [house[p - 2] == '|' 
                            and not house[pt - x - 2] == '|' 
                            for pt in range(p, p - x, -wg)]
                if any(room_up): has_room_up.append(p)
                if any(room_left): has_room_left.append(p)
                
                # draw houses
                house[p - 2] = '|'
                house[p + 2] = '|'
                house[p - x] = '-'
                house[p - x + 1] = '-'
                house[p - x - 1] = '-'                
                house[p - x - 2] = '+'
                house[p - x + 2] = '+'
    
    # remove inside edges
    for p in has_room_up:
        house[p - x] = ' '
        house[p - x + 1] = ' '
        house[p - x - 1] = ' '
    for p in has_room_left:
        house[p - 2] = ' '        
    
    # smooth out the lines (convert + to | or - as appropriate)
    for i in range(x * y):
        if house[i] == '+':
            if house[i - x] == '|' and house[i + x] == '|':
                house[i] = '|'
                continue

            # ignore left/right edges now
            if i % x == 0 or i % x == x - 1: continue
            
            if house[i - 1] == '-' and house[i + 1] == '-':
                house[i] = '-'
            if house[i - 1] == ' ' and house[i + 1] == ' ':
                house[i] = ' '
                
    # add the bottom row
    for p in ground_floor:
        house[p + x] = '-'
        house[p + x - 1] = '-'
        house[p + x + 1] = '-'
        house[p + x + 2] = '-'
    house[ground_floor[0] + x - 2] = '+'
    house[ground_floor[0] + x + x -3] = '+'
        
    # add a door (at the ground floor, obviously)
    door_room = choice(ground_floor)
    house[door_room - 1] = '|'
    house[door_room] = '|'
    rooms.remove(door_room)
    
    # add windows
    for p in rooms:
        if choice([True, False]):
            house[p] = 'o'
    
    # find possible points from which roofs are to be raised
    roof_possibles = []
    for i in range(y):
        for j in range(x):
            p = i * x + j
            if house[p] == '+':
                roof_possibles.append((p // x, p % x))

    # need to allocate space (rh rows) to display the roofs
    # around "half the baseline length" number of rows
    # this will expand the list at the beginning
    rh = x / 2 + 1
    house = [' '] * rh * x + house
    
    # set of locations of roof points across the x-axis
    # out of all possible points in a position,
    # the roof can only be raised from the topmost point 
    roof_xpos = {x for _, x in roof_possibles}
    roof_pts = []
    for ypos, xpos in sorted(roof_possibles):
        roof_pts.append((ypos + rh, xpos))
        roof_xpos.discard(xpos)
        if not len(roof_xpos): break
        
    # raise the roof
    for i in range(0, len(roof_pts), 2):
        left = roof_pts[i][0] * x + roof_pts[i][1]
        right = roof_pts[i+1][0] * x + roof_pts[i+1][1]
        while not left == right:
            left -= x - 1
            right -= x + 1
            house[left] = '/'
            house[right] = '\\'
        house[left] = 'A'

    # display the house
    for i in range(0, x * (y+rh), x):
        print(''.join(house[i: i + x]))
