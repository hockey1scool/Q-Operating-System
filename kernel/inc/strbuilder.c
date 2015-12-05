#include "strbuilder.h"

strbuilder_t strbuilder_init() {
    strbuilder_t tmp;
    tmp.prevTxt = "";
    tmp.ilist = list_init();
    tmp.ilist.autoShrink = true;
    return tmp;
}

static inline void __backupText(strbuilder_t* stb) {
    stb->prevTxt = strbuilder_tostr(*stb);
}

void strbuilder_appendc(strbuilder_t* stb, char c) {
    __backupText(stb);
    list_addc(&(stb->ilist), c);
}

void strbuilder_appends(strbuilder_t* stb, string str) {
    __backupText(stb);
    do
        list_addc(&(stb->ilist), *str++);
    while (*str != 0);
}

static string __vstb_tos(strbuilder_t stb, uint32 l, uint32 h) {
    uint32 strlen = abs(h - l);
    if (strlen > stb.ilist.size) return NULL;
    string msg = (string) kmalloc((strlen) * sizeof(char));
    uint32 i = 0;
    for(i = 0; i < strlen; i++) {
        msg[i] = list_getc(stb.ilist, i);
    }
    msg[i] = '\0'; // Strings are null terminated!
    return msg;
}

string strbuilder_tostr(strbuilder_t stb) {
    return __vstb_tos(stb, 0, stb.ilist.size);
}

string strbuilder_substr(strbuilder_t stb, uint32 l, uint32 h) {
    return __vstb_tos(stb, l, h);
}

void strbuilder_clear(strbuilder_t* stb) {
    __backupText(stb);
    list_clear(&(stb->ilist));
}

void strbuilder_destroy(strbuilder_t* stb) {
    list_destroy(&(stb->ilist));
    stb->prevTxt = "";
}

