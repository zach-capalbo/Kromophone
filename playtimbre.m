function [] = playtimbre (pitch, amplitudes, frequencies)
	t=linspace(0,1,48000/pitch); 
	d = 1/sum(amplitudes).*sum(amplitudes .* sin(frequencies*t*2*pi*1.0/min(frequencies))); 
	d2 = repmat(d, 1, pitch); 
	playaudio(d2',48000);
end
