import wave
import numpy


signalname = 'hl2_8k_int16'

# Read file to get buffer                                                                                               
ifile = wave.open(f"{signalname}.wav")
samples = ifile.getnframes()
audio = ifile.readframes(samples)
print("samples=",samples);

                                                                             
audio16bit = numpy.frombuffer(audio, dtype=numpy.int16)

print("max audio = ",max(audio16bit))
k = 32767/max(audio16bit)
audio16bit = numpy.frombuffer(audio16bit*k, dtype=numpy.int16)

print(max(audio16bit))




f = open(f'{signalname}.h', 'w')
f.write(f'#define WAV_SAMPLES {samples}\n')
f.write(f'int16_t signal_samples[WAV_SAMPLES] = ')
f.write('{                      //Wav-файл, преобразованный в массив\n')
a = 0 
for i in range(0,samples):
    f.write(str(audio16bit[i]))
    if i!=samples-1:
        f.write(', ')
    if a==8:
        f.write('\n')
        a=0
    a = a+1

f.write('};')
f.close

