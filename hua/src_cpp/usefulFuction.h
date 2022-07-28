#include <string>

#include "TString.h"

void getOption(TString option, std::vector<TString> &optionVec)
{
    optionVec.clear();
    while (option.Contains(":"))
    {
        TString ioption = option(0, option.First(":"));
        option.Remove(0, option.First(":") + 1);
        optionVec.push_back(ioption);
    }
}