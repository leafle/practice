#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int reverse_string ( char *string_to_reverse )
{
    int		rc			= 0 ;
    int 	i			= 0 ;
    int		length			= strlen ( string_to_reverse ) ;

    /* reverse every character */
    for ( i = 0 ; i < length - i - 1 ; i++ )
    {
	char temp 			= string_to_reverse[i] ;
	string_to_reverse[i] 		= string_to_reverse[length-i-1] ;
	string_to_reverse[length-i-1] 	= temp ;
    }

    return rc ;
}

int reverse_words ( char *string_to_reverse )
{
    int		rc			= 0 ;
    int		i			= 0 ;
    int		length			= strlen ( string_to_reverse ) ;
    char	*word			= NULL ;

    /* reverse every character */
    reverse_string ( string_to_reverse ) ;
    printf ( "Processing: %s\n", string_to_reverse ) ;

    /* reverse each word */
    word = string_to_reverse ;
    for ( i = 0 ; i < length ; i++ )
    {
	if ( isspace ( string_to_reverse[i] ) )
	{
	    char temp = string_to_reverse[i] ;
	    string_to_reverse[i] = '\0' ;
	    reverse_string ( word ) ;
	    string_to_reverse[i] = temp ;
	    printf ( "Processing: %s\n", string_to_reverse ) ;
	    if ( i+1 < length )
		word = string_to_reverse + i + 1 ;
	}
	else if ( i == length - 1 )
	{
	    reverse_string ( word ) ;
	    printf ( "Processing: %s\n", string_to_reverse ) ;
	}
    }

    return rc ;
}

/*
 * Reverse the words in the string provided
 */
int main ( int argc, char *argv[] )
{
    int		rc			= 0 ;
    char 	*string_to_reverse	= NULL ;

    if ( argc != 2 )
    {
	printf ( "Usage: reverse_words <string_to_reverse>\n" ) ;
	exit (0) ;
    }

    string_to_reverse = argv[1] ;

    printf ( "Input: %s\n", string_to_reverse ) ;

    rc = reverse_words ( string_to_reverse ) ;
    if ( rc != 0 )
    {
	printf ( "Error while reversing string, rc=%d\n", rc ) ;
	exit ( rc ) ;
    }

    printf ( "Result: %s\n", string_to_reverse ) ;
    exit ( rc ) ;
}
