%Considerare una sbarretta di lunghezza L. Al tempo t = 0 si dà  un impulso di temperatura T0 al centro e 
%si osservi l'andamento di temperatura nella sbarra per un tempo t1 con estremi fissati a T1 = T0/10.
%Successivamente si lascia libero uno degli estremi dal termostato, mantenendo però la derivata nulla; 
%analizzare l'andamento della temperatura fino a 2*t1. Graficare l'andamento della temperatura del punto 
%a 3/4L in funzione del tempo.

function HeatScheme
    % Parametri fisici
    eta = 0.2; L = 0.5; kappa = 10; 
    N = 101; x = linspace(0.0,L,N);
    dx = x(2)-x(1); dt = (eta*dx^2)/kappa; 
    DeltaT = 80;                %spike iniziale
    T0 = DeltaT/10;             %temperatura del termostato
    T = ones(N,1)*T0; T((N-1)/2+1) = T0+DeltaT; %impulso centrale
    % Evoluzione
    t =0; 
    t1 = 500*dt;
    
     v=ones(N-2,1)*(2/eta+2);    %la matrice è N-2 x N-2
     w=ones(N-3,1)*(-1);         %le diag secondarie hanno 1 elemento in meno
     m1=diag(v,0);
     m2=diag(w,1);
     m3=diag(w,-1);
     m=m1+m2+m3;
    
     B=ones(N-2,1);
     
    while t<t1
     %impongo le condizioni al contorno   
        T(N) = T0;  %sbarretta termostatata agli estremi
        T(1) = T0;
        % ... (Cranck-Nicholson o inv. matrice)
        
       B=T(1:N-2)+(2/eta-2)*T(2:N-1)+T(3:N);
       B(1)=B(1)+T(1);      %setto i valori agli estremi
       B(N-2)=B(N-2)+T(N);

        T(2:N-1)= inv(m)*B;     %aggiorno T tranne agli estremi
        
        %%fuzione teorica
        sigma = 2*kappa*t
        gauss= T0 + (DeltaT*dx)/sqrt(2*pi*sigma) * exp(-(x-0.5*L).^2/(2*sigma));    
        
         plot(x,T);
         hold on
         plot(x,gauss);
         hold off
         
         drawnow limitrate %cercare parametri per rendere meno lenta la visualizzazione pause(0.0001)
        t = t+dt; 
    end
    
    %ora dovrei rimuovere il termostato e imporre le condizioni di
    %Dirichlet
end