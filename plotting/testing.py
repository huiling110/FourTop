import ROOT

def compute_branch_means_with_rdataframe(root_file_path, tree_name, branch_names):
    # Create a RDataFrame for the specified tree
    df = ROOT.RDataFrame(tree_name, root_file_path)

    # Dictionary to store means
    branch_means = {}

    # Calculate means for each branch
    for branch_name in branch_names:
        # Use the Mean method to compute the mean of the branch
        mean_result = df.Mean(branch_name)
        branch_means[branch_name] = mean_result.GetValue()

    
    # return branch_means
    print(root_file_path)
    print(branch_means)
    print('\n')

branchesToCheck = ['btagShape_weight', 'btagShapeR', 'btagWPMT_weight', 'HLT_weight', 'tauT_IDSF_weight_new', 'EVENT_genWeight', 'jets_num']

# inputNominal = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/tttt.root'
inputNominal = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/tttt.root'
compute_branch_means_with_rdataframe(inputNominal, 'newtree', branchesToCheck)

# inputUp = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1FixedBtagWeightWhenJES_JESup_0_v89HadroPre_JESPt22/mc/tttt.root'
inputUp = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1FixedBtagWeightWhenJES_JESup_0_v89HadroPre_JESPt22/mc/tttt.root'
compute_branch_means_with_rdataframe(inputUp, 'newtree', branchesToCheck)
# inputDown = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1FixedBtagWeightWhenJES_JESDown_0_v89HadroPre_JESPt22/mc/tttt.root'
inputDown = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1FixedBtagWeightWhenJES_JESDown_0_v89HadroPre_JESPt22/mc/tttt.root'
compute_branch_means_with_rdataframe(inputDown, 'newtree', branchesToCheck)