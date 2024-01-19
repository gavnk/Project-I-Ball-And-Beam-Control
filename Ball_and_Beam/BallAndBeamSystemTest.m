% Ball & Beam 
m = 0.220;  % [kg] mass of the ball 220g
R = 0.04;  % [m] radius of the ball 4cm
g = -9.8;  % [m/s^2]acceleration due to gravity
L = 1.0;   % [m] Length of the Beam 1 m
d = 0.1;   % [m] the lever offset, or the length of the lever 10cm
J = 1.416e-4;  %Polar Moment of inertia of the ball [m^4]  /// I = 2/5 mr^2
s = tf('s');  %  creates special variable s can be used to create a continuous-time transfer function model.
Pos_ball = -m*g*d/L/(J/R^2+m)/s^2 %transfer function

%PID variables
%Proportional
Kp =5;
%Integral
Ki =0;
%Derivative
Kd =10;

C =pid(Kp,Ki,Kd);
sys_cl=feedback(C*Pos_ball,1); %pid terms muliplied with function pos_ball
step(0.40*sys_cl,'b')  %setpoint 0.40 [m]
axis([0 8 0 0.5])

%step(Pos_ball,'b')
title('Ball & Beam Step Response ');
xlabel('time');
ylabel('Position (m)');