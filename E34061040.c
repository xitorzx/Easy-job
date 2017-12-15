#include <stdio.h>
#include <math.h>

#define DATA "DATA.txt"
#define num_data 90 //number of data from Data.txt
#define row 3
#define col 3
#define max 3
double c_x[max]; //coefficient of X
double c_y[max]; //coefficient of Y
double c_z[max]; //coefficient of Z
double c_d[max]; //coefficient of d


double one_time (double *tmp1, double *tmp2) //sigma X
{
    double sum=0;
    int i=0;
    for(i=0;i<num_data;i++)
        sum += tmp1[i]+sum;        
    return sum;
}
double two_times(double *tmp1, double *tmp2) //sigma X^2
{
    double sum=0;
    int i=0;
    for(i=0;i<num_data;i++)
        sum += pow(tmp1[i],2.0) + sum;
    return sum;
}
double three_times(double* tmp1,double* tmp2) //sigma X^3
{
    double sum=0;
    int i=0;
        for(i=0;i<num_data;i++)
            sum += pow(tmp1[i],3.0) + sum;
    return sum;
}
double four_times(double *tmp1, double* tmp2) //sigma X^4
{
    double sum=0;
    int i=0;
        for(i=0;i<num_data;i++)
            sum += pow(tmp1[i],4.0);
    return sum;
}
double sum_y(double *tmp1, double* tmp2) //sum of y
{
    double sum=0;
    int i=0;
    for(i=0;i<num_data;i++)
        sum += tmp2[i]+sum;
    return sum;
}
double xy(double *tmp1, double* tmp2) //sum of xy
{
    double sum=0;
    int i=0;
    for(i=0;i<num_data;i++)
        sum += tmp1[i]*tmp2[i]+sum;
    return sum;
}
double x2y(double *tmp1, double* tmp2) //sum of x^2y
{
    double sum=0;
    int i=0;
    for(i=0;i<num_data;i++)
        sum += pow(tmp1[i],2.0)*tmp2[i]+sum;
    return sum;
}
void coefficient(double* tmp1,double* tmp2)
{
        c_x[0]=num_data;
        c_x[1]=one_time(tmp1,tmp2);
        c_x[2]=two_times(tmp1,tmp2);
    
        c_y[0]=one_time(tmp1,tmp2);
        c_y[1]=two_times(tmp1,tmp2);
        c_y[2]=three_times(tmp1,tmp2);
    
        c_z[0]=two_times(tmp1,tmp2);
        c_z[1]=three_times(tmp1,tmp2);
        c_z[2]=four_times(tmp1,tmp2);
    
        c_d[0]=sum_y(tmp1,tmp2);
        c_d[1]=xy(tmp1,tmp2);
        c_d[2]=x2y(tmp1,tmp2);
}
double value3x3(double a0, double a1, double a2, double b0, double b1, double b2, double c0,double c1, double c2)
{
        double sum=0;
            sum= a0*(b1*c2-b2*c1)-b0*(a1*c2-a2*c1)+c0*(a1*b2-a2*b1);
        return sum;
}
int main()
{
    FILE * fp;
    fp=fopen(DATA,"r");
    double tmp1[num_data],tmp2[num_data];
    
    for(int i=0;i<num_data;i++)
    {
        fscanf(fp,"%lf %lf\n",&tmp1[i],&tmp2[i]);
    }
    
    coefficient(tmp1,tmp2);
//    
    double a0,a1,a2,delta;
    delta = value3x3(c_x[0],c_x[1],c_x[2],c_y[0],c_y[1],c_y[2],c_z[0],c_z[1],c_z[2]);
    
    a0 = value3x3(c_d[0],c_d[1],c_d[2],c_y[0],c_y[1],c_y[2],c_z[0],c_z[1],c_z[2])/delta;
    a1 = value3x3(c_x[0],c_x[1],c_x[2],c_d[0],c_d[1],c_d[2],c_z[0],c_z[1],c_z[2])/delta;
    a2 = value3x3(c_x[0],c_x[1],c_x[2],c_y[0],c_y[1],c_y[2],c_d[0],c_d[1],c_d[2])/delta;
    
    printf(" a0: %f \n a1: %f \n a2: %f \n",a0,a1,a2);
    
    fclose(fp);
    getchar();
}