#include <stdio.h>
#include "serializator.h"

int main()
{

    struct Serializator* ser = InitSerializator();

    if (!ser)
        return -1;
    else
        printf("Serializator OK\r\n");

    int a[] = {1, 2, 3,
               4, 5, 6,
               7, 8, 9,
               10};
    int i;
    WriteHeader(ser);
    for(i=0; i < 10; i++)
        SerializeInt(ser, a[i]);


    // test write

    TestOUT(ser, "test.bin");

    TestIN("test.bin");


    return 0;
}


