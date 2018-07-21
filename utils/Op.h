#include "sch.h"

op_t *OpCreate(/*copy params from schedadd*/);

void OpDestroy(op_t *op);

guid_t OpGetUid(op_t *op);

op_t * OpGetPtr(guid_t uid);
