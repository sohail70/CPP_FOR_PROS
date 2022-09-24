#include<iostream>
void *operator new ( size_t size , bool Alloc )
{
    if ( Alloc )
        return NULL;
    else
    {
        try
        {
            void *Memory    =    ::operator new ( size );
            return Memory;
        }
        catch ( std::bad_alloc )
        {
            return NULL;
        }
    }
    return NULL;
}
void    SimpleFunction ( int MemCounter , bool AllFail )
{

    int LocalCounter = 0;

    char *Mem1 = new ( ( MemCounter == LocalCounter ++ ) || AllFail ) char [32];
    if ( Mem1 != NULL )
        strcpy ( Mem1 , "First Memory" );

    char *Mem2 = new ( ( MemCounter == LocalCounter ++ ) || AllFail ) char [ 32 ];
    if ( Mem2 != NULL )
        strcpy ( Mem2 , "Second Memory" );

    int NumTimesLoop    =    10;
    int LoopCounter     =    0;
    
    //    Create a Variable that will be allocate Inner Memory
    char **InnerMemory = new ( ( MemCounter == LocalCounter ++ ) 
                             || AllFail ) char * [ NumTimesLoop ];
    
    //    Loop through and allocate the memory required    
    for ( LoopCounter = 0; LoopCounter < NumTimesLoop ; LoopCounter ++ )
    {
        InnerMemory [ LoopCounter ] = new ( ( MemCounter == LocalCounter ++ ) 
                                                   || AllFail ) char [ 32 ];
    }

}

int main()
{
    for ( int counter = 0; counter < 12; counter ++ )
        SimpleFunction ( counter , false );
    SimpleFunction ( -1 , true );

    return 0;
}