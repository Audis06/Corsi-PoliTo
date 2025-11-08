#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "quotazione.h"

int QUOTAZIONEcheckNull(Quotazione q) {
    return (q.den == 0);
}
Quotazione QUOTAZIONEsetNull() {
    Quotazione q = {{-1,-1,-1}, 0.0, 0};
    return q;
}

static float media(Quotazione q) {
    if (q.den != 0)
        return q.num / (float) q.den;
    return -1.0;
}

void QUOTAZIONEstore(FILE *fp, Quotazione q) {
    DATAstore(q.data, fp);
    printf(" %.2f\n", QUOTAZIONEgetValore(q));
}

Data QUOTAZIONEgetData(Quotazione q) {
    Data d = {-1,-1,-1};
    if (QUOTAZIONEcheckNull(q))
        return d;
    return q.data;
}

float QUOTAZIONEgetValore(Quotazione q) {
    return media(q);
}

