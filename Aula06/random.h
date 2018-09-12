
 class Randz {
   public:
    Randz(long MULTIPLIER, long ADDEND, long PMOD);
    // Member functions declaration
    double drandom();
    void seed( double low_in,double hi_in );
   
   private:
    long MULTIPLIER ;
    long ADDEND ;
    long PMOD ;
    long random_last;
    double random_low, random_hi;

    

};
 