#ifndef TTREEREADERVALUEDERIVED_H
#define TTREEREADERVALUEDERIVED_H

#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TBranch.h>
#include <TDataType.h>

#include <memory>
#include <string>

class AbstractTTreeReaderValue {
public:
    virtual ~AbstractTTreeReaderValue() = default;
    virtual void Read() = 0; // A virtual function to read the value
    // virtual void GetValue() const = 0; // A virtual function to get the value
};

template<typename T>
class TTreeReaderValueDerived : public AbstractTTreeReaderValue {
private:
    TTreeReaderValue<T> readerValue;

public:
    TTreeReaderValueDerived(TTreeReader& reader, const char* branchName)
        : readerValue(reader, branchName) {}

    void Read() override {
        // Implement the reading logic for this specific type
        // For example, just printing the value
        // if (*(readerValue.GetSetupStatus()) == TTreeReaderValueBase::kReadSuccess) {
        //     std::cout << *readerValue << std::endl;
        // }
        if (readerValue.IsValid()) {
            std::cout << *readerValue << std::endl;
        }
    }
    const TTreeReaderValue<T>& GetValue() const {
        return readerValue;
    }
};

#endif
