Everything implemented and checked except all types of boundary conditions
As of now only const boundary condition is implemented. (Boundary condition where all boundaries are given a constant value)
To generate coefficients for the PDE I used matlab matrices, copied and pasted them into the code in Main.cpp
A simple example for a 3*3 space is given, change the size, generate matrices with Matlab and paste them in appropriate locations to solve any PDE in Main.cpp
Choosing the type of solver is also given in the comments in Main.cpp

When giving inputs to space, the first matrix corresponds to A, second to B and so on. A and B here
are the coefficients of a PDE in standard form. (Example A*D2u/Dx2 + B*D2u/Dy2 ...)
A simple way of generating the matrix is shown. Constant coefficients can be done simply, but for functions like sinx and all use Matlab.

Iterative methods always give some solution, Matrix methods get stuck when singular matrices are present
The output is printed in n*n form. Kindly change the disp function is Space to change the printed output, (TO text or to Matlab etc)

Any questions please contact : stsashank6@gmail.com, 9940331480.
