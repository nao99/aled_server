/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.8 at Sat Dec 18 17:56:56 2021. */

#include "LedTape.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t LedTape_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, LedTape, diodes, diodes, &LedTape_Diode_fields),
    PB_LAST_FIELD
};

const pb_field_t LedTape_Diode_fields[5] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, LedTape_Diode, id, id, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, LedTape_Diode, r, id, 0),
    PB_FIELD(  3, INT32   , SINGULAR, STATIC  , OTHER, LedTape_Diode, g, r, 0),
    PB_FIELD(  4, INT32   , SINGULAR, STATIC  , OTHER, LedTape_Diode, b, g, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */