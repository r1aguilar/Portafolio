% Asignar variables
clear;
clc;

R = 12500; %// radius
H = 5426; %// height
N = 100; %// number of points to define the circumference

y = 5426;
k = -0.03;
dt = 0.1;
iter = 10000;

xvel=randi([-300 300], 50,1);
yvel=randi([0 300], 50,1);
zvel=randi([-300 300], 50,1);
 
m = randi([1 2000], 50,1);
 
Rx = zeros(50,iter);
Ry = zeros(50,iter);
Ry(:,1) = y;
Rz = zeros(50,iter);
 
Vx = zeros(50,iter);
Vx(:,1) = xvel;
Vy = zeros(50,iter);
Vy(:,1) = yvel;
Vz = zeros(50,iter);
Vz(:,1) = zvel;
 
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


filtro = (R-sqrt(Rx.^2+Rz.^2))*H/R;
filtro = filtro<=Ry;

Rx = Rx.*filtro;
Ry=Ry.*filtro;
Rz = Rz.*filtro;
Ry(Ry==0)=NaN;
Rx(Rx==0)=NaN;
Rz(Rz==0)=NaN;

for i =1:50
    plot3(Rx(i,:),Rz(i,:),Ry(i,:))
    hold on
end

[x, y, z] = cylinder([R,0], N);
surf(x,y,H*z,"FaceColor","r")

