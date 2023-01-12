/*
** hw4_io.h:
**
** The header file declaring library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
Contains the declarations of integral and root finding functions for this homework. 
You are not expected to modify this file in your submission. 
You may modify it for your own testing and debugging needs.

Bu kısım sadece lib.c dosyasının daha temiz görünmesi için var.

*/


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta);


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta);


double root3(double a0, double a1, double a2, double a3, double xs, double xe);


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe);
