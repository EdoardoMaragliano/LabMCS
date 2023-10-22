eps0=8.85*10^(-12);
N=100;
V=zeros(N,N);
rho=zeros(N,N);

%parametri fisici
L=100;                          %quadrato LxL ambiente
w=40;                           %lunghezza armature
d=10;                           %semidistanza armature
delta=L/N                      %spaziatura griglia
xin=(L-w)/(2*delta)+1;          %coord x inizio armatura
xfin=xin+w/delta;               %coord x fine armatura
y1=(L/2-d)/delta;               %coord y armatura 1
y2=(L/2+d)/delta;               %coord y armatura 2


%fisso la carica 
rho((xin+xfin)/2,y1)=5;
rho((xin+xfin)/2,y2)=-5;

t=0;
dt=0.0000001;
tend=100*dt;


err=zeros(N,N);
while(t<tend)
   
        Vold=V;
        %non aggiorno n=1 e n=N perché V(infinito)=0
        V(2:N-1,2:N-1)=1/4.*(Vold(3:N,2:N-1)+Vold(1:N-2,2:N-1)+Vold(2:N-1,1:N-2)+Vold(2:N-1,3:N))+(1/(4*pi*eps0))*rho(2:N-1,2:N-1)*delta^2;
        drawnow;
        t=t+dt;
        
  
end;
figure(1)
surfc(V);               %%surfc fa il grafico 3d della superficie
figure(2)
[Ex,Ey]=gradient(V);
quiver(-Ex,-Ey,'b');    %%quiver grafica il campo vettoriale
hold on
contour(V)
axis equal
hold off
figure(3)
