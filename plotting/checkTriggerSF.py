import random
import ROOT

def generate_pairs_with_sum_one(n=1000):
    pairs = []
    for _ in range(n):
        first_number = random.random()  # Generate a random float between 0 and 1
        second_number = 1 - first_number  # Calculate the second number so that the sum is 1
        pairs.append((first_number, second_number))
    return pairs

def plot(sfList):
    hist = ROOT.TH1F("hist", "Distribution of Floats", 20, 0.952, 0.954)
    for value in sfList:
        hist.Fill(value)

    canvas = ROOT.TCanvas("canvas", "Canvas for plotting", 800, 600)
    hist.Draw()
    canvas.SaveAs('sf.png')


def main():
   
    # p1p2List = [[0.1, 0.9], [0.2, 0.8], [0.3, 0.7], [0.4, 0.6], [0.5,0.5]]
    p1p2 = [0.8, 0.2]

    p1p2List = generate_pairs_with_sum_one(100000) 
    sfList = []
    for ipair in p1p2List:
        # isf=getSFAverage(ipair[0], ipair[1], True)
        isf=getSFAverage(ipair[0], ipair[1], False)
        sfList.append(isf)
    
    plot(sfList)
    
def getSFAverage(p1, p2, ifPrint=False):
    e1MC = 0.84
    e1Data = 0.8
    e2MC = 0.86
    e2Data = 0.82
    sf1 = e1Data/e1MC
    sf2 = e2Data/e2MC
    sf = ((p1*e1Data) + (p2*e2Data)) / ((p1*e1MC)+(p2*e2MC))
    
    if ifPrint:
        print('sf1={:.4f} sf2={:4f}'.format(sf1, sf2))
        message = 'sfAverage={:.4f}   p1={:.3f} p2={:.3f}'.format(sf, p1, p2)
        print(message, '\n')
    return sf
    
if __name__=='__main__':
    main()
     