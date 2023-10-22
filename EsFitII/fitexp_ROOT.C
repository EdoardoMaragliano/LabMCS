void fitexp_ROOT(){

  TTree tree;
  tree.ReadFile("exp.dat","t");

  TF1 f("f","1/[0]*exp(-x/[0])",0,10);
  f.SetParameter(0,1);
  tree.UnbinnedFit("f","t");

}
