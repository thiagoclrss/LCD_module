#include<p18f4520.h>

#define RS LATCbits.LATC5
#define RW LATCbits.LATC6
#define E LATCbits.LATC7
#define lcd LATD

void delay_s(int s);
void delay_ms(int ms);
void iniciaLCD(int a);
void enviaComando(char comando);
void enviaComando4(char comando);
void enviaDado(char dado);
void enviaDado4(char dado);
void clear();


void delay_s(int s){
    
    int i;
    for(;s>0;s--){
        delay_ms(1001);
        for(i=0;i<60;i++){}
    }
}

void delay_ms(int ms){
  
    unsigned int i;
    for (;ms>0;ms--){
        for(i=0;i<131;i++){}
    }
}

void iniciaLCD(int a){
    if (a==4){
        
        delay_s(1);
        enviaComando(0b00100000);//
        enviaComando(0b00100000);//function set
        enviaComando(0b10000000);//
        
        enviaComando(0b00000000);// display on/off
        enviaComando(0b11100000);//

        enviaComando(0b00000000);//
        enviaComando(0b00010000);//display clear
    } 
    else if(a==8){

        delay_s(1);
        enviaComando(0b00111000);
        enviaComando(0b00001110);
        enviaComando(0b00000001);

    }
}

void enviaComando(char comando){

    RS=0; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)

    lcd = comando;
    E=1;
    E=0; //pulso de habilitação do lcd
    delay_ms(2); //delay pedido no datasheet do lcd
}

void enviaComando4(char comando){

    RS=0; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)
    lcd= comando;
    E=1;
    E=0;
    delay_ms(2);

    comando=(comando<<4);
    
    RS=0;
    RW=0;
    E=0;
    lcd= comando;
    E=1;
    E=0;
    delay_ms(2);
}

void enviaDado(char dado){

    RS=1; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)

    lcd = dado;
    E=1;
    E=0; //pulso de habilitação do lcd
    delay_ms(2); //delay pedido no datasheet do lcd

}

void enviaDado4(char dado){

    RS=1; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)
    lcd = dado;
    E=1;
    E=0; //pulso de habilitação do lcd
    delay_ms(2);    

    dado=(dado<<4); //os lowers bits são deslocados para a esquerda e passam a ser nível alto

    RS=1; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)
    lcd = dado; 
    E=1;
    E=0; //pulso de habilitação do lcd
    delay_ms(2);
}


void clear(){

    RS=0; //0 - set para funções do led; 1 - set para dado
    RW=0; //0 - set para escrita; 1 - set para leitura
    E=0; // comando é enviado na transição de descida do cloko(1--0)

    lcd = 0b00000001;
    E=1;
    E=0; //pulso de habilitação do lcd
    delay_ms(1);

}


void main(void){
    
    TRISCbits.RC5 = 0; //RS
    TRISCbits.RC6 = 0; //RW
    TRISCbits.RC7 = 0; //E
    TRISD = 0b00000000;//lcd

    iniciaLCD(4);

    while(1){
        enviaComando4(0xc0); //aqui eu mando para o endereço
        enviaDado4('T'); //0x54 ou 0b01010100
        enviaDado4('H');
        enviaDado4('I');
        enviaDado4('A');
        enviaDado4('G');
		enviaDado4('O');
        //enviaDado('');
		delay_s(1);
    }

    return 0;
}