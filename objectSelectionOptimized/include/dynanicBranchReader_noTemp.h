#ifndef DYNAMICBRANCHREADER_H
#define DYNAMICBRANCHREADER_H
#include "TTreeReader.h"
//!!! virtual function + temlate = super complicated

// base class
template<typename T> //!!!base class can be templates too!
class IBranchReader {
public:
    virtual ~IBranchReader() = default;
    virtual void Print() const = 0; // A method to print the value for demonstration
    virtual UInt_t GetSize() const = 0;
    virtual T v() const = 0;
    virtual TTreeReaderArray<T>& v() const = 0;
};

/*
template<typename T>
class BranchReader : public IBranchReader {
// class BranchReader{
public:
    TTreeReaderValue<T> readerValue;
    BranchReader(TTreeReader& reader, const char* branchName) : readerValue(reader, branchName) {}
    void Print() const override {
        if (readerValue.IsValid()) {
            // std::cout << *readerValue << std::endl;
            // unsigned char value = *readerValue;
            // std::cout << static_cast<int>(value) << std::endl;
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

};
*/
class BranchReader_Int_t : public IBranchReader<Int_t> {
public:
    TTreeReaderValue<Int_t> readerValue;
    BranchReader(TTreeReader& reader, const char* branchName) : readerValue(reader, branchName) {}
    void Print() const override {
        if (readerValue.IsValid()) {
            // std::cout << *readerValue << std::endl;
            // unsigned char value = *readerValue;
            // std::cout << static_cast<int>(value) << std::endl;
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
    Int_t v() const override {
        return *readerValue;
    }

};
class BranchReader_UChar_t : public IBranchReader<UChar_t> {
    public:
    TTreeReaderValue<UChar_t> readerValue;
    BranchReader_UChar_t(TTreeReader& reader, const char* branchName) : readerValue(reader, branchName) {}
    UChar_t v() const override {
        return *readerValue;
    }   
};
class BranchReader_Short_t : public IBranchReader<Short_t> {
    public:
    TTreeReaderValue<Short_t> readerValue;
    BranchReader_Short_t(TTreeReader& reader, const char* branchName) : readerValue(reader, branchName) {}
    Short_t v() const override {
        return *readerValue;
    }   
};

/*
template<typename Y>
class BranchReaderArray : public IBranchReader {
public:
    TTreeReaderArray<Y> readerArray;
    BranchReaderArray(TTreeReader& reader, const char* branchName) : readerArray(reader, branchName) {}
    void Print() const override {
        if (readerArray.IsValid()) {
            // std::cout << *readerValue << std::endl;
            // unsigned char value = *readerValue;
            // std::cout << static_cast<int>(value) << std::endl;
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

};
*/

class BranchReaderArray_Int_t : public IBranchReader<In_t> {
    TTreeReaderArray<Int_t> readerArray;
    public:
    BranchReaderArray_Int_t(TTreeReader& reader, const char* branchName) : readerArray(reader, branchName) {}
    TTreeReaderArray<Int_t>& v() const override {
        return &readerArray;
    }
};
class BranchReaderArray_UChar_t : public IBranchReader<UChar_t> {
    TTreeReaderArray<UChar_t> readerArray;
    public:
    BranchReaderArray_UChar_t(TTreeReader& reader, const char* branchName) : readerArray(reader, branchName) {}
    TTreeReaderArray<UChar_t>& v() const override {
        return &readerArray;
    }
};
class BranchReaderArray_Short_t : public IBranchReader<Short_t> {
    TTreeReaderArray<Short_t> readerArray;
    public:
    BranchReaderArray_Short_t(TTreeReader& reader, const char* branchName) : readerArray(reader, branchName) {}
    TTreeReaderArray<Short_t>& v() const override {
        return &readerArray;
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
                            branchReader = std::make_unique<BranchReader_Int_t>(reader, branchName);
                            break;
                        // case kUInt_t:
                        //     branchReader = std::make_unique<BranchReader_UInt_t>(reader, branchName);
                        //     break;
                        case kUChar_t:
                            branchReader = std::make_unique<BranchReader_UChar_t>(reader, branchName);
                            break;
                        case kShort_t:
                            branchReader = std::make_unique<BranchReader_Short_t>(reader, branchName);
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
                            branchReader = std::make_unique<BranchReaderArray_Int_t>(reader, branchName);
                            break;
                        // case kUInt_t:
                        //     std::cout<<"initializing type: kUInt_t "<<branchType<<"\n";
                        //     branchReader = std::make_unique<BranchReaderArray_UInt_t>(reader, branchName);
                        //     break;
                        case kUChar_t:
                            std::cout<<"initializing type: kUChar_t "<<branchType<<"\n";    
                            branchReader = std::make_unique<BranchReaderArray_UChar_t>(reader, branchName);
                            break;
                        case kShort_t:
                            std::cout<<"initializing type: kShort_t "<<branchType<<"\n";
                            branchReader = std::make_unique<BranchReaderArray_Short_t>(reader, branchName);
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

    // void Print() {
    //     if (branchReader) {
    //         branchReader->Print();
    //     }
    // }
};

#endif