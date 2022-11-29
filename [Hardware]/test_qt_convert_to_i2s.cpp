#include <QCoreApplication>

float t=0;
float dt=0.1;

float double_Pi = 6.283;
uint16_t m_frequency = 1;
float m_time=0;
float m_deltaTime = 0.01;
float m_amplitude = 32767.0;


int16_t readSample() {
    float angle = double_Pi * m_frequency * m_time;
    int16_t result = m_amplitude * sin(angle);
    m_time += m_deltaTime;
    return result;
}


int16_t bufo[25] = {12512,2323,555,5,55,5267,1234,1256,777,666,555,422,122,-22,-112,-1235,-26676,7777,-23,0,1123,0,0,0,0};
/// filles the data with 2 channels
size_t read(uint8_t *buffer, size_t bytes,size_t dreyf){
    size_t result = 0;
    int16_t *ptr = (int16_t*)buffer;
    for (int j=0;j < bytes/4;j++){
        int16_t sample = bufo[j+dreyf];
        *ptr++ = sample;
        *ptr++ = sample;
        result+=4;
    }
    return result;
}

void get_buffer(uint8_t * buff,uint16_t buff_size ){
    for(uint16_t i=0;i<buff_size*4;i+=4){
        qDebug()<<buff[i] << buff[i+1] << buff[i+2]<<buff[i+3];
    }
}

int main(int argc, char *argv[])
{

    uint8_t buffer[5];

    for(int i=0;i<25;i+=4){
        read(buffer,4,i);
        get_buffer(buffer,4);
    }



    return 0;
}
