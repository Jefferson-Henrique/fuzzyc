struct FInOutput {
       int universeFrom;
       int universeTo;
       int keys[];
       float values[][];
};

struct FRule {
       int inputTerms[];
       int outputTerms[];
};

struct FProcessor {
       int discretizationPoints;
       
       FInOutput inputs[];
       FInOutput outputs[];
       
       FRule rules[];
};

int fuzzycGetMultidimensionalLength(float t[]) {
    return ArrayLen(t);
}

float fuzzycFunctionGetMembershipValue(FInOutput &variable, int term, float valueX) {
      int index, length;
      int termsLength = ArrayLen(variable.keys);
      
      int termIndex = 0;
      for (index = 0, length = termsLength; index < termsLength; index++) {
          if (term == variable.keys[index]) {
             termIndex = index;
             break;
          }
      }
      
      length = fuzzycGetMultidimensionalLength(variable.values[termIndex]);
      
      for (index = 0; index < length-2; index += 2) {
          float currentValueX = variable.values[termIndex][index];
          float currentValueY = variable.values[termIndex][index+1];
          float nextValueX = variable.values[termIndex][index+2];
          float nextValueY = variable.values[termIndex][index+3];
          
          if (valueX >= currentValueX && valueX <= nextValueX) {
             float diffX = nextValueX - currentValueX;
             float diffY = nextValueY - currentValueY;
             
             float ratio = diffY / diffX;
             
             return currentValueY + (valueX - currentValueX) * ratio;
          }
      }
      
      if (length == 2 && valueX == variable.values[termIndex][0]) {
         return variable.values[termIndex][1];
      }
      
      return 0;
}
