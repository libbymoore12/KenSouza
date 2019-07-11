function [] = BalloonShield(textfile)
data = load(textfile);
time = data(:,1)/1000;
Temp1F = data(:,2);
RH = data(:,4);
Pres = data(:,5);
AccX = data(:,6);
AccZ = data(:,7);

figure
subplot(2,2,1)
plot(time,Temp1F);
title('Temperature')
xlabel('Time (s)')
ylabel('Temperature (deg F)')

subplot(2,2,2)
plot(time,RH);
title('Relative Humidity')
xlabel('Time (s)')
ylabel('Relative Humidity')

subplot(2,2,3)
plot(time,Pres);
title('Pressure')
xlabel('Time (s)')
ylabel('Pressure (psi)')

subplot(2,2,4)
plot(time,AccX);
hold on
plot(time,AccZ);
title('Acceleration')
xlabel('Time (s)')
ylabel('Acceleration (g''s)')
legend('X','Z')

figure
plot(time,Pres);
title('Pressure')
xlabel('Time (s)')
ylabel('Pressure (psi)')


end
