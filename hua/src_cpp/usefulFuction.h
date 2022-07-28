
#include "TString.h"

void getOption(TString option, std::vector<TString> &optionVec)
{
    optionVec.clear();
    Int_t optionNum = option.CountChar(":");
    for (Int_t i = 0; i < option; i++)
    {
        ioption = option(0, option.First(":"));
        option.Remove(0, option.First(":"));
        optionVec.push_back(ioption);
    }
}