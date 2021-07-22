
import sys
import os


def main():
    resultsDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/results/'
     
    #  for entry in os.listdir( resultsDir ):
    allPlots = os.listdir( resultsDir )
    allPlots.sort()
    #  print(allPlots)
    plotPairList = []
    iPair = []
    pngNum = 0
    for entry in allPlots:
        #  if entry.find( 'varibleList'):
        if 'varibleList' in entry:
            #  print( entry )
            if '.png' in entry:
                pngNum = pngNum + 1
                #  print( entry )
                iPair.append( entry )
                if len(iPair) == 2:
                    #  print( iPair )
                    #  plotPairList.append( iPair )
                    plotPairList.append( iPair.copy() )
                    iPair.clear()
                
    print(plotPairList)


    filename = '/workfs2/cms/huahuil/slides/tauOfTTTT/plots/2021_4-6/HuilingReport_MVA20210722.tex'
    fileout = '/workfs2/cms/huahuil/slides/tauOfTTTT/plots/2021_4-6/HuilingReport_MVA20210722_add.tex'
        #  with open(filename, 'a') as file:
    with open(filename, 'r+') as file:
        lines = file.readlines()

        index = 0
        for iline in lines:
            if 'subsection' in iline and '2tau1l' in iline :
                print( iline )
                sectionIndex = index
            index = index + 1

    i=0
    for pair in plotPairList:
        if i == 0:
            i+=1
            addLinesToList( pair, sectionIndex, lines )
    print( lines )

    with open(fileout, 'w+') as fileOut:
        fileOut.writelines(lines)



def addLinesToList( pair, sectionIndex, lines):
    lines.insert( sectionIndex+1, '\n')
    lines.insert( sectionIndex+2, '\\begin{frame}{}\n')
    lines.insert( sectionIndex+3, '  \\begin{columns}[b]\n')
    lines.insert( sectionIndex+4, '   \\column{.5\\textwidth}\n' )
    lines.insert( sectionIndex+5, '    \\centering\n' )
    lines.insert( sectionIndex+6, '    \\begin{figure}\n' )
    lines.insert( sectionIndex+7, '        \\includegraphics[width=.99\\textwidth]{/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/results/'+pair[0] + '}\n' )
    lines.insert( sectionIndex+8, '    \\end{figure}\n' )
    lines.insert( sectionIndex+9, '    \\column{.5\\textwidth}\n' )
    lines.insert( sectionIndex+10, '    \\centering\n' )
    lines.insert( sectionIndex+11, '    \\begin{figure}\n' )
    lines.insert( sectionIndex+12, '        \\includegraphics[width=.99\textwidth]{/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/results/' + pair[1] + '}\n' )
    lines.insert( sectionIndex+13, '    \\end{figure}\n'  )
    lines.insert( sectionIndex+14, '  \\end{columns}\n'  )
    lines.insert( sectionIndex+15, '\\end{frame}\n'  )
    #  lines.insert( sectionIndex+1,  )





if __name__ == '__main__' :
    main()
