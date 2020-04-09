#ifndef SEIRMODEL_H
#define SEIRMODEL_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <QVector>
using namespace std;
class SEIRModel
{
    public:
        SEIRModel();

        void Execute()
        {
            ofstream salida("valores.txt",ios::app);
            salida << setprecision(2) <<setw(11)<< t << setw(11) << I << setw(11) << R << setw(11) << E <<setw(11) << S <<endl;
                resultados[0].append(t);
                resultados[1].append(I);
                resultados[2].append(R);
                resultados[3].append(E);
                resultados[4].append(S);

            do
             {
                 K1=f1(S,E,I,R,beta,mu,nu);
                 L1=f2(S,E,I,R,beta,sigma,mu);
                 M1=f3(S,E,I,R,gamma,sigma,mu);
                 N1=f4(S,E,I,R,gamma,mu,nu);

                 K2=f1(S+h*K1/2,E+h*L1/2,I+h*M1/2,R+h*N1/2,beta,mu,nu);
                 L2=f2(S+h*K1/2,E+h*L1/2,I+h*M1/2,R+h*N1/2,beta,sigma,mu);
                 M2=f3(S+h*K1/2,E+h*L1/2,I+h*M1/2,R+h*N1/2,gamma,sigma,mu);
                 N2=f4(S+h*K1/2,E+h*L1/2,I+h*M1/2,R+h*N1/2,gamma,mu,nu);

                 K3=f1(S+h*K2/2,E+h*L2/2,I+h*M2/2,R+h*N2/2,beta,mu,nu);
                 L3=f2(S+h*K2/2,E+h*L2/2,I+h*M2/2,R+h*N2/2,beta,sigma,mu);
                 M3=f3(S+h*K2/2,E+h*L2/2,I+h*M2/2,R+h*N2/2,gamma,sigma,mu);
                 N3=f4(S+h*K2/2,E+h*L2/2,I+h*M2/2,R+h*N2/2,gamma,mu,nu);

                 K4=f1(S+h*K3,E+h*L3,I+h*M3,R+h*N3,beta,mu,nu);
                 L4=f2(S+h*K3,E+h*L3,I+h*M3,R+h*N3,beta,sigma,mu);
                 M4=f3(S+h*K3,E+h*L3,I+h*M3,R+h*N3,gamma,sigma,mu);
                 N4=f4(S+h*K2,E+h*L3,I+h*M3,R+h*N3,gamma,mu,nu);

                 S=S+h*(K1+2*K2+2*K3+K4)/6;
                 E=E+h*(L1+2*L2+2*L3+L4)/6;
                 I=I+h*(M1+2*M2+2*M3+M4)/6;
                 R=R+h*(N1+2*N2+2*N3+N4)/6;

                 t+=h;
                 salida << setprecision(2) <<setw(11)<< t << setw(11) << I << setw(11) << R << setw(11) << E <<setw(11) << S <<endl;
                    resultados[0].append(t);
                    resultados[1].append(I);
                    resultados[2].append(R);
                    resultados[3].append(E);
                    resultados[4].append(S);

            }
             while (t<tmax-0.01);
        }
        // variables: S=susceptible, E=exposed, I=infected, R=recovered
        double f1(double S,double E, double I,double R,const double Beta,const double Mu,const double Nu)
        {
            double N=S+E+I+R;
            return Mu*(N-S)-Beta*S*I/N-Nu*S;
        }
        double f2(double S,double E, double I,double R,const double Beta,const double Sigma,const double Mu)
        {
            double N=S+E+I+R;
            return Beta*S*I/N-(Mu+Sigma)*E;
        }
        double f3(double S,double E, double I,double R,const double Gamma,const double Sigma,const double Mu)
        {
            return Sigma*E-(Mu+Gamma)*I;
        }
        double f4(double S,double E, double I,double R,const double Gamma,const double Mu,const double Nu){
            return Gamma*I-Mu*R+Nu*S;
        }
        void InitParametersByVectorDouble(vector<double> valuesDouble){
            beta=valuesDouble[0];
            gamma=valuesDouble[1];
            sigma=valuesDouble[2];
            mu=valuesDouble[3];
            nu=valuesDouble[4];
        }
        void InitParametersByVectorInt(vector<int> valuesInt,bool convert=true){
            if(convert){
                S=static_cast<double>(valuesInt[0]);
                E=static_cast<double>(valuesInt[1]);
                I=static_cast<double>(valuesInt[2]);
                R=static_cast<double>(valuesInt[3]);
                tmax=static_cast<double>(valuesInt[4]);
            }
            else
            {
                S=valuesInt[0];
                E=valuesInt[1];
                I=valuesInt[2];
                R=valuesInt[3];
                tmax=valuesInt[4];
            }
        }
        map<int,QVector<double> > getResultados(){return  resultados;}
    private:
        //const parameters
        double beta=.9, gamma=.2, sigma=.5, mu=0, nu=0;
        // variables: S=susceptible, E=exposed, I=infected, R=recovered
        //Initial value of the variables
        double S=1000, E=200, I=2, R=0;
        // maximum time (days)
        double tmax=10;

        double h=0.01; // step size
        double K1, K2, K3, K4, L1, L2, L3, L4, M1, M2, M3, M4, N1, N2, N3, N4;
        double t=0;
        int totalVariables=5;
        map<int,QVector<double> > resultados;
};

#endif // SEIRMODEL_H
