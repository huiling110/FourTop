#include "eventReader_nano.C"

class objectSelection
{
public:
    objectSelection()
    {
        e = new eventForNano{m_reader};
    };
    eventForNana *e;
    TTreeReader *m_reader;

    Init(){

    };

    EventLoop()
    {
        Long_int entryCount = 0;
        while (m_reader.Next() && entryCount < numEntries)
        {
            muonSelection(e, m_outTree);
            // Increment the entry count
            entryCount++;
        }
    }
    Terminate(){

    };
};