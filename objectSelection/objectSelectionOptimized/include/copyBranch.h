#ifndef COPYBRANCH_H
#define COPYBRANCH_H

#include "eventReader_nano.h"

class CopyBranch
{
public:
    CopyBranch(TTree *outTree);
    ~CopyBranch(){};

    void Select(eventForNano *e);
    void clearBranch();

private:
    // output branches
    UInt_t run_;
    ULong64_t event_;
};

#endif
