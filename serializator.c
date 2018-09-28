#include "serializator.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Buffer
{
    size_t Count;
    void* data;
    size_t next;
};


static inline struct Buffer* create_buffer(unsigned int inital_count)
{
    struct Buffer* bf = (struct Buffer*) malloc(sizeof(struct Buffer));
    if (!bf)
        return  0;

    if (inital_count < 32)
        inital_count = 32;

    bf->data = calloc(inital_count, sizeof(char));
    if (!bf->data)
    {
        free(bf);
        return  0;
    }

    bf->Count = inital_count;
    bf->next = 0;

    return  bf;
}


static inline void request_mem(struct Buffer* buffer, size_t size)
{
    if (!buffer)
        return;
    if (size + buffer->next> buffer->Count)
    {
        buffer->Count = size;
        buffer->data = realloc(buffer->data, buffer->Count * 2);
        buffer->Count *= 2;
    }
}

struct Serializator* InitSerializator(void)
{
    struct Serializator* sr = (struct Serializator*) malloc(sizeof(struct Serializator));
    if (!sr)
        return  0;


    sr->_prv = create_buffer(64);
    if (!sr->_prv)
    {
        free(sr);
        return  0;
    }
    return  sr;
}



void SerializeInt(struct Serializator* _this, int value)
{
    if (!_this)
        return;

    request_mem(_this->_prv, sizeof(int));
    memcpy( ((char*)(_this->_prv->data)) + _this->_prv->next, &value, sizeof(int));
    _this->_prv->next += sizeof(int);
}


void TestOUT(struct Serializator* _this, const char* fname)
{
    FILE* fp = fopen(fname, "wb");
    if (!fp || !_this)
        return;

    fwrite((char*)_this->_prv->data, sizeof(char), _this->_prv->Count, fp);
    fclose(fp);

    free(_this->_prv->data);
    free(_this->_prv);

}

void TestIN(const char* fname)
{
    FILE* fp = fopen(fname, "rb");
    if (!fp)
        return;

    int* data = (int*)calloc(10, sizeof(int));

    fread(data, sizeof(int), 10, fp);

    int i;
    for(i=0; i < 10; ++i)
    {
        printf("%d\r\n", data[i]);
    }

    fclose(fp);
    free(data);
}

