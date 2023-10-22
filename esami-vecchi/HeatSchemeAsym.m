function HeatSchemeAsym
    % condizioni iniziali

    N     = 101;
    eta   = 0.2;
    L     = 0.5;
    x     = linspace(0.0,L,N);
    dx    = x(2)-x(1);
    kappa = 10;
    dt    = (eta*dx^2)/kappa;
    tmax=1000*dt;
    t=0;
    
    % impulso di calore inziale
    T0     = 20;
    DeltaT = 80;
    T      = ones(N,1)*T0;
    T(1)   = T0+DeltaT;
    
    figure(1)
    Temperature=[];   %creazione vettore vuoto
    Tempi=[];
    while(t<tmax)
        T(N)=T0;                             %condizioni iniziali 
        T1 = T(1)+eta*(T(2)+T(2)-2*T(1));
        T(2:N-1) = T(2:N-1) +eta*(T(3:N)+T(1:N-2)-2*T(2:N-1)); %metodo iterativo esplicito utilizzando 
                                                           %calcolo
                                                           %vettoriale
        T(1)=T1;    %imposto la condizione sulla derivata  
        Temperature(end+1)=T(6);      %riempiamo gli array vuoti con il valore della temperatura a x fissato
        Tempi(end+1)=t;     %riempiamo con i valori del tempo
        plot(Tempi,Temperature)
        drawnow
       % plot(x,T)
       % drawnow     %disegno il plot in tempo reale 
        t=t+dt;
    end 
    
end