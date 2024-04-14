import ROOT 

input = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/crabNanoPost_2022preEE_v3/mc/TTTT/tree_1.root'

df = ROOT.RDataFrame('Events', input)


ROOT.gInterpreter.Declare("""
bool containsValue5(const ROOT::VecOps::RVec<int>& vec) {
    for (auto el : vec) {
        if (el == 5) return true;
    }
    return false;
}
""")
df = df.Define("contains5", "containsValue5(Tau_genPartFlav)")
genTau_f = df.Filter("contains5")

initial_event = df.Count().GetValue()
genTau_event = genTau_f.Count().GetValue()

print('allEvent=', initial_event, ' >=1genTau=', genTau_event, 'eff=', genTau_event/initial_event)