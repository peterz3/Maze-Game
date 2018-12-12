

# 11/10 to 11/13
setup SDL with visual studio and created screen with background color

# 11/13 to 11/14
loaded images in the screen and moved them around the screen and changed dimensions

# 11/14 to 11/16
created a Map, which contains images that create background and used it to load and change background color

# 11/25 to 11/26
worked on entity controll system and modifying object composition

# 11/26 to 11/27
worked on fixing include error and tried to get to work with openframeworks

# 11/28 to 11/29
worked on creating game boundaries, implementing user control and creating walls

# 11/30
started working on getting maze to scale, gtting weird bug where program thinks map width is 0

# Next week
get maze to scale and maybe start working on maze generation algorithms

# 12/1 -12/2

* solving problem with map_width being reset to 0 for some reason
* had to learn debugging
* problem solved! I wasn't initlizing a double array correctly which resulted in variables being lost
* map effectively scaled! there is however a small chunk of the screen being uncolored because of integer division 
causing for decimal point inaccuracies
* problem with horizontal movement being bounded too early
* changed movement so it converts from map index(in the double array) to pixels on the screen(instead of visa versa)this greatly simplified my code and solved the movement bounding bug
* added squares that hid remainder of map not filled out with texture squares(due to decimal point cutting)

# 12/3 - 12/5

* created maze generator class which holds boolean array for cells
* converted between boolean array to physical maze, I had to scale maze size by 4 in order to change maze strcture to empty cells surrounded by walls(like a grid) from just a map of walls and spaces
* implemented maze generating algorithm using recursion
* implemented maze generator cpp
* improved clean function to delete generated arrays

# 12/6 - 12/7

* changed texture names
* implemented depth first maze generation algorithm
* tried fixing overflow error
* implemented finishing block texture and made it so game quits when you hit it