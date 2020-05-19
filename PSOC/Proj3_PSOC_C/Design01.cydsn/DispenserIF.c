/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "DispenserIF.h"
#include "project.h"


//private functions:
static int rotatePlatform(DispenserIF *this,enum PilleType type);
static void pushPill(DispenserIF *this);
static void calibratePlatform(DispenserIF *this);
static void rotateTo(DispenserIF *this, PLATPOS position);
static int detekterPillebeholdning(DispenserIF *this);
static int vejefunktion(DispenserIF *this);

//new type to store current state.
typedef enum
{
    HALF1,
    HALF2,
    HALF3,
    HALF4,
    HALF5,
    HALF6,
    HALF7,
    HALF8
    
}HALF_STATE;
static HALF_STATE halfState=HALF1;
typedef enum
{
    FULL1,
    FULL2,
    FULL3,
    FULL4
    
}FULL_STATE;
static FULL_STATE fullState=FULL1;

//Help functions:
//roterer i trin i retning
static void rotateRight(int i);
static void rotateLeft(int i);
//roterer i tin i retning direction
static void rotate(int i, enum DIRECTION direction);
//roterer 1 trin i retning direction
static void half(enum DIRECTION direction);
static void full(enum DIRECTION direction);



void DispenserIF_Init(DispenserIF *this, Tester* testPtr)
{
   
    //opsæt og kalibrer stepper-motorer.
     this->platpos=UNKNOWN;
    this->testPtr=testPtr;
    calibratePlatform(this);
    
    
}

//returnerer 0 ved succesful dispensering, returnerer 1 ved vejefejl
//returnerer -1 ved tom beholder
int dispense(DispenserIF *this,enum PilleType type)
{
    //roter platformen
    rotatePlatform(this,type);
    
    //detekter pillebeholdning
    //hvis pillebeholdning OK
    //{
    //stempel-funktion (skub en pille ud)
    //Hvis sensor er high = der er piller.
    if(detekterPillebeholdning(this))
    {
        pushPill(this);
    }
    else
    {
        writeTester(this->testPtr,"Pill conatiner empty\r\n");
        return -1;
    }
    
    
    //vejefunktion
    //returner succes eller fejlmelding
    
    if(vejefunktion(this)==0)
    {
        writeTester(this->testPtr,"Pill was dispensed\r\n");
        return 0;
    }   
    //ellers: fejlhåndtering
    else
    {
        writeTester(this->testPtr,"Pill was not dispensed\r\n");
        //fejlhåndtering manlger
        return 1;
    }
    
}
static int rotatePlatform(DispenserIF *this,enum PilleType type)
{
    //roter platform i korrekt position baseret på pilletyppe
    switch(type)
    {
        case A:
            writeTester(this->testPtr,"Rotating platform to A\r\n");
            rotateTo(this,FIRST);
        break;
        case B:
            writeTester(this->testPtr,"Rotating platform to B\r\n");
            rotateTo(this,SECOND);
        break;
        case C:
            writeTester(this->testPtr,"Rotating platform to C\r\n");
            rotateTo(this,THIRD);
        break;
        default:
        break;
    }
    //evt. fejlcheck og fejlbesked som returværdi
    return 0;
    
}

static void pushPill(DispenserIF *this)
{
    writeTester(this->testPtr,"Pushing pill\r\n");
    //1,8 grader pr. step *100 = 180 grader
    for(int i=0;i<100;i++)
    {
        full(LEFT);
    }
    //tilbage igen
     for(int i=0;i<180;i++)
    {
        full(RIGHT);
    }
    //få stempel til at køre frem og tilbage igen
}
void full(enum DIRECTION direction)
{
    // denne switch case koeres hvis programmet er i full mode
    switch(fullState)
    {
        case FULL1:
        {
            Pin_C1_Write(1);
            Pin_C2_Write(1);
            Pin_D1_Write(0);
            Pin_D2_Write(0);
           if(direction==RIGHT)     // der tjekkes i hver state hvilken retning motoren skal koere
            {
                fullState=FULL2;
            }
            else
            {
                fullState=FULL4;
            }
        }
        break;
        case FULL2:
        {
            Pin_C1_Write(0);
            Pin_C2_Write(1);
            Pin_D1_Write(1);
            Pin_D2_Write(0);
            if(direction==RIGHT)
            {
                fullState=FULL3;
            }
            else
            {
                fullState=FULL1;
            }
        }
        break;
        case FULL3:
        {
            Pin_C1_Write(0);
            Pin_C2_Write(0);
            Pin_D1_Write(1);
            Pin_D2_Write(1);
            if(direction==RIGHT)
            {
                fullState=FULL4;
            }
            else
            {
                fullState=FULL2;
            }
        }
        break;
        case FULL4:
        {
            Pin_C1_Write(1);
            Pin_C2_Write(0);
            Pin_D1_Write(0);
            Pin_D2_Write(1);
            if(direction==RIGHT)
            {
                fullState=FULL1;
            }
            else
            {
                fullState=FULL3;
            }
        }
        break;
        default:
        break;
    }
}
//returnerer 0 ved dispenseret pille, og 1 ved fejl
static int vejefunktion(DispenserIF *this)
{
    float tmpweight = GenADCInput(this->testPtr);
    if (this->weight+0.5> tmpweight)//med fejlmargin
    {
        // pille vægten er uændret, hysterese...
        this->weight=tmpweight;
        return 1;
    }else
    {
        // pille er dispenseret
        this->weight=tmpweight;
        return 0;
    }
    // opdateret this->weight
    //thist->weight=tmpweight;
    //return status
    
}

