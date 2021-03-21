#ifndef CreatePPM_H
#define CreatePPM_H

#include <cstdio>

template<typename SeqIt>
void createPPM(SeqIt field_begin, int n, const char* filename)
{
   FILE *f = fopen(filename,"w");

   fprintf(f,"P3\n%i %i\n255\n",n,n);
   double tmax = 25.0;
   double tmin = -tmax;
   double r,g,b;
   for (int j = 0; j < n; ++j)
   {
      for (int i = 0; i < n; ++i)
      {
        auto val = *(field_begin + j*n + i);
        r = 0;
        g = 0;
        b = 0;
        if (val <= tmin)
        {
           b = 1.0*255.0;
        }
        else if(val >= -25.0 && val < -5)
        {
           b = 255*1.0;
           g = 255*((val+25)/20);
        }
        else if(val >= -5 && val <= 0.0)
        {
           g = 255*1.0;
           b = 255*(1.0-(val+5)/5);
        }
        else if(val > 0.0 && val <= 5)
        {
           g = 255*1.0;
           r = 255*((val)/5);
        }
        else if(val > 5 && val < 25.0)
        {
            r = 255*1.0;
            g = 255*((25-val)/20);
        }
        else
        {
            r = 255*1.0;
        }
        fprintf(f,"%i\n%i\n%i\n",(int)r,(int)g,(int)b);
      }
   }
   fclose(f);
}

#endif /* end of include guard: CreatePPM_H */
