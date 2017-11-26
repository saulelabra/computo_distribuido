#include <stdio.h>
#include <omp.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <mpi.h>
using namespace std;
class Vector
{
public:
	int n; //para saber cuántos componentes tiene el vector
	vector<double> v;
	double magnitud=0;
	//char nom;
	Vector(int nums)
	{
        srand(time(NULL));
		this->n=nums;
		LlenarVector(time(NULL), 100);
		Consiguemagnitud();
        v.resize(n);
        cout<<"Vector de tamanio: "<<n<<endl;

	}
	Vector(){}
    void LlenarVector(unsigned int tiempoSemilla, int rango)
      {
        int i,j;
        unsigned int seed = time(NULL);

        #pragma omp parallel private(i, j)
        {


          #pragma omp for
          for(i=0; i<n; i++)
          {
  //           srand((time(NULL)));
              v.push_back(rand()%rango);
          }
        }
        cout << "Se lleno el vector" << endl;
      }

	void Consiguemagnitud()
	{
		cout<<"entré";
        magnitud=0;
		for(int x=0; x<n; x++)
		{
			magnitud += pow(v[x],2);
			//cout<<"la magnitud de"<<nom<<" Magnitud lleva" <<magnitud<<endl;
		}

		magnitud = sqrt(magnitud);

		//return magnitud;
	}
	double CalculaAngulo(Vector b)
	{
		Vector a;
		//a.nom='c';
		int llena=0;
		for(llena=0; v[llena]!=NULL && b.v[llena]!=NULL;llena++)
		{
			a.v.push_back(v[llena]*b.v[llena]);
		}
		a.n=llena-1;
		a.Consiguemagnitud();
        cout<<"pude con la magnitud" <<endl;
		double seno= 0;
		seno = (a.magnitud / (magnitud * b.magnitud));
        cout<<"pude con el seno. mi seno es de "<< seno<< "con a de "<<a.magnitud<< " magnitud de "<<magnitud<< " y magnitud de b de " <<b.magnitud<<endl;
		double angulo = asin(seno);
        angulo= angulo * 360 / (2*3.141592); //convierte de radianes a grados.
        cout<<"Mi angulo es de "<<angulo<<endl;

		return angulo;

	}
	double productoPunto(Vector b)
	{
		double angulo = CalculaAngulo(b);
		double producto= 0;
        angulo= angulo*2*3.141592/360;

		producto = magnitud * b.magnitud * cos(angulo);
	}
    void printVector()
      {
          for(int i=0; i<n; i++)
          {
            cout << v[i] << endl;
          }
          cout << endl;
      }

      Vector suma(Vector B)
      {
          if (n == B.n) {
              int i, j;
               Vector C(n);
              #pragma omp parallel shared(B, C)
              {
                #pragma omp for private(i, j)
                for(i=0; i<n; i++)
                {
                    C.v[i] += v[i] + B.v[i];
                }
              }
              return C;
          }else{
              cout<<"Debe de ser igual el tamanio de los vectores"<<endl;
              return *this;
          }

      }
};

int main()
{
	//vector<int> a;
	Vector A(3);
	//A.nom='A';
//	cout<<A.magnitud;
	Vector B(5);
	//B.nom='B';
//	cout<<endl<<B.magnitud;
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	double prueba=A.CalculaAngulo(B);
	cout<<endl<<prueba;
	cout<<"Mi producto punto es de " <<A.productoPunto(B)<<endl;
	MPI_Finalize();
	return 0;
}
