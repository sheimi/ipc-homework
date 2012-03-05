#ifndef ENV_H
#define ENV_H

typedef int bool;
#define true 1
#define false 0
#define max(a, b) (a > b ? a : b)
#define str_equal(a, b) (!strcmp(a, b))
#define strcase_equal(a, b) (!strcasecmp(a, b))
#define str_nequal(a, b) (strcmp(a, b))
#define strcase_nequal(a, b) (strcasecmp(a, b))

#endif
