#include "user.h"

void main() {
    *((volatile int *) 0x80200000) = 0x1234; // new!
    for (;;); 
}
