{
S->SetLineColor(kBlack);
S->Draw("t","z==25 && Pol==3");
S->SetLineColor(kRed);
S->Draw("t","z==25 && Pol==1","SAME");
S->SetLineColor(kBlue);
S->Draw("t","z==25 && Pol==2","SAME");
}
