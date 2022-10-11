from math import floor, sqrt
import numpy as np

# Setting image dimensions
width = 400
height = 400
image_size = 3*width*height

# Initializing image as a list
image = list()

# Initializing colors
r, g, b, a = 0, 255, 255, 0.7

# Init. triangles and points' coordinates
triangles = [[6, 2, 4], [0, 3, 1], [1, 2, 0], [4, 1, 2], [0, 2, 5], [0, 3, 7]]
point = [[74.5, 175.5], [224.5, 325.5], [374.5, 175.5], [74.5, 325.5], [374.5, 325.5], [150.0, 100.0], [390.0, 390.0], [25.0, 125.0]]

# Function to sort triangle vertices: from top to bottom, left to right
def sorting():
    for i in range(len(triangles)):
        t = triangles[i]
        li = [[point[j][1], point[j][0], j] for j in t]
        li.sort(key=lambda seq: (int(seq[0]), int(seq[1])))
        
        triangles[i] = [i[2] for i in li]

# Function to draw pixels
def set_pixel(x, y):
    transp = 1 - a
    if (x >= 0) and (x < width) and (y >= 0) and (y < height):
        index = 3*(x + width*y)
        image[index  ] = 255*sqrt(a*r + transp*image[index  ])
        image[index+1] = 255*sqrt(a*g + transp*image[index+1])
        image[index+2] = 255*sqrt(a*b + transp*image[index+2])
        
        
# Function to find and return points that lay on a horizontal edge
def horizontal(t):
    a, b, c = t
    if point[a][1]==point[b][1]:
        return [a, b]
    elif point[c][1]==point[b][1]:
        return [b, c]
    elif point[c][1]==point[a][1]:
        return [a, c]
    else:
        return -1

# Function to find and return the point opposite of the horizontal edge
def non_horizontal(t):
    a, b, c = t
    if point[a][1]==point[b][1]:
        return c
    elif point[c][1]==point[b][1]:
        return a 
    else:
        return b 

# Function to divide a triangle into two triangles with a horizontal edge
def divide_horizontal(t, i):
    # Verteces and their coordinates
    a = t[0]
    b = t[1]
    c = t[2]

    ax = point[a][0]
    bx = point[b][0]
    cx = point[c][0]

    ay = point[a][1]
    by = point[b][1]
    cy = point[c][1]

    # Slope and intercept of the edge opposite of the middle vertex (by y)
    if cx==ax:
        x_n = ax
    else:
        m = (cy - ay)/(cx - ax)
        k = cy - m*cx
        # Coordinates of a new point
        x_n = (by - k)/m 

    point.append([x_n, by])
    
    # Updating list of triangles
    if (x_n < bx):
        triangles[i][2] = triangles[i][1]
        triangles[i][1] = len(point) - 1
        triangles.append([len(point) - 1, b, c])
    else:
        triangles[i][2] = len(point) - 1
        triangles.append([b, len(point) - 1, c])


# Function visits all pixel within a triangle or certain bounds
def iterator(start, stop, y, iy, incr, m, step):
    # Moving along x
    for i in range(start, stop):
        y_line = floor(iy)
        # Moving along y
        for j in range(y, y_line+incr, step):
            set_pixel(i, j) 
        iy += m


# Function to color the triangles
def fill_in(t, n):
    horiz = horizontal(t) 
    vertex = non_horizontal(t)
    horiz_y = point[horiz[0]][1] 

    vertex_y = point[vertex][1]
    left_y = point[horiz[0]][1]
    right_y = point[horiz[1]][1]

    vertex_x = point[vertex] [0]
    left_x = point[horiz[0]][0]
    right_x = point[horiz[1]][0]

    x_start = floor(left_x) 
    x_stop = floor(right_x) 
    x_vertex = floor(vertex_x) 

    # Determining orientation of a vertex relative to the horizontal edge
    if (horiz_y < vertex_y):
        y = floor(horiz_y) + 1
        step = 1
    else:
        y = floor(horiz_y)
        step = -1
    

    # For a right triangle with the right angle at the left
    #####     #
    #  #  or  # #
    # #       #  #
    #         #####
    if x_start==x_vertex:
        m_right = (right_y - vertex_y)/(right_x - vertex_x)

        iy = vertex_y
        iterator(x_vertex, x_stop, y, iy, 0, m_right, step)

    # For a right triangle with the right angle at the right
        #     #####
      # #  or  #  #
     #  #       # #
    #####         #
    elif right_x==vertex_x:
        m_left = (left_y - vertex_y)/(left_x - vertex_x)

        iy = left_y
        iterator(x_start, x_vertex, y, iy, 0, m_left, step)

    # For other not right triangles
    else:
        # For a triangle with only acute angles
        if (vertex_x>x_start) and (vertex_x<x_stop):
            m_left = (left_y - vertex_y)/(left_x - vertex_x) 
            m_right = (right_y - vertex_y)/(right_x - vertex_x)

            iy = left_y
            iterator(x_start, x_vertex, y, iy, 1, m_left, step)
            iy = vertex_y
            iterator(x_vertex, x_stop, y, iy, 1, m_right, step)

        # For a triangle with an obtuse angle
        #
         # #
          #   #
           #     #
            # # # # #
        else:
            m = (right_y - vertex_y)/(right_x - vertex_x)
            k = vertex_y - vertex_x*m
            m2 = (left_y - vertex_y)/(left_x - vertex_x) 
            k2 = vertex_y - vertex_x*m2

            # With an obtuse angle to the left
            if vertex_x < x_start:
                iy = (x_start - left_x + 0.5)*m + x_start*m + k
                iterator(x_start, x_stop, y, iy, 0, m, step)

                y1 = x_vertex*m + k
                y2 = x_vertex*m2 + k2
                
                if y1>y2:
                    step = -1
                elif y1==y2:
                    if m>m2:
                        step = -1
                    else:
                        step = 1
                else:
                    step = 1
                
                for i in range(x_vertex, x_start):
                    for j in range(floor(y1), floor(y2), step):
                        set_pixel(i, j)
                    y1 = floor(y1) + m
                    y2 = floor(y2) + m2
                
            
            # With an obtuse angle to the right
            else:
                iy = (x_start - left_x + 0.5)*m2 + x_start*m2 + k2
                iterator(x_start, x_stop, y, iy, 0, m2, step)
                
                y1 = x_stop*m + k
                y2 = x_stop*m2 + k2

                if y1+m>y2+m2:
                    step = -1
                elif y1==y2:
                    if m>m2:
                        step = -1
                    else:
                        step = 1
                else:
                    step = 1

                for i in range(x_stop, x_vertex):                    
                    for j in range(floor(y1), floor(y2), step):
                        set_pixel(i, j)
                    y1 += m
                    y2 += m2       



# Set image to black background
image = list(np.zeros(image_size))

# Sort triangle vertices
sorting()

# Divide triangles without a horizontal edge
for i in range(len(triangles)):
    t = triangles[i] 
    if (horizontal(t) == -1):
        divide_horizontal(t, i)

# Fill in triangles with color
for i in range(len(triangles)):
    t = triangles[i] 
    fill_in(t, i)

# Reshape 1d array to 3d
arr_3d = np.array(image).reshape((height, width, 3))

# Convert array to an image
from PIL import Image
im = Image.fromarray(np.uint8(arr_3d[::-1])).convert('RGB')
im.save("filledin.bmp")