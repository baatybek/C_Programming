#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 *
 * @author beksultan
 */


typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TEmployee         * m_Bak;
    char                     * m_Name;
} TEMPLOYEE;



#endif /* __PROGTEST__ */
/*
	Function creates a new element in the linked list and places the new element at the first position of the list.
	The parameters are name - name of the new employee and next - a link to the first element of an existing employee list.
	Return value is the first element of the newly updated linked list.
	The function is responsible for the allocation of the employee structure, moreover it must initialize the fields.
	The newly listed employee does not have any substitute defined, i.e. m_Bak must be set to NULL.
*/


TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{
    TEMPLOYEE *newEmp = (TEMPLOYEE *) malloc (sizeof(TEMPLOYEE));

    if(newEmp == NULL) { exit(0); }

    if(name != NULL)
    {
        size_t len = strlen(name);
        newEmp->m_Name = (char *) malloc (len * 2);
	    if(newEmp->m_Name == NULL) { exit(0); }
		
        strncpy(newEmp->m_Name, name, len);
        newEmp->m_Name[len] = '\0';

    }

    newEmp->m_Bak = NULL;
    newEmp->m_Next = next;
    next = newEmp;

    return newEmp;
}

/*
void copyName (TEMPLOYEE * src, TEMPLOYEE * dst)
{
    size_t len = strlen(src->m_Name);
    dst->m_Name = (char *) malloc (len * 2);
    if(dst->m_Name == NULL) {  exit(0); }
    strncpy(dst->m_Name, src->m_Name, len);
    dst->m_Name[len] = '\0';
}

TEMPLOYEE * insertNode (TEMPLOYEE *prev_node)
{
    // create a new node and allocated memory for it
    TEMPLOYEE *new_node;
    new_node = (TEMPLOYEE *) calloc (1, sizeof(TEMPLOYEE));
    if(new_node == NULL) {  exit(0); }

    copyName(prev_node, new_node);
    new_node->m_Next = prev_node->m_Next;		// next node or NULL will be link of the new node for next node
    new_node->m_Bak = prev_node->m_Bak;		// m_Bak node or NULL will be link of the new node for m_Bak node
    prev_node->m_Next = new_node;			// new node will be a link for the previous node wich is given

    return new_node;
}

void seprate_m_Bak (TEMPLOYEE       * src)
{
    TEMPLOYEE * current = src;
    while(current != NULL)
    {
        TEMPLOYEE * prime = NULL;
        prime = current->m_Next;
        TEMPLOYEE * tmp = current->m_Bak;
        if(tmp == NULL)
        {
            prime->m_Bak = NULL;
        }else{
            prime->m_Bak = tmp->m_Next;
        }
        current = prime->m_Next;
    }
}

void seprate_Clone (TEMPLOYEE       * src)
{
    TEMPLOYEE * current = src;
    TEMPLOYEE * newList = src->m_Next;

    while(current!=NULL)
    {
        current->m_Next = newList->m_Next;
        current = current->m_Next;
        if(current==NULL)
        {
            newList->m_Next = NULL;
        }
        else
        {
            newList->m_Next = current->m_Next;
        }
        newList = newList->m_Next;
    }
}

TEMPLOYEE        * cloneList   ( TEMPLOYEE       * src )
{
    TEMPLOYEE * current = src;
    while(current != NULL)
    {
        TEMPLOYEE * prime = NULL;
        if(current != NULL)
            prime = insertNode(current);
        current = prime->m_Next;
    }

    current = src;
    seprate_m_Bak(current);
    current = src;
    TEMPLOYEE *newList = current->m_Next;
    seprate_Clone(current);
    return newList;
}

*/
TEMPLOYEE  *  cloneList ( TEMPLOYEE * src )
{
    if(src == NULL)
        return NULL;

    TEMPLOYEE *current = src;

    while(current != NULL)
    {
        TEMPLOYEE *prime = current -> m_Next;
        current -> m_Next = newEmployee(current->m_Name, current->m_Next);
        current -> m_Next -> m_Next = prime;
        current = prime;
    }
    current = src;

    TEMPLOYEE * cloneList = current->m_Next;
    while(current != NULL)
    {
        TEMPLOYEE *cloneTmp = current->m_Next;
        if(current->m_Bak != NULL)
            cloneTmp -> m_Bak = current ->m_Bak -> m_Next;
        current = cloneTmp->m_Next;
    }

    current = src;

    while(current != NULL)
    {
        TEMPLOYEE *cloneTmp = current->m_Next;
        current->m_Next = cloneTmp -> m_Next;
        if(cloneTmp->m_Next != NULL)
            cloneTmp -> m_Next = cloneTmp -> m_Next -> m_Next;
        current = current->m_Next;
    }
    return cloneList;

}

void               freeList     ( TEMPLOYEE       * src )
{
    if(src == NULL)
        return;
    else{
        TEMPLOYEE *current = src;
        TEMPLOYEE *next;
        while(current != NULL){
            next = current -> m_Next;
		    if(current -> m_Name != NULL)
            	free(current -> m_Name);
		    if(current != NULL)
           		free(current);
            current = next;
        }
        src = NULL;
    }
}




void printList( TEMPLOYEE *src)
{
    TEMPLOYEE *current = src;
    while(current != NULL)
    {
        printf("%s\n", current->m_Name);
        current = current->m_Next;
    }
}




#ifndef __PROGTEST__
int                main         ()
{
    TEMPLOYEE * a, *b;
    char tmp[100];

    assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
    a = NULL;
    a = newEmployee ( "Peter", a );
    a = newEmployee ( "John", a );
    a = newEmployee ( "Joe", a );
    a = newEmployee ( "Maria", a );
    a -> m_Bak = a -> m_Next;
    a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
    a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );

    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    b = cloneList ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    a = newEmployee ( tmp, a );
    b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
    assert ( a
             && ! strcmp ( a -> m_Name, "Peter" )
             && a -> m_Bak == NULL );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
             && a -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
             && a -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == NULL );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( a );
    b -> m_Next -> m_Bak = b -> m_Next;
    a = cloneList ( b );
    assert ( a
             && ! strcmp ( a -> m_Name, "Maria" )
             && a -> m_Bak == a -> m_Next );
    assert ( a -> m_Next
             && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
             && a -> m_Next -> m_Bak == a -> m_Next );
    assert ( a -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
    assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b
             && ! strcmp ( b -> m_Name, "Maria" )
             && b -> m_Bak == b -> m_Next );
    assert ( b -> m_Next
             && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
             && b -> m_Next -> m_Bak == b -> m_Next );
    assert ( b -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
    assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

    freeList ( b );
    freeList ( a );

    return 0;
}
#endif /* __PROGTEST__ */
