#include <QCoreApplication>

#define SAMPLES 55
#define CBUFF   29

uint8_t buff[CBUFF]={0};

int16_t samples[SAMPLES]={0};//{0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                          //0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
                          //0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2B,0x2C,0x2D,0x2E,0x2F};//,0x4,-0x1};
int smp_cnt=0;

uint32_t reading(uint8_t *buffer,int len){
            size_t result = 0;
            int16_t *ptr = (int16_t*)(buffer);

            for (int j=0;j<len;j++){
                int16_t sample = samples[j+smp_cnt];
                *ptr++ = sample;
                *ptr++ = sample;
                result+=4;
            }
            smp_cnt+=len;
            if(smp_cnt>SAMPLES){
                smp_cnt=0;
                //qDebug()<<"разброс: "<<smp_cnt-SAMPLES;
            }

            return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    for(int i=0;i<SAMPLES;i++){
        samples[i]=i;
        //qDebug()<<"s:"<<samples[i];
    }
    uint32_t len = reading(buff,CBUFF);
    qDebug()<<"---info1 :"<< len;
    for(int i=0;i<len;i+=4){
        qDebug()<<buff[i] << buff[i+1] << buff[i+2] << buff[i+3];
    }

    len = reading(buff,CBUFF);
    qDebug()<<"---info2 :"<< len;
    for(int i=0;i<len;i+=4){
        qDebug()<<buff[i] << buff[i+1] << buff[i+2] << buff[i+3];
    }



    return a.exec();
}


