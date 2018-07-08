sbit LCD_RS at P2_0_bit;
sbit LCD_EN at P2_1_bit;
sbit LCD_D4 at P2_2_bit;
sbit LCD_D5 at P2_3_bit;
sbit LCD_D6 at P2_4_bit;
sbit LCD_D7 at P2_5_bit;
 //////// counter ///////////
  char message1[]="Attend:";
  char c0='0',c1='0',c2='0';
  char if1,if2;
/////////////counter end //////

//////////////timer //////////////
           //set time limit here
unsigned char m0='2',m1='3',s0='9',s1='5';  //m1m0:s1s0
unsigned char timerMessage[]="Time: ";
////////////timer end///////////
void refreshLcd(void);
void cct_init(void);
void InitINT0(void);
//void display_int(void);
void  checkLights(void);
void count(void);

void main (void){
     cct_init();  //initialize interrupt
     InitINT0();
  p0=0xff;
  lcd_init();
  lcd_cmd(_LCD_CLEAR);
  lcd_cmd(_LCD_CURSOR_OFF);
  
  lcd_out(1,2,message1);
  lcd_out(2,2,timerMessage);
  lcd_chr(1,13,c0);
  lcd_chr(1,12,c1);
  lcd_chr(1,11,c2);
  

  count();
   do{



     count();
     refreshLcd();
     delay_ms(1000);  ///this delay will control timer

  } while(1);



}


/****************control lights end here ************/

/************* timer functions *************/

  void refreshLcd(){
          p2=~p2;
          s0--;
          if(s0<'0'){
             s0='9';
             s1--;
             if(s1<'0'){
               s1='5';
               m0--;
               if(m0<'0'){
                 m0='9';
                 m1--;
                 if(m1<'0'){
                   m0=m1=s0=s1='1';
                 }
               }
             }
          }

          lcd_chr(2,11,m1);
          lcd_chr(2,12,m0);
          lcd_chr(2,13,':');
          lcd_chr(2,14,s1);
          lcd_chr(2,15,s0);
  }
  
/*****************timer function end here **********/
/************control lights*******/
void  checkLights(){
      if(c0=='0' & c1=='0' & c2=='0'){
         p0=0xff;
      }
      else if(c0>'0' & c1=='0'){
        p0=0xfe;
      }
      else if(c1=='1'){
        p0=0xfc;
      }
      else if(c1=='2'){
        p0=0xf8;
      }
      else if( c1=='3'){
        p0=0xf0;
      }
      else if(  c1 =='4'){
        p0=0xe0;
      }
      else if(c1=='5'){
        p0=0xc0;
      }
      else if( c1 =='6'){
        p0=0x80;
      }
      else if(c1 > '6'){
          p0=0x00;
      }




 }


/*************** counter functions ************/
  void count(){

    if(c0>'9'){
      c0='0';
      c1++;
      lcd_chr(1,13,c0);
      lcd_chr(1,12,c1);
      if(c1>'9'){
        c1='0';
        c2++;
        lcd_chr(1,12,c1);
        lcd_chr(1,11,c2);
        if(c2>'9'){
         c0=c1=c2='0';
         lcd_chr(1,13,c0);
         lcd_chr(1,12,c1);
         lcd_chr(1,11,c2);

        }

      }
    }
    else if(c0<'0'){
      c0='9';
      c1--;
      lcd_chr(1,13,c0);
      lcd_chr(1,12,c1);
      if(c1<'0'){
        c1='9';
        c2--;
        lcd_chr(1,12,c1);
        lcd_chr(1,11,c2);
        if(c2<'0'){
         c0=c1=c2='0';
         lcd_chr(1,13,c0);
         lcd_chr(1,12,c1);
         lcd_chr(1,11,c2);

        }

      }
    }
    lcd_chr(1,13,c0);
    checkLights() ;

}

/*
void display_int()
  {
    digit[0]= (number/100)%10+48;
    digit[1]= (number/10)%10+48;
    digit[2]= number%10+48;
    lcd_out(1,10,digit);
  }

/***********interrupt functions **************/
void cct_init(void){
      p2_6_bit=0;
      p2_7_bit=0;
     p3=0x0c;
     }
void InitINT0(){
     IT0_bit = 1;   // Configure interrupt 0 for falling edge on /INT0 (P3.2)
     IT1_bit = 1;
     EX1_bit = 1;
    EX0_bit = 1;   // Enable EX0 Interrupt

    EA_bit = 1;    // Enable Global Interrupt Flag
 }

 void interrupt1() iv IVT_ADDR_EX1 ilevel 3 ics ICS_AUTO
 {

      p2_6_bit = 0xbf & (~p2);

      if1=1;
      if(if2==1){          //entry
          c0++;
          if1=0;
          if2=0;
      }
      delay_ms(5);



 }
 void interrupt() iv IVT_ADDR_EX0 ilevel 1 ics ICS_AUTO
 {
     p2_7_bit = 0x7f & (~p2);

       if2=1;
      if(if1==1){              //exit
          c0--;
          if1=0;
          if2=0;
      }
      delay_ms(5);

 }


 /*****************interrupt function end *************/