#ifndef EVENTREADDER_FORMV_H
#define EVENTREADDER_FORMV_H

#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

class EventForMV
{
public:
    EventForMV(TTreeReader &reader) : HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_(reader, "HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_"),
                                      HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_(reader, "HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_")

                                          {};

    ~EventForMV(){};

    // event branches reading
    TTreeReaderValue<Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_;
    TTreeReaderValue<Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_;
}

#endif