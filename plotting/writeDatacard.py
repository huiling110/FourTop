import os
import usefulFunc as uf
import ttttGlobleQuantity as gq

MCSys = {
    #sys: [isCorrelated, whichProces] ; whichProcess=0: mc; whichProcess=1: fakeTau, whichProcess=2: fakeLepton
    'CMS_pileup': [True, 0],
    'CMS_prefiring': [True, 0],
    'CMS_eff_t_vsMu': [False, 0], #uncorrelated
    'CMS_eff_t_vsEle': [False, 0], #need to add era to the name
    'CMS_eff_t_vsJet_stat1_dm0': [False, 0],
    'CMS_eff_t_vsJet_stat1_dm1': [False, 0],
    
}



def main():
   channel = '1tau1l'
   inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
   
   inputDir = os.path.dirname(inputTemplate) 
   outDir = inputDir + 'datacardSys/'
   uf.checkMakeDir(outDir)
   outCard = f"{outDir}datacard_{channel}.txt"
    
   processes = gq.proChannelDic[channel]
   print(processes)

   
def write_shape_datacard(output_file, root_file, channel_name, processes, rates, systematics):
    """
    Write a shape datacard for CMS Combine.

    Parameters:
    - output_file: Name of the text file to write the datacard to.
    - root_file: Name of the ROOT file containing histograms.
    - channel_name: Name of the analysis channel.
    - processes: List of process names (e.g., ["signal", "background1", "background2"]).
    - rates: List of initial expected rates for each process.
    - systematics: Dictionary of systematic uncertainties structured as:
      { "uncertainty_name": (type, { "process_name": ("up_modifier", "down_modifier") }) }
      Example: { "lumi": ("lnN", {"background1": (1.10, 0.90) }) }
    """

    num_processes = len(processes)
    signal_index = 0  # Assuming the first process is the signal

    lines = [
        "imax 1  number of channels",
        "jmax {}  number of background processes".format(num_processes - 1),
        "kmax *  number of nuisance parameters (sources of systematic uncertainties)",
        "---------------",
        f"shapes * {channel_name} {root_file} $PROCESS $PROCESS_$SYSTEMATIC",
        "---------------",
        f"bin         {channel_name}",
        "observation -1",
        "---------------",
        "bin                        " + " ".join([channel_name] * num_processes),
        "process                   " + " ".join(processes),
        "process                   " + " ".join(str(i - signal_index) for i in range(num_processes)),
        "rate                      " + " ".join(f"{rate:.3f}" for rate in rates),
        "---------------"
    ]

    for unc_name, (unc_type, uncertainties) in systematics.items():
        line = f"{unc_name}   {unc_type}   "
        line += " ".join(
            f"{uncertainties[proc][0]:.3f}/{uncertainties[proc][1]:.3f}" if proc in uncertainties else "-"
            for proc in processes
        )
        lines.append(line)

    # Write to file
    with open(output_file, 'w') as f:
        for line in lines:
            f.write(line + "\n")
    print(f"Datacard written to {output_file}")

if __name__=='__main__':
    main()