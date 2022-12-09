import wave
import numpy


signalname = 'signal10ms_18k'

# Read file to get buffer                                                                                               
ifile = wave.open(f"{signalname}.wav")
samples = ifile.getnframes()
audio = ifile.readframes(samples)
print("samples=",samples);   

i=0
while(i!=480*2):
    print(int((i/2)+1),":",audio[i],"",audio[i+1],"\n")
    i+=2



f = open(f'{signalname}8bit.h', 'w')
f.write(f'#define WAV_SAMPLES {1024}\n')
f.write(f'uint8_t wav_array8bit[WAV_SAMPLES] = ')
f.write('{')
f.write(f'          //Wav file - {signalname}\n')
a = 1 


for i in range(0,samples*2):
    #print("i = ",i)
    f.write(str(audio[i]))
    if i<samples*2:
        f.write(", ")
    if a==2:
        f.write('\n')
        a=0
    a = a+1



for i in range(0,1024-samples*2):
    f.write('0')
    if i<1024-samples*2-1:
        f.write(', ')
    if a==2:
        f.write('\n')
        a=0
    a = a+1

f.write('};')
f.close

