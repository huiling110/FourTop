
import pandas as pd

genSum2016pre = 'genWeightCSV/genSum_2016preVFP.csv'
genSum2016post = 'genWeightCSV/genSum_2016postVFP.csv'

df1 = pd.read_csv( genSum2016pre )
df2 = pd.read_csv( genSum2016post )

df3 = df2.copy()
df3 = df3.join( df1['2016preVFP'])

df3['2016']=df3['2016preVFP']+df3['2016postVFP']

print(df3)

df3.to_csv( 'genWeightCSV/genSum_2016.csv')
