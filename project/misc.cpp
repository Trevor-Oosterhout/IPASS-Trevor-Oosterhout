#include "misc.hpp"

/// @file


/// \brief
/// exponent arithmetic function
/// \details
/// calculate (signed) integer to the power of an unsigned integer
int exponent(int base, unsigned int power){
  if(power > 0){
    for(unsigned int i = 0; i < power; i++){
      base = base * base;
    }
    return base;
  }
  else{
    return 1;
  }

}
