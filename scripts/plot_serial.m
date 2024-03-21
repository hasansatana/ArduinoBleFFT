clear all
close all
% Create serial port object
s = serialport("COM10", 9600);
configureTerminator(s, "LF");

Testdata=0;


if(Testdata)
    datalen = 128;
else
    datalen=100;
end

% Initialize variables
timeBufferSize = datalen;  % Size of the time-domain data buffer
freqBufferSize = 64;   % Size of the frequency-domain data buffer
timeData = zeros(timeBufferSize, 1);  % Buffer to store time-domain data
freqData = zeros(freqBufferSize, 1);  % Buffer to store frequency-domain data
energy = 0;  
time = 0;

% Plot setup
figure;
h1 = plot(1:timeBufferSize, timeData, '-');
title('Time-domain Data');
xlabel('Sample');
ylabel('Value');


figure;
h2 = plot(1:freqBufferSize, freqData, '-');
title('Frequency-domain Data');
xlabel('Sample');
ylabel('Magnitude');


figure;
h3 = plot(1, energy, '-');
title('Energy');
xlabel('Update');
ylabel('Value');


% Synchronization series
syncSeries = 55555;

% Flag to indicate whether synchronization series is detected
syncDetected = false;
% Listen for data
while ishandle(h1)
    % Read line from serial port
    line = readline(s);
    % Check if synchronization series is detected
    if ~syncDetected && (str2double(line) == syncSeries)
        syncDetected = true;
    end
    
    % Continue filling arrays if synchronization series is detected
    if syncDetected
        % Read time-domain data
        for i = 1:timeBufferSize
            timeLine = readline(s);
            timeData(i) = str2double(timeLine);
        end

        % Read frequency-domain data
        for i = 1:freqBufferSize
            freqLine = readline(s);
            freqData(i) = str2double(freqLine);
        end

        % Read energy
        energyLine = readline(s);
        energy = str2double(energyLine);

        timeLine = readline(s);
        time = str2double(energyLine);

        % Update plots
        % Update time-domain plot
        set(h1, 'YData', timeData);

        % Update frequency-domain plot
        set(h2, 'YData', freqData);

        % Update energy plot
        set(h3, 'YData', energy);
        fprintf('Energy = %.3f\n',energy);

        fprintf('Elapsed time = .%3f us\n',time);
        % Pause to allow time for plot update
        drawnow;
    end
    syncDetected = false;
end

% Close serial port
clear s;