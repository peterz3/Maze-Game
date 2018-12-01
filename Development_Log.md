

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

# 11/31

* solving problem with map_width being reset to 0 for some reason
* had to learn debugging
* problem solved! I wasn't initlizing a double array correctly which resulted in variables being lost
* map effectively scaled! there is however a small chunk of the screen being uncolored because of integer division 
causing for decimal point inaccuracies
* problem with horizontal movement eing bounded too early
