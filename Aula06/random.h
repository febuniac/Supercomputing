double drandom();
void seed(double low_in, double hi_in);
 
 class Randz {
   public:
    Randz(long MULTIPLIER, long ADDEND, long PMOD);
    ~Randz();
   private:
    long MULTIPLIER ;
    long ADDEND ;
    long PMOD ;
    long random_last;
    double random_low, random_hi;

      // Member functions declaration
      double drandom();
      void seed( double low_in,double hi_in );

};
 