// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIworkfs2dIcmsdIhuahuildI4topCodedICMSSW_10_2_20_ULdIsrcdIFourTopdIhuadIwriteVariableHistdIwriteHist_forBtagRCal_C_ACLiC_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/writeVariableHist/./writeHist_forBtagRCal.C"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_writeHist_forBtagRCal(void *p = 0);
   static void *newArray_writeHist_forBtagRCal(Long_t size, void *p);
   static void delete_writeHist_forBtagRCal(void *p);
   static void deleteArray_writeHist_forBtagRCal(void *p);
   static void destruct_writeHist_forBtagRCal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::writeHist_forBtagRCal*)
   {
      ::writeHist_forBtagRCal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::writeHist_forBtagRCal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("writeHist_forBtagRCal", ::writeHist_forBtagRCal::Class_Version(), "writeHist_forBtagRCal.h", 83,
                  typeid(::writeHist_forBtagRCal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::writeHist_forBtagRCal::Dictionary, isa_proxy, 4,
                  sizeof(::writeHist_forBtagRCal) );
      instance.SetNew(&new_writeHist_forBtagRCal);
      instance.SetNewArray(&newArray_writeHist_forBtagRCal);
      instance.SetDelete(&delete_writeHist_forBtagRCal);
      instance.SetDeleteArray(&deleteArray_writeHist_forBtagRCal);
      instance.SetDestructor(&destruct_writeHist_forBtagRCal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::writeHist_forBtagRCal*)
   {
      return GenerateInitInstanceLocal((::writeHist_forBtagRCal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::writeHist_forBtagRCal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr writeHist_forBtagRCal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *writeHist_forBtagRCal::Class_Name()
{
   return "writeHist_forBtagRCal";
}

//______________________________________________________________________________
const char *writeHist_forBtagRCal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::writeHist_forBtagRCal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int writeHist_forBtagRCal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::writeHist_forBtagRCal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *writeHist_forBtagRCal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::writeHist_forBtagRCal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *writeHist_forBtagRCal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::writeHist_forBtagRCal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void writeHist_forBtagRCal::Streamer(TBuffer &R__b)
{
   // Stream an object of class writeHist_forBtagRCal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(writeHist_forBtagRCal::Class(),this);
   } else {
      R__b.WriteClassBuffer(writeHist_forBtagRCal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_writeHist_forBtagRCal(void *p) {
      return  p ? new(p) ::writeHist_forBtagRCal : new ::writeHist_forBtagRCal;
   }
   static void *newArray_writeHist_forBtagRCal(Long_t nElements, void *p) {
      return p ? new(p) ::writeHist_forBtagRCal[nElements] : new ::writeHist_forBtagRCal[nElements];
   }
   // Wrapper around operator delete
   static void delete_writeHist_forBtagRCal(void *p) {
      delete ((::writeHist_forBtagRCal*)p);
   }
   static void deleteArray_writeHist_forBtagRCal(void *p) {
      delete [] ((::writeHist_forBtagRCal*)p);
   }
   static void destruct_writeHist_forBtagRCal(void *p) {
      typedef ::writeHist_forBtagRCal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::writeHist_forBtagRCal

namespace {
  void TriggerDictionaryInitialization_writeHist_forBtagRCal_C_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./writeHist_forBtagRCal.C",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/etc/",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/etc//cling",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include/",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include",
"/cvmfs/cms.cern.ch/slc7_amd64_gcc900/lcg/root/6.22.08-8d9ab2b279c3f35e6100d909611c3c2f/include/",
"/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/writeVariableHist/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "writeHist_forBtagRCal_C_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/writeVariableHist/./writeHist_forBtagRCal.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$writeHist_forBtagRCal.h")))  __attribute__((annotate("$clingAutoload$./writeHist_forBtagRCal.C")))  writeHist_forBtagRCal;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "writeHist_forBtagRCal_C_ACLiC_dict dictionary payload"

#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./writeHist_forBtagRCal.C"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"push_backHists", payloadCode, "@",
"writeHist_forBtagRCal", payloadCode, "@",
"writeHist_forBtagRCal::fgIsA", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("writeHist_forBtagRCal_C_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_writeHist_forBtagRCal_C_ACLiC_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_writeHist_forBtagRCal_C_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_writeHist_forBtagRCal_C_ACLiC_dict() {
  TriggerDictionaryInitialization_writeHist_forBtagRCal_C_ACLiC_dict_Impl();
}
