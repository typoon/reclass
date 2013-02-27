%{
#include <stdio.h>
#include "parser.tab.h"

#define YY_NO_INPUT

int new_instruction = 0;
int line = 1;

%}

%option nounput
%option noyywrap

%x SL_COMMENT
%x ML_COMMENT

%%

<INITIAL>{
    [\t]                           ;
    [\n]                           { new_instruction = 1; ++line; }

    [1-9]+[0-9]*                   { 
                                       int x = atoi(yytext); 
                                       if((x >= 0) && (x <= 255)) {
                                           yylval.byte_val = x;
                                           return BYTE;
                                       } else {
                                           yylval.int_val = x;
                                           return INT;
                                       }
                                   }
                            
    "0x"[0-9a-fA-F]{1,8}           {
                                       int x = strtol(yytext, NULL, 16);
                                       if((x >= 0) && (x <= 255)) {
                                           yylval.byte_val = x;
                                           return BYTE;
                                       } else {
                                           yylval.int_val = x;
                                           return INT;
                                       }
                                   }
        
    ["]([^\\"]+|\\.)*["]           { yylval.str_val = strdup(yytext);  return STRING; }

    [\.]byte                       { return VAR_BYTE;   }
    [\.]int                        { return VAR_INT;    }
    [\.]double                     { return VAR_DOUBLE; }
    [\.]string                     { return VAR_STRING; }

    [\.]method                     { return METHOD_START; }
    [\.]method_end                 { return METHOD_END;   }
    [\(][a-zA-Z\[;\/]*[\)][a-zA-Z\[;\/]* { yylval.param = strdup(yytext); return PARAMS; }
    [\*]                           { return DEREF; }



    nop                            { return NOP;                                  }
    aconst_null                    { return ACONST_NULL;                          }
    iconst_m1                      { return ICONST_M1;                            }
    iconst_0                       { return ICONST_0;                             }
    iconst_1                       { return ICONST_1;                             }
    iconst_2                       { return ICONST_2;                             }
    iconst_3                       { return ICONST_3;                             }
    iconst_4                       { return ICONST_4;                             }
    iconst_5                       { return ICONST_5;                             }
    lconst_0                       { return LCONST_0;                             }
    lconst_1                       { return LCONST_1;                             }
    fconst_0                       { return FCONST_0;                             }
    fconst_1                       { return FCONST_1;                             }
    fconst_2                       { return FCONST_2;                             }
    dconst_0                       { return DCONST_0;                             }
    dconst_1                       { return DCONST_1;                             }
    bipush                         { return BIPUSH;                               }
    sipush                         { return SIPUSH;                               }
    ldc                            { return LDC;                                  }
    ldc_w                          { return LDC_W;                                }
    ldc2_w                         { return LDC2_W;                               }
    aaload                         { return AALOAD;                               }
    return                         { return RETURN;                               }
    getstatic                      { return GETSTATIC;                            }
    newarray                       { return NEWARRAY;                             }
    pop                            { return POP;                                  }
    invokevirtual                  { return INVOKEVIRTUAL;                        }
    invokestatic                   { return INVOKESTATIC;                         }


    ";"                            { BEGIN(SL_COMMENT);                           }

    [$][a-zA-Z_$]+                   { yylval.identifier = strdup(yytext);  return IDENTIFIER; }
    [a-zA-Z]+                        { yylval.identifier = strdup(yytext);  return METHOD_IDENTIFIER; }

    .                              ;
}

<SL_COMMENT>{
    [\n]                           { new_instruction = 1; ++line; BEGIN(INITIAL); }
    .                              ;
}

%%
