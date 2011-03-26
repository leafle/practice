#include <stdlib.h>
#include <stdio.h>


int main ( int argc, char *argv[] )
{
    unsigned char 	byte 		= '\0' ;
    unsigned char 	byte2 		= '\0' ;
    int			i		= 0 ;
    int			bitwise_length	= 8 ;
    int			num_set_bits	= 0 ;

    if ( argc != 2 || argv[1] == NULL )
    {
	printf ( "Usage: num_set_bits byte\n" ) ;
	exit ( 1 ) ;
    }

    byte = argv[1][0] ;

    printf ( "byte = %c, byte = %d\n", byte, byte ) ;
    byte2 = byte ;

    for ( i = 0 ; i < bitwise_length ; i++, byte >>= 1 )
	if ( byte & 1 ) num_set_bits++ ;

    printf ( "%c has %d set bits\n", byte2, num_set_bits ) ;
    exit ( 0 ) ;
}
