#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

struct Buffer;

struct Serializator
{
    struct Buffer* _prv;
};


extern struct Serializator* InitSerializator(void);
extern void SerializeInt(struct Serializator* _this, int value);
extern void TestOUT(struct Serializator* _this, const char* fname);
extern void TestIN(const char* fname);


#endif // SERIALIZATOR_H
