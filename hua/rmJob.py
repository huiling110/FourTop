
import subprocess

startID = 29166395.0
endID = 29166428.0
# for ijob range():

while startID<endID+1:
    iCommand = 'hep_rm {}'.format(startID)
    print( iCommand)
    subprocess.run( iCommand, shell=True)
    startID+=1
    

