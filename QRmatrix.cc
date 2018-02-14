{
 //set matrix
  size_t N =3;
  TMatrixD origin(N,N);
  TMatrixD a(N,N); TMatrixD b(N,N);
  TArrayD data(N*N);  
  double array[N*N] = {12,-51,4,6,167,-68,-4,24,-41}; 
  for(int i =0;i<N*N;i++)
  {
   data[i] = array[i];
  }
  origin.SetMatrixArray(data.GetArray());
  a = origin; b = origin;
  TDecompLU lu(a);
  TDecompQRH qr(b);

   if (!lu.Decompose()) {
      cout << "Decomposition failed, matrix singular ?" << endl;
      cout << "condition number = " << = a.GetCondition() << endl;
   } 
   else {
      lu.Invert(a);
      qr.Invert(b); 
      cout <<"LU composition"<<endl;
      Double_t d1_lu; Double_t d2_lu;
      lu.Det(d1_lu,d2_lu);
      Double_t det3 = d1_lu*TMath::Power(2.,d2_lu);
     // TMatrixD U3(H3,TMatrixD::kMult,H_square);
     // TMatrixDDiag diag3(U3); diag3 = 0.0;
     // const Double_t U3_max_offdiag = (U3.Abs()).Max();
//      cout << "  Maximum off-diagonal = " << U3_max_offdiag << endl;
      cout << "  Determinant          = " << det3 <<endl;
      a.Print();
      cout <<"QR composition"<<endl;
      b.Print();
   }

  TMatrixD I = origin*a;
  I.Print();
}
