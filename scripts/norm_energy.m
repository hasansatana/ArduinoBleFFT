len =128;
f = 5; %hz
fs = 100;
t = 0:1/fs:len*1/fs -1/fs;

frames = sin(2*pi*f*t);
figure; plot(frames)
stft_frames = fft(frames,len);

figure; plot(abs(stft_frames(1:len/2)))

energy = abs(stft_frames).^2;
normalized_energy = sum(energy)/ (numel(frames)^2);
fprintf('Norm Energy = .%3f\n',normalized_energy);



