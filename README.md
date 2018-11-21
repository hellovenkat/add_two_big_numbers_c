# add_two_big_numbers_c
To accommodate the inputs greater than 20 digits, I have used GNU Multiple Precision Arithmetic Library (GMP).It's fairly simple in Linux, just apt-get the library and run it
Compiling and running:
$ gcc -o prog prog.c -lgmp
$ ./prog input1 input2
References: https://gmplib.org/
