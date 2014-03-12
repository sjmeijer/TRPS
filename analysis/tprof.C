//Prepares a quick and dirty box plot for time profile comparisons
//from TRPS output trees
//
void PlotTimeProfile( TTree* S )
{
	TCanvas* c1 = new TCanvas("tprof",600,900);
	
	c1->cd(1);
	S->Draw("t:Pol","x==-25","BOX");
	c1->cd(2);
	S->Draw("t:Pol","x==25","BOX");
	c1->cd(3);
	S->Draw("t:Pol","y==-25","BOX");
	c1->cd(4);
	S->Draw("t:Pol","y==25","BOX");
	c1->cd(5);
	S->Draw("t:Pol","z==-25","BOX");
	c1->cd(6);
	S->Draw("t:Pol","z>24.9","BOX");
}
