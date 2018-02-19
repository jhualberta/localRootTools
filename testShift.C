{
  TH1F h1("h1","",10,0,10);
  h1.SetBinContent(1,0);
  h1.SetBinContent(2,0);
  h1.SetBinContent(3,4);
  h1.SetBinContent(4,5);
  h1.SetBinContent(5,3);
  for(int i=6;i<=10;i++)
  h1.SetBinContent(i,0);
  h1.Draw();

  TH1F h2("h2","",10,0,10);
  int shift = 3;
  int ishift;
  if(shift<0) ishift=-1*shift;
  //else ishift = shift;
  for(int i=0;i<10+1;i++)
  {
   h2.SetBinContent(i,h1.GetBinContent(i+shift));
  }

  h2.SetLineColor(kRed);
  h2.Draw("same");
}
