import pandas as pd

def makeplot(csv,b,b_unc,bcolor,s,scolor,scalesignal=1,plotname="myplot",cmslabel="WIP", data=True, lumi=16, year=2016):
    k=pd.read_csv(csv,index_col=0)
    
    for si in s:
        k[si+'x'+str(scalesignal)]=k[si]*scalesignal
    s=[si+'x'+str(scalesignal) for si in s]

    k['ttttx50']=k['tttt']*scalesignal
    b_color=bcolor
    s_color={}
    for ii,si in enumerate(s):
        s_color[si]=scolor[ii]
    k['uncert']=0
    k['b_sum']=0
    for unci in b_unc:
        k['uncert']=k['uncert']+(k[unci]*k[unci])
    for bi in b:
        k['b_sum']=k['b_sum']+(k[bi])
    k['uncert']=k['uncert']**(1/2)
    k['u_b']=(k['uncert']/k['b_sum'])
    k['data_MC']=k['data']/k['b_sum']

    k['r_uncert']=k['data_MC']*k['u_b']
    k['d_m']=k['data_MC'].round(2).astype(str)+' +/- '+k['r_uncert'].round(2).astype(str)
    
    
    import mplhep as hep

    hep.style.use("CMS")


    import matplotlib.pyplot as plt
    import seaborn as sns
    fig, ax = plt.subplots(2,sharex=True,gridspec_kw={'height_ratios': [5, 1]})
    ax1=ax[0]
    ax2=ax[1]
    #ax3=ax[2]
    hep.cms.label(cmslabel, data=data, lumi=lumi, year=year,ax=ax1)
    k[b].plot(color=b_color,stacked='True',ax=ax1,sort_columns='True',kind='bar')
    #k[b].plot(colors=[bcolor[key] for key in b_color.keys()],subplots=True,ax=ax3,sort_columns='True',kind='pie')
    k[s].plot(color=s_color,ax=ax1,kind='bar',alpha=1,facecolor='None',edgecolor=sns.color_palette("dark",24))
    ax1.errorbar(k.index, k['data'], yerr=k['data_uncert'], ecolor='k',fmt='.k',label='data')
    ax1.errorbar(k.index, k['b_sum'], lw=30,yerr=k['uncert'],fmt='none', ecolor='k',alpha=0.2,label='stat_unc')
    ax1.legend(loc="best",bbox_to_anchor=(1.01, 0.8))
    ax1.set_ylim(ymin=0)


    for ir in range(len(k)):
        ax1.text(ir-0.25,list(k.b_sum)[ir]+10,str(list(k.d_m)[ir]),rotation='horizontal',fontsize=15)

    ax2.errorbar(k.index, k['data']/k['b_sum'],yerr=k['r_uncert'],ecolor='k',fmt='.k',capsize=1,label='data/MC')
    ax2.grid('both')

    
    #

    ax2.legend(loc="best",bbox_to_anchor=(1.01, 0.8))
    ax2.set_xticklabels(labels=list(k.index), rotation=90)
    plt.tight_layout()
    plt.subplots_adjust(hspace=.05)
    plt.savefig(plotname+'.pdf')
    plt.savefig(plotname+'.png')