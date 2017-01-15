#include "catch.hpp"
#include "../Binary.h"
#define rr REQUIRE
namespace HLR1{
TEST_CASE("Binary: Smackering of tests: big endian", "[Binary]"){
    Binary b(1000, false);
    rr(b.getOffset() == 0);

    b.pushByte(0x1);
    b.pushByte(0x2);
    b.pushByte(0x3);
    b.pushByte(0x4);
    rr(b.getWordAt(0)==0x01020304);
    b.pushHWord(0x1234);
    b.pushHWord(0x5678);
    rr(b.getWordAt(4)==0x12345678);
    b.pushWord(0x87654321);
    rr(b.getWordAt(8)==0x87654321);
    rr(b.getOffset()==12);
    b.insertWordAt(0x98765432, 0);
    rr(b.getWordAt(0)==0x98765432);
    b.insertWordAt(0x08762345, 4);
    rr(b.getWordAt(4)==0x08762345);
    b.insertWordAt(0x13425345, 1);
    rr(b.getWordAt(1)==0x13425345);
    b.pushByte(0x9D);
    b.align();
    rr(b.getWordAt(12)==0x9D000000);
    b.pushHWord(0x4321);
    b.align();
    rr(b.getWordAt(16)==0x43210000);

}

TEST_CASE("Binary: Smackering of tests: little endian", "[Binary]"){
    Binary b(1000, true);
    rr(b.getOffset() == 0);

    b.pushByte(0x1);
    b.pushByte(0x2);
    b.pushByte(0x3);
    b.pushByte(0x4);
    rr(b.getWordAt(0)==0x04030201);
    b.pushHWord(0x1234);
    b.pushHWord(0x5678);
    rr(b.getWordAt(4)==0x56781234);
    b.pushWord(0x87654321);
    rr(b.getWordAt(8)==0x87654321);
    rr(b.getOffset()==12);
    b.insertWordAt(0x98765432, 0);
    rr(b.getWordAt(0)==0x98765432);
    b.insertWordAt(0x08762345, 4);
    rr(b.getWordAt(4)==0x08762345);
    b.insertWordAt(0x13425345, 1);
    rr(b.getWordAt(1)==0x13425345);
    b.pushByte(0x9D);
    b.align();
    rr(b.getWordAt(12)==0x0000009D);
    b.pushHWord(0x4321);
    b.align();
    rr(b.getWordAt(16)==0x00004321);

}
}
