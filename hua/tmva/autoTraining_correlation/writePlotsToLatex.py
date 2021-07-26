
import sys
import os


def main():
    resultsDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v2/results/'
    channel = 3
    #  resultsDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v1/results/'
    #  channel = 2
    #  resultsDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau2l_v2/results/'
    #  channel = 4
    #  resultsDir = '/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/1tau1l_v2/results/'
    #  channel = 1
    isSP = True
    filename = '/workfs2/cms/huahuil/slides/tauOfTTTT/plots/2021_4-6/HuilingReport_MVA20210726.tex'
    fileout = '/workfs2/cms/huahuil/slides/tauOfTTTT/plots/2021_4-6/HuilingReport_MVA20210726.tex'
     
    allPlots = os.listdir( resultsDir )
    allPlots.sort()
    #  print(allPlots)
    plotPairList = getPlotFromList( allPlots, isSP )
                
    print(plotPairList)


    with open(filename, 'r+') as file:
        lines = file.readlines()
    
    sectionIndex = getInsertIndex( lines, isSP, channel )
    

    for pair in plotPairList:
        if isSP:
            addSPtoList( pair, sectionIndex, lines, resultsDir)
            sectionIndex = sectionIndex +25
        if not isSP:
            addLinesToList( pair, sectionIndex, lines, resultsDir )
            sectionIndex = sectionIndex + 15
    #  print( lines )

    with open(fileout, 'w+') as fileOut:
        fileOut.writelines(lines)


def getInsertIndex( lines, isSP , channel):
    index = 0
    sectionIndex = 0
    for iline in lines:
        if channel ==1:
            if isSP:
                if 'subsection' in iline and '1tau1l' in iline :
                    sectionIndex = index
            if not isSP:
                if 'section' in iline and '1tau1l' in iline :
                    print( iline )
                    sectionIndex = index
        if channel ==2:
            if isSP:
                if 'subsection' in iline and '1tau2os' in iline :
                    sectionIndex = index
            if not isSP:
                if 'section' in iline and '1tau2os' in iline :
                    print( iline )
                    sectionIndex = index
        if channel ==3:
            if isSP:
                if 'subsection' in iline and '2tau1l' in iline :
                    sectionIndex = index
            if not isSP:
                if 'section' in iline and '2tau1l' in iline :
                    print( iline )
                    sectionIndex = index
        if channel ==4:
            if isSP:
                if 'subsection' in iline and '1tau2l' in iline :
                    sectionIndex = index
            if not isSP:
                if 'section' in iline and '1tau2l' in iline :
                    print( iline )
                    sectionIndex = index
        index = index + 1
    if sectionIndex == 0:
        print('have not find the section')
        sys.exit()
    return sectionIndex

def getPlotFromList( allPlots, isSP ):
    plotPairList = []
    #  vlistPlotPair = []
    iPair = []
    pngNum = 0
    for entry in allPlots:
        #  if entry.find( 'varibleList'):
        if not isSP:
            if ('varibleList' in entry) and ('.png' in entry):
                    pngNum = pngNum + 1
                    #  print( entry )
                    iPair.append( entry )
                    if len(iPair) == 2:
                        #  print( iPair )
                        #  plotPairList.append( iPair )
                        plotPairList.append( iPair.copy() )
                        iPair.clear()
        if isSP:
            if 'SP' in entry:
                iPair.append( entry )
                if len(iPair) == 4:
                    plotPairList.append( iPair.copy() )
                    iPair.clear()
    return plotPairList

def addLinesToList( pair, sectionIndex, lines, resultsDir ):
    lines.insert( sectionIndex+1, '\n')
    lines.insert( sectionIndex+2, '\\begin{frame}{}\n')
    lines.insert( sectionIndex+3, '  \\begin{columns}[b]\n')
    lines.insert( sectionIndex+4, '   \\column{.5\\textwidth}\n' )
    lines.insert( sectionIndex+5, '    \\centering\n' )
    lines.insert( sectionIndex+6, '    \\begin{figure}\n' )
    #  lines.insert( sectionIndex+7, '        \\includegraphics[width=.99\\textwidth]{/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/results/'+pair[0] + '}\n' )
    lines.insert( sectionIndex+7, '        \\includegraphics[width=.99\\textwidth]{'+ resultsDir +pair[0] + '}\n' )
    lines.insert( sectionIndex+8, '    \\end{figure}\n' )
    lines.insert( sectionIndex+9, '    \\column{.5\\textwidth}\n' )
    lines.insert( sectionIndex+10, '    \\centering\n' )
    lines.insert( sectionIndex+11, '    \\begin{figure}\n' )
    #  lines.insert( sectionIndex+12, '        \\includegraphics[width=.99\\textwidth]{/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v2Resubmitv1/2tau1l_v1/results/' + pair[1] + '}\n' )
    lines.insert( sectionIndex+7, '        \\includegraphics[width=.99\\textwidth]{'+ resultsDir +pair[1] + '}\n' )
    lines.insert( sectionIndex+13, '    \\end{figure}\n'  )
    lines.insert( sectionIndex+14, '  \\end{columns}\n'  )
    lines.insert( sectionIndex+15, '\\end{frame}\n'  )
    #  lines.insert( sectionIndex+1,  )


def addSPtoList( pair, sectionIndex, lines, resultsDir ):
    lines.insert( sectionIndex+1, '\n')
    lines.insert( sectionIndex+2, '\\begin{frame}{Input lists}\n')
    lines.insert( sectionIndex+3, '  \\begin{columns}[b]\n')
    lines.insert( sectionIndex+4, '  \\column{.25\\textwidth}\n')
    lines.insert( sectionIndex+5, '      \\centering\n')
    lines.insert( sectionIndex+6, '      \\begin{figure}\n')
    lines.insert( sectionIndex+7, '      \\includegraphics[width=.9\\textwidth]{' + resultsDir + pair[0] + '}\n')
    lines.insert( sectionIndex+8, '      \\end{figure}\n')
    lines.insert( sectionIndex+9, '   \\column{.25\\textwidth}\n')
    lines.insert( sectionIndex+10, '      \\centering\n')
    lines.insert( sectionIndex+11, '      \\begin{figure}\n')
    lines.insert( sectionIndex+12, '      \\includegraphics[width=.9\\textwidth]{' + resultsDir + pair[1] + '}\n')
    lines.insert( sectionIndex+13, '      \\end{figure}\n')
    lines.insert( sectionIndex+14, '  \\column{.25\\textwidth}\n')
    lines.insert( sectionIndex+15, '      \\centering\n')
    lines.insert( sectionIndex+16, '      \\begin{figure}\n')
    lines.insert( sectionIndex+17, '      \\includegraphics[width=.9\\textwidth]{' + resultsDir + pair[2] + '}\n')
    lines.insert( sectionIndex+18, '      \\end{figure}\n')
    lines.insert( sectionIndex+19, '  \\column{.25\\textwidth}\n')
    lines.insert( sectionIndex+20, '      \\centering\n')
    lines.insert( sectionIndex+21, '      \\begin{figure}\n')
    lines.insert( sectionIndex+22, '      \\includegraphics[width=.9\\textwidth]{' + resultsDir + pair[3] + '}\n')
    lines.insert( sectionIndex+23, '      \\end{figure}\n')
    lines.insert( sectionIndex+24, '  \\end{columns}\n')
    lines.insert( sectionIndex+25, '\\end{frame}\n')


if __name__ == '__main__' :
    main()