static int detekterPillebeholdning(DispenserIF* this)
{
    //Check refleksbrikdetektor
    //returner 1 hvis der er piller, returner 0 hvis der ikke er
    GenConSensorInput(this->testPtr);
    return Pill_Container_Sensor_Read();
}


//Taget fra GFV øvelse
static void half(enum DIRECTION direction)
{
    // denne switch case koeres hvis programmet er i half mode
    switch(halfState)
    {
    case HALF1:
    {
            Pin_A1_Write(1);
            Pin_A2_Write(0);
            Pin_B1_Write(0);
            Pin_B2_Write(0);
            if(direction==RIGHT)     // der tjekkes i hver state hvilken retning motoren skal koere
            {
                halfState=HALF2;
            }
            else
            {
                halfState=HALF8;
            }
                     
    }
    break;
    case HALF2:
    {
            Pin_A1_Write(1);
            Pin_A2_Write(1);
            Pin_B1_Write(0);
            Pin_B2_Write(0);
            if(direction==RIGHT)
            {
                halfState=HALF3;
            }
            else
            {
                halfState=HALF1;
            }           
    }
    break;
    case HALF3:
    {
            Pin_A1_Write(0);
            Pin_A2_Write(1);
            Pin_B1_Write(0);
            Pin_B2_Write(0);
            if(direction==RIGHT)
            {
                halfState=HALF4;
            }
            else
            {
                halfState=HALF2;
            }            
    }
    break;
    case HALF4:
    {
            Pin_A1_Write(0);
            Pin_A2_Write(1);
            Pin_B1_Write(1);
            Pin_B2_Write(0);
            if(direction==RIGHT)
            {
                halfState=HALF5;
            }
            else
            {
                halfState=HALF3;
            }            
    }
    break;
    case HALF5:
    {
            Pin_A1_Write(0);
            Pin_A2_Write(0);
            Pin_B1_Write(1);
            Pin_B2_Write(0);
            if(direction==RIGHT)
            {
                halfState=HALF6;
            }
            else
            {
                halfState=HALF4;
            }            
    }
    break;
    case HALF6:
    {
            Pin_A1_Write(0);
            Pin_A2_Write(0);
            Pin_B1_Write(1);
            Pin_B2_Write(1);
            if(direction==RIGHT)
            {
                halfState=HALF7;
            }
            else
            {
                halfState=HALF5;
            }           
    }
    break;
    case HALF7:
    {
            Pin_A1_Write(0);
            Pin_A2_Write(0);
            Pin_B1_Write(0);
            Pin_B2_Write(1);
            if(direction==RIGHT)
            {
                halfState=HALF8;
            }
            else
            {
                halfState=HALF6;
            }            
    }
    break;
    case HALF8:
    {
            Pin_A1_Write(1);
            Pin_A2_Write(0);
            Pin_B1_Write(0);
            Pin_B2_Write(1);
            if(direction==RIGHT)
            {
                halfState=HALF1;
            }
            else
            {
                halfState=HALF7;
            }            
    }
    break;
    default:
    break;
    }
}
static void rotate(int i, enum DIRECTION direction)
{
    //iterer i gange gennem for lykke.
    for(int j=0;j<i;++j)
    {
    //roter 1 trin i angiven retning.
    half(direction);
    //delay mellem steps: 2 milisekunder
    CyDelay(2);
    }
}
static void rotateRight(int i)
{
    rotate(i,RIGHT);
}
static void rotateLeft(int i)
{
    rotate(i,LEFT);
}

static void calibratePlatform(DispenserIF *this)
{
    //Iterer indtil Motor_Calibration_Sensor==1
    while(Motor_Calibration_Sensor_Read()!=1)
    {
        //et trin af gangen, så refleksbrikken ikke bliver misset. Delay mellem steps er indbygget i funktion
        rotateRight(1);
        GenPlatSensorInput(this->testPtr);
    }
    this->platpos=FIRST;
}
static void rotateTo(DispenserIF *this, PLATPOS position)
{
    switch(position)
    {
        case FIRST:
            switch(this->platpos)
            {
                case FIRST:
                break;
                case SECOND:
                //45 deg. right:
                //45/0.9=50
                rotateRight(50);
                break;
                case THIRD:
                //90 deg. right:
                //90/0.9=100
                rotateRight(100);
                break;
                default:
                break;
            }
        break;
        case SECOND:
            switch(this->platpos)
            {
                case FIRST:
                //45 deg. left:
                //45/0.9=50
                rotateLeft(50);
                break;
                case SECOND:
                break;
                case THIRD:
                //45 deg. right:
                //45/0.9=50
                rotateRight(50);
                break;
                default:
                break;
            }
        break;
        case THIRD:
            switch(this->platpos)
            {
                case FIRST:
                //90 deg. left:
                //90/0.9=100
                rotateLeft(100);
                break;
                case SECOND:
                //45 deg. left:
                //45/0.9=40
                rotateLeft(50);
                break;
                case THIRD:
                break;
                default:
                break;
            }
        break;
        default:
        break;
    }
}