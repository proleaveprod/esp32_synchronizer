import wave
import numpy


signalname = 'signal10ms_18k'

# Read file to get buffer                                                                                               
ifile = wave.open(f"{signalname}.wav")
samples = ifile.getnframes()
audio = ifile.readframes(samples)
print("samples=",samples);                                                                        
audio16bit = numpy.frombuffer(audio, dtype=numpy.int16)

print("\nData:")
a = 0 
for i in range(0,samples):
    print((audio16bit[i]),end='')
    if i!=samples-1:
        print(', ',end='')
    if a==8:
        print('\n')
        a=0
    a = a+1


if(samples>1024):
    print("WARNING!\nArray is larger than buffer")
    
else:
    print("\n\nAdd zeros to 1024")
    buffSamples = 1024




f = open(f'{signalname}.h', 'w')
f.write(f'#define WAV_SAMPLES {buffSamples}\n')
f.write(f'int16_t wav_array[WAV_SAMPLES] = ')
f.write('{')
f.write(f'          //Wav file - {signalname}\n')
a = 1 
for i in range(0,samples):
    print("i = ",i)
    f.write(str(audio16bit[i]))
    if i<samples:
        f.write(", ")
    if a==8:
        f.write('\n')
        a=0
    a = a+1



for i in range(0,1024-samples):
    f.write('0')
    if i<1024-samples-1:
        f.write(', ')
    if a==8:
        f.write('\n')
        a=0
    a = a+1

f.write('};')
f.close

