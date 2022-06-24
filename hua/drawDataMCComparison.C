
void drawDataMCComparison(){

    //get to data/mc ratio
    //fabio
    // hRatio = (TH1F*)h_DATA->Clone("Ratio") // for VR
    //hRatio->Divide(hBkg) 
    //??? this seems too simple, error bar would be wrong 
    // hRatio = (TH1F*)hBkg->Clone("Ratio") // "Ratio" is just the newname
    //TGraphAsymmErrors* gRatio = new TGraphAsymmErrors(hRatio->GetSize() - 2, Px, Py, Exl, Exr, Eyl, Eyh);


}


