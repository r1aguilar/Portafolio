R = 12500; %// radius
H = 5426; %// height
N = 100; %// number of points to define the circumference

altura = 5426;
k = -0.03;
dt = 0.1;
iter = 800;
explosiones = 100;

xvel=randi([-300 300], 50,explosiones);
yvel=randi([0 300], 50,explosiones);
zvel=randi([-300 300], 50,explosiones);
masa = randi([1 2000], 50,explosiones);

for i = 1:explosiones
 
Rx = zeros(50,iter);
Ry = zeros(50,iter);
Ry(:,1) = altura;
Rz = zeros(50,iter);
 
Vx = zeros(50,iter);
Vx(:,1) = xvel(:,i);
Vy = zeros(50,iter);
Vy(:,1) = yvel(:,i);
Vz = zeros(50,iter);
Vz(:,1) = zvel(:,i);

m = masa(:,i);
 
A = @(v,m) -k.*v./m;
Ay = @(v,m)-9.8+(((-k).*v)./m);

% Calcular las trayectorias
for i = 1:iter

    Vx(:,i+1) = Vx(:,i) + A(Vx(:,i),m).*dt;

    Rx(:,i+1) = Rx(:,i) + Vx(:,i).*dt;

    Vy(:,i+1) = Vy(:,i) + Ay(Vy(:,i),m).*dt;

    Ry(:,i+1) = Ry(:,i) + Vy(:,i).*dt;

    Vz(:,i+1) = Vz(:,i) + A(Vz(:,i),m).*dt;

    Rz(:,i+1) = Rz(:,i) + Vz(:,i).*dt;
end

Ry(Ry<0)=NaN;

magnitud = @(x,z) sqrt(x^2+z^2);

magnitudes = zeros(50,1);



for i = 1:50
    RysinNan = Ry(i,:);
    RysinNan = ~isnan(RysinNan);
    RysinNan = RysinNan(RysinNan>0);
    magnitudes(i,1) = magnitud(Rx(i,length(RysinNan)),Rz(i,length(RysinNan)));
    puntox = Rx(i,length(RysinNan));
    puntoz = Rz(i,length(RysinNan));
    if magnitudes(i,1) > 12500
    plot(puntox,puntoz,"r*")
    hold on
    end
end    

[x, y, z] = cylinder([R,0], N);
surf(x,y,H*z,"FaceColor","r")

end