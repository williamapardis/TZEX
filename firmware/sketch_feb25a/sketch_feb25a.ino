
#define STEP 4
#define SWITCH 7
#define DELAY 4

bool Notched=false;
bool OUT=false;


void setup() {

  //initilize control GPIOs
  pinMode(STEP, OUTPUT);
  pinMode(SWITCH, INPUT);

  //debug
  Serial.begin(9600);
  while(!Serial){
    delay(3000);
    break;
  }
  delay(5000);
  Serial.println("begin, steping");

  delay(100);


  Notched=false;
  nextNotch();
  Notched = true;
  //moveSteps(2000);
  //nextNotch();  
  
}

void loop() {
  Serial.print(OUT);Serial.print(',');Serial.print(Notched);Serial.print(" ");
  Serial.println("waiting");
  Serial.println(digitalRead(SWITCH));
  delay(5000);
         
}

void nextNotch(){

  double stepsTaken = 0;
  
  //step microswitch out of notch
  if(digitalRead(SWITCH)==0){
    while(digitalRead(SWITCH)==0){
      digitalWrite(STEP, !digitalRead(STEP));   // change step pin state
      delay(DELAY);     
      stepsTaken += 0.5;
    }
  }
  else{
    moveSteps(400);
  }
  OUT=true;
  Serial.println("out of notch");
  //move to next notch
  Serial.println(stepsTaken);
  while(digitalRead(SWITCH)==1){
    digitalWrite(STEP, !digitalRead(STEP));   // change step pin state
    delay(DELAY);     
    stepsTaken += 0.5;
  }
  
  Serial.println(stepsTaken);
  Serial.println("in position");
  stepsTaken = 0;
  
}
  

void moveSteps(int n){
  Serial.print("moving ");Serial.print(n);Serial.println(" steps");
  for(int i=0;i<n;i++){
    digitalWrite(STEP, !digitalRead(STEP));   // change step pin state
    delay(DELAY);   
    //Serial.print(i);Serial.print(',');
  }
  Serial.println();
  Serial.println("complete");
}
