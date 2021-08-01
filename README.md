# Quadify

Computer art based on quadtrees.
Programm gets the input image, that is split into four quads. Each quad is filled with an averaged color based on the colors inside it. The quad with the largest difference between coloros is split into four new quads inside it. This process is repeated N times. You can set repeat count by command line argument or by arrow-buttons. 

### Animation

The first animation - with border.

![Animation](https://imgur.com/nknqK1t.gif)

The second animation - without border.

![Animation](https://imgur.com/u6WGSjr.gif)

### Usage

  quadify.exe <input file path> <output file extension(.png or .jpg)> <repeat count>
  
  or
  
  quadify.exe <input file path> <output file extension(.png or .jpg)>
  
  You can change repeat count by UP and DOWN arrow buttons and minimum size of quad by LEFT and RIGHT arrow buttons.
  To save image - click SPACE.
  To show/hide borders - click B.
  
