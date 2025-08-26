//switches
#define interruptPin PORTB.B0
#define streetPin PORTB.B7
//west   ports&pins
#define westDisplay PORTC
#define westRed PORTB.B1
#define westYellow PORTB.B2
#define westGreen PORTB.B3
//south ports&pins
#define southDisplay PORTD
#define southRed PORTB.B4
#define southYellow PORTB.B5
#define southGreen PORTB.B6
unsigned short westCounter = 0;
unsigned short southCounter = 0;
const int SEC = 1000;
int countDown[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23};
void InintialCOnfig(){
TrisB=Trisc=trisd=0;  //Set PORT B&C&D as Output
TrisB.b0=TrisB.b7=1; //set pins b0&b7 as input
INTE_Bit=GIE_Bit = 1;  //interrupt&Global interrupt enable
INTEDG_Bit = 1; //Interrupt On Rising Edge
}
void setwest(int red,int yellow,int green ){
westRed=red;westYellow=yellow;westGreen=green;
}
void setsouth(int red,int yellow,int green ){
southRed=red;
southYellow=yellow;
southGreen=green;
}
void interrupt(){
if(INTf_bit==1){ //interrupt on B0 bin
INTf_bit=0;   //reset flag pin  .
while(interruptPin==1){ //still in manual mode
        westDisplay=southDisplay=0;
        if(streetPin==1) {  //west street
        //can't call setwest and setsouth due to reentrancy isn't allowed
        westRed=0;westYellow=0;westGreen=1;
        southRed=1;southYellow=0;southGreen=0;
        }
        else if (streetPin==0){//south street
         westRed=1;westYellow=0;westGreen=0;
        southRed=0;southYellow=0;southGreen=1;
        }

}
             }
}
void FirstPhase(){//west >> green &south >>red for 20s
setwest(0,0,1);
setsouth(1,0,0);
for(westcounter=20,southcounter=23;westcounter>0;westcounter--,southcounter--){
westDisplay=countdown[westcounter];
southDisplay=countdown[southCounter];
delay_ms(SEC);
}

}
void SecondPhase(){//west>>yellow(after G) & south>>red for 3s
setwest(0,1,0);
setsouth(1,0,0);
for(westcounter=3,southcounter=3;southcounter>0;westcounter--,southcounter--){
       westDisplay=countdown[westcounter];
       southDisplay=countdown[southcounter];
       delay_ms(sec);
}
}
void ThirdPhase(){//west>>red & south>>yellow(after red) for 3 sec
setwest(1,0,0);
setsouth(0,1,0);
for(westcounter=15,southcounter=3;southcounter>0;westcounter--,southcounter--){
westDisplay= countDown[westcounter];
southDisplay=countdown[southcounter];
delay_ms(sec);                          }
}
void FourthPhase(){//west>>red & south>>green for 12 s
setwest(1,0,0);
setsouth(0,0,1);
for(westcounter=12,southcounter=12;southcounter>0;southcounter--,westcounter--){
westDisplay= countDown[westcounter];
southDisplay=countdown[southcounter];
delay_ms(sec);
}
}
void FifthPhase(){ //west>>yellow(after red) &south>>yellow (after green)for 3s
setwest(0,1,0);
setsouth(0,1,0);
for(westcounter=3,southcounter=3;southcounter>0;westcounter--,southcounter--){
westDisplay= countDown[westcounter];
southDisplay=countdown[southcounter];
delay_ms(sec);
}
}
void main(){
    InintialCOnfig();
    while(1){
    firstphase();
    SecondPhase();
    ThirdPhase();
    fourthphase();
    FifthPhase();
    }
}