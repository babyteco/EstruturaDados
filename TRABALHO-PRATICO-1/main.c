#include <stdio.h>
#include <stdlib.h>
#include "booked.h"

int main(){
    Booked *b = criaBooked();
    leLeitoresTxt(b);
    leLivrosTxt(b);
    comandosTxt(b);
    liberaBooked(b);
    return 0;
}