//
//  EffectExtra.h
//  Additional Plugin Code
//
//  This file is a workspace for developing new DSP objects or functions to use in your plugin.
//
float cubed(float x){
    return x * x * x;
}

class MyBuffer{
public:
    
    void set(){
        iBufferSize = 0.5 * 192000; //0.5 secs at 192kHz. Use max as sample rate unknown and memory allocation is slow and expensive and thus should be avoided
        
        pfCircularBuffer = new float[iBufferSize];
        for(int s = 0; s < iBufferSize; s++){
            pfCircularBuffer[s] = 0; //initialising buffer values to 0 - writes over any data already there
        }
        
        iBufferWritePos = 0;
    }
    
    float process(float input, float dParameter){
     
        iBufferWritePos++;
        if(iBufferWritePos == iBufferSize)
            iBufferWritePos = 0;
        
        for(int c = 0; c < dParameter; c++)
        {
            iBufferReadPos =  (fSR * c)/1000 - iBufferWritePos;
            if(iBufferReadPos < 0)
                iBufferReadPos += iBufferSize;
        }
        
        pfCircularBuffer[iBufferWritePos] = input;
        
        fDelSig = pfCircularBuffer[iBufferReadPos];
        
        return fDelSig;
    }
    
private:
    float *pfCircularBuffer;
    int iBufferSize, iBufferWritePos;
    float fSR = getSampleRate();
    int iBufferReadPos = 0;
    float fDelSig = 0;
};


