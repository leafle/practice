#include <stdio.h>

void swap ( int *x, int *y )
{
    *x ^= *y ;
    *y ^= *x ;
    *x ^= *y ;
}

int main ( int argc, char *argv[] )
{
    int x = 0, y = 0 ;

    x = atoi ( argv[1] ) ;
    y = atoi ( argv[2] ) ;

    printf ( "%d %d\n", x, y ) ;
    swap ( &x, &y ) ;
    printf ( "%d %d\n", x, y ) ;
}
