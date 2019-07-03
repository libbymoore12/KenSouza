function [] = DemoSatRead(textfile)
data = load(textfile);

time = data(:,1);
Voltage = data(:,2);
SoC = data(:,3);
MQ137 = data(:,4);
MQ135 = data(:,5);
TempA = data(:,6);
TempB = data(:,7);
PressA = data(:,8);
PressB = data(:,9);
RH = data(:,10);
AccelX = data(:,11);
AccelY = data(:,12);
AccelZ = data(:,13);

a=4;
b=2;
figure
subplot(a,b,1)
plot(time,Voltage);
title('Voltage')
xlabel('Time (s)')
ylabel('Voltage (V)')

subplot(a,b,2)
plot(time,SoC);
title('State of Charge')
xlabel('Time (s)')
ylabel('State of Charge (%)')

subplot(a,b,3)
plot(time,MQ137);
hold on
plot(time,MQ135);
title('Ammonia Concentration')
xlabel('Time (s)')
ylabel('Ammonia Concentration (PPM)')
legend('MQ137','MQ135')

subplot(a,b,4)
plot(time,TempA);
hold on
plot(time,TempB);
title('Temperature')
xlabel('Time (s)')
ylabel('Temperature (F)')
legend('TempA','TempB')

subplot(a,b,5)
plot(time,PressA);
hold on
plot(time,PressB);
title('Pressure')
xlabel('Time (s)')
ylabel('Pressure (psi)')
legend('PressA','PressB')

subplot(a,b,6)
plot(time,RH);
title('Relative Humidity')
xlabel('Time (s)')
ylabel('Relative Humidity (%)')

subplot(a,b,7)
plot(time,AccelX);
hold on
plot(time,AccelY);
hold on
plot(time,AccelZ);
title('Acceleration')
xlabel('Time (s)')
ylabel('Acceleration (g''s)')
legend('X','Y','Z')

end
