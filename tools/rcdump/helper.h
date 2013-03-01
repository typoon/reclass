#ifndef HELPER_H_
#define HELPER_H_

#include "reclass.h"

char *name_index_to_str(ClassFile *cf, int index);
char* access_flags_to_str(u2 flags);
char* parse_method_signature(ClassFile *cf, method_info *mi);

#endif /* HELPER_H_ */
