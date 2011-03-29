#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

typedef struct _sll_node_s
{
    int			val ;
    struct _sll_node_s	*next ;
} node ;

static char	*f_data_filename 	= NULL ;
static int	f_insert_value		= -1 ;
static int	f_delete_value		= -1 ;
static int	f_split_value		= -1 ;
static int	f_opt_fail		= 0 ;
static int	f_verbose		= 0 ;
static int	f_find_middle		= 0 ;
static int	f_check_for_cycle	= 0 ;

static int parse_options ( int argc, char *argv[] )
{
    int c = 0 ;

    while ( ( c = getopt( argc, argv, "cmvd:f:i:s:" ) ) != -1 )
    {
	switch ( c )
	{
	    case 'c':
		f_check_for_cycle = 1 ;
		break ;
	    case 'd':
		f_delete_value = atoi(optarg) ;
		break ;
	    case 'f':
		f_data_filename = optarg ;
		break ;
	    case 'i':
		f_insert_value = atoi(optarg) ;
		break ;
	    case 'm':
		f_find_middle = 1 ;
		break ;
	    case 's':
		f_split_value = atoi(optarg) ;
		break ;
	    case 'v':
		f_verbose = 1 ;
		break ;
	    default:
		printf ( "bad option %s\n", optarg ) ;
		f_opt_fail = 1 ;
		break ;
	}
    }

    return optind ;
}

void insert ( node **head, int val )
{
    node	*curr		= *head ;
    node	*prev		= NULL ;
    node	*new_node	= (node*)malloc ( sizeof(node) ) ;

    new_node->val = val ;

    while ( curr != NULL )
    {
	if ( curr->val >= new_node->val )
	{
	    new_node->next = curr ;
	    if ( prev != NULL )
		prev->next = new_node ;
	    else
		*head = new_node ;

	    break ;
	}
	else if ( curr->next == NULL )
	{
	    curr->next = new_node ;
	    break ;
	}

	prev = curr ;
	curr = curr->next ;
    }
}

void delete ( node **head, int val )
{
    node	*curr		= *head ;
    node	*prev		= NULL ;

    while ( curr != NULL )
    {
	if ( curr->val == val )
	{
	    if ( prev == NULL )
		*head = curr->next ;
	    else
		prev->next = curr->next ;

	    free ( curr ) ;
	    break ;
	}

	prev = curr ;
	curr = curr->next ;
    }
}

void split ( node *head, int val, node **lt, node **gt )
{
    node *curr = head ;
    node *prev = NULL ;

    if ( head->val >= val )
    {
	*lt = NULL ;
	*gt = curr ;
	return ;
    }

    while ( curr != NULL && curr->val < val )
    {
	prev = curr ;
	curr = curr->next ;
    }

    prev->next = NULL ;
    *lt = head ;
    *gt = curr ;
}

node *find_middle ( node *head )
{
    node *slowNode = head ;
    node *fastNode = head ;

    while ( fastNode != NULL )
    {
	fastNode = fastNode->next ;
	if ( fastNode == NULL )
	    break ;
	slowNode = slowNode->next ;
	fastNode = fastNode->next ;
    }

    return slowNode ;
}

int has_cycle ( node *head )
{
    node	*slowNode	= head ;
    node	*fastNode	= head ;
    node	*fasterNode	= head ;

    while ( fasterNode != NULL && (fastNode = fasterNode->next) != NULL
	    && (fasterNode = fastNode->next) != NULL )
    {
	if ( slowNode == fasterNode || slowNode == fastNode )
	    return 1 ;
	slowNode = slowNode->next ;
    }

    return 0 ;
}

void printll ( node *curr )
{
    while ( curr != NULL )
    {
	printf ( "%d ", curr->val ) ;
	curr = curr->next ;
    }
    printf ( "\n" ) ;
}

int main ( int argc, char *argv[] )
{
    node 	*head 		= NULL ;
    node 	*prev 		= NULL ;
    node 	*curr 		= NULL ;
    FILE	*data_file	= NULL ;
    char	line[1024] ;

    parse_options ( argc, argv ) ;
    if ( f_opt_fail != 0 || f_data_filename == NULL )
    {
	printf ( "filename=%s\n", f_data_filename ) ;
	printf ( "Usage: linked_lists [options]\n" ) ;
	exit ( 1 ) ;
    }

    /* load list */
    data_file = fopen ( f_data_filename, "r" ) ;
    if ( data_file == NULL )
    {
	printf ( "Failed to open file [%s], errno=%d\n",
		 f_data_filename, errno ) ;
	exit ( errno ) ;
    }

    while ( fgets ( line, sizeof(line), data_file ) != NULL )
    {
	curr = (node*)malloc ( sizeof ( node ) ) ;
	curr->next = NULL ;
	curr->val = atoi ( line ) ;

	if ( prev == NULL )
	    head = curr ; /* base case */
	else
	    prev->next = curr ; /* after the base case */

	prev = curr ;
    }

    //curr->next = head ; /* test has_cycle */

    if ( f_check_for_cycle )
    {
	int hasCycle = has_cycle ( head ) ;
	printf ( "has_cycle=%d\n", hasCycle ) ;
	if ( hasCycle ) return 0 ;
    }

    if ( f_verbose )
    {
	printll ( head ) ;
    }

    if ( f_insert_value >= 0 )
	insert ( &head, f_insert_value ) ;

    if ( f_delete_value >= 0 )
	delete ( &head, f_delete_value ) ;

    if ( f_split_value >= 0 )
    {
	node *lt = NULL ;
	node *gt = NULL ;
	split ( head, f_split_value, &lt, &gt ) ;
	if ( f_verbose )
	{
	    printf ( "lt: " ) ; printll ( lt ) ;
	    printf ( "gt: " ) ; printll ( gt ) ;
	}

	if ( lt != NULL )
	{
	    curr = lt ;
	    while ( curr->next != NULL )
		curr = curr->next ;
	    curr->next = gt ;
	}
    }

    if ( f_find_middle )
    {
	node *middle = find_middle ( head ) ;
	printf ( "m=" ) ;
	if ( middle )
	    printf ( "%d", middle->val ) ;
	printf ( "\n" ) ;
    }

    if ( f_verbose )
	printll ( head ) ;

//end:
    /* free the list */
    curr = head ;
    while ( curr != NULL )
    {
	prev = curr ;
	curr = prev->next ;
	free ( prev ) ;
    }

    exit(0) ;
}
