# classPolynomial
definition of a class polynomial, to manipulate a polynomial of any order with overloaded operators.

to use this class, just copy and paste it in your program or include it using 

               #include"classPolynomial.cpp" 

after saving the file in the sirectory of your program.

to create a object pass it's degree as a parameter for example :

                polynomial poly(5);


to enter the coefficients of the polynomial just use the class cin with insertion operator as you would with any other pre-defined data type  :        
           
               cin>>poly;
        Output :
               Enter the coefficents of the terms as asked
               x^5     5
               x^4     2
               x^3     1
               x^2     2
               x^1     4
               x^0     3
to print the polynomial use the  use the class cout with extraction operator :
              
              cout<<poly;
        Output :
              5x^5 + 2x^4 + x^3 + 2x^2 + 4x^1 + 3
              
to get the degree of polynomial call the function trueDegree(), it returns an integer type value  :

            poly.trueDegree();
                       
