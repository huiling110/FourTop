#ifndef DYNAMICBRANCHREADER_H
#define DYNAMICBRANCHREADER_H
#include "TTreeReader.h"

#include <any>
//virtual function + temlate = complicated, actually not necessryily

// base class
class IBranchReader {
public:
    virtual ~IBranchReader() = default;
    virtual void Print() const = 0; // A method to print the value for demonstration
    virtual UInt_t GetSize() const = 0; //, it specifies that the function is a constant member function. This means that the function is not allowed to modify any member variables of the object (except those marked as mutable) or call any non-const member functions on the object. 
    virtual std::any GetValue()  = 0;
    virtual std::any at(UInt_t idx) const = 0;
};


template<typename T>
class BranchReader : public IBranchReader {
    TTreeReaderValue<T> readerValue;
public:
    BranchReader(TTreeReader& reader, const char* branchName) : readerValue(reader, branchName) {
        std::cout << "initializing type: "<<typeid(T).name()<<"\n";
    }
    void Print() const override {
        if (readerValue.IsValid()) {
            std::cout << "valid\n";
        }
        else
        {
            std::cerr << "Invalid TTreeReaderValue for branch: " << readerValue.GetBranchName() << std::endl;
        }
    }
    UInt_t GetSize() const override {
        return 1;
    }
    // std::any GetValue() const override {
    std::any GetValue() override {
        return std::any(*readerValue);
        // return std::any(*(readerValue.Get()));
        // return std::any(*(readerValue.Get()));
        // return *readerValue;
    }
    std::any at(UInt_t idx) const { //!!! it seems every derived class needs to implement this function
        return std::any(0);
    }

};

template<typename Y>
class BranchReaderArray : public IBranchReader {
    TTreeReaderArray<Y> readerArray;
public:
    BranchReaderArray(TTreeReader& reader, const char* branchName) : readerArray(reader, branchName) {}
    void Print() const override {
        if (readerArray.IsValid()) {
            std::cout << "valid\n";
        }
        else
        {
            std::cerr << "Invalid TTreeReaderArray for branch: " << readerArray.GetBranchName() << std::endl;
        }
    }
    UInt_t GetSize() const override {
        return readerArray.GetSize();
    }
    // std::any GetValue() const override {
    std::any GetValue()  override {
        return std::any(&readerArray);
    }
    std::any at(UInt_t idx) const{
        return std::any(readerArray.At(idx));
    }

};


// template<typename T> //doesn't work here because T needs to be known at compile time
class DynamicBranchReader {
// I want this class to handle the different type of input branch for reading
public:
    std::unique_ptr<IBranchReader> branchReader; //base class

    DynamicBranchReader(TTreeReader& reader, const char* branchName) {
        TBranch* branch = reader.GetTree()->GetBranch(branchName);
        if (!branch) {
            // throw std::runtime_error("Branch not found");
            std::cout << "!!!Branch not found!!!\n";
            branchReader = nullptr;
        }

        if (branch){
            TClass* branchClass;
            EDataType branchType;
            branch->GetExpectedType(branchClass, branchType);
            //check if it's an array
            bool isArray = false;
            // TObjArray *leaves = branch->GetListOfLeaves();
            // if (leaves->GetEntriesFast() > 0) {
            //     TLeaf *leaf = (TLeaf*)leaves->At(0);
            //     isArray = (leaf->GetLenStatic() > 1) || (leaf->GetLen() > 1) || (strstr(leaf->GetTypeName(), "[]") != nullptr);
            // }//not working
            TIter next(branch->GetListOfLeaves());
            TLeaf *leaf;
            while ((leaf = (TLeaf*)next())) {
                if (leaf->GetLeafCount() != nullptr || leaf->IsOnTerminalBranch() == kFALSE) {
                    isArray = true;
                    break;
                }
            }

            if (branchClass) {
                // Handle object types
            } else {
                // Handle fundamental types
                if (!isArray){
                    switch (branchType) {
                        case kInt_t:
                            branchReader = std::make_unique<BranchReader<Int_t>>(reader, branchName);
                            break;
                        case kUInt_t:
                            branchReader = std::make_unique<BranchReader<UInt_t>>(reader, branchName);
                            break;
                        case kUChar_t:
                            branchReader = std::make_unique<BranchReader<UChar_t>>(reader, branchName);
                            break;
                        case kShort_t:
                            branchReader = std::make_unique<BranchReader<Short_t>>(reader, branchName);
                            break;
                        // case kA
                        // Add cases for other types as needed
                        default:
                            std::cout << branchName << "\n";
                            throw std::runtime_error("Unsupported branch type: ");
                    }
                }else
                {
                    switch (branchType) {
                        case kInt_t:
                            std::cout << "initializing type: kInt_t "<<branchType<<"\n";
                            branchReader = std::make_unique<BranchReaderArray<Int_t>>(reader, branchName);
                            break;
                        case kUInt_t:
                            std::cout<<"initializing type: kUInt_t "<<branchType<<"\n";
                            branchReader = std::make_unique<BranchReaderArray<UInt_t>>(reader, branchName);
                            break;
                        case kUChar_t:
                            std::cout<<"initializing type: kUChar_t "<<branchType<<"\n";    
                            branchReader = std::make_unique<BranchReaderArray<UChar_t>>(reader, branchName);
                            break;
                        case kShort_t:
                            std::cout<<"initializing type: kShort_t "<<branchType<<"\n";
                            branchReader = std::make_unique<BranchReaderArray<Short_t>>(reader, branchName);
                            break;
                        // Add cases for other array types as needed
                        default:
                            throw std::runtime_error("Unsupported array branch type");
                    }
                }
                std::cout << branchName <<" "<<branchType<< " properly initialized\n\n";
            }
        }
    }    

    void Print() {
        if (branchReader) {
            branchReader->Print();
        }
    }

    std::any GetValue() {
        if (branchReader) {
            return branchReader->GetValue();
        }
        else
        {
            return std::any();
        }
    }
    std::any at(UInt_t idx) const {
        if (branchReader) {
            return std::any(branchReader->at(idx));
        }
        else
        {
            return std::any();
        }
    }
};

#endif