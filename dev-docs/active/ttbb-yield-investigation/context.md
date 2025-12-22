# ttbb Yield Investigation - Technical Context

## Key Files

### FR Calculation
- `myLibrary/commenFunction.C:315-374` - getFRandError() function
- `myLibrary/commenFunction.h` - EtaProngGraph struct definition
- `makeVariables_goodCode/src/weightVarMaker.C` - FR_weight calculation
- `makeVariables_goodCode/include/inputMap_MV.h` - FR file path (hardcoded)

### FR Data File
```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_backupV2/mc/variableHists_v0FRMeasure/results/fakeRateInPtEtaProng.root
```
Contains 4 TGraphAsymmErrors objects with 8 points each.

## Useful Commands

### Build
```bash
cd myLibrary && source ../setEnv_newNew.sh && make
cd makeVariables_goodCode && make clean && make
```

### Test MV locally
```bash
cd makeVariables_goodCode
source ../setEnv_newNew.sh
./apps/run_makeVariables.out INPUT_DIR PROCESS OUTPUT_DIR 0 0 0 0
```

### Verify FR file with Python
```python
import ROOT
f = ROOT.TFile.Open("fakeRateInPtEtaProng.root")
g = f.Get("data_eta_0_4_prong1")
for i in range(g.GetN()):
    x, y = ROOT.Double(), ROOT.Double()
    g.GetPoint(i, x, y)
    print(f"Point {i}: x={x}, y={y}")
```

## Data Paths

### XGB080 Test (current)
- OS: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v95XGB080testOS7/`
- MV: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v95XGB080testOS7/`

### TTBBtest Reference (working)
- OS: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/`
- MV: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/`

## Debug Output Added

### weightVarMaker.C
```cpp
if(m_entry < 5) {
    std::cout<<"[FR DEBUG] Entry "<<m_entry<<": eta="<<absEta<<", prong="<<tauProng<<", pt="<<jetPt<<", m_graphs.size="<<m_graphs.size()<<"\n";
}
ifFR = TTTT::getFRandError(m_graphs, absEta, tauProng, jetPt, nominal, errDown, errUp);
if(m_entry < 5) {
    std::cout<<"[FR DEBUG] ifFR="<<ifFR<<", nominal="<<nominal<<", errDown="<<errDown<<", errUp="<<errUp<<"\n";
}
```

### commenFunction.C getFRandError()
```cpp
static int debugCount = 0;
// Debug prints for graph matching, point index, and values
```

## Known Issues

1. TGraph y-values return 0 or garbage when accessed in C++
2. Python verification shows correct values - suggesting ROOT TFile handling issue
3. errUp shows garbage (100) while errDown shows reasonable values
