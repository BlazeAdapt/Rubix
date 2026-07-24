# Rubix
Basically a rubix cube solver with a single axis with a motor to rotate the cube face, and another motor to hold down the rest of the cube while rotating the cube and to flip the cube to get to the other side.

## <ins> Server </ins> 
contains the python code for the server that actually solves the cube using the __koceimba__ algorithm.

## <ins> rubix_esp.ino </ins>
The main code that is flashed into the esp32 cam module, which uses wifi to connect to the __Server__ to request for the solution for the scramble scanned by the camera.

### <ins> f2_solve.c </ins> 
contains an unused code that solves the cube using the f2l method, which unlike __koceimba__, doesn't require pruning tables and *could* be used in a situation without wifi and less flash memory.
