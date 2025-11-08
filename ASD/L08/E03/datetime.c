#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "datetime.h"

Data DATAload(char *sd) {
    Data d;
    sscanf(sd, "%d/%d/%d", &d.aaaa, &d.mm, &d.gg);
    return d;
}

Ora ORAload(char *so) {
    Ora o;
    sscanf(so, "%d:%d", &o.hh, &o.mm);
    return o;
}

int DATAcmp(Data d1, Data d2) {
    if (d1.aaaa != d2.aaaa)
        return (d1.aaaa - d2.aaaa);
    if (d1.mm != d2.mm)
        return (d1.mm - d2.mm);
    if (d1.gg != d2.gg)
        return (d1.gg - d2.gg);
    return 0;
}

void DATAstore(Data d, FILE *fp) {
    fprintf(fp, "%d/%02d/%02d  ", d.aaaa, d.mm, d.gg);
}

void ORAstore(Ora o, FILE *fp) {
    fprintf(fp, "%02d:%02d  \n", o.hh, o.mm);
}
